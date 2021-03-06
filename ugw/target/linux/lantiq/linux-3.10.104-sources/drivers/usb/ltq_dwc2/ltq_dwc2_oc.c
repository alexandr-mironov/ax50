/*
 * Copyright (C) 2015 LANTIQ Semiconductor Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/usb/otg.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/gpio.h>
#include <linux/of_address.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>

#define SECOND_TIME_DELAY 30

struct ltq_usb_oc {
	struct workqueue_struct *workq;
	struct delayed_work oc_recover_w;
	struct device	*dev;
	unsigned int irqnum;
	int oc_gpio;
};

int oc_gpio_init(struct platform_device *_dev, int gpio)
{
	int err;

	dev_dbg(&_dev->dev, "oc_gpio_init, gpio %d\n", gpio);

	err = gpio_is_valid(gpio);
	if (!err)
	{
		dev_dbg(&_dev->dev, "%s: gpio pin %d is invalid\n", __func__, gpio);
		return -EINVAL;
	}

	err = gpio_request(gpio, "oc_gpio");
	if (err)
	{
		dev_dbg(&_dev->dev, "%s: can't request gpio %d\n", __func__, gpio);
		return -EINVAL;
	}
	gpio_direction_output(gpio, 1);

	return 0;
}

int oc_gpio_deinit(struct platform_device *_dev, int gpio)
{
	int err;

	dev_dbg(&_dev->dev, "oc_gpio_deinit, gpio %d\n", gpio);

	err = gpio_is_valid(gpio);
	if (!err)
	{
		dev_dbg(&_dev->dev, "%s: gpio pin %d is invalid\n", __func__, gpio);
		return -EINVAL;
	}

	gpio_free(gpio);

	return 0;
}


void ltq_usb_oc_recovery_worker(struct work_struct *work)  
{
	struct ltq_usb_oc *usb_oc = container_of(work, \
		struct ltq_usb_oc, oc_recover_w.work);

	dev_dbg(usb_oc->dev, "+ltq_usb_oc_recovery_worker: enter, to enable power switch\n");

	gpio_direction_output(usb_oc->oc_gpio, 1);

	dev_dbg(usb_oc->dev, "-ltq_usb_oc_recovery_worker: return\n");
}

static irqreturn_t ltq_usb_oc_irq (int irq, void * _usb_oc)
{
	struct ltq_usb_oc *usb_oc = _usb_oc;

	dev_dbg(usb_oc->dev, "+ltq_usb_oc_irq: enter, to disable power switch\n");

	gpio_direction_output(usb_oc->oc_gpio, 0);

	queue_delayed_work(usb_oc->workq, \
		&usb_oc->oc_recover_w, SECOND_TIME_DELAY*HZ);
	
	dev_dbg(usb_oc->dev, "-ltq_usb_oc_irq: return\n");

	return IRQ_HANDLED;
}

static int ltq_usb_oc_probe(struct platform_device *pdev)
{
	struct ltq_usb_oc *usb_oc;
	struct device *dev = &pdev->dev;
	int ret, irq;
	int oc_gpio = 0;
	struct device_node	*oc_node = pdev->dev.of_node;

	dev_dbg(dev, "ltq_usb_oc_probe(%p)\n", pdev);

	usb_oc = devm_kzalloc(dev, sizeof(*usb_oc), GFP_KERNEL);
	if (!usb_oc)
		return -ENOMEM;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "missing IRQ resource\n");
		return -EINVAL;
	}

	printk("%s: USB OC irq %d\n", __func__, irq);

	oc_gpio = of_get_named_gpio(oc_node, "overcurrent-gpio", 0);
	if (oc_gpio < 0)
	{
		/* ENOENT means no gpio is deined for over-current control	*/
		if (oc_gpio != -ENOENT)
		{
			/* vbus is defined in device tree but something's wrong */
			dev_err(&pdev->dev, "Failed to get vbus-gpio, errno %d\n", oc_gpio);
			return -ENODEV;
		}
	}
	
	printk("%s: USB OC overcurrent-gpio %d\n", __func__, oc_gpio);

	usb_oc->dev = dev;
	usb_oc->irqnum = irq;
	usb_oc->oc_gpio = oc_gpio;
	platform_set_drvdata(pdev, usb_oc);

	oc_gpio_init(pdev, usb_oc->oc_gpio);

	dev_dbg(dev, "creat workqueue\n");

	usb_oc->workq = create_singlethread_workqueue("ltq_dwc2 usb oc wq");
	if (!usb_oc->workq) {
		dev_err(dev, "create_singlethread_workqueue() failed\n");
		return -ENOMEM;
	}
	INIT_DELAYED_WORK(&usb_oc->oc_recover_w, ltq_usb_oc_recovery_worker);

	dev_dbg(dev, "request irq %d\n", usb_oc->irqnum);

	ret = devm_request_irq(dev, usb_oc->irqnum, &ltq_usb_oc_irq, \
		IRQF_SHARED, dev_name(dev), usb_oc);

	if (ret) {
		dev_err(dev, "failed to request IRQ #%d --> %d\n",
			usb_oc->irqnum, ret);
		return ret;
	}

	irq_set_irq_type(usb_oc->irqnum, IRQ_TYPE_EDGE_FALLING);

	printk("%s: USB OCP is running\n", __func__);

	return 0;
}

static int ltq_usb_oc_remove(struct platform_device *pdev)
{
	struct ltq_usb_oc *usb_oc = platform_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "ltq_usb_oc_remove(%p)\n", pdev);

	flush_workqueue(usb_oc->workq);
	destroy_workqueue(usb_oc->workq);
	devm_free_irq(usb_oc->dev, usb_oc->irqnum, usb_oc);
	devm_kfree(usb_oc->dev, usb_oc);
	oc_gpio_deinit(pdev, usb_oc->oc_gpio);
	return 0;
}

static const struct of_device_id of_ltq_usb_oc_match[] = {
	{
		.compatible = "lantiq,usb-oc"
	},
	{ },
};
MODULE_DEVICE_TABLE(of, of_ltq_usb_oc_match);

static struct platform_driver ltq_usb_oc_driver = {
	.probe          = ltq_usb_oc_probe,
	.remove         = ltq_usb_oc_remove,
	.driver         = {
		.name   = "ltq-usb-oc",
		.owner  = THIS_MODULE,
		.pm = NULL,
		.of_match_table	= of_match_ptr(of_ltq_usb_oc_match),
	},
};

module_platform_driver(ltq_usb_oc_driver);
MODULE_LICENSE("GPL v2");