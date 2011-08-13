/* drivers/input/keyboard/s3c-keypad.c
 *
 * Driver core for Samsung SoC onboard UARTs.
 *
 * Kim Kyoungil, Copyright (c) 2006-2009 Samsung Electronics
 *      http://www.samsungsemi.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/clk.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/i2c.h>


#include "../../staging/android/timed_output.h"

#include <linux/io.h>
#include <mach/hardware.h>
#include <asm/delay.h>
#include <asm/irq.h>

#include <mach/regs-gpio.h>
#include <mach/gpio.h>
#include <mach/gpio-aries.h>

#include <plat/gpio-cfg.h>
#include <plat/regs-keypad.h>
#ifdef CONFIG_CPU_FREQ
#include <mach/cpu-freq-v210.h>
#endif
 
#include "s3c-keypad.h"

#define USE_PERF_LEVEL_KEYPAD 1 
#undef S3C_KEYPAD_DEBUG 

#ifdef S3C_KEYPAD_DEBUG
#define DPRINTK(x...) printk("S3C-Keypad " x)
#else
#define DPRINTK(x...)		/* !!!! */
#endif

#define DEVICE_NAME "s3c-keypad"

#define TRUE 1
#define FALSE 0
#define	SUBJECT	"s3c_keypad.c"
#define P(format,...)\
    printk ("[ "SUBJECT " (%s,%d) ] " format "\n", __func__, __LINE__, ## __VA_ARGS__);
#define FI \
    printk ("[ "SUBJECT " (%s,%d) ] " "%s - IN" "\n", __func__, __LINE__, __func__);
#define FO \
    printk ("[ "SUBJECT " (%s,%d) ] " "%s - OUT" "\n", __func__, __LINE__, __func__);

#define FLASH_MOVIE_MODE

static struct timer_list keypad_timer;
static int is_timer_on = FALSE;
static struct clk *keypad_clock;


static u32 keymask[KEYPAD_COLUMNS];
static u32 prevmask[KEYPAD_COLUMNS];


static int s3c_keygpio_isr_setup(void *pdev)
{

}

static ssize_t keyshort_test(struct device *dev, struct device_attribute *attr, char *buf)
{
	int count;
	
	if(!gpio_get_value(GPIO_KBR1) || !gpio_get_value(GPIO_KBR2) || !gpio_get_value(GPIO_nPOWER)  || !gpio_get_value(S5PV210_GPH3(5)))
	{
		count = sprintf(buf,"PRESS\n");
              printk("keyshort_test: PRESS\n");
	}
	else
	{
		count = sprintf(buf,"RELEASE\n");
              printk("keyshort_test: RELEASE\n");
	}	

	return count;
}
static DEVICE_ATTR(key_pressed, 0664, keyshort_test, NULL);

#ifdef FLASH_MOVIE_MODE

#define CAM_FLASH_EN                    S5PV210_GPJ1(2)
#define CAM_FLASH_EN_SET                S5PV210_GPJ1(0)
#define CAM_FLASH_EN_STR                "GPJ12"
#define CAM_FLASH_EN_SET_STR    	"GPJ10"


#define OFF             0
#define ON              1

#define MOVIE_MODE_CURRENT                      17
#define FLASH_SAFETY_TIMER                      18
#define MOVIE_MODE_CONFIG                       19
#define FLASH_TO_MOVIE_RATIO                    20

#define MOVIE_MODE_CURRENT_71                   4
#define MOVIE_MODE_CURRENT_63                   5
#define MOVIE_MODE_CURRENT_56                   6

#define OFFSET_CAM_FLASH                (0x1 << 9)
/*
 * timed_output for movie mode flash
 */
static struct hrtimer timer;

static int max_timeout = 5000;
static int flash_value = 0;

/*
 * IFLOUTA = IFLOUTB = 81K / 160K * A = 500mA
 * T = 7.98s / uF * Ct(uF) = 7.98s / uF * 0.1uF = 0.798s 
 */
//extern void s3c_bat_set_compensation_for_drv(int mode,int offset);

static void aat1271a_flash_write(int addr, int data)
{
        int i;

        for (i = 0; i < addr; i++) {
                gpio_set_value(CAM_FLASH_EN_SET, GPIO_LEVEL_LOW);
                udelay(10);
                gpio_set_value(CAM_FLASH_EN_SET, GPIO_LEVEL_HIGH);
                udelay(50);
        }

        udelay(500);

        for (i = 0; i < data; i++) {
                gpio_set_value(CAM_FLASH_EN_SET, GPIO_LEVEL_LOW);
                udelay(10);
                gpio_set_value(CAM_FLASH_EN_SET, GPIO_LEVEL_HIGH);
                udelay(50);
        }

        udelay(500);
}

void aat1271a_falsh_camera_control(int ctrl)
{
        if (ctrl) {
                /* Movie Mode Off */
                gpio_set_value(CAM_FLASH_EN_SET, GPIO_LEVEL_LOW);
                gpio_set_value(CAM_FLASH_EN, GPIO_LEVEL_LOW);
                udelay(10);
                /* Falsh Mode On */
                gpio_set_value(CAM_FLASH_EN, GPIO_LEVEL_HIGH);
                //s3c_bat_set_compensation_for_drv(1,OFFSET_CAM_FLASH);

        }
        else {
                /* Movie Mode Off */
                gpio_set_value(CAM_FLASH_EN_SET, GPIO_LEVEL_LOW);
                /* Falsh Mode Off */
                gpio_set_value(CAM_FLASH_EN, GPIO_LEVEL_LOW);
                //s3c_bat_set_compensation_for_drv(0,OFFSET_CAM_FLASH);
        }
}

/*
 * IMOVIEMODE = IFLOUTA / 7.3 = 500mA / 7.3 = 68mA
 * 45mA / 68mA = 0.66 = 0.7 = 70 %
 */

void aat1271a_falsh_movie_control(int ctrl)
{
        if (ctrl) {

                /* Falsh Mode Off */
                gpio_set_value(CAM_FLASH_EN, GPIO_LEVEL_LOW);
                /* Movie Mode Current Setting & On */
                aat1271a_flash_write(MOVIE_MODE_CURRENT, MOVIE_MODE_CURRENT_63);
                //s3c_bat_set_compensation_for_drv(1,OFFSET_CAM_FLASH);
        } 
        else {
                /* Falsh Mode Off */
                gpio_set_value(CAM_FLASH_EN, GPIO_LEVEL_LOW);
                /* Movie Mode Off */
                gpio_set_value(CAM_FLASH_EN_SET, GPIO_LEVEL_LOW);
                //s3c_bat_set_compensation_for_drv(0,OFFSET_CAM_FLASH);
        }
}

static enum hrtimer_restart aat1271_flash_timer_func(struct hrtimer *timer)
{
        /* Movie Mode Off */
        gpio_set_value(CAM_FLASH_EN_SET, GPIO_LEVEL_LOW);
        /* Falsh Mode Off */
        gpio_set_value(CAM_FLASH_EN, GPIO_LEVEL_LOW);

        return HRTIMER_NORESTART;
}

static int get_time_for_flash(struct timed_output_dev *dev)
{
        int remaining;

        if (hrtimer_active(&timer)) {
                ktime_t r = hrtimer_get_remaining(&timer);
                remaining = r.tv.sec * 1000 + r.tv.nsec / 1000000;
        } else
                remaining = 0;

        if (flash_value ==-1)
                remaining = -1;

        return remaining;

}

static void enable_flash_from_user(struct timed_output_dev *dev,int value)
{
	int err;

        if (value > 0) {
                if (value < 780) {       /* Flash Mode */
					gpio_direction_output(CAM_FLASH_EN, 0);
                    gpio_direction_output(CAM_FLASH_EN_SET, 0);

                    aat1271a_falsh_camera_control(ON);
                    printk("flash test: FLASH MODE\n");
               }
                else {   /* Movie Mode */
                	gpio_direction_output(CAM_FLASH_EN, 0);
                    gpio_direction_output(CAM_FLASH_EN_SET, 0);

                    aat1271a_falsh_movie_control(ON);
                    printk("flash test: MOVIE MODE\n");
               }
        } else if (value == 0) {
        	gpio_direction_output(CAM_FLASH_EN, 0);
            gpio_direction_output(CAM_FLASH_EN_SET, 0);

            aat1271a_falsh_camera_control(OFF);
            aat1271a_falsh_movie_control(OFF);
            printk("flash test: Flash OFF\n");
       }

}

static struct timed_output_dev timed_output_flash= {
        .name     = "flash",
        .get_time = get_time_for_flash,
        .enable   = enable_flash_from_user,
};

#endif

static int __init s3c_keypad_probe(struct platform_device *pdev)
{
	int ret;
	struct input_dev *input_dev;
	struct s3c_keypad *s3c_keypad;

	if (device_create_file(&(pdev->dev), &dev_attr_key_pressed) < 0) {
		printk("%s s3c_keypad_probe\n",__FUNCTION__);
		pr_err("Failed to create device file(%s)!\n",
			dev_attr_key_pressed.attr.name);
	}

#ifdef FLASH_MOVIE_MODE
        /* hrtimer settings */
        hrtimer_init(&timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
        timer.function = aat1271_flash_timer_func;

        timed_output_dev_register(&timed_output_flash);

#endif

	return 0;


}

static int s3c_keypad_remove(struct platform_device *pdev)
{

	return 0;
}


#define s3c_keypad_suspend NULL
#define s3c_keypad_resume  NULL


static struct platform_driver s3c_keypad_driver = {
	.probe		= s3c_keypad_probe,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "s3c-keypad",
	},
};

static int __init s3c_keypad_init(void)
{
	int ret;
	
	ret = platform_driver_register(&s3c_keypad_driver);

	if(!ret)
	   printk(KERN_INFO "S3C Keypad Driver\n");

	return ret;
}

static void __exit s3c_keypad_exit(void)
{
	platform_driver_unregister(&s3c_keypad_driver);
}

module_init(s3c_keypad_init);
module_exit(s3c_keypad_exit);

MODULE_AUTHOR("Samsung");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("KeyPad interface for Samsung S3C");

