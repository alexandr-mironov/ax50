
/*
 * Lantiq I2C bus adapter
 *
 * Parts based on i2c-designware.c and other i2c drivers from Linux 2.6.33
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Copyright (C) 2012 Thomas Langer <thomas.langer@lantiq.com>
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/slab.h> /* for kzalloc, kfree */
#include <linux/i2c.h>
#include <linux/errno.h>
#include <linux/completion.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/of_irq.h>
#include <linux/of_i2c.h>
#include <linux/pinctrl/consumer.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/cpufreq.h>
#include <cpufreq/ltq_cpufreq.h>
#include <lantiq_soc.h>
#include <linux/wait.h>
#include "i2c-lantiq.h"



#define LTQ_I2C_FIFO_LIMIT 8

#ifdef CONFIG_LTQ_CPUFREQ
#define LTQ_I2C_SUPPORT_COC 1
#endif

#define LTQ_I2C_KERNEL_CLOCK (10*1000*1000)


/* #define DEBUG */

/* access macros */
#define i2c_r32(reg)	\
	__raw_readl(&(priv->membase)->reg)
#define i2c_w32(val, reg)	\
	__raw_writel(val, &(priv->membase)->reg)
#define i2c_w32_mask(clear, set, reg)	\
	i2c_w32((i2c_r32(reg) & ~(clear)) | (set), reg)

#define DRV_NAME "i2c-lantiq"
#define DRV_VERSION "1.01"

#define LTQ_I2C_BUSY_TIMEOUT		20 /* ms */

#define LTQ_I2C_RX_FIFO_TIMEOUT		HZ

#ifdef DEBUG
#define LTQ_I2C_XFER_TIMEOUT		(25*HZ)
#else
#define LTQ_I2C_XFER_TIMEOUT		(2*LTQ_I2C_RX_FIFO_TIMEOUT)
#endif


#define LTQ_I2C_IMSC_DEFAULT_MASK	(I2C_IMSC_I2C_P_INT_EN | \
					 I2C_IMSC_I2C_ERR_INT_EN)

#define LTQ_I2C_ARB_LOST		(1 << 0)
#define LTQ_I2C_NACK			(1 << 1)
#define LTQ_I2C_RX_UFL			(1 << 2)
#define LTQ_I2C_RX_OFL			(1 << 3)
#define LTQ_I2C_TX_UFL			(1 << 4)
#define LTQ_I2C_TX_OFL			(1 << 5)

#ifdef LTQ_I2C_SUPPORT_COC
#define LTQ_I2CCOCDRV_BUSY	1
#define LTQ_I2CCOCDRV_IDLE	0

/* this ID represent the I2C interface No. (0, 1, 2, 3, ...) */
#define LTQ_I2C_ID		0

#define LTQ_I2C_NORMAL_CPU_FREQUENCY 600000
#endif

struct ltq_i2c {
	struct mutex mutex;


	/* active clock settings */
	unsigned int input_clock;	/* clock input for i2c hardware block */
	unsigned int i2c_clock;		/* approximated bus clock in kHz */

	struct clk *clk_gate;
	struct clk *clk_input;


	/* resources (memory and interrupts) */
	int irq_lb;				/* last burst irq */

	struct lantiq_reg_i2c __iomem *membase;	/* base of mapped registers */

	struct i2c_adapter adap;
	struct device *dev;

	struct completion cmd_complete;


	/* message transfer data */
	struct i2c_msg *current_msg;	/* current message */
	int msgs_num;		/* number of messages to handle */
	u8 *msg_buf;		/* current buffer */
	u32 msg_buf_len;	/* remaining length of current buffer */
	int msg_err;		/* error status of the current transfer */

	u32 prev_rps_stat;
	wait_queue_head_t rx_wait_queue;
	wait_queue_head_t rx_thread_wait_queue;
	u8 rx_thread_force_stop;
	struct mutex rx_lock;
	enum {
		RX_THREAD_STOP = 0,
		RX_THREAD_RUNNING
	} rx_thread_status; /* last burst indicator */
	enum {
		BURST = 0,
		LAST_BURST
	} last_burst; /* last burst indicator */
#ifdef LTQ_I2C_SUPPORT_COC
	enum ltq_cpufreq_state i2c_cocdrv_ps;
	int ltq_i2c_cpu_frequency;
	int ltq_i2c_clock_change;
	int i2c_cocdrv_busy;
#endif
	/* master status codes */
	enum {
		STATUS_IDLE,
		STATUS_ADDR,	/* address phase */
		STATUS_WRITE,
		STATUS_READ,
		STATUS_READ_END,
		STATUS_STOP
	} status;
};

#ifdef LTQ_I2C_SUPPORT_COC
#define LTQ_I2CCOCDRV_BUSY	1
#define LTQ_I2CCOCDRV_IDLE	0

/* this ID represent the I2C interface No. (0, 1, 2, 3, ...) */
#define LTQ_I2C_ID		0

#define LTQ_I2C_COC_BUSY	1
#define LTQ_I2C_COC_IDLE	0

struct ltq_i2c *i2c_priv;


static int ltq_i2c_cocdrv_stateget(enum ltq_cpufreq_state *state)
{
	/* dev_info(i2c_priv->dev, "%s is called\n", __func__); */
	*state = i2c_priv->i2c_cocdrv_ps;
	return LTQ_CPUFREQ_RETURN_SUCCESS;
}

static int ltq_i2c_cocdrv_fss_ena(int ena)
{
	/* pr_info("%s is called\n", __func__); */
	if (ena)
		pr_debug("enable frequency scaling\n");
	else
		pr_debug("disable frequency scaling\n");

	return LTQ_CPUFREQ_RETURN_SUCCESS;
}


static int ltq_i2c_cocdrv_prechange(enum ltq_cpufreq_module module,
			enum ltq_cpufreq_state new_state,
			enum ltq_cpufreq_state old_state)
{
	/* pr_info("%s is called new_state[%d]\n",__func__, new_state); */
	return LTQ_CPUFREQ_RETURN_SUCCESS;
}

static int ltq_i2c_cocdrv_statechange(enum ltq_cpufreq_state new_state)
{
	/* pr_info("%s is called new_state[%d]\n",__func__, new_state); */
	return LTQ_CPUFREQ_RETURN_SUCCESS;
}

static int ltq_i2c_cocdrv_postchange(enum ltq_cpufreq_module module,
			enum ltq_cpufreq_state new_state,
			enum ltq_cpufreq_state old_state)
{
	unsigned long freq;
	/*
	dev_info(i2c_priv->dev, "%s is called\n", __func__);
	pr_info("%s is called\n", __func__); */
	freq = ltq_cpufreq_get_khz_from_ps(new_state);
	/* pr_info("ps = %d, freq = %d\n", new_state, freq); */
	if (freq == 0)
		return LTQ_CPUFREQ_RETURN_DENIED;
	if (freq != i2c_priv->ltq_i2c_cpu_frequency) {
		i2c_priv->ltq_i2c_cpu_frequency = freq;
		i2c_priv->ltq_i2c_clock_change = 1;
	}
	i2c_priv->i2c_cocdrv_ps = new_state;
	return LTQ_CPUFREQ_RETURN_SUCCESS;
}

/* keep track of frequency transitions */
static int i2c_cpufreq_notifier(
	struct notifier_block *nb,
	unsigned long val,
	void *data)
{
	struct cpufreq_freqs *freq = data;
	enum ltq_cpufreq_state new_state, old_state;
	int ret;
	/* dev_info(i2c_priv->dev, "%s is called\n", __func__); */

	new_state = ltq_cpufreq_get_ps_from_khz(freq->new);
	if (new_state == LTQ_CPUFREQ_PS_UNDEF)
		return NOTIFY_STOP_MASK | (LTQ_CPUFREQ_MODULE_I2C<<4);
	old_state = ltq_cpufreq_get_ps_from_khz(freq->old);
	if (old_state == LTQ_CPUFREQ_PS_UNDEF)
		return NOTIFY_STOP_MASK | (LTQ_CPUFREQ_MODULE_I2C<<4);
	if (val == CPUFREQ_PRECHANGE) {
		ret = ltq_i2c_cocdrv_prechange(LTQ_CPUFREQ_MODULE_I2C,
						new_state, old_state);
		if (ret < 0)
			return NOTIFY_STOP_MASK | (LTQ_CPUFREQ_MODULE_I2C<<4);
		ret = ltq_i2c_cocdrv_statechange(new_state);
		if (ret < 0)
			return NOTIFY_STOP_MASK | (LTQ_CPUFREQ_MODULE_I2C<<4);
	} else if (val == CPUFREQ_POSTCHANGE) {
		ret = ltq_i2c_cocdrv_postchange(LTQ_CPUFREQ_MODULE_I2C,
						new_state, old_state);
		if (ret < 0)
			return NOTIFY_STOP_MASK | (LTQ_CPUFREQ_MODULE_I2C<<4);
	} else {
		return NOTIFY_OK | (LTQ_CPUFREQ_MODULE_I2C<<4);
	}
	return NOTIFY_OK | (LTQ_CPUFREQ_MODULE_I2C<<4);
}


static struct notifier_block i2c_cpufreq_notifier_block = {
	.notifier_call = i2c_cpufreq_notifier
};

struct ltq_cpufreq_module_info i2c_cocdrv_feature_fss = {
.name                           = "I2C frequency scaling support",
.pmcuModule                     = LTQ_CPUFREQ_MODULE_I2C,
.pmcuModuleNr                   = LTQ_I2C_ID,
.powerFeatureStat               = 1,
.ltq_cpufreq_state_get          = ltq_i2c_cocdrv_stateget,
.ltq_cpufreq_pwr_feature_switch = ltq_i2c_cocdrv_fss_ena,
};

void ltq_i2c_coc_idle(struct ltq_i2c *priv)
{
	int ret = LTQ_CPUFREQ_RETURN_SUCCESS;
	ret = ltq_cpufreq_state_req(LTQ_CPUFREQ_MODULE_I2C,
			LTQ_I2C_ID,
			LTQ_CPUFREQ_PS_D0D3
			);
	if (ret != LTQ_CPUFREQ_RETURN_SUCCESS)
		dev_err(priv->dev, "Power state request D0D3 failed");
}

static int ltq_i2c_cpufreq_init(struct ltq_i2c *priv)
{
	struct ltq_cpufreq *i2c_cpufreq_p;
	priv->i2c_cocdrv_ps = LTQ_CPUFREQ_PS_D0;
	priv->ltq_i2c_clock_change = 0;
	priv->ltq_i2c_cpu_frequency = LTQ_I2C_NORMAL_CPU_FREQUENCY;
	i2c_cpufreq_p = ltq_cpufreq_get();
	if (i2c_cpufreq_p == NULL) {
		dev_err(priv->dev, "CPUFREQ registration failed.\n");
		return -1;
	}
	if (cpufreq_register_notifier(&i2c_cpufreq_notifier_block,
						CPUFREQ_TRANSITION_NOTIFIER)) {
		dev_err(priv->dev, "Fail in registering I2C to CPUFreq\n");
		return -1;
	}
	list_add_tail(&i2c_cocdrv_feature_fss.list,
			&i2c_cpufreq_p->list_head_module);

	dev_info(priv->dev, "Register I2CCOCDRV to CPUFREQ.\n");
	return LTQ_CPUFREQ_RETURN_SUCCESS;
}

static int ltq_i2c_cpufreq_exit(struct ltq_i2c *priv)
{
	/* set status of i2ccocdrv inside CPUFreq to don't care */
	ltq_i2c_coc_idle(priv);

	if (cpufreq_unregister_notifier(&i2c_cpufreq_notifier_block,
						CPUFREQ_TRANSITION_NOTIFIER)) {
		dev_err(priv->dev, "CPUFREQ unregistration failed.");
		return -1;
	}
	list_del(&i2c_cocdrv_feature_fss.list);
	return LTQ_CPUFREQ_RETURN_SUCCESS;
}

#endif /* LTQ_I2C_SUPPORT_COC */

static irqreturn_t ltq_i2c_isr(int irq, void *dev_id);

static inline void enable_burst_irq(struct ltq_i2c *priv)
{
	i2c_w32_mask(0,
	I2C_IMSC_LBREQ_INT_EN |
		I2C_IMSC_BREQ_INT_EN,
		imsc);
}
static inline void disable_burst_irq(struct ltq_i2c *priv)
{
	i2c_w32_mask(I2C_IMSC_LBREQ_INT_EN |
		I2C_IMSC_BREQ_INT_EN |
		I2C_IMSC_LSREQ_INT_EN |
		I2C_IMSC_SREQ_INT_EN,
		0,
		imsc);
}

static void prepare_msg_send_addr(struct ltq_i2c *priv)
{
	struct i2c_msg *msg = priv->current_msg;
	int rd = !!(msg->flags & I2C_M_RD);	/* extends to 0 or 1 */
	u16 addr = msg->addr;

	/* new i2c_msg */
	priv->msg_buf = msg->buf;
	priv->msg_buf_len = msg->len;
	pr_debug("ADDR: rd[%d]msg->flags[%d]\n", rd, msg->flags);
	if (rd)
		priv->status = STATUS_READ;
	else
		priv->status = STATUS_WRITE;

	/* send slave address */
	if (msg->flags & I2C_M_TEN) {
		i2c_w32(0xf0 | ((addr & 0x300) >> 7) | rd, txd);
		i2c_w32(addr & 0xff, txd);
	} else {
		i2c_w32((addr & 0x7f) << 1 | rd, txd);
	}
}

static void ltq_i2c_set_tx_len(struct ltq_i2c *priv)
{
	struct i2c_msg *msg = priv->current_msg;
	int len = (msg->flags & I2C_M_TEN) ? 2 : 1;

	pr_debug("set_tx_len %cX\n", (msg->flags & I2C_M_RD) ? 'R' : 'T');

	priv->status = STATUS_ADDR;

	if (!(msg->flags & I2C_M_RD)) {
		len += msg->len;
	} else {
		/* set maximum received packet size (before rx int!) */
		i2c_w32(msg->len, mrps_ctrl);
		priv->prev_rps_stat = 0;
	}
	i2c_w32(len, tps_ctrl);
	enable_burst_irq(priv);

}

static int ltq_i2c_hw_set_clock(struct i2c_adapter *adap)
{
	struct ltq_i2c *priv = i2c_get_adapdata(adap);
	unsigned int input_clock = clk_get_rate(priv->clk_input);
	u32 dec, inc = 1;
	u32 rmc = 0;

	/* clock changed? */
	if (priv->input_clock == input_clock
#ifdef LTQ_I2C_SUPPORT_COC
		&& i2c_priv->ltq_i2c_clock_change == 0
#endif
		)
		return 0;

	/* recalculate RMC value */

	rmc = input_clock / LTQ_I2C_KERNEL_CLOCK;

	i2c_w32(rmc << I2C_CLC_RMC_OFFSET, clc);
	/*
	 * this formula is only an approximation, found by the recommended
	 * values in the "I2C Architecture Specification 1.7.1"
	 */
	dec = LTQ_I2C_KERNEL_CLOCK / (priv->i2c_clock * 2);
#ifdef LTQ_I2C_SUPPORT_COC
	if (i2c_priv->ltq_i2c_clock_change) {
		/* base on the frequency, select the correct divider value
		* currently, for low frequency, divider will be 5
		*/
		i2c_priv->ltq_i2c_clock_change = 0;
		if (i2c_priv->ltq_i2c_cpu_frequency <
			LTQ_I2C_NORMAL_CPU_FREQUENCY)
			dec = dec * 10;
	}
#endif
	if (dec <= 6) {
		dev_info(priv->dev, "dec is too small [%d]", dec);
		return -ENXIO;
	}

	i2c_w32(0, fdiv_high_cfg);
	i2c_w32((inc << I2C_FDIV_CFG_INC_OFFSET) |
		(dec << I2C_FDIV_CFG_DEC_OFFSET),
		fdiv_cfg);

	/* dev_info(priv->dev, "in %d kHz, bus %d kHz,rmc =%d dec=%d %d\n",
		input_clock, priv->i2c_clock, rmc, dec, LTQ_I2C_KERNEL_CLOCK);*/

	priv->input_clock = input_clock;
	return 0;
}

static int ltq_i2c_hw_init(struct i2c_adapter *adap)
{
	int ret = 0;
	struct ltq_i2c *priv = i2c_get_adapdata(adap);

	/* disable bus */
	i2c_w32_mask(I2C_RUN_CTRL_RUN_EN, 0, run_ctrl);

	/* setup clock */
	ret = ltq_i2c_hw_set_clock(adap);
	if (ret != 0) {
		dev_warn(priv->dev, "invalid clock settings\n");
		return ret;
	}
	/* configure fifo */
	i2c_w32(I2C_FIFO_CFG_TXFC | /* tx fifo as flow controller */
		I2C_FIFO_CFG_RXFC | /* rx fifo as flow controller */
		I2C_FIFO_CFG_TXFA_TXFA2 | /* tx fifo 4-byte aligned */
		I2C_FIFO_CFG_RXFA_RXFA2 | /* rx fifo 4-byte aligned */
		I2C_FIFO_CFG_TXBS_TXBS0 | /* tx fifo burst size is 1 word */
		I2C_FIFO_CFG_RXBS_RXBS0,  /* rx fifo burst size is 1 word */
		fifo_cfg);


	/* configure address */
	if (priv->msgs_num == 1)
		i2c_w32(I2C_ADDR_CFG_SOPE_EN |/* generate stop
			when no more data in the fifo*/
			I2C_ADDR_CFG_SONA_EN |/* generate
				stop when NA received */
			I2C_ADDR_CFG_MnS_EN |/* we are master device */
			0,/* our slave address (not used!) */
		addr_cfg);
	else
		i2c_w32(
			I2C_ADDR_CFG_SONA_EN |/* generate
				stop when NA received */
			I2C_ADDR_CFG_MnS_EN |/* we are master device */
			0,/* our slave address (not used!) */
			addr_cfg);


	/* enable bus */
	i2c_w32_mask(0, I2C_RUN_CTRL_RUN_EN, run_ctrl);

	return 0;
}

static int ltq_i2c_wait_bus_not_busy(struct ltq_i2c *priv)
{
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(LTQ_I2C_BUSY_TIMEOUT);

	do {
		u32 stat = i2c_r32(bus_stat);

		if ((stat & I2C_BUS_STAT_BS_MASK) == I2C_BUS_STAT_BS_FREE)
			return 0;

		cond_resched();
	} while (!time_after_eq(jiffies, timeout));

	dev_err(priv->dev, "timeout waiting for bus ready\n");
	return -ETIMEDOUT;
}

/* send addr and tx in word (LSB first) */
static inline void ltq_i2c_addr_tx(struct ltq_i2c *priv)
{
	struct i2c_msg *msg = priv->current_msg;
	u16 addr = msg->addr;
	u32 word = 0;
	u32 tmp;
	const int bytes_per_word = 4;
	int i = 0;

	if (priv->status == STATUS_ADDR) {
		/* new i2c_msg */
		priv->msg_buf = msg->buf;
		priv->msg_buf_len = msg->len;
		pr_debug("ADDR: msg->flags[%d] addr 0x%x\n", msg->flags, addr);

		/* send slave address */
		if (msg->flags & I2C_M_TEN) {
			word = 0xf0 | ((addr & 0x300) >> 7);
			word |= ((addr & 0xff) << 8);
			i += 2;
		} else {
			word = (addr & 0x7f) << 1;
			i += 1;
		}
		priv->status = STATUS_WRITE;
	}

	for (; i < bytes_per_word; i++) {
		if (priv->msg_buf_len && priv->msg_buf) {
			tmp = ((u32) *priv->msg_buf) << (8 * i) ;
			word |= tmp;
			if (--priv->msg_buf_len)
				priv->msg_buf++;
			else
				priv->msg_buf = NULL;
		} else
			priv->last_burst = LAST_BURST;
	}

	/* write as word */
	i2c_w32(word, txd);

	if (priv->last_burst)
		disable_burst_irq(priv);
}

static inline int ltq_i2c_rx(struct ltq_i2c *priv)
{
	u32 loopcount;
	int ret = 0;
	if (priv->msg_buf_len && priv->msg_buf) {
		if (wait_event_interruptible_timeout(priv->rx_wait_queue,
			(i2c_r32(ffs_stat) != 0) ||
			(priv->rx_thread_force_stop == 1),
			LTQ_I2C_RX_FIFO_TIMEOUT) <= 0) {
				dev_err(priv->dev, "I2C: RX FIFO Timeout\n");
				priv->last_burst = LAST_BURST;
				goto err;
		}

		if (i2c_r32(ffs_stat) && priv->rx_thread_force_stop != 1) {
			loopcount = i2c_r32(rps_stat) - priv->prev_rps_stat;
			priv->prev_rps_stat += loopcount;
			if (loopcount > LTQ_I2C_FIFO_LIMIT)
				loopcount = LTQ_I2C_FIFO_LIMIT;
			if (loopcount > 0) {
				int i, j;
				u32 data;
				j = ((loopcount - 1) / 4) + 1;
				while (j > 0) {
					data = i2c_r32(rxd);
				for (i = 0;
					(i < 4) && (loopcount > 0);
					i++) {
					*priv->msg_buf =
						(data >> (8 * i)) & 0xff;
					loopcount--;
					if (--priv->msg_buf_len)
						priv->msg_buf++;
					else {
						priv->last_burst = LAST_BURST;
						priv->msg_buf = NULL;
						break;
					}
				}
				j--;
				if (!priv->msg_buf)
					break;
				}
			}
		} else {
			dev_err(priv->dev, "I2C: Force to stop\n");
			priv->last_burst = LAST_BURST;
			goto err;
		}
	} else {
		priv->last_burst = LAST_BURST;
	}
err:
	if (priv->last_burst) {
		ret = 1;
		disable_burst_irq(priv);
		if (priv->status == STATUS_READ_END) {
			/*
			 * do the STATUS_STOP and complete() here, as sometimes
			 * the tx_end is already seen before this is finished
			 */
			priv->status = STATUS_STOP;
			complete(&priv->cmd_complete);
		} else {
			priv->status = STATUS_READ_END;
			/* make sure that bus is not free
			before sending out SETEND */
			if ((i2c_r32(bus_stat) & I2C_BUS_STAT_BS_MASK)
				== I2C_BUS_STAT_BS_BM) {
				if (i2c_r32(bus_stat) !=
					I2C_BUS_STAT_RNW_READ)
					i2c_w32(I2C_ENDD_CTRL_SETEND,
						endd_ctrl);
			}
		}
	}
	return ret;
}

static void ltq_i2c_xfer_init(struct ltq_i2c *priv)
{
	/* enable interrupts */
	struct i2c_adapter *adap;
	adap = &priv->adap;
	ltq_i2c_hw_init(adap);
	i2c_w32(LTQ_I2C_IMSC_DEFAULT_MASK, imsc);
	/* trigger transfer of first msg */
#ifdef LTQ_I2C_SUPPORT_COC
	i2c_priv->i2c_cocdrv_busy = LTQ_I2CCOCDRV_BUSY;
#endif
	ltq_i2c_set_tx_len(priv);
}
static void dump_msgs(struct i2c_msg msgs[], int num, int rx)
{
#if defined(DEBUG)
	int i, j;
	pr_debug("Messages %d %s\n", num, rx ? "out" : "in");
	for (i = 0; i < num; i++) {
		pr_debug("%2d %cX Msg(%d) addr=0x%X: ", i,
			(msgs[i].flags & I2C_M_RD) ? 'R' : 'T',
			msgs[i].len, msgs[i].addr);
		if (!(msgs[i].flags & I2C_M_RD) || rx) {
			for (j = 0; j < msgs[i].len; j++)
				pr_debug("%02X ", msgs[i].buf[j]);
		}
		pr_debug("\n");
	}
#endif
}

static void ltq_i2c_release_bus(struct ltq_i2c *priv)
{
	if ((i2c_r32(bus_stat) & I2C_BUS_STAT_BS_MASK) == I2C_BUS_STAT_BS_BM)
		i2c_w32(I2C_ENDD_CTRL_SETEND, endd_ctrl);
}

static int ltq_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msgs[],
			   int num)
{
	struct ltq_i2c *priv = i2c_get_adapdata(adap);
	int ret;

	dev_dbg(priv->dev, "xfer %u messages\n", num);
	dump_msgs(msgs, num, 0);

	mutex_lock(&priv->mutex);

	INIT_COMPLETION(priv->cmd_complete);
	priv->current_msg = msgs;
	priv->msgs_num = num;
	priv->msg_err = 0;
	priv->status = STATUS_IDLE;
	priv->rx_thread_status = RX_THREAD_STOP;
	priv->rx_thread_force_stop = 0;
	/* wait for the bus to become ready */
	ret = ltq_i2c_wait_bus_not_busy(priv);
	if (ret) {
		ltq_i2c_hw_init(adap);
		goto done;
	}

	while (priv->msgs_num) {
		/* start the transfers */
		ltq_i2c_xfer_init(priv);
		/* wait for transfers to complete */
		ret = wait_for_completion_interruptible_timeout(
			&priv->cmd_complete, LTQ_I2C_XFER_TIMEOUT);
		if (ret == 0) {
			ltq_i2c_hw_init(adap);
			dev_err(priv->dev, "controller timed out 0x%x\n",
				priv->msg_err);
			ret = -ETIMEDOUT;
			goto done;
		} else if (ret < 0)
			goto done;

		if (priv->msg_err) {
			if (priv->msg_err & LTQ_I2C_NACK)
				ret = -ENXIO;
			else {
				ltq_i2c_hw_init(adap);
				dev_err(priv->dev, "remote io 0x%x\n",
				priv->msg_err);
				ret = -EREMOTEIO;
			}

			goto done;
		}
		if (--priv->msgs_num)
			priv->current_msg++;
	}
	/* no error? */
	ret = num;

done:
	ltq_i2c_release_bus(priv);
#ifdef LTQ_I2C_SUPPORT_COC
	i2c_priv->i2c_cocdrv_busy = LTQ_I2CCOCDRV_IDLE;
#endif
	if (priv->rx_thread_status != RX_THREAD_STOP) {
		priv->rx_thread_force_stop = 1;
		if (wait_event_interruptible_timeout(
				priv->rx_thread_wait_queue,
				priv->rx_thread_status == RX_THREAD_STOP,
				LTQ_I2C_RX_FIFO_TIMEOUT*3) <= 0)
				dev_err(priv->dev, "RX Threaded could not stop!!!\n");
	}

	mutex_unlock(&priv->mutex);

	if (ret >= 0)
		dump_msgs(msgs, num, 1);


	pr_debug("XFER ret %d\n", ret);
	return ret;
}

static irqreturn_t ltq_i2c_rx_thread_fn(int irq, void *dev_id)
{
	struct ltq_i2c *priv = dev_id;
	if (!priv)
		return IRQ_HANDLED;
	mutex_lock(&priv->rx_lock);
	priv->rx_thread_status = RX_THREAD_RUNNING;
	if (ltq_i2c_rx(priv) == 0)
		enable_burst_irq(priv);
	priv->rx_thread_status = RX_THREAD_STOP;
	mutex_unlock(&priv->rx_lock);
	return IRQ_HANDLED;
}
static irqreturn_t ltq_i2c_isr_burst(int irq, void *dev_id)
{
	struct ltq_i2c *priv = dev_id;
	struct i2c_msg *msg = priv->current_msg;

	int ret = IRQ_HANDLED;
	priv->last_burst = (irq == priv->irq_lb) ? LAST_BURST : BURST;
	if (priv->last_burst)
		pr_debug("===LB: flags[%x] status[%x]\n",
			msg->flags, priv->status);
	else
		pr_debug("===B: flags[%x] status[%x]\n",
			msg->flags, priv->status);

	if (msg->flags & I2C_M_RD) {
		switch (priv->status) {
		case STATUS_ADDR:
			pr_debug("===X===\n");
			disable_burst_irq(priv);
			prepare_msg_send_addr(priv);
			break;
		case STATUS_READ:
		case STATUS_READ_END:
			pr_debug("===R===\n");
			disable_burst_irq(priv);
			/* we need to handle RX in kernel thread */
			ret  = IRQ_WAKE_THREAD;
			break;
		default:
			disable_burst_irq(priv);
			pr_err("===Status R %d\n", priv->status);
			break;
		}
	} else {
		switch (priv->status) {
		case STATUS_ADDR:
		case STATUS_WRITE:
			pr_debug("===a===\n");
			ltq_i2c_addr_tx(priv);
			break;
		default:
			disable_burst_irq(priv);
			pr_err("===Status W %d\n", priv->status);
			break;
		}
	}

	i2c_w32(I2C_ICR_BREQ_INT_CLR | I2C_ICR_LBREQ_INT_CLR, icr);
	return ret;
}

static inline irqreturn_t ltq_i2c_isr_prot(struct ltq_i2c *priv)
{
	u32 i_pro = i2c_r32(p_irqss);
	int ret = IRQ_HANDLED;
	if (i_pro)
		i2c_w32(i_pro, p_irqsc);

	pr_debug("i2c-p");

	/* not acknowledge */
	if (i_pro & I2C_P_IRQSS_NACK) {
		priv->msg_err |= LTQ_I2C_NACK;
		pr_debug(" nack");
	}

	/* arbitration lost */
	if (i_pro & I2C_P_IRQSS_AL) {
		priv->msg_err |= LTQ_I2C_ARB_LOST;
		pr_err(" arb-lost");
	}
	/* tx -> rx switch */
	if (i_pro & I2C_P_IRQSS_RX)
		pr_debug(" rx");

	/* tx end */
	if (i_pro & I2C_P_IRQSS_TX_END)
		pr_debug(" txend");
	pr_debug("\n");

	if (!priv->msg_err) {
		/* tx -> rx switch */
		if (i_pro & I2C_P_IRQSS_RX) {
			priv->status = STATUS_READ;
			enable_burst_irq(priv);
		}
		if (i_pro & I2C_P_IRQSS_TX_END) {
			if (priv->status == STATUS_READ) {
				/*
				Get data in FIFO before
				with threaded RX function before
				closing the transaction.
				*/
				priv->status = STATUS_READ_END;
				priv->last_burst = LAST_BURST;
				disable_burst_irq(priv);
				ret = IRQ_WAKE_THREAD;
			} else {
				disable_burst_irq(priv);
				priv->status = STATUS_STOP;
				pr_debug("----0x%x\n", i_pro);
			}
		}
	}
	return ret;
}


static irqreturn_t ltq_i2c_isr(int irq, void *dev_id)
{
	u32 i_raw, i_err = 0;
	struct ltq_i2c *priv = dev_id;
	int ret = IRQ_HANDLED;
	i_raw = i2c_r32(mis);
	if (i_raw)
		i2c_w32(i_raw, icr);
	pr_debug("i_raw 0x%08X\n", i_raw);


	/* error interrupt */
	if (i_raw & I2C_RIS_I2C_ERR_INT_INTOCC) {
		i_err = i2c_r32(err_irqss);
		if (i_err)
			i2c_w32(i_err, err_irqsc);
		pr_debug("i_err 0x%08X bus_stat 0x%04X\n",
			i_err, i2c_r32(bus_stat));

		/* tx fifo overflow (8) */
		if (i_err & I2C_ERR_IRQSS_TXF_OFL)
			priv->msg_err |= LTQ_I2C_TX_OFL;


		/* tx fifo underflow (4) */
		if (i_err & I2C_ERR_IRQSS_TXF_UFL)
			priv->msg_err |= LTQ_I2C_TX_UFL;


		/* rx fifo overflow (2) */
		if (i_err & I2C_ERR_IRQSS_RXF_OFL)
			priv->msg_err |= LTQ_I2C_RX_OFL;

		/* rx fifo underflow (1) */
		if (i_err & I2C_ERR_IRQSS_RXF_UFL)
			priv->msg_err |= LTQ_I2C_RX_UFL;

	}

	/* protocol interrupt */
	if (i_raw & I2C_RIS_I2C_P_INT_INTOCC)
		ret = ltq_i2c_isr_prot(priv);
	else {
		i_err = i2c_r32(err_irqss);
		if (i_err) {
			i2c_w32(i_err, p_irqsc);
			/* pr_err("%s: ERROR\n", __func__); */
		}
	}

	if ((priv->msg_err) || (priv->status == STATUS_STOP))
		complete(&priv->cmd_complete);

	return ret;
}

static u32 ltq_i2c_functionality(struct i2c_adapter *adap)
{
	return	I2C_FUNC_I2C |
		I2C_FUNC_SMBUS_EMUL;
}

static struct i2c_algorithm ltq_i2c_algorithm = {
	.master_xfer	= ltq_i2c_xfer,
	.functionality	= ltq_i2c_functionality,
};

static int ltq_i2c_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct ltq_i2c *priv;
	struct i2c_adapter *adap;
	struct resource *mmres, irqres[4];
	struct pinctrl *pinctrl;
	int ret = 0;

	dev_dbg(&pdev->dev, "probing\n");

	mmres = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ret = of_irq_to_resource_table(node, irqres, 4);
	if (!mmres || (ret != 4)) {
		dev_err(&pdev->dev, "no resources\n");
		return -ENODEV;
	}

	pinctrl = devm_pinctrl_get_select_default(&pdev->dev);
	if (IS_ERR(pinctrl))
		dev_warn(&pdev->dev, "pins are not configured from the driver\n");

	/* allocate private data */

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		dev_err(&pdev->dev, "can't allocate private data\n");
		return -ENOMEM;
	}

#ifdef LTQ_I2C_SUPPORT_COC
	i2c_priv = priv;
#endif
	adap = &priv->adap;
	i2c_set_adapdata(adap, priv);
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	strlcpy(adap->name, DRV_NAME "-adapter", sizeof(adap->name));
	adap->algo = &ltq_i2c_algorithm;
	adap->dev.parent = &pdev->dev;

	if (of_property_read_u32(node, "clock-frequency", &priv->i2c_clock)) {
		dev_warn(&pdev->dev, "No I2C speed selected, using 100kHz\n");
		priv->i2c_clock = 100000;
	}

	init_completion(&priv->cmd_complete);
	mutex_init(&priv->mutex);
	mutex_init(&priv->rx_lock);
	init_waitqueue_head(&priv->rx_wait_queue);
	init_waitqueue_head(&priv->rx_thread_wait_queue);
	priv->membase = devm_request_and_ioremap(&pdev->dev, mmres);
	if (priv->membase == NULL)
		return -ENOMEM;

	priv->dev = &pdev->dev;
	priv->irq_lb = irqres[0].start;

	ret = devm_request_threaded_irq(&pdev->dev,
		irqres[0].start,
		ltq_i2c_isr_burst,
		ltq_i2c_rx_thread_fn,
		IRQF_ONESHOT,
		"i2c lb",
		priv);

	if (ret) {
		dev_err(&pdev->dev, "can't get last burst IRQ %d\n",
			irqres[0].start);
		return -ENODEV;
	}

	ret = devm_request_threaded_irq(&pdev->dev,
			irqres[1].start,
			ltq_i2c_isr_burst,
			ltq_i2c_rx_thread_fn,
		IRQF_ONESHOT,
		"i2c b",
		priv);

	if (ret) {
		dev_err(&pdev->dev, "can't get burst IRQ %d\n",
			irqres[1].start);
		return -ENODEV;
	}

	ret = devm_request_threaded_irq(&pdev->dev,
			irqres[2].start,
			ltq_i2c_isr,
			ltq_i2c_rx_thread_fn,
		IRQF_ONESHOT,
		"i2c err",
		priv);

	if (ret) {
		dev_err(&pdev->dev, "can't get error IRQ %d\n",
			irqres[2].start);
		return -ENODEV;
	}

	ret = devm_request_threaded_irq(&pdev->dev,
			irqres[3].start,
			ltq_i2c_isr,
			ltq_i2c_rx_thread_fn,
		IRQF_ONESHOT,
		"i2c p",
		priv);

	if (ret) {
		dev_err(&pdev->dev, "can't get protocol IRQ %d\n",
			irqres[3].start);
		return -ENODEV;
	}

	dev_dbg(&pdev->dev, "mapped io-space to %p\n", priv->membase);
	dev_dbg(&pdev->dev, "use IRQs %d, %d, %d, %d\n", irqres[0].start,
		irqres[1].start, irqres[2].start, irqres[3].start);

	/* this is a static clock, which has no refcounting */
	priv->clk_input = clk_get_fpi();
	if (IS_ERR(priv->clk_input)) {
		dev_err(&pdev->dev, "failed to get fpi clk\n");
		return -ENOENT;
	}
	priv->clk_gate = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR_OR_NULL(priv->clk_gate)) {
		dev_err(&pdev->dev, "failed to get i2c clk\n");
		return -ENOENT;
	} else
		clk_activate(priv->clk_gate);


	adap->dev.of_node = node;

	/* add our adapter to the i2c stack */
	adap->nr = pdev->id;
	ret = i2c_add_numbered_adapter(adap);
	if (ret) {
		dev_err(&pdev->dev, "can't register I2C adapter\n");
		goto out;
	}

	platform_set_drvdata(pdev, priv);

	/* print module version information */
	dev_dbg(&pdev->dev, "module id=%u revision=%u\n",
		(i2c_r32(id) & I2C_ID_ID_MASK) >> I2C_ID_ID_OFFSET,
		(i2c_r32(id) & I2C_ID_REV_MASK) >> I2C_ID_REV_OFFSET);
	/* initialize HW */
	ret = ltq_i2c_hw_init(adap);
	if (ret) {
		dev_err(&pdev->dev, "can't configure adapter\n");
		i2c_del_adapter(adap);
		platform_set_drvdata(pdev, NULL);
	} else {
		dev_info(&pdev->dev, "version %s\n", DRV_VERSION);
	}
	of_i2c_register_devices(adap);
#ifdef LTQ_I2C_SUPPORT_COC
	/*ltq_i2c_cpufreq_init(priv);*/
#endif
out:
	/* if init failed, we need to deactivate the clock gate */
	if (ret)
		clk_deactivate(priv->clk_gate);

	return ret;
}

static int ltq_i2c_remove(struct platform_device *pdev)
{
	struct ltq_i2c *priv = platform_get_drvdata(pdev);
	/* make sure that RX thread is done */
	if (priv->rx_thread_status != RX_THREAD_STOP) {
		priv->rx_thread_force_stop = 1;
		if (wait_event_interruptible_timeout(
				priv->rx_thread_wait_queue,
				priv->rx_thread_status == RX_THREAD_STOP,
				LTQ_I2C_RX_FIFO_TIMEOUT*3) <= 0)
				dev_err(priv->dev, "RX Threaded could not stop!!!\n");
	}
#ifdef LTQ_I2C_SUPPORT_COC
	ltq_i2c_cpufreq_exit(priv);
#endif

	/* disable bus */
	i2c_w32_mask(I2C_RUN_CTRL_RUN_EN, 0, run_ctrl);

	/* power down the core */
	clk_deactivate(priv->clk_gate);


	/* remove driver */
	i2c_del_adapter(&priv->adap);
	/* free priv data */
	devm_kfree(&pdev->dev, priv);

	dev_dbg(&pdev->dev, "removed\n");
	platform_set_drvdata(pdev, NULL);

	return 0;
}
static const struct of_device_id ltq_i2c_match[] = {
	{ .compatible = "lantiq,lantiq-i2c" },
	{},
};
MODULE_DEVICE_TABLE(of, ltq_i2c_match);

static struct platform_driver ltq_i2c_driver = {
	.probe	= ltq_i2c_probe,
	.remove	= ltq_i2c_remove,
	.driver	= {
		.name	= DRV_NAME,
		.owner	= THIS_MODULE,
		.of_match_table = ltq_i2c_match,
	},
};

static int __init ltq_i2c_init(void)
{
	int ret;

	ret = platform_driver_register(&ltq_i2c_driver);
	if (ret)
		pr_err("ltq-i2c: probe failed: %d\n", ret);

	return ret;
}

subsys_initcall(ltq_i2c_init);


#ifdef LTQ_I2C_SUPPORT_COC
static int __init ltq_i2c_coc_init(void)
{
	ltq_i2c_cpufreq_init(i2c_priv);
	return 0;
}
module_init(ltq_i2c_coc_init)
#endif

/* module_platform_driver(ltq_i2c_driver); */

MODULE_DESCRIPTION("Lantiq I2C bus adapter");
MODULE_AUTHOR("Thomas Langer <thomas.langer@lantiq.com>");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
