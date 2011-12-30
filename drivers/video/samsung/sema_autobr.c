/*  Semaphore Auto Brightness driver
 *  for Samsung Galaxy S I9000
 *  
 *   Copyright (c) 2011-2012 stratosk@semaphore.gr
 *   
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>	
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <linux/device.h>


#define AUTOBR_WORK_QUEUE_NAME "kautobr"

extern int ls_get_adcvalue(void);
extern int bl_update_brightness(int bl);
extern void block_bl_update(void);
extern void unblock_bl_update(void);

static void autobr_handler(struct work_struct *w);

static struct workqueue_struct *wq=0;

static DECLARE_DELAYED_WORK(autobr_wq, autobr_handler);

static int min_brightness = 15;
static int max_brightness = 255;
static int instant_update_thres = 30;	/* the difference threshold that we have to update instantly */
static int max_lux = 2900;		/* max value from the light sensor */
static int effect_delay_ms = 0;		/* delay between step for the fade effect */


static int current_br = 150;	/* holds the current brighntess */
static int update_br;		/* the brighness value that we have to reach */
static int sum_update_br;	/* the sum of samples */
static int cnt = 0;
static int delay;


/* sysfs */
static ssize_t show_min_brightness(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", min_brightness);
}

static ssize_t store_min_brightness(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	int input;
	int ret;
	
	ret = sscanf(buf, "%u", &input);
	if (ret != 1 || input < 1 || input > 255 || input > max_brightness) {
		return -EINVAL;
	}
	
	min_brightness = input;

	return size;
}
 
static ssize_t show_max_brightness(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", max_brightness);
}

static ssize_t store_max_brightness(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	int input;
	int ret;
	
	ret = sscanf(buf, "%u", &input);
	if (ret != 1 || input < 1 || input > 255 || input < min_brightness) {
		return -EINVAL;
	}
	
	max_brightness = input;

	return size;
}

static ssize_t show_instant_update_thres(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", instant_update_thres);
}

static ssize_t store_instant_update_thres(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	int input;
	int ret;
	
	ret = sscanf(buf, "%u", &input);
	if (ret != 1 || input < 1 || input > 100) {
		return -EINVAL;
	}
	
	instant_update_thres = input;

	return size;
}

static ssize_t show_max_lux(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", max_lux);
}

static ssize_t store_max_lux(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	int input;
	int ret;
	
	ret = sscanf(buf, "%u", &input);
	if (ret != 1 || input < 1 || input > 3000) {
		return -EINVAL;
	}
	
	max_lux = input;

	return size;
}

static ssize_t show_effect_delay_ms(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%i\n", effect_delay_ms);
}

static ssize_t store_effect_delay_ms(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	int input;
	int ret;
	
	ret = sscanf(buf, "%i", &input);
	if (ret != 1 || input < -1 || input > 10) {
		return -EINVAL;
	}
	
	effect_delay_ms = input;

	return size;
}

static DEVICE_ATTR(min_brightness, S_IRUGO | S_IWUGO , show_min_brightness, store_min_brightness);
static DEVICE_ATTR(max_brightness, S_IRUGO | S_IWUGO , show_max_brightness, store_max_brightness);
static DEVICE_ATTR(instant_update_thres, S_IRUGO | S_IWUGO , show_instant_update_thres, store_instant_update_thres);
static DEVICE_ATTR(max_lux, S_IRUGO | S_IWUGO , show_max_lux, store_max_lux);
static DEVICE_ATTR(effect_delay_ms, S_IRUGO | S_IWUGO , show_effect_delay_ms, store_effect_delay_ms);
 
static struct attribute *sema_autobr_attributes[] = {
	&dev_attr_min_brightness.attr,
	&dev_attr_max_brightness.attr,
	&dev_attr_instant_update_thres.attr,
	&dev_attr_max_lux.attr,
	&dev_attr_effect_delay_ms.attr,
	NULL
};

static struct attribute_group sema_autobr_group = {
	.attrs  = sema_autobr_attributes,
};

static struct miscdevice sema_autobr_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "sema_autobr",
};
/* sysfs end */

static void autobr_handler(struct work_struct *w)
{
	int ret, diff;
	
	/* Get the adc value from light sensor and normalize it to 0 - max_brightness scale */
	sum_update_br += ls_get_adcvalue() * max_brightness / max_lux;
	
	cnt++;
	
	/* Get the average after 5 samples and only then adjust the brightness */
	if (cnt == 5) {
		update_br = sum_update_br / 5;
		
		/* cap the update brightness within the limits */
		if (update_br < min_brightness)
			update_br = min_brightness;
		if (update_br > max_brightness)
			update_br = max_brightness;
		
		/* the difference between current and update brightness */
		diff = abs(current_br - update_br);
		
		if ((diff > 1) && (diff <= instant_update_thres)) {
		  
			/* we have to update step by step */
			(current_br < update_br) ? ++current_br : --current_br; 
			
			ret = bl_update_brightness(current_br);
		}
		else if (diff > instant_update_thres) {	/* immediately update */
			
			if (current_br < update_br) {
				if (effect_delay_ms >= 0) {
				    while (current_br++ < update_br) {	/* fade in */
					    ret = bl_update_brightness(current_br);
					    msleep(effect_delay_ms);
				    }
				}
				else {
				    current_br = update_br;
				    ret = bl_update_brightness(current_br);
				}
			}
			else {
				if (effect_delay_ms >= 0) {
				    while (current_br-- > update_br) {	/* fade out */
					    ret = bl_update_brightness(current_br);
					    msleep(effect_delay_ms);
				    }			  
				}
				else {
				    current_br = update_br;
				    ret = bl_update_brightness(current_br);
				}
			}
			
		}
		else
			current_br = update_br;
		
		/* reset counters */
		sum_update_br = 0;
		cnt = 0;
	}
	
	
	queue_delayed_work(wq, &autobr_wq, delay);
}

static int autobr_init(void)
{
	
	misc_register(&sema_autobr_device);
	if (sysfs_create_group(&sema_autobr_device.this_device->kobj, &sema_autobr_group) < 0)
	{
		printk("%s sysfs_create_group fail\n", __FUNCTION__);
		pr_err("Failed to create sysfs group for device (%s)!\n", sema_autobr_device.name);
	}  
  
  
	delay = usecs_to_jiffies(400000); 	/* check every 0.4s */
	
	if (!wq)
                wq = create_workqueue(AUTOBR_WORK_QUEUE_NAME);
	
	if (wq)
		queue_delayed_work(wq, &autobr_wq, delay);

	block_bl_update();
		
	printk(KERN_INFO "Semaphore Auto Brightness enabled\n");
	
	return 0;
}

static void autobr_exit(void)
{
	misc_deregister(&sema_autobr_device);
	
	if (wq) {
		cancel_delayed_work(&autobr_wq);	/* no "new ones" */
		flush_workqueue(wq);
		destroy_workqueue(wq);
	}

	unblock_bl_update();
	
	printk(KERN_INFO "Semaphore Auto Brightness disabled\n");
}

module_init(autobr_init);
module_exit(autobr_exit);

MODULE_AUTHOR("stratosk@semaphore.gr");
MODULE_DESCRIPTION("Semaphore Auto Brightness driver");
MODULE_LICENSE("GPL");