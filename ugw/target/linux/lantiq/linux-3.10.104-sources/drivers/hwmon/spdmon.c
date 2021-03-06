/*
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 *
 *  Copyright (C) 2015 victor yeo <s.yeo.ee@lantiq.com>
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <lantiq_soc.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/hwmon.h>
#include <linux/hwmon-vid.h>
#include <linux/sysfs.h>
#include <linux/hwmon-sysfs.h>
#include <linux/kobject.h>
#include <linux/clk.h>
#include <lantiq.h>
#include <../arch/mips/lantiq/grx500/clk.h>

/** driver version, major number */
#define SPD_MON_VER_MAJOR	1
/** driver version, minor number */
#define SPD_MON_VER_MINOR	4
/** driver version, build number */
#define SPD_MON_VER_STEP	0

#define LTQ_SPD_MON_VERSION(a, b, c) (((a) << 16) + ((b) << 8) + (c))
#ifndef _MKSTR_1
#define _MKSTR_1(x)	#x
#define _MKSTR(x)	_MKSTR_1(x)
#endif


/** driver version as string */
#define SPD_MON_VER_STR	_MKSTR(SPD_MON_VER_MAJOR) "." \
			_MKSTR(SPD_MON_VER_MINOR) "." \
			_MKSTR(SPD_MON_VER_STEP)

/* ioctl definition */
#define TYPE 0xF4
#define LTQ_SPD_MON_IOC_VERSION			_IOR(TYPE, 0, struct ioctl_arg*)
#define LTQ_SPD_MON_IOC_READ			_IOR(TYPE, 1, struct ioctl_arg*)
#define LTQ_SPD_MON_IOC_GET_SPD			_IOR(TYPE, 2, struct ioctl_arg*)
#define LTQ_SPD_MON_IOC_SET_SAMPLE_RATE_SVT	_IOW(TYPE, 3, struct ioctl_arg*)
#define LTQ_SPD_MON_IOC_SET_SAMPLE_RATE_LVT	_IOW(TYPE, 4, struct ioctl_arg*)
#define LTQ_SPD_MON_IOC_SEL_CHANNEL		_IOW(TYPE, 5, struct ioctl_arg*)
#define LTQ_SPD_MON_IOC_SET_THRESHOLD	_IOW(TYPE, 6, struct ioctl_th_arg*)
#define LTQ_SPD_MON_IOC_WRITE			_IOW(TYPE, 7, struct ioctl_arg*)

/* spd_mon register offset */
#define SPD_MON_CON			0x0
#define SPD_MON_SVT_DATA		0x4
#define SPD_MON_LVT_DATA		0x8

/* spd_mon bit settings */
#define LTQ_SPDMON_LVT_SLOW_LOW		2000
#define LTQ_SPDMON_LVT_SLOW_HIGH	5400
#define LTQ_SPDMON_LVT_MEDIUM_LOW	5401
#define LTQ_SPDMON_LVT_MEDIUM_HIGH	5800
#define LTQ_SPDMON_LVT_FAST_LOW		5801
#define LTQ_SPDMON_LVT_FAST_HIGH	7000

#define LTQ_SPDMON_SVT_SLOW_LOW		1000
#define LTQ_SPDMON_SVT_SLOW_HIGH	3400
#define LTQ_SPDMON_SVT_MEDIUM_LOW	3401
#define LTQ_SPDMON_SVT_MEDIUM_HIGH	3800
#define LTQ_SPDMON_SVT_FAST_LOW		3801
#define LTQ_SPDMON_SVT_FAST_HIGH	5000

/*max SMON channels*/
#define LTQ_SPD_MON_CH_MAX		3

/* spd_mon defines */
#define SPD_MON_VERSION LTQ_SPD_MON_VERSION(SPD_MON_VER_MAJOR, \
						SPD_MON_VER_MINOR, \
						SPD_MON_VER_STEP)
#define SPD_MON_NAME			"spdmon"
#define SPD_MON_DATA_TGL		0x20000

#define SHOW_NAME			1
#define SHOW_CLASS			2
#define SHOW_CHANNEL			3
#define SHOW_RATE_SVT			4
#define SHOW_RATE_LVT			5
#define DEVICE_ATTR_NUM			7
#define THRESHOLD_SIZE			6
#define SHOW_SPD_DATA			7
#define SHOW_CLASS_B			9

#define SHOW_THRESHOLD_SVT_SLOW_LOW	10
#define SHOW_THRESHOLD_SVT_MEDIUM_LOW	11
#define SHOW_THRESHOLD_SVT_FAST_LOW	12
#define SHOW_THRESHOLD_SVT_SLOW_HIGH	13
#define SHOW_THRESHOLD_SVT_MEDIUM_HIGH	14
#define SHOW_THRESHOLD_SVT_FAST_HIGH	15
#define SHOW_THRESHOLD_LVT_SLOW_LOW	16
#define SHOW_THRESHOLD_LVT_MEDIUM_LOW	17
#define SHOW_THRESHOLD_LVT_FAST_LOW	18
#define SHOW_THRESHOLD_LVT_SLOW_HIGH	19
#define SHOW_THRESHOLD_LVT_MEDIUM_HIGH	20
#define SHOW_THRESHOLD_LVT_FAST_HIGH	21

/* smon fused register offset (part of CHIPID registers)*/
#define SMON_FUSED			0x0
/* smon bit settings */
#define SMON_FD				0x40
#define SMON_LVT_M			0x38
#define SMON_SVT_M			0x07
#define SMON_FAST			0x04

/* Vddmin fused register offset (part of CHIPID registers)*/
#define FUSE_REDUND_2			0x0
/* smon bit settings */
#define VDDM_FUD			0x40
#define VDD_MIN				0x3F

/* helpers used to access the chipid register FAB_LOT_ID*/
#define ltq_fablotid_r32(x)	ltq_r32(ltq_fablotid_membase + (x))
__iomem void *ltq_fablotid_membase = (__iomem void *)0xBF107354;

/* helpers used to access the chipid register FAB_LOT_ID*/
#define ltq_fuse_redund_2_r32(x)	ltq_r32(ltq_fuse_redund_2_membase + (x))
__iomem void *ltq_fuse_redund_2_membase = (__iomem void *)0xBF107378;

/* GRX500 product variants */
#define GRX350				0x1
#define GRX550				0x2

/* struct define */
struct ioctl_arg {
	u32 address;
	u32 value;
};

struct ioctl_th_arg {
	u32 vt;
	u32 range;
	u32 low;
	u32 high;
};

struct spd_mon_ctrl {
	void __iomem	*membase;
	u32		spd_mon_irq;
	u32		phybase;
	struct device	*dev;
	struct device	*hwmon_dev;
};

struct spd_data {
	u32		svt;
	u32		lvt;
};

struct spd_cnt {
	u32		slow;
	u32		medi;
	u32		fast;
};

static unsigned int base_freq_svt;
static unsigned int base_freq_lvt;
static struct spd_mon_ctrl ltq_spd_mon_ctrl;
static dev_t dev_num;			/* first device number */
static struct cdev c_dev;		/* character device structure */
static struct class *cl;		/* the device class */
static struct mutex spdmon_mutex;	/* mutex protection */
struct kobject *threshold_svt_kobj;
struct kobject *threshold_lvt_kobj;

/* threshold value */
static u32 spd_lvt_s_low = LTQ_SPDMON_LVT_SLOW_LOW;
static u32 spd_lvt_s_high = LTQ_SPDMON_LVT_SLOW_HIGH;
static u32 spd_lvt_m_low = LTQ_SPDMON_LVT_MEDIUM_LOW;
static u32 spd_lvt_m_high = LTQ_SPDMON_LVT_MEDIUM_HIGH;
static u32 spd_lvt_f_low = LTQ_SPDMON_LVT_FAST_LOW;
static u32 spd_lvt_f_high = LTQ_SPDMON_LVT_FAST_HIGH;

static u32 spd_svt_s_low = LTQ_SPDMON_SVT_SLOW_LOW;
static u32 spd_svt_s_high = LTQ_SPDMON_SVT_SLOW_HIGH;
static u32 spd_svt_m_low = LTQ_SPDMON_SVT_MEDIUM_LOW;
static u32 spd_svt_m_high = LTQ_SPDMON_SVT_MEDIUM_HIGH;
static u32 spd_svt_f_low = LTQ_SPDMON_SVT_FAST_LOW;
static u32 spd_svt_f_high = LTQ_SPDMON_LVT_FAST_HIGH;

/* pre load counter values */
static u32 spd_sample_rate_svt = 0xFF;
static u32 spd_sample_rate_lvt = 0xFF;

static enum spd_class_t spd_mon_get_speed_class(struct spd_cnt *smcl);
static void spd_mon_get_spd_data(void);
static int32_t spd_mon_sel_channel(int32_t channel);
static int32_t spd_mon_get_channel(void);
static int32_t spd_mon_set_sample_rate_svt(int32_t sample_rate);
static int32_t spd_mon_set_sample_rate_lvt(int32_t sample_rate);
static int32_t spd_mon_get_sample_rate_svt(void);
static int32_t spd_mon_get_sample_rate_lvt(void);

static struct spd_data spd_mon_data[LTQ_SPD_MON_CH_MAX];
static char *spc[] = {"FAST0", "FAST1", "FAST2", "FAST3",
			"TYP0", "TYP1", "TYP2", "TYP3",
			"SLOW0", "SLOW1", "SLOW2", "SLOW3",
			"SLOW_DEFAULT", "NOT DEFINED"};
static int spd_svt_fused[] = {MEDIUM0, SLOW0, SLOW0, MEDIUM0,
				MEDIUM0, MEDIUM0, FAST0, FAST0};

//static int chip_type; /*holds info: GRX350 or GRX550*/
int chip_type; /*holds info: GRX350 or GRX550*/

/*======================================================================*/
/* SYSFS HELPER FUNCTION CALLED FROM LINUX HWMON CORE                   */
/*======================================================================*/
static int show_version(struct device *dev,
	struct device_attribute *devattr, char *buf)
{
	return sprintf(buf, SPD_MON_VER_STR"\n");
}

static int show_value(struct device *dev,
	struct device_attribute *devattr, char *buf)
{
	struct spd_cnt smcl;
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);

	if (attr->index == SHOW_NAME)
		return sprintf(buf, "%s\n", SPD_MON_NAME);
	else if (attr->index == SHOW_CLASS_B) {
		int spg;
		spg = ltq_grx500_get_speed_grade();
		return sprintf(buf, "%s, default = %s, chiptyp = %s\n",
				((spg & 0xFF) < 14) ? spc[spg & 0xFF] : "undefined",
				(spg & 0x100) ? "Yes" : "Updated",
				(chip_type == 1) ? "GRX350" : "GRX550");
	} else if (attr->index == SHOW_CLASS) {
		return sprintf(buf, "%s, slow=%d, med=%d, fast=%d\n",
				spc[spd_mon_get_speed_class(&smcl)],
				smcl.slow, smcl.medi, smcl.fast);
	} else if (attr->index == SHOW_SPD_DATA) {
		int i, len = 0;
		spd_mon_get_spd_data();
		for (i = 0; i < LTQ_SPD_MON_CH_MAX; i++) {
			len += sprintf(buf+len, " CH%d_DATA_SVT: %d (%dkHz)",
					i,
					spd_mon_data[i].svt,
					(base_freq_svt / spd_mon_data[i].svt));

			len += sprintf(buf+len, " CH%d_DATA_LVT: %d (%dkHz)\n",
					i,
					spd_mon_data[i].lvt,
					(base_freq_svt / spd_mon_data[i].lvt));
		}
		return len;
	} else if (attr->index == SHOW_CHANNEL)
		return sprintf(buf, "%d\n", spd_mon_get_channel());
	else if (attr->index == SHOW_RATE_SVT)
		return sprintf(buf, "%d\n", spd_mon_get_sample_rate_svt());
	else if (attr->index == SHOW_RATE_LVT)
		return sprintf(buf, "%d\n", spd_mon_get_sample_rate_lvt());
	else if (attr->index == SHOW_THRESHOLD_SVT_SLOW_LOW)
		return sprintf(buf, "%d\n", spd_svt_s_low);
	else if (attr->index == SHOW_THRESHOLD_SVT_MEDIUM_LOW)
		return sprintf(buf, "%d\n", spd_svt_m_low);
	else if (attr->index == SHOW_THRESHOLD_SVT_FAST_LOW)
		return sprintf(buf, "%d\n", spd_svt_f_low);
	else if (attr->index == SHOW_THRESHOLD_SVT_SLOW_HIGH)
		return sprintf(buf, "%d\n", spd_svt_s_high);
	else if (attr->index == SHOW_THRESHOLD_SVT_MEDIUM_HIGH)
		return sprintf(buf, "%d\n", spd_svt_m_high);
	else if (attr->index == SHOW_THRESHOLD_SVT_FAST_HIGH)
		return sprintf(buf, "%d\n", spd_svt_f_high);
	/* for LVT */
	else if (attr->index == SHOW_THRESHOLD_LVT_SLOW_LOW)
		return sprintf(buf, "%d\n", spd_lvt_s_low);
	else if (attr->index == SHOW_THRESHOLD_LVT_MEDIUM_LOW)
		return sprintf(buf, "%d\n", spd_lvt_m_low);
	else if (attr->index == SHOW_THRESHOLD_LVT_FAST_LOW)
		return sprintf(buf, "%d\n", spd_lvt_f_low);
	else if (attr->index == SHOW_THRESHOLD_LVT_SLOW_HIGH)
		return sprintf(buf, "%d\n", spd_lvt_s_high);
	else if (attr->index == SHOW_THRESHOLD_LVT_MEDIUM_HIGH)
		return sprintf(buf, "%d\n", spd_lvt_m_high);
	else if (attr->index == SHOW_THRESHOLD_LVT_FAST_HIGH)
		return sprintf(buf, "%d\n", spd_lvt_f_high);
	else
		return sprintf(buf, "0\n");
}

static int set_value(struct device *dev,
	struct device_attribute *devattr, const char *buf, size_t count)
{
	int ch;
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	int ret = kstrtoint(buf, 10, &ch);

	if (ret < 0)
		return ret;

	if (attr->index == SHOW_CHANNEL)
		spd_mon_sel_channel(ch);
	else if (attr->index == SHOW_RATE_SVT)
		spd_mon_set_sample_rate_svt(ch);
	else if (attr->index == SHOW_RATE_LVT)
		spd_mon_set_sample_rate_lvt(ch);
	else if (attr->index == SHOW_THRESHOLD_SVT_SLOW_LOW)
		spd_svt_s_low = ch;
	else if (attr->index == SHOW_THRESHOLD_SVT_MEDIUM_LOW)
		spd_svt_m_low = ch;
	else if (attr->index == SHOW_THRESHOLD_SVT_FAST_LOW)
		spd_svt_f_low = ch;
	else if (attr->index == SHOW_THRESHOLD_SVT_SLOW_HIGH)
		spd_svt_s_high = ch;
	else if (attr->index == SHOW_THRESHOLD_SVT_MEDIUM_HIGH)
		spd_svt_m_high = ch;
	else if (attr->index == SHOW_THRESHOLD_SVT_FAST_HIGH)
		spd_svt_f_high = ch;
	/* for LVT */
	else if (attr->index == SHOW_THRESHOLD_LVT_SLOW_LOW)
		spd_lvt_s_low = ch;
	else if (attr->index == SHOW_THRESHOLD_LVT_MEDIUM_LOW)
		spd_lvt_m_low = ch;
	else if (attr->index == SHOW_THRESHOLD_LVT_FAST_LOW)
		spd_lvt_f_low = ch;
	else if (attr->index == SHOW_THRESHOLD_LVT_SLOW_HIGH)
		spd_lvt_s_high = ch;
	else if (attr->index == SHOW_THRESHOLD_LVT_MEDIUM_HIGH)
		spd_lvt_m_high = ch;
	else if (attr->index == SHOW_THRESHOLD_LVT_FAST_HIGH)
		spd_lvt_f_high = ch;
	return count;
}

static struct sensor_device_attribute spdmon_attributes[] = {
	SENSOR_ATTR(version, S_IRUGO, show_version, NULL, 0),
	SENSOR_ATTR(name, S_IRUGO, show_value, NULL, SHOW_NAME),
	SENSOR_ATTR(spd_data, S_IRUGO, show_value, NULL, SHOW_SPD_DATA),
	SENSOR_ATTR(speed_class, S_IRUGO, show_value, NULL, SHOW_CLASS),
	SENSOR_ATTR(speed_class_boot, S_IRUGO, show_value, NULL, SHOW_CLASS_B),
	SENSOR_ATTR(channel, S_IWUSR | S_IRUGO, show_value,
		set_value, SHOW_CHANNEL),
	SENSOR_ATTR(rate_svt, S_IWUSR | S_IRUGO, show_value,
		set_value, SHOW_RATE_SVT),
	SENSOR_ATTR(rate_lvt, S_IWUSR | S_IRUGO, show_value,
		set_value, SHOW_RATE_LVT),
};

static SENSOR_DEVICE_ATTR(svt_slow_low, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_SVT_SLOW_LOW);
static SENSOR_DEVICE_ATTR(svt_medium_low, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_SVT_MEDIUM_LOW);
static SENSOR_DEVICE_ATTR(svt_fast_low, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_SVT_FAST_LOW);
static SENSOR_DEVICE_ATTR(svt_slow_high, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_SVT_SLOW_HIGH);
static SENSOR_DEVICE_ATTR(svt_medium_high, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_SVT_MEDIUM_HIGH);
static SENSOR_DEVICE_ATTR(svt_fast_high, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_SVT_FAST_HIGH);

static SENSOR_DEVICE_ATTR(lvt_slow_low, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_LVT_SLOW_LOW);
static SENSOR_DEVICE_ATTR(lvt_medium_low, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_LVT_MEDIUM_LOW);
static SENSOR_DEVICE_ATTR(lvt_fast_low, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_LVT_FAST_LOW);
static SENSOR_DEVICE_ATTR(lvt_slow_high, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_LVT_SLOW_HIGH);
static SENSOR_DEVICE_ATTR(lvt_medium_high, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_LVT_MEDIUM_HIGH);
static SENSOR_DEVICE_ATTR(lvt_fast_high, S_IWUSR | S_IRUGO,
	show_value, set_value, SHOW_THRESHOLD_LVT_FAST_HIGH);

static struct attribute *threshold_svt_attrs[] = {
	&sensor_dev_attr_svt_slow_low.dev_attr.attr,
	&sensor_dev_attr_svt_medium_low.dev_attr.attr,
	&sensor_dev_attr_svt_fast_low.dev_attr.attr,
	&sensor_dev_attr_svt_slow_high.dev_attr.attr,
	&sensor_dev_attr_svt_medium_high.dev_attr.attr,
	&sensor_dev_attr_svt_fast_high.dev_attr.attr,
	NULL,
};

static struct attribute *threshold_lvt_attrs[] = {
	&sensor_dev_attr_lvt_slow_low.dev_attr.attr,
	&sensor_dev_attr_lvt_medium_low.dev_attr.attr,
	&sensor_dev_attr_lvt_fast_low.dev_attr.attr,
	&sensor_dev_attr_lvt_slow_high.dev_attr.attr,
	&sensor_dev_attr_lvt_medium_high.dev_attr.attr,
	&sensor_dev_attr_lvt_fast_high.dev_attr.attr,
	NULL,
};

static struct attribute_group threshold_svt_attr_group = {
	.attrs = threshold_svt_attrs,
};

static struct attribute_group threshold_lvt_attr_group = {
	.attrs = threshold_lvt_attrs,
};

/*
 * internal functions
 */
static int32_t spd_mon_reg_init(struct spd_mon_ctrl *pctrl)
{
	struct device_node *node = pctrl->dev->of_node;
	const unsigned int *cnt;
	u32 thresholds_svt[THRESHOLD_SIZE];
	u32 thresholds_lvt[THRESHOLD_SIZE];
	size_t size = THRESHOLD_SIZE;
	int i;

	/* read from device tree */
	if (!of_property_read_u32_array(node, "lantiq,thresholds_svt",
			thresholds_svt, size)) {
		for (i = 0; i < THRESHOLD_SIZE; i++) {
			if (thresholds_svt[i] != 0) {
				switch (i) {
				case 0:
					spd_svt_s_low = thresholds_svt[i];
					break;
				case 1:
					spd_svt_s_high =
						thresholds_svt[i];
					break;
				case 2:
					spd_svt_m_low =
						thresholds_svt[i];
					break;
				case 3:
					spd_svt_m_high =
						thresholds_svt[i];
					break;
				case 4:
					spd_svt_f_low = thresholds_svt[i];
					break;
				case 5:
					spd_svt_f_high =
						thresholds_svt[i];
					break;
				}
			}
		}
	}

	if (!of_property_read_u32_array(node, "lantiq,thresholds_lvt",
			thresholds_lvt, size)) {
		for (i = 0; i < THRESHOLD_SIZE; i++) {
			if (thresholds_lvt[i] != 0) {
				switch (i) {
				case 0:
					spd_lvt_s_low = thresholds_lvt[i];
					break;
				case 1:
					spd_lvt_s_high =
						thresholds_lvt[i];
					break;
				case 2:
					spd_lvt_m_low =
						thresholds_lvt[i];
					break;
				case 3:
					spd_lvt_m_high =
						thresholds_lvt[i];
					break;
				case 4:
					spd_lvt_f_low = thresholds_lvt[i];
					break;
				case 5:
					spd_lvt_f_high =
						thresholds_lvt[i];
					break;
				}
			}
		}
	}

	cnt = of_get_property(node, "lantiq,sample_rate_svt", NULL);
	if (cnt) {
		spd_sample_rate_svt = *cnt & 0xFF;
		base_freq_svt = 250000 * spd_sample_rate_svt; /* kHz */
	}

	cnt = of_get_property(node, "lantiq,sample_rate_lvt", NULL);
	if (cnt) {
		spd_sample_rate_lvt = *cnt & 0xFF;
		base_freq_lvt = 250000 * spd_sample_rate_lvt; /* kHz */
	}

	return 0;
}

static enum spd_class_t spd_mon_get_fused_svt_spc(void)
{
	u32 val;

	val = ltq_fablotid_r32(SMON_FUSED);
	if ((val & SMON_FD) == 0)
		return UNDEF; /*not fused*/

	val &= SMON_SVT_M;
	return spd_svt_fused[val];
}

static enum spd_class_t spd_mon_get_fused_vddmin_spc(enum spd_class_t spc)
{
	u32 val;

	val = ltq_fuse_redund_2_r32(FUSE_REDUND_2);
	if ((val & VDDM_FUD) == 0)
		return UNDEF; /*not fused*/

	val &= VDD_MIN;
	if (chip_type == GRX350) {
		switch ((spc)) {
		case SLOW0:
			if (val == 0x1E)
				return SLOW1;
			else if (val == 0x19)
				return SLOW2;
			else
				return SLOW0;
			break;
		case MEDIUM0:
			if (val == 0x1E)
				return MEDIUM1;
			else if (val == 0x19)
				return MEDIUM2;
			else if (val == 0x0F)
				return MEDIUM3;
			else
				return MEDIUM0;
			break;
		case FAST0:
			if (val == 0x19)
				return FAST1;
			else if (val == 0x0F)
				return FAST2;
			else
				return FAST0;
			break;
		default:
			return SLOW0;
		}
	} else { /*GRX550*/
		switch ((spc)) {
		case MEDIUM0:
			if (val == 0x29)
				return MEDIUM1;
			else if (val == 0x1D)
				return MEDIUM2;
			else
				return MEDIUM0;
			break;
		case FAST0:
			if (val == 0x29)
				return FAST1;
			else if (val == 0x1D)
				return FAST2;
			else
				return FAST0;
			break;
		default:
			return MEDIUM0;
		}
	}
}

static int32_t spd_mon_set_sample_rate_svt(int32_t sample_rate)
{
	u32 value;
	struct spd_mon_ctrl *pctrl;

	pctrl = &ltq_spd_mon_ctrl;

	value = ltq_r32(pctrl->membase + SPD_MON_CON);

	mutex_lock(&spdmon_mutex);
	ltq_w32(((value & 0xFF000007) | ((sample_rate & 0xFF) << 16)),
		pctrl->membase + SPD_MON_CON);
	mutex_unlock(&spdmon_mutex);
	return 0;
}
EXPORT_SYMBOL(spd_mon_set_sample_rate_svt);

static int32_t spd_mon_set_sample_rate_lvt(int32_t sample_rate)
{
	u32 value;
	struct spd_mon_ctrl *pctrl;

	pctrl = &ltq_spd_mon_ctrl;

	value = ltq_r32(pctrl->membase + SPD_MON_CON);

	mutex_lock(&spdmon_mutex);
	ltq_w32(((value & 0x00FF0007) | ((sample_rate & 0xFF) << 24)),
		pctrl->membase + SPD_MON_CON);
	mutex_unlock(&spdmon_mutex);
	return 0;
}
EXPORT_SYMBOL(spd_mon_set_sample_rate_lvt);

static int32_t spd_mon_get_sample_rate_svt(void)
{
	struct spd_mon_ctrl *pctrl;
	u32 value;

	pctrl = &ltq_spd_mon_ctrl;
	value = ltq_r32(pctrl->membase + SPD_MON_CON);

	return (value >> 16) & 0xFF;
}

static int32_t spd_mon_get_sample_rate_lvt(void)
{
	struct spd_mon_ctrl *pctrl;
	u32 value;

	pctrl = &ltq_spd_mon_ctrl;
	value = ltq_r32(pctrl->membase + SPD_MON_CON);

	return (value >> 24) & 0xFF;
}

static int32_t spd_mon_get_channel(void)
{
	struct spd_mon_ctrl *pctrl;
	u32 value;

	pctrl = &ltq_spd_mon_ctrl;
	value = ltq_r32(pctrl->membase + SPD_MON_CON);

	return value & 0x03;
}

static int32_t spd_mon_sel_channel(int32_t channel)
{
	struct spd_mon_ctrl *pctrl;
	u32 value;

	pctrl = &ltq_spd_mon_ctrl;
	value = ltq_r32(pctrl->membase + SPD_MON_CON);
	mutex_lock(&spdmon_mutex);
	ltq_w32((value & 0xFFFF0004), pctrl->membase + SPD_MON_CON);
	value = ltq_r32(pctrl->membase + SPD_MON_CON);
	ltq_w32((value | (channel & 0x3)), pctrl->membase + SPD_MON_CON);
	mutex_unlock(&spdmon_mutex);

	return 0;
}
EXPORT_SYMBOL(spd_mon_sel_channel);

static int32_t spd_mon_set_threshold(u32 vt, u32 range,
	u32 threshold_low, u32 threshold_high)
{
	if (vt == 0) {
		if (range == 0) {
			spd_lvt_s_low = threshold_low;
			spd_lvt_s_high = threshold_high;
		} else if (range == 1) {
			spd_lvt_m_low = threshold_low;
			spd_lvt_m_high = threshold_high;
		} else if (range == 2) {
			spd_lvt_f_low = threshold_low;
			spd_lvt_f_high = threshold_high;
		}
	} else if (vt == 1) {
		if (range == 0) {
			spd_svt_s_low = threshold_low;
			spd_svt_s_high = threshold_high;
		} else if (range == 1) {
			spd_svt_m_low = threshold_low;
			spd_svt_m_high = threshold_high;
		} else if (range == 2) {
			spd_svt_f_low = threshold_low;
			spd_svt_f_high = threshold_high;
		}
	}
	return 0;
}
EXPORT_SYMBOL(spd_mon_set_threshold);

static void spd_mon_get_spd_data(void)
{
	u32 value, i;
	struct spd_mon_ctrl *pctrl = &ltq_spd_mon_ctrl;

	for (i = 0; i < LTQ_SPD_MON_CH_MAX; i++) {
		spd_mon_sel_channel(i);
		do {
			/* wait till toggle is 1 */
			value = ltq_r32(pctrl->membase + SPD_MON_SVT_DATA);
		} while ((value & 0x20000) != SPD_MON_DATA_TGL);
		spd_mon_data[i].svt = (value & 0xFFFF);
		do {
			/* wait till toggle is 1 */
			value = ltq_r32(pctrl->membase + SPD_MON_LVT_DATA);
		} while ((value & 0x20000) != SPD_MON_DATA_TGL);
		spd_mon_data[i].lvt = (value & 0xFFFF);
	}
}
EXPORT_SYMBOL(spd_mon_get_spd_data);

#if 0 /*I will keep this for later use*/
static enum spd_class_t spd_mon_get_speed_class(struct spd_cnt *smcl)
{
	u32 lvt_spd, svt_spd;

	spd_mon_get_spd_data();

	/* Compare the values for all channels and found the lowest value */
	if (spd_mon_data[0].lvt > spd_mon_data[1].lvt)
		lvt_spd = spd_mon_data[1].lvt;
	else
		lvt_spd = spd_mon_data[0].lvt;

	if (lvt_spd > spd_mon_data[2].lvt)
		lvt_spd = spd_mon_data[2].lvt;

	if (spd_mon_data[0].svt > spd_mon_data[1].svt)
		svt_spd = spd_mon_data[1].svt;
	else
		svt_spd = spd_mon_data[0].svt;

	if (svt_spd > spd_mon_data[2].svt)
		svt_spd = spd_mon_data[2].svt;

	/*Compare with threshold and Decide device class*/
	/*Device is fast if both LVT and SVT class are fast; */
	if ((lvt_spd > spd_lvt_f_low && lvt_spd < spd_lvt_f_high) &&
	    (svt_spd > spd_svt_f_low && svt_spd < spd_svt_f_high))
		return FAST; /* FAST DEVICE */

	/*Device is Medium if LVT class is fast
		or Med and SVT class is fast or Med;*/
	if ((lvt_spd > spd_lvt_m_low && lvt_spd < spd_lvt_f_high) &&
	    (svt_spd > spd_svt_m_low && svt_spd < spd_svt_f_high))
		return MEDIUM; /* MEDIUM DEVICE */

	if ((lvt_spd > spd_lvt_s_low && lvt_spd < spd_lvt_f_high) &&
	    (svt_spd > spd_svt_s_low && svt_spd < spd_svt_f_high))
		return SLOW; /* SLOW DEVICE */

	return UNDEF;
}
EXPORT_SYMBOL(spd_mon_get_speed_class);
#endif


static enum spd_class_t spd_mon_get_speed_class(struct spd_cnt *smcl)
{
	int i;
	enum spd_class_t spd_mon_res, smon_fused, spc, spc_vddmin;
	u32 svt_spd, slow = 0, med = 0, fast = 0;

	for (i = 0; i < 200; i++) {
		spd_mon_get_spd_data();

		/* build average from all 3 channels */
		svt_spd = spd_mon_data[0].svt;
		svt_spd += spd_mon_data[1].svt;
		svt_spd += spd_mon_data[2].svt;
		svt_spd /= 3;
		svt_spd = base_freq_svt / svt_spd; /*kHz conversion*/

		/*Compare with threshold and Decide device class*/
		/*Device is fast if SVT class are fast; */
		if ((svt_spd >= spd_svt_f_low) && (svt_spd <= spd_svt_f_high))
			fast++; /* FAST DEVICE */

		/*Device is Medium if SVT class is medium*/
		if ((svt_spd >= spd_svt_m_low) && (svt_spd <= spd_svt_m_high))
			med++; /* MEDIUM DEVICE */

		if ((svt_spd >= spd_svt_s_low) && (svt_spd <= spd_svt_s_high))
			slow++; /* SLOW DEVICE */

	}

	if (smcl != NULL) {
		smcl->fast = fast;
		smcl->medi = med;
		smcl->slow = slow;
	}

	spd_mon_res = UNDEF;
	if ((fast > med) && (fast > slow))
		spd_mon_res = FAST0;

	if ((med > fast) && (med > slow))
		spd_mon_res = MEDIUM0;

	if ((slow > fast) && (slow > med))
		spd_mon_res = SLOW0;

#if 0
	/*now check this SMON value against the fused SMON value*/
	smon_fused = spd_mon_get_fused_svt_spc();
	if ((smon_fused == spd_mon_res) || (smon_fused == UNDEF))
		spc = spd_mon_res;
	else if ((smon_fused == SLOW0) || (spd_mon_res == SLOW0))
		spc = SLOW0;
	else if ((smon_fused == MEDIUM0) || (spd_mon_res == MEDIUM0))
		spc = MEDIUM0;
	else
		spc = FAST0;
#endif
	/* we use only the fused values from now on */
	smon_fused = spd_mon_get_fused_svt_spc();
	if (smon_fused == UNDEF)
		spc = SLOW0;
	else
		spc = smon_fused;


	/*now check this device class against the fused Vddmin*/
	spc_vddmin = spd_mon_get_fused_vddmin_spc(spc);
	if (spc_vddmin == UNDEF)
		return spc;

	return spc_vddmin;
}
EXPORT_SYMBOL(spd_mon_get_speed_class);


static int spd_mon_open(struct inode *inode, struct file *file)
{
	return 0;
}

static long spd_mon_ioctl(struct file *file,	unsigned int cmd,
	unsigned long arg)
{
	int ret = 0;
	u32 data = 0x0;
	u32 offset = 0x0;
	struct spd_mon_ctrl *pctrl;
	u32 low = 0, high = 0;

	pctrl = &ltq_spd_mon_ctrl;

	switch (cmd) {
	case LTQ_SPD_MON_IOC_VERSION:
		data = SPD_MON_VERSION;
		put_user(data, (u32 __user *) (arg+0x4));
		break;
	case LTQ_SPD_MON_IOC_SET_SAMPLE_RATE_SVT:
		if (get_user(data, (u32 __user *) (arg+0x4)) == 0) {
			spd_mon_set_sample_rate_svt(data);
		} else {
			dev_err(pctrl->dev, "get 0x%x from user space\n",
				(unsigned int)arg);
			ret = -EINVAL;
		}
		break;
	case LTQ_SPD_MON_IOC_SET_SAMPLE_RATE_LVT:
		if (get_user(data, (u32 __user *) (arg+0x4)) == 0) {
			spd_mon_set_sample_rate_lvt(data);
		} else {
			dev_err(pctrl->dev, "get 0x%x from user space\n",
				(unsigned int)arg);
			ret = -EINVAL;
		}
		break;
	case LTQ_SPD_MON_IOC_SEL_CHANNEL:
		if (get_user(data, (u32 __user *) (arg+0x4)) == 0) {
			spd_mon_sel_channel(data);
		} else {
			dev_err(pctrl->dev, "get 0x%x from user space\n",
				(unsigned int)arg);
			ret = -EINVAL;
		}
		break;
	case LTQ_SPD_MON_IOC_SET_THRESHOLD:
		if (get_user(offset, (u32 __user *) arg) == 0) {
			if (get_user(data, (u32 __user *) (arg+0x4)) == 0) {
				/* set threshold */
				get_user(low, (u32 __user *) (arg+0x8));
				get_user(high, (u32 __user *) (arg+0xc));
				spd_mon_set_threshold(offset, data, low, high);
			} else {
				dev_err(pctrl->dev, "get 0x%x from user space\n",
					(unsigned int)arg);
				ret = -EINVAL;
			}
		} else {
			dev_err(pctrl->dev, "get 0x%x from user space\n",
				(unsigned int)arg);
			ret = -EINVAL;
		}
		break;
	case LTQ_SPD_MON_IOC_GET_SPD:
		data = spd_mon_get_speed_class(NULL);
		put_user(data, (u32 __user *) (arg+0x4));
		break;
	case LTQ_SPD_MON_IOC_READ:
		if (get_user(offset, (u32 __user *) arg) == 0) {
			/* check offset value */
			if (offset <= SPD_MON_LVT_DATA) {
				data = ltq_r32(pctrl->membase + offset);
				put_user(data, (u32 __user *) (arg+0x4));
			} else
				ret = -EINVAL;
		} else {
			dev_err(pctrl->dev, "get 0x%x from user space\n",
				(unsigned int)arg);
			ret = -EINVAL;
		}
		break;
	case LTQ_SPD_MON_IOC_WRITE:
		if (get_user(offset, (u32 __user *) arg) == 0) {
			if (get_user(data, (u32 __user *) (arg+0x4)) == 0) {
				if (offset <= SPD_MON_LVT_DATA)
					ltq_w32(data, pctrl->membase + offset);
				else
					ret = -EINVAL;
			} else
				ret = -EINVAL;
		} else {
			dev_err(pctrl->dev, "get 0x%x from user space\n",
				(unsigned int)arg);
			ret = -EINVAL;
		}
		break;
	}

	return ret;
}

static const struct file_operations spd_mon_fops = {
	.owner = THIS_MODULE,
	.open = spd_mon_open,
	.unlocked_ioctl = spd_mon_ioctl,
};

static int spd_mon_remove(struct platform_device *pdev)
{
	struct spd_mon_ctrl *pctrl = platform_get_drvdata(pdev);
	int i;

	hwmon_device_unregister(pctrl->hwmon_dev);
	for (i = 0; i < DEVICE_ATTR_NUM; i++)
		device_remove_file(&pdev->dev, &spdmon_attributes[i].dev_attr);

	if (threshold_svt_kobj) {
		sysfs_remove_group(threshold_svt_kobj,
			&threshold_svt_attr_group);
		kobject_put(threshold_svt_kobj);
	}

	if (threshold_lvt_kobj) {
		sysfs_remove_group(threshold_lvt_kobj,
			&threshold_lvt_attr_group);
		kobject_put(threshold_lvt_kobj);
	}

	dev_info(&pdev->dev, "spd_mon driver: Remove Done !!\n");

	return 0;
}

static int spd_mon_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct resource *res;
	int i;
	struct device *spd_mon_device = NULL;
	struct spd_mon_ctrl *pctrl = &ltq_spd_mon_ctrl;
	unsigned int chip_id = ltq_get_cpu_id();
	unsigned int chip_rev = ltq_get_soc_rev();
	/*struct spd_cnt smcl;*/

	threshold_svt_kobj = NULL;
	threshold_lvt_kobj = NULL;
	memset(pctrl, 0, sizeof(ltq_spd_mon_ctrl));
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		panic("Failed to get spd_mon resources\n");

	pctrl->phybase = res->start;
	pctrl->membase = devm_ioremap_resource(&pdev->dev, res);
	if (!pctrl->membase)
		panic("Failed to remap spd_mon resources\n");

	dev_info(&pdev->dev, "base address: 0x%x\t", (u32)pctrl->membase);
	dev_info(&pdev->dev, "PHY base address: 0x%x\n", pctrl->phybase);

	pctrl->dev = &pdev->dev;

	/* Link platform with driver data for retrieving */
	platform_set_drvdata(pdev, pctrl);

	/* register char dev */
	ret = alloc_chrdev_region(&dev_num, 0, 1, SPD_MON_NAME);
	if (ret < 0) {
		pr_err("spd_mon alloc_chrdev_region failed\n");
		return ret;
	} else
	pr_alert("device number :%d\n", MAJOR(dev_num));

	cl = class_create(THIS_MODULE, SPD_MON_NAME);
	if (IS_ERR(cl))  {
		pr_err("spd_mon Class Create failed\n");
		return -ENODEV;
	}

	spd_mon_device = device_create(cl, NULL /*no parent device*/, dev_num,
		NULL, SPD_MON_NAME"%d", MINOR(dev_num));
	if (IS_ERR(spd_mon_device)) {
		pr_err("spd_mon Device Registration failed\n");
		return -ENODEV;
	}
	cdev_init(&c_dev, &spd_mon_fops);

	ret = cdev_add(&c_dev, dev_num, 1);
	if (ret)
		pr_err("spd_mon Device addition failed\n");

	for (i = 0; i < DEVICE_ATTR_NUM; i++) {
		ret = device_create_file(&pdev->dev,
			&spdmon_attributes[i].dev_attr);
		if (ret) {
			dev_err(&pdev->dev, "device_create_file failed.\n");
			goto out_err;
		}
	}

	threshold_svt_kobj = kobject_create_and_add
		("threshold_svt", &pdev->dev.kobj);
	if (!threshold_svt_kobj) {
		dev_err(&pdev->dev, "kobject_create_and_add failed.\n");
		kobject_put(threshold_svt_kobj);
	} else {
		/* Create the files associated with this kobject */
		ret = sysfs_create_group(threshold_svt_kobj,
			&threshold_svt_attr_group);
		if (ret)
			dev_err(&pdev->dev, "sysfs_create_group failed.\n");
	}

	threshold_lvt_kobj = kobject_create_and_add("threshold_lvt",
		&pdev->dev.kobj);
	if (!threshold_lvt_kobj) {
		dev_err(&pdev->dev, "kobject_create_and_add failed.\n");
		kobject_put(threshold_lvt_kobj);
	} else {
		/* Create the files associated with this kobject */
		ret = sysfs_create_group(threshold_lvt_kobj,
			&threshold_lvt_attr_group);
		if (ret)
			dev_err(&pdev->dev, "sysfs_create_group failed.\n");
	}

	pctrl->hwmon_dev = hwmon_device_register(&pdev->dev);
	if (IS_ERR(pctrl->hwmon_dev)) {
		dev_err(&pdev->dev, "hwmon_device_register failed.\n");
		goto out_err;
	}

	spd_mon_reg_init(pctrl);
	mutex_init(&spdmon_mutex);	/* called to init mutex */
	spd_mon_set_sample_rate_svt(spd_sample_rate_svt);
	spd_mon_set_sample_rate_lvt(spd_sample_rate_lvt);

	dev_info(pctrl->dev, "spd_mon driver : init done !!\n");

	/*
	pr_alert("speed_class=%s ", spc[spd_mon_get_speed_class(&smcl)]);
	pr_alert("slow=%d, med=%d, fast=%d\n", smcl.slow, smcl.medi, smcl.fast);
	*/

	if (chip_rev == 1) { /*V1.1*/
		chip_type = GRX350;
	} else {
		switch (chip_id) {
		case 0x20:
		case 0x26:
		       chip_type = GRX350;
		       break;
		case 0x24:
		case 0x25:
		       chip_type = GRX550;
		       break;
		default:
		       chip_type = GRX350;
		       break;
		}
	}
	ltq_grx500_set_speed_grade(spd_mon_get_speed_class(NULL));

	return 0;

out_err:
	for (i--; i >= 0; i--)
		device_remove_file(&pdev->dev, &spdmon_attributes[i].dev_attr);

	return -ENODEV;
}

static const struct of_device_id spd_mon_xrx500_match[] = {
	{ .compatible = "lantiq,speedm-xrx500" },
	{},
};

static struct platform_driver spd_mon_driver = {
	.remove     = spd_mon_remove,
	.probe      = spd_mon_probe,
	.driver = {
		.name   = "spdmon",
		.owner = THIS_MODULE,
		.of_match_table = spd_mon_xrx500_match,
	},
};

static int __init spd_mon_init(void)
{
	int rc;

	pr_alert("try to register spd_mon driver");

	rc = platform_driver_register(&spd_mon_driver);
	if (!rc)
		pr_alert("spd_mon driver registered\n");

	return rc;
}
subsys_initcall(spd_mon_init);

static void __exit spd_mon_exit(void)
{
	cdev_del(&c_dev);
	device_destroy(cl, dev_num);
	class_destroy(cl);
	unregister_chrdev_region(dev_num, 1);
	platform_driver_unregister(&spd_mon_driver);
}

module_exit(spd_mon_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Speed Mon driver");
MODULE_AUTHOR("lantiq");
MODULE_ALIAS("platform : spdmon");

