/* linux/drivers/input/keyboard/s3c-keypad.h 
 *
 * Driver header for Samsung SoC keypad.
 *
 * Kim Kyoungil, Copyright (c) 2006-2009 Samsung Electronics
 *      http://www.samsungsemi.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#ifndef _S3C_KEYPAD_H_
#define _S3C_KEYPAD_H_

static void __iomem *key_base;


#define KEYPAD_COLUMNS	   2
#define KEYPAD_ROWS    3
#define MAX_KEYPAD_NR  6



#ifdef CONFIG_ANDROID
int keypad_keycode[] = {
	50,0,0,0,58,42,
};

#else
int keypad_keycode[] = {
		1, 2, KEY_1, KEY_Q, KEY_A, 6, 7, KEY_LEFT,
		9, 10, KEY_2, KEY_W, KEY_S, KEY_Z, KEY_RIGHT, 16,
		17, 18, KEY_3, KEY_E, KEY_D, KEY_X, 23, KEY_UP,
		25, 26, KEY_4, KEY_R, KEY_F, KEY_C, 31, 32,
		33, KEY_O, KEY_5, KEY_T, KEY_G, KEY_V, KEY_DOWN, KEY_BACKSPACE,
		KEY_P, KEY_0, KEY_6, KEY_Y, KEY_H, KEY_SPACE, 47, 48,
		KEY_M, KEY_L, KEY_7, KEY_U, KEY_J, KEY_N, 55, KEY_ENTER,
		KEY_LEFTSHIFT, KEY_9, KEY_8, KEY_I, KEY_K, KEY_B, 63, KEY_COMMA
};
#endif

#if CONFIG_ANDROID
#ifdef CONFIG_CPU_S3C6410
#define KEYPAD_ROW_GPIOCON      S3C64XX_GPKCON
#define KEYPAD_ROW_GPIOPUD      S3C64XX_GPKPUD
#define KEYPAD_COL_GPIOCON      S3C64XX_GPLCON
#define KEYPAD_COL_GPIOPUD      S3C64XX_GPLPUD
#elif defined( CONFIG_CPU_S5PC100 )
#define KEYPAD_ROW_GPIOCON      S5PC1XX_GPH3CON
#define KEYPAD_ROW_GPIOPUD      S5PC1XX_GPH3PUD
#define KEYPAD_COL_GPIOCON      S5PC1XX_GPH2CON
#define KEYPAD_COL_GPIOPUD      S5PC1XX_GPH2PUD
#elif defined( CONFIG_CPU_S5PC110 ) || defined (CONFIG_CPU_S5PV210 )
#define KEYPAD_ROW_GPIOCON      (S5PV210_GPH3_BASE + 0x00)
#define KEYPAD_ROW_GPIOPUD      (S5PV210_GPH3_BASE + 0x08)
#define KEYPAD_COL_GPIOCON      (S5PV210_GPH2_BASE + 0x00)
#define KEYPAD_COL_GPIOPUD      (S5PV210_GPH2_BASE + 0x08)
#endif
#endif /* CONFIG_ANDROID */

#if defined(CONFIG_CPU_S3C6410)
#define KEYPAD_DELAY		(50)
#elif defined(CONFIG_CPU_S5PC100) || defined(CONFIG_CPU_S5PC110) || defined(CONFIG_CPU_S5PV210)
#define KEYPAD_DELAY		(300)  //600
#endif

#define	KEYIFCOL_CLEAR		(readl(key_base+S3C_KEYIFCOL) & ~0xffff)
#define	KEYIFCON_CLEAR		(readl(key_base+S3C_KEYIFCON) & ~0x1f)
#define KEYIFFC_DIV		(readl(key_base+S3C_KEYIFFC) | 0x1)

#define KEYCODE_UNKNOWN 10 

struct s3c_keypad {
	struct input_dev *dev;
	int nr_rows;	
	int no_cols;
	int total_keys; 
	int keycodes[MAX_KEYPAD_NR];
};

extern void s3c_setup_keypad_cfg_gpio(int rows, int columns);

#endif				/* _S3C_KEYIF_H_ */
