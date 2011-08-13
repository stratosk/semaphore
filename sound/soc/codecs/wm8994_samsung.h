/*
 * wm8994_samsung.h  --  WM8994 Soc Audio driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _WM8994_SAMSUNG_H
#define _WM8994_SAMSUNG_H

#include <sound/soc.h>
#include <linux/mfd/wm8994/wm8994_pdata.h>

extern struct snd_soc_codec_device soc_codec_dev_wm8994;

/* Sources for AIF1/2 SYSCLK - use with set_dai_sysclk() */
#define WM8994_SYSCLK_MCLK1 1
#define WM8994_SYSCLK_MCLK2 2
#define WM8994_SYSCLK_FLL1  3
#define WM8994_SYSCLK_FLL2  4

#define WM8994_FLL1 1
#define WM8994_FLL2 2

/* Added belows codes by Samsung Electronics.*/

#include "wm8994_def.h"

extern struct snd_soc_dai wm8994_dai;

#define WM8994_SYSCLK_MCLK     1
#define WM8994_SYSCLK_FLL      2

#define AUDIO_COMMON_DEBUG	0

/* For VT call */
#define USE_INFINIEON_EC_FOR_VT
#define ATTACH_ADDITINAL_PCM_DRIVER

#define DEACTIVE		0x00
#define PLAYBACK_ACTIVE		0x01
#define CAPTURE_ACTIVE		0x02
#define CALL_ACTIVE		0x04
#define FMRADIO_ACTIVE		0x08

#define PCM_STREAM_DEACTIVE	0x00
#define PCM_STREAM_PLAYBACK	0x01
#define PCM_STREAM_CAPTURE	0x02

/*
Codec Output Path BIT
[0:15]		: For output device
[0:3]	: For mode
*/
#define PLAYBACK_MODE	(0x01 << 0)
#define VOICECALL_MODE	(0x01 << 1)
#define RECORDING_MODE	(0x01 << 2)
#define FMRADIO_MODE	(0x01 << 3)

#define COMMON_SET_BIT		(0x01 << 0)
#define PLAYBACK_RCV		(0x01 << 1)
#define PLAYBACK_SPK		(0x01 << 2)
#define PLAYBACK_HP		(0x01 << 3)
#define PLAYBACK_HP_NO_MIC	(0x01 << 4)
#define PLAYBACK_BT		(0x01 << 5)
#define PLAYBACK_SPK_HP		(0x01 << 6)
#define PLAYBACK_EXTRA_DOCK	(0x01 << 7)
#define PLAYBACK_RING_SPK	(0x01 << 8)
#define PLAYBACK_RING_HP	(0x01 << 9)
#define PLAYBACK_RING_SPK_HP	(0x01 << 10)
#define PLAYBACK_VOIP_RCV	(0x01 << 11)
#define PLAYBACK_VOIP_SPK	(0x01 << 12)
#define PLAYBACK_VOIP_HP	(0x01 << 13)
#define PLAYBACK_VOIP_BT	(0x01 << 14)


#define VOICECALL_RCV		(0x01 << 1)
#define VOICECALL_SPK		(0x01 << 2)
#define VOICECALL_HP		(0x01 << 3)
#define VOICECALL_HP_NO_MIC	(0x01 << 4)
#define VOICECALL_BT		(0x01 << 5)

#define RECORDING_MAIN		(0x01 << 1)
#define RECORDING_HP		(0x01 << 2)
#define RECORDING_BT		(0x01 << 3)
#define RECORDING_REC_MAIN	(0x01 << 4)
#define RECORDING_REC_HP	(0x01 << 5)
#define RECORDING_REC_BT	(0x01 << 6)
#define RECORDING_CAM_MAIN	(0x01 << 7)
#define RECORDING_CAM_HP	(0x01 << 8)
#define RECORDING_CAM_BT	(0x01 << 9)
#define RECORDING_VOIP_MAIN	(0x01 << 10)
#define RECORDING_VOIP_HP	(0x01 << 11)
#define RECORDING_VOIP_BT	(0x01 << 12)

#define FMRADIO_HP		(0x01 << 1)
#define FMRADIO_SPK		(0x01 << 2)
#define FMRADIO_SPK_HP		(0x01 << 3)

#define PLAYBACK_GAIN_NUM	48
#define VOICECALL_GAIN_NUM	32
#define RECORDING_GAIN_NUM	31
#define FMRADIO_GAIN_NUM	34

#define DCS_NUM 5


#define CMD_FMR_INPUT_DEACTIVE		0 /* Codec Input PGA off */
#define CMD_FMR_INPUT_ACTIVE		1 /* Codec Input PGA on */
#define CMD_FMR_FLAG_CLEAR		2 /* Radio flag clear for shutdown */
#define CMD_FMR_END			3 /* Codec off in FM radio mode */
#define CMD_CALL_FLAG_CLEAR		4 /* Call flag clear for shutdown */
#define CMD_CALL_END			5 /* Codec off in call mode */

/*
 * Definitions of enum type
 */
enum audio_path	{
	OFF, RCV, SPK, HP, HP_NO_MIC, BT, SPK_HP,
	EXTRA_DOCK_SPEAKER
};
enum mic_path			{MAIN, SUB, BT_REC, MIC_OFF};
enum fmradio_path		{FMR_OFF, FMR_SPK, FMR_HP, FMR_DUAL_MIX};
enum fmradio_mix_path		{FMR_MIX_OFF, FMR_MIX_DUAL};
enum power_state		{CODEC_OFF, CODEC_ON };
enum input_source_state		{DEFAULT_INPUT, RECOGNITION, CAMCORDER, VOIP_INPUT};
enum output_source_state	{DEFAULT_OUTPUT, RING_TONE, VOIP_OUTPUT};
enum vtcall_state		{VT_OFF, VT_ON};

typedef void (*select_route)(struct snd_soc_codec *);
typedef void (*select_mic_route)(struct snd_soc_codec *);
typedef int (*select_clock_control)(struct snd_soc_codec *, int);


struct wm8994_setup_data {
	int i2c_bus;
	unsigned short i2c_address;
};

enum wm8994_dc_servo_slots {
	DCS_MEDIA = 0,
	DCS_VOICE = 1,
	DCS_SPK_HP = 2,
	DCS_FMRADIO = 3,
	DCS_FMRADIO_SPK_HP = 4,
};

struct wm8994_priv {
	struct snd_soc_codec codec;
	int master;
	int sysclk_source;
	unsigned int mclk_rate;
	unsigned int sysclk_rate;
	unsigned int fs;
	unsigned int bclk;
	unsigned int hw_version;
	unsigned int codec_state;
	unsigned int  stream_state;
	enum audio_path cur_path;
	enum mic_path rec_path;
	enum fmradio_path fmradio_path;
	enum fmradio_mix_path fmr_mix_path;
	enum power_state power_state;
	enum input_source_state input_source;
	enum output_source_state output_source;
	select_route *universal_playback_path;
	select_route *universal_voicecall_path;
	select_mic_route *universal_mic_path;
	select_clock_control universal_clock_control;
	struct wm8994_platform_data *pdata;
	struct clk *codec_clk;
	int testmode_config_flag;
	u16 dc_servo[DCS_NUM];
	bool output_source_flag;
};

struct gain_info_t {
	int mode;
	int reg;
	int mask;
	int gain;
};

#if AUDIO_COMMON_DEBUG
#define DEBUG_LOG(format, ...)\
	printk(KERN_INFO "[ "SUBJECT " (%s,%d) ] " format "\n", \
			__func__, __LINE__, ## __VA_ARGS__);
#else
#define DEBUG_LOG(format, ...)
#endif

#define DEBUG_LOG_ERR(format, ...)\
	printk(KERN_ERR "[ "SUBJECT " (%s,%d) ] " format "\n", \
			__func__, __LINE__, ## __VA_ARGS__);

/* Definitions of function prototype. */
void wm8994_shutdown(struct snd_pcm_substream *substream,
			    struct snd_soc_dai *codec_dai);
unsigned int wm8994_read(struct snd_soc_codec *codec, unsigned int reg);
int wm8994_write(struct snd_soc_codec *codec,
		unsigned int reg, unsigned int value);
int wm8994_configure_clock(struct snd_soc_codec *codec, int en);
void wm8994_disable_path(struct snd_soc_codec *codec);
void wm8994_disable_rec_path(struct snd_soc_codec *codec);
void wm8994_record_main_mic(struct snd_soc_codec *codec);
void wm8994_record_headset_mic(struct snd_soc_codec *codec);
void wm8994_record_bluetooth(struct snd_soc_codec *codec);
void wm8994_set_playback_receiver(struct snd_soc_codec *codec);
void wm8994_set_playback_headset(struct snd_soc_codec *codec);
void wm8994_set_playback_speaker(struct snd_soc_codec *codec);
void wm8994_set_playback_bluetooth(struct snd_soc_codec *codec);
void wm8994_set_playback_speaker_headset(struct snd_soc_codec *codec);
void wm8994_set_playback_extra_dock_speaker(struct snd_soc_codec *codec);
void wm8994_set_voicecall_common(struct snd_soc_codec *codec);
void wm8994_set_voicecall_receiver(struct snd_soc_codec *codec);
void wm8994_set_voicecall_headset(struct snd_soc_codec *codec);
void wm8994_set_voicecall_headphone(struct snd_soc_codec *codec);
void wm8994_set_voicecall_speaker(struct snd_soc_codec *codec);
void wm8994_set_voicecall_bluetooth(struct snd_soc_codec *codec);
void wm8994_disable_fmradio_path(struct snd_soc_codec *codec,
	enum fmradio_path path);
void wm8994_set_fmradio_input_active(struct snd_soc_codec *codec, int on);
void wm8994_set_fmradio_common(struct snd_soc_codec *codec);
void wm8994_set_fmradio_headset(struct snd_soc_codec *codec);
void wm8994_set_fmradio_speaker(struct snd_soc_codec *codec);
void wm8994_set_fmradio_speaker_headset_mix(struct snd_soc_codec *codec);
int wm8994_set_codec_gain(struct snd_soc_codec *codec, u16 mode, u16 device);
#endif
