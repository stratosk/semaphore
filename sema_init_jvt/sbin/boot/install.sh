if /sbin/ext/busybox [ ! -f /system/cfroot/release-82-JVT-s1- ]; 
then
# Remount system RW
    /sbin/ext/busybox mount -o remount,rw /system

# Remove startup and shutdown sounds, to make some space
    if /sbin/ext/busybox [ -f /system/etc/PowerOn.snd ];
    then
    	toolbox cat /system/etc/PowerOn.snd > /data/local/PowerOn.snd
	toolbox rm /system/etc/PowerOn.snd
    fi;

    if /sbin/ext/busybox [ -f /system/etc/PowerOn.wav ];
    then
	toolbox cat /system/etc/PowerOn.wav > /data/local/PowerOn.wav
	toolbox rm /system/etc/PowerOn.wav
    fi;

    if /sbin/ext/busybox [ -f /system/media/audio/ui/PowerOff.wav ];
    then
    	toolbox cat /system/media/audio/ui/PowerOff.wav > /data/local/PowerOff.wav
	toolbox rm /system/media/audio/ui/PowerOff.wav
    fi;

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

#    toolbox cat /res/misc/TweakManager.apk > /system/app/TweakManager.apk
#    toolbox chown 0.0 /system/app/TweakManager.apk
#    toolbox chmod 644 /system/app/TweakManager.apk

# Semaphore Script Manager
    toolbox rm /system/app/Semaphore.apk
    toolbox rm /data/dalvik-cache/*semaphore.apk*
    toolbox rm /data/app/hm.semaphore*.apk

    toolbox cat /res/misc/Semaphore.apk > /system/app/Semaphore.apk
    toolbox chown 0.0 /system/app/Semaphore.apk
    toolbox chmod 644 /system/app/Semaphore.apk

# Once be enough
    toolbox mkdir /system/cfroot
    toolbox chmod 755 /system/cfroot
    toolbox rm /data/cfroot/*
    toolbox rmdir /data/cfroot
    toolbox rm /system/cfroot/*
    echo 1 > /system/cfroot/release-82-JVT-s1-

# Remount system RO
    /sbin/ext/busybox mount -o remount,ro /system
fi;
