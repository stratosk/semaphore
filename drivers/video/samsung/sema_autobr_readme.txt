Semaphore Auto Brightness driver

This driver handles the brightness level automatically. Over a threshold it adjust the brightness instantly. Under this threshold it adjust the brightness step by step.
It's embedded in the kernel as module and it is fully configurable through sysfs (device /sys/devices/virtual/misc/sema_autobr).
Once loaded, blockes adjustments from framework (browser, user)

Tunable values:
- min_brightness (valid values 1-255, default 15- minimum brightness)
- max_brightness (valid values 1-255, default 255 - maximum brightness)
- max_lux (valid values 1-3000, default 2900 - maximum lux from sensor sensitivity, how easily you can reach the maximum brightness)
- instant adjust_thres (valid values 1-100, default 30 - instant adjust threshold, the threshold that over this the brightness is adjusted instantly and under this is adjusted step by step)
- effect_delay_ms (valid values -1-10, default 0 - Fade in/out duration, delay in ms for each brightness step, -1 disable)

There are 3 scripts with default presets Normal, Dark, Bright that may used through Semaphore Script Manager application.
