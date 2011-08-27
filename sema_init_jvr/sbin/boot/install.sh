if /sbin/ext/busybox [ ! -f /system/cfroot/release-80-JVR-s1 ]; 
then
# Remount system RW
    /sbin/ext/busybox mount -o remount,rw /system

# Remove startup and shutdown sounds, to make some space
    toolbox rm /system/etc/PowerOn.snd
    toolbox rm /system/etc/PowerOn.wav
    toolbox rm /system/media/audio/ui/PowerOff.wav

# ensure /system/xbin exists
    toolbox mkdir /system/xbin
    toolbox chmod 755 /system/xbin

# make init.d
    toolbox mkdir /system/etc/init.d
    toolbox chmod 777 /system/etc/init.d

# su
    toolbox rm /system/bin/su
    toolbox rm /system/xbin/su
    toolbox cat /res/misc/su > /system/xbin/su
    toolbox chown 0.0 /system/xbin/su
    toolbox chmod 4755 /system/xbin/su

# Superuser
    toolbox rm /system/app/Superuser.apk
    toolbox rm /data/app/Superuser.apk
    toolbox cat /res/misc/Superuser.apk > /system/app/Superuser.apk
    toolbox chown 0.0 /system/app/Superuser.apk
    toolbox chmod 644 /system/app/Superuser.apk

# CWM & Tweak Manager
    toolbox rm /system/app/CWMReboot.apk
    toolbox rm /data/dalvik-cache/*CWMReboot.apk*
    toolbox rm /data/app/eu.chainfire.cfroot.cwmreboot*.apk

    toolbox rm /system/app/CWMManager.apk
    toolbox rm /data/dalvik-cache/*CWMManager.apk*
    toolbox rm /data/app/eu.chainfire.cfroot.cwmmanager*.apk

    toolbox rm /system/app/TweakManager.apk
    toolbox rm /data/dalvik-cache/*TweakManager.apk*
    toolbox rm /data/app/eu.chainfire.cfroot.tweakmanager*.apk

    toolbox cat /res/misc/CWMManager.apk > /system/app/CWMManager.apk
    toolbox chown 0.0 /system/app/CWMManager.apk
    toolbox chmod 644 /system/app/CWMManager.apk

    toolbox cat /res/misc/TweakManager.apk > /system/app/TweakManager.apk
    toolbox chown 0.0 /system/app/TweakManager.apk
    toolbox chmod 644 /system/app/TweakManager.apk

# Once be enough
    toolbox mkdir /system/cfroot
    toolbox chmod 755 /system/cfroot
    toolbox rm /data/cfroot/*
    toolbox rmdir /data/cfroot
    toolbox rm /system/cfroot/*
    echo 1 > /system/cfroot/release-80-JVR-s1-

# Remount system RO
    /sbin/ext/busybox mount -o remount,ro /system
fi;
