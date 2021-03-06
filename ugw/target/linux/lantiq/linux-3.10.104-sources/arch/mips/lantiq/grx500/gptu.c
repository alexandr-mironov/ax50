/*
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 *
 *  Copyright (C) 2012 John Crispin <blogic@openwrt.org>
 *  Copyright (C) 2012 Lantiq GmbH
 *  Copyright (C) 2014 Kavitha  Subramanian <s.kavitha.EE@lantiq.com>

 */

#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>
#include <linux/klogging.h>

#include <lantiq_soc.h>
#include "../clk.h"

#define gptu_assert(cond, fmt, arg...)  \
	do { \
		if (!(cond)) \
			LOGF_KLOG_ERROR("%d:%s:" fmt "\n", __LINE__, __func__, ##arg);\
	} while (0)
#define gptu_err(fmt, arg...)          \
			LOGF_KLOG_ERROR("%d:%s:"fmt "\n", __LINE__, __func__, ##arg);
#define gptu_print(fmt, arg...)        \
			printk(fmt, ##arg);

/* the magic ID byte of the core */
#define GPTU_MAGIC	0x59
/* clock control register */
#define GPTU_CLC	0x00
/* id register */
#define GPTU_ID		0x08
/* interrupt node enable */
#define GPTU_IRNEN	0xf4
/* interrupt control register */
#define GPTU_IRCR	0xf8
/* interrupt capture register */
#define GPTU_IRNCR	0xfc
/* there are 3 identical blocks of 2 timers. calculate register offsets */
#define GPTU_SHIFT(x)	(x % 2 ? 4 : 0)
#define GPTU_BASE(x)	(((x >> 1) * 0x20) + 0x10)
/* timer control register */
#define GPTU_CON(x)	(GPTU_BASE(x) + GPTU_SHIFT(x) + 0x00)
/* timer auto reload register */
#define GPTU_RUN(x)	(GPTU_BASE(x) + GPTU_SHIFT(x) + 0x08)
/* timer manual reload register */
#define GPTU_RLD(x)	(GPTU_BASE(x) + GPTU_SHIFT(x) + 0x10)
/* timer count register */
#define GPTU_CNT(x)	(GPTU_BASE(x) + GPTU_SHIFT(x) + 0x18)

/* GPTU_CON(x) */
#define CON_CNT		BIT(2)
#define CON_STP		BIT(3)
#define CON_EXT		BIT(4)
#define CON_EDGE_ANY	(BIT(7) | BIT(6))
#define CON_SYNC	BIT(8)
#define CON_CLK_INT	BIT(10)
#define CON_CLK_EXT	BIT(9)

/* GPTU_RUN(x) */
#define RUN_SEN		BIT(0)
#define RUN_RL		BIT(2)
#define RUN_STOP    BIT(1)
/* set clock to runmode */
#define CLC_RMC		BIT(8)
#define CLC_SMC     BIT(16)

/* bring core out of suspend */
#define CLC_SUSPEND	BIT(4)
/* the disable bit */
#define CLC_DISABLE	BIT(0)

#define GPTC_MODULE_CLOCK 200000000
#define GRX500_MAX_GPTU_TIMER_MODULE 2
#define gptu_w32(x, gptu_membase, y)	ltq_w32((x), gptu_membase + (y))
#define gptu_r32(x, gptu_membase)	ltq_r32(gptu_membase + (x))


enum gptu_timer {
	TIMER1A = 0,
	TIMER1B,
	TIMER2A,
	TIMER2B,
	TIMER3A,
	TIMER3B
};
struct grx500_gptu_port {
	const char *dev_id;
	unsigned char __iomem *gptu_membase; /* Virtual */
	int port_idx;
	struct resource irqres[6];
};
static struct grx500_gptu_port *gptu_port[GRX500_MAX_GPTU_TIMER_MODULE];

#if 1
static irqreturn_t timer_irq_handler(int irq, void *priv)
{
	struct grx500_gptu_port *port = priv;
	int timer = irq - port->irqres[0].start;
	gptu_w32(1 << timer, port->gptu_membase, GPTU_IRNCR);
	return IRQ_HANDLED;
}
#endif

static int gptu_getport(struct clk *clk, struct grx500_gptu_port **port)
{
	int i = 0;
	for (i = 0; i < GRX500_MAX_GPTU_TIMER_MODULE; i++) {
		if (gptu_port[i]
			 && strcmp(clk->cl.dev_id, gptu_port[i]->dev_id) == 0) {
			*port = gptu_port[i];
			break;
		}
	}
	if (*port == NULL)
		return -ENXIO;
	return 0;
}
#ifndef CONFIG_CEVT_GPTC
static void gptu_hwinit(struct grx500_gptu_port *port)
{
	gptu_w32(0x00, port->gptu_membase, GPTU_IRNEN);
	gptu_w32(0xff, port->gptu_membase, GPTU_IRNCR);
	gptu_w32(CLC_SMC|CLC_RMC, port->gptu_membase, GPTU_CLC);
}
static void gptu_hwexit(struct grx500_gptu_port *port)
{
	gptu_w32(0x00, port->gptu_membase, GPTU_IRNEN);
	gptu_w32(0xff, port->gptu_membase, GPTU_IRNCR);
	gptu_w32(CLC_DISABLE, port->gptu_membase, GPTU_CLC);
}
#endif

static int gptu_setrate(unsigned long rate)
{
	/*Dummy function but used*/
	return 0;
}
static int setrate(struct clk *clk)
{
	uint64_t cpu_freq = 0;
	int ret = 0;
	uint32_t reg;
	struct grx500_gptu_port *port = NULL;
	ret = gptu_getport(clk, &port);
	if (ret)
		return ret;
	cpu_freq = GPTC_MODULE_CLOCK;
	LOGF_KLOG_INFO("cpu_clk %llu\r\n", cpu_freq);
	if (!clk->rate)
		clk->rate = cpu_freq;
	do_div(cpu_freq, clk->rate);
	LOGF_KLOG_INFO("reload_counter_value %llu\r\n", cpu_freq);
	if (cpu_freq > 0xFFFF) {
		/*check if this timerA or timerB*/
		if (clk->bits % 2) {
			return -EINVAL;
		} else {
			/*Timer B is running*/
			if ((gptu_r32(GPTU_CON((clk->bits + 1)),
				port->gptu_membase) & 1) == 1)
				return -EBUSY;
		}
		reg = gptu_r32(GPTU_CON(clk->bits), port->gptu_membase);
		reg |= CON_EXT;
		gptu_w32(reg, port->gptu_membase, GPTU_CON(clk->bits));
	}
	gptu_w32(cpu_freq, port->gptu_membase, GPTU_RLD(clk->bits));
	return 0;
}

static int gptu_enable(struct clk *clk)
{
	int ret = 0;
	struct grx500_gptu_port *port = NULL;
	ret = gptu_getport(clk, &port);
	if (ret)
		return ret;
	if (atomic_read(&clk->refcount))
		return -EBUSY;
	gptu_w32(0 , port->gptu_membase, GPTU_CON(clk->bits));
	ret = setrate(clk);
	if (ret)
		return ret;
	if ((strcmp(clk->cl.con_id, "timer2a") != 0) && (strcmp(clk->cl.con_id, "timer3a") != 0)) {
		ret = request_irq(port->irqres[clk->bits].start,
			timer_irq_handler, IRQF_TIMER, "gtpu", (void *)port);
		if (ret) {
			LOGF_KLOG_ERROR("gptu: failed to request irq\n");
			return ret;
		}
	}
	gptu_w32(gptu_r32(GPTU_IRNEN, port->gptu_membase) | BIT(clk->bits),
		port->gptu_membase, GPTU_IRNEN);
	gptu_w32(RUN_SEN | RUN_RL, port->gptu_membase, GPTU_RUN(clk->bits));
	atomic_inc(&clk->refcount);
    /*wait for status bit*/
	while ((gptu_r32(GPTU_CON(clk->bits),
		port->gptu_membase) & 1) == 0) {
	}
	return 0;
}

static void gptu_disable(struct clk *clk)
{
	int ret = 0;
	struct grx500_gptu_port *port = NULL;
	ret = gptu_getport(clk, &port);
	if (ret)
		return;
	atomic_dec(&clk->refcount);
	gptu_w32(0, port->gptu_membase, GPTU_RLD(clk->bits));
	gptu_w32(RUN_STOP, port->gptu_membase, GPTU_RUN(clk->bits));
	gptu_w32(0, port->gptu_membase, GPTU_CON(clk->bits));
    /*wait for status bit*/
	while ((gptu_r32(GPTU_CON(clk->bits),
		port->gptu_membase) & 1) == 1) {

	}
	if ((strcmp(clk->cl.con_id, "timer2a") != 0) && (strcmp(clk->cl.con_id, "timer3a") != 0)) {
		gptu_w32(
		gptu_r32(GPTU_IRNEN, port->gptu_membase) & ~BIT(clk->bits),
		port->gptu_membase, GPTU_IRNEN);
		free_irq(port->irqres[clk->bits].start, NULL);
	}
}

static inline void clkdev_add_gptu(struct device *dev, const char *con,
							unsigned int timer)
{
	struct clk *clk = kzalloc(sizeof(struct clk), GFP_KERNEL);

	if (clk) {
		LOGF_KLOG_ERROR("Memory Allocation suceeded\r\n");
		clk->cl.dev_id = dev_name(dev);
		clk->cl.con_id = con;
		clk->cl.clk = clk;
		clk->enable = gptu_enable;
		clk->disable = gptu_disable;
		clk->set_rate = gptu_setrate;
		clk->bits = timer;
		atomic_set(&(clk->refcount), 0);
		clkdev_add(&clk->cl);
		return;
	}
	LOGF_KLOG_ERROR("Memory Allocation failed\r\n");
}

static int gptu_probe(struct platform_device *pdev)
{
#ifndef CONFIG_CEVT_GPTC
	struct clk *clk;
#endif
	struct resource *res;
	int ret_val = -ENOMEM;
	static int grx500_gptu_init_count;
	struct grx500_gptu_port *port;

	if (grx500_gptu_init_count > (GRX500_MAX_GPTU_TIMER_MODULE - 1)) {
		ret_val = -ENODEV;
		return ret_val;
	}

	gptu_port[grx500_gptu_init_count] = kzalloc(
		sizeof(struct grx500_gptu_port), GFP_KERNEL);
	if (gptu_port[grx500_gptu_init_count] == NULL) {
		LOGF_KLOG_ERROR("%s: no memory for gptu port\n", __func__);
	    return ret_val;
	}
	port = gptu_port[grx500_gptu_init_count];
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		LOGF_KLOG_DEV_ERROR(&pdev->dev, "platform_get_resource\n");
		ret_val = -ENOENT;
		return ret_val;
	}

	/* remap gptu register range */
	port->gptu_membase = devm_ioremap_resource(&pdev->dev, res);
	if (!port->gptu_membase) {
		LOGF_KLOG_DEV_ERROR(&pdev->dev, "failed to remap memory region\n");
		ret_val = -ENXIO;
		return ret_val;
	}

	if (of_irq_to_resource_table(pdev->dev.of_node, port->irqres, 6) != 6) {
		LOGF_KLOG_DEV_ERROR(&pdev->dev, "Failed to get IRQ list\n");
		return -EINVAL;
	}
	port->port_idx = grx500_gptu_init_count;
	port->dev_id   = dev_name(&pdev->dev);
	LOGF_KLOG_INFO("dev id %s\r\n", port->dev_id);
#ifndef CONFIG_CEVT_GPTC
	/* enable our clock */
	clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(clk)) {
		LOGF_KLOG_DEV_ERROR(&pdev->dev, "Failed to get clock\n");
		return -ENOENT;
	}
	clk_enable(clk);
	/* power up the core */
	gptu_hwinit(port);
#endif

	/* the gptu has a ID register */
	if (((gptu_r32(GPTU_ID, port->gptu_membase) >> 8)
		& 0xff)	!= GPTU_MAGIC) {
		LOGF_KLOG_DEV_ERROR(&pdev->dev, "Failed to find magic\n");
#ifndef CONFIG_CEVT_GPTC
		gptu_hwexit(port);
		clk_disable(clk);
		clk_put(clk);
#endif
	return -ENAVAIL;
	}

#ifndef CONFIG_CEVT_GPTC
	/* register the clocks */
	clkdev_add_gptu(&pdev->dev, "timer1a", TIMER1A);
	clkdev_add_gptu(&pdev->dev, "timer1b", TIMER1B);
	clkdev_add_gptu(&pdev->dev, "timer2a", TIMER2A);
	clkdev_add_gptu(&pdev->dev, "timer2b", TIMER2B);
	clkdev_add_gptu(&pdev->dev, "timer3a", TIMER3A);
	clkdev_add_gptu(&pdev->dev, "timer3b", TIMER3B);
	LOGF_KLOG_DEV_INFO(&pdev->dev, "gptu: 6 timers loaded\n");
#else
	clkdev_add_gptu(&pdev->dev, "timer2a", TIMER2A);
	clkdev_add_gptu(&pdev->dev, "timer2b", TIMER2B);
	clkdev_add_gptu(&pdev->dev, "timer3a", TIMER3A);
	clkdev_add_gptu(&pdev->dev, "timer3b", TIMER3B);
	LOGF_KLOG_DEV_INFO(&pdev->dev, "gptu: 4 timers loaded\n");
#endif
	grx500_gptu_init_count++;
	gptu_print("gptu driver init successfully\r\n");
	return 0;
}

static const struct of_device_id gptu_match[] = {
	{ .compatible = "lantiq,gptu-xrx500" },
	{},
};
MODULE_DEVICE_TABLE(of, gptu_match);

static struct platform_driver gptu_driver = {
	.probe = gptu_probe,
	.driver = {
		.name = "gptu-xrx500",
		.owner = THIS_MODULE,
		.of_match_table = gptu_match,
	},
};

int __init gptu_init(void)
{
	int ret = platform_driver_register(&gptu_driver);

	if (ret)
		LOGF_KLOG_INFO("gptu: Error registering GPTU platform driver\n");
	return ret;
}

core_initcall_sync(gptu_init);
