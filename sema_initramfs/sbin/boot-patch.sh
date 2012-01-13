#!/sbin/ext/busybox sh

/sbin/ext/busybox sh /sbin/boot/busybox.sh
/sbin/ext/busybox sh /sbin/boot/cwm.sh
/sbin/ext/busybox sh /sbin/boot/properties.sh
/sbin/ext/busybox sh /sbin/boot/install.sh
/sbin/ext/busybox sh /sbin/boot/ext4speed.sh
/sbin/ext/busybox sh /sbin/boot/bl_detect.sh
/sbin/ext/busybox sh /sbin/boot/bl_detect2.sh &
/sbin/ext/busybox sh /sbin/boot/scripts.sh
/sbin/ext/busybox sh /sbin/boot/tweaks.sh

/sbin/ext/busybox sh /sbin/install_bln_liblights.sh

read sync < /data/sync_fifo
rm /data/sync_fifo
