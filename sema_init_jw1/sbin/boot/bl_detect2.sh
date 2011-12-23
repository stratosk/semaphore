if /sbin/ext/busybox [ ! -f /system/cfroot/disable_bl ]; 
then

sleep 120 

# create flags
echo 1 > /data/local/first_boot
echo 1 > /data/local/succ_boot

fi;
