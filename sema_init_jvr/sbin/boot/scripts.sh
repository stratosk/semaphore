if [ -d /system/etc/init.d ]; then
  busybox run-parts /system/etc/init.d
fi;

if [ -f /system/bin/customboot.sh ]; then
  busybox sh /system/bin/customboot.sh;
fi;

if [ -f /system/xbin/customboot.sh ]; then
  busybox sh /system/xbin/customboot.sh
fi;

if [ -f /data/local/customboot.sh ]; then
  busybox sh /data/local/customboot.sh
fi;
