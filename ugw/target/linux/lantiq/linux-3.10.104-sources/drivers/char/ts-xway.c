/******************************************************************************
**
** FILE NAME    : ts-xway.c
** PROJECT      : 
** MODULES      : Thermal Sensor
**
** DATE         : 04 April 2014
** AUTHOR       : Kavitha Subramanian
** DESCRIPTION  : Thermal Sensor driver source file
** COPYRIGHT    :       Copyright (c) 2014
**
**    This program is free software; you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation; either version 2 of the License, or
**    (at your option) any later version.
**
*******************************************************************************/

/*
 * ####################################
 *              Head File
 * ####################################
 */

/*
 *  Common Head File
 */
#include <linux/err.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#include <linux/of_platform.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <lantiq_soc.h>

#define LTQ_GPHY1_CFG               0x40
#define LTQ_TS_MAJOR 0
#define ltq_ts_w32_mask(clear, set, reg) \
                ltq_cgu_w32((ltq_cgu_r32( reg) & ~(clear)) | (set), \
                 reg)
//#define INT_NUM_IM3_IRL19           (INT_NUM_IM3_IRL0 + 19)


struct xway_ts {
        void __iomem *virt;
		unsigned int irq;

};
struct xway_ts g_ts;
/*
 * ####################################
 *             Declaration
 * ####################################
 */

/*
 *  File Operations
 */
static int ts_open(struct inode *, struct file *);
static int ts_release(struct inode *, struct file *);

static int ts_temp_proc_open(struct inode *inode, struct file *file);

static const struct file_operations ts_temp_proc_fops = {
	.open = ts_temp_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release,
};

/*
 *  Interrupt Handler
 */
static irqreturn_t ts_irq_handler(int, void *);

/*
 *  Proc File Functions
 */
static int proc_file_create(void);
static void proc_file_delete(void);
static int proc_read_temp(struct seq_file *s, void *);

/*
 *  Init Help Functions
 */
static int print_temp(char *);

/*
 * ####################################
 *            Local Variable
 * ####################################
 */

//static int g_temp_read_enable = 0;

static int g_ts_major;
static struct file_operations g_ts_fops = {
	.owner      = THIS_MODULE,
	.open       = ts_open,
	.release    = ts_release,
};


static struct proc_dir_entry* g_proc_dir = NULL;

/*
 * ####################################
 *            Local Function
 * ####################################
 */

static int ts_open(struct inode *inode, struct file *filep)
{
    return 0;
}

static int ts_release(struct inode *inode, struct file *filep)
{
    return 0;
}

#if 0
static int ts_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
    int retval = 0;

    printk(KERN_ERR "IOCTL: Undefined IOCTL call!\n");
    retval = -EACCES;

    return retval;
}
#endif

static irqreturn_t ts_irq_handler(int irq, void *dev_id)
{
    char str[16];

    print_temp(str);
    printk("Chip is over heated (%s)!", str);
    return IRQ_HANDLED;
}

static int ts_temp_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_read_temp, NULL);
}

static  int proc_file_create(void)
{
    struct proc_dir_entry *entry;

    g_proc_dir = proc_mkdir("driver/ltq_ts", NULL);

    if (!g_proc_dir)
	return -ENOMEM;

    entry = proc_create("temp", 0,
			g_proc_dir, &ts_temp_proc_fops);

    if (!entry)
    {
	remove_proc_entry("driver/ltq_ts", NULL);
	return -ENOMEM;
    }
    return 0;
}

static  void proc_file_delete(void)
{
    remove_proc_entry("temp", g_proc_dir);
    remove_proc_entry("driver/ltq_ts", NULL);
}


static int proc_read_temp(struct seq_file *s, void *v)
{
    int temp_value = 0;
    int fraction;

    if ( ltq_ts_get_temp(&temp_value) == 0 ) {
	seq_printf (s, "Chip Temparature:  ");
        if (temp_value < 0 ) {
            temp_value = -temp_value;
	    seq_printf (s, "%c", '-');
        }
	seq_printf (s, "%d", temp_value/10);
        if ( (fraction = temp_value % 10) != 0 )
            seq_printf(s, ".%d\r\n", fraction);
	else
            seq_printf(s, "\r\n");
    } else
        seq_printf (s, "Failed to read temperature info!\n");

    return 0;
}


static  int print_temp(char *buf)
{
    int len = 0;
    int temp_value = 0;
    int fraction;

    if ( ltq_ts_get_temp(&temp_value) == 0 ) {
        if ( temp_value < 0 ) {
            len += sprintf(buf + len, "=");
            temp_value = -temp_value;
        }
        len += sprintf(buf + len, "%d", temp_value / 10);
        if ( (fraction = temp_value % 10) != 0 )
            len += sprintf(buf + len, ".%d", fraction);
        len += sprintf(buf + len, "\n");
    }
    else
        len += sprintf(buf + len, "Failed in reading temperature info!\n");

    return len;
}



/*
 * ####################################
 *           Global Function
 * ####################################
 */

int ltq_ts_get_temp(int *p_temp)
{
    int temp_value;
    if ( p_temp == NULL )
        return -EINVAL;

    //  value x 5 = (Celsius Degree + 38) x 10
    temp_value = (ltq_cgu_r32( LTQ_GPHY1_CFG ) >> 9) & 0x01FF;
    *p_temp = (int)((temp_value << 2) + temp_value);
    *p_temp -= 380;

#ifdef AIKAN_CALC
    //  value x 5 = (Celsius Degree + 38) x 10
    temp_value = (ltq_cgu_r32( LTQ_GPHY1_CFG ) >> 9) & 0x01FF;
   // printk("reg value: 0x%x\r\n", temp_value);
     i = temp_value & 0x1;
     temp_value = (temp_value >> 1) - 38;
     if(temp_value < 0) 
     {    
           temp_value = temp_value +i;
           if(temp_value == 0) printk("-");
     }
     //printk("\nTEMP\t\t: %d",temp_value);
     //if(i==1) printk(".5C\n");
     //else printk(".0C\n");
     *p_temp = temp_value;
#endif
    return 0;
}
EXPORT_SYMBOL(ltq_ts_get_temp);




static int ts_xway_probe(struct platform_device *pdev)
{
	int ret = 0;
	unsigned int chipid;
	unsigned int partnum;
        struct resource irqres;
	struct device_node *node = pdev->dev.of_node;

	chipid = *((volatile uint32_t *)LTQ_MPS_CHIPID);
	partnum = (chipid & 0x0FFFF000) >> 12;
	if (partnum != 0xB) {
		dev_err(&pdev->dev, "temp sensor not supported in this chip !!");
		return -ENODEV;
	}

	if (proc_file_create() < 0)
	{
		dev_err(&pdev->dev, "proc file create failed!!");
		return -ENOMEM;
	}
	
	#if 1 
	ret = register_chrdev(LTQ_TS_MAJOR, "ltq_ts", &g_ts_fops);
	#if LTQ_TS_MAJOR == 0
	g_ts_major = ret;
	#else
	g_ts_major = LTQ_TS_MAJOR;
	#endif
	if ( ret < 0 ) {
		printk("Can not register thermal sensor device - %d", ret);
		return ret;
	}
	#endif

	ret = of_irq_to_resource_table(node, &irqres, 1);
	if (ret != 1) {
                dev_err(&pdev->dev,
                        "failed to get irq for temp sensor\n");
                return -ENODEV;
	}
	g_ts.irq = irqres.start;

	ltq_ts_w32_mask(0, 0x00080000, LTQ_GPHY1_CFG);    //  turn on Thermal Sensor

	ret = request_irq(g_ts.irq, ts_irq_handler, IRQF_DISABLED, "ts_isr", NULL);
	if ( ret ) {
		printk("Can not get IRQ - %d", ret);
		unregister_chrdev(g_ts_major, "ltq_ts");
		return ret;
	}

	printk(KERN_INFO "%s", "Temperature Sensor: Init Done !!");
	return 0;


}

static int  ts_xway_release(struct platform_device *pdev)
{
	proc_file_delete();

	free_irq(g_ts.irq, NULL);

	ltq_ts_w32_mask(0, 0x00080000, LTQ_GPHY1_CFG);    //  turn off Thermal Sensor

	#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,32)
	if ( unregister_chrdev(g_ts_major, "ltq_ts") ) {
	err("Can not unregister TS device (major %d)!", g_ts_major);
	}
	#else
	unregister_chrdev(g_ts_major, "ltq_ts");
	#endif
	return 0;
}


static const struct of_device_id ts_xway_match[] = {
        { .compatible = "lantiq,ts-xway" },
        {},
};

static struct platform_driver ts_xway_driver = {
        .probe = ts_xway_probe,
		.remove = ts_xway_release,
        .driver = {
                .name = "ts-xway",
                .owner = THIS_MODULE,
                .of_match_table = ts_xway_match,
        },
};

module_platform_driver(ts_xway_driver);
                                                               
