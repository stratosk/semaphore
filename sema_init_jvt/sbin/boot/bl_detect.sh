if /sbin/ext/busybox [ -f /data/local/first_boot ] && /sbin/ext/busybox [ ! -f /data/local/succ_boot ];
then
	# Remount system RW
	/sbin/ext/busybox mount -o remount,rw /system


	# backup original init.d
	toolbox mv /system/etc/init.d /system/etc/init.d.ori

	# re-create init.d
	toolbox mkdir /system/etc/init.d
	toolbox chmod 777 /system/etc/init.d

	# Remount system RO
	/sbin/ext/busybox mount -o remount,ro /system
	
fi;

# remove succesful boot flag
toolbox rm /data/local/succ_boot
