TWEAK_BASE="persist.tweak";

TWEAK_IO="$TWEAK_BASE.ioscheduler";
TWEAK_NOATIME="$TWEAK_BASE.noatime";
TWEAK_VM_SWAPPINESS="$TWEAK_BASE.vm.swappiness";
TWEAK_VM_DIRTY="$TWEAK_BASE.vm.dirty";
TWEAK_SCHEDULER="$TWEAK_BASE.scheduler";
TWEAK_MINFREE="$TWEAK_BASE.minfree";
TWEAK_SDCARD="$TWEAK_BASE.sdcard";

TWEAK_STAGEFRIGHT="$TWEAK_BASE.stagefright";
TWEAK_GOVERNOR_CONSERVATIVE="$TWEAK_BASE.gov_conservative";
TWEAK_SCHEDULER_DEADLINE="$TWEAK_BASE.sched_deadline";
TWEAK_TOUCHSCREEN="$TWEAK_BASE.touchscreen";

for i in $TWEAK_IO $TWEAK_NOATIME $TWEAK_VM_SWAPPINESS $TWEAK_VM_DIRTY $TWEAK_SCHEDULER $TWEAK_MINFREE $TWEAK_SDCARD; do
  if [ "$(getprop $i)" = "" ]; then
    setprop $i enabled;
  fi;
done;

for i in $TWEAK_STAGEFRIGHT $TWEAK_GOVERNOR_CONSERVATIVE $TWEAK_SCHEDULER_DEADLINE $TWEAK_TOUCHSCREEN; do
  if [ "$(getprop $i)" = "" ]; then
    setprop $i disabled;
  fi;
done;

if [ $(getprop $TWEAK_IO) = "enabled" ]; then
  # Tweak cfq io scheduler
  for i in $(ls -1 /sys/block/stl*) $(ls -1 /sys/block/mmc*) $(ls -1 /sys/block/bml*) $(ls -1 /sys/block/tfsr*)
  do 
    echo "0" > $i/queue/rotational
    echo "1" > $i/queue/iosched/low_latency
    echo "1" > $i/queue/iosched/back_seek_penalty
    echo "1000000000" > $i/queue/iosched/back_seek_max
    echo "2" > $i/queue/iosched/slice_idle
  done
fi;

if [ $(getprop $TWEAK_SCHEDULER_DEADLINE) = "enabled" ]; then
  # use deadline scheduler
  echo deadline > /sys/class/block/mmcblk0/queue/scheduler
  echo deadline > /sys/class/block/mmcblk1/queue/scheduler
  echo deadline > /sys/class/block/stl10/queue/scheduler
  echo deadline > /sys/class/block/stl9/queue/scheduler
  echo 8 > /sys/class/block/mmcblk0/queue/iosched/fifo_batch
  echo 8 > /sys/class/block/mmcblk1/queue/iosched/fifo_batch
  echo 8 > /sys/class/block/stl10/queue/iosched/fifo_batch
  echo 8 > /sys/class/block/stl9/queue/iosched/fifo_batch
  echo 400 > /sys/class/block/mmcblk0/queue/iosched/read_expire
  echo 400 > /sys/class/block/mmcblk1/queue/iosched/read_expire
  echo 400 > /sys/class/block/stl10/queue/iosched/read_expire
  echo 400 > /sys/class/block/stl9/queue/iosched/read_expire
  echo 4 > /sys/class/block/mmcblk0/queue/iosched/writes_starved
  echo 4 > /sys/class/block/mmcblk1/queue/iosched/writes_starved
  echo 4 > /sys/class/block/stl10/queue/iosched/writes_starved
  echo 4 > /sys/class/block/stl9/queue/iosched/writes_starved
fi;

if [ $(getprop $TWEAK_NOATIME) = "enabled" ]; then
  # Remount all partitions with noatime, nodiratime
  for k in $(busybox mount | grep relatime | cut -d " " -f3)
  do
    sync;
    busybox mount -o remount,noatime,nodiratime $k;
  done
fi;

if [ $(getprop $TWEAK_SDCARD) = "enabled" ]; then
  # SDcard speed tweak
  for i in $(ls -1 /sys/devices/platform/s3c-sdhci.*/mmc_host/mmc*/mmc*/block/*/queue/read_ahead_kb); do 
    echo 3072 > $i; 
  done;
fi;

if [ $(getprop $TWEAK_VM_SWAPPINESS) = "enabled" ]; then
  # Tweak kernel VM management
  echo "0" > /proc/sys/vm/swappiness
fi;

if [ $(getprop $TWEAK_VM_DIRTY) = "enabled" ]; then
  # Miscellaneous tweaks
  echo "2000" > /proc/sys/vm/dirty_writeback_centisecs
  echo "1000" > /proc/sys/vm/dirty_expire_centisecs
  echo "90" > /proc/sys/vm/dirty_ratio
  echo "5" > /proc/sys/vm/dirty_background_ratio
  echo "1" > /proc/sys/vm/vfs_cache_pressure
fi;

if [ $(getprop $TWEAK_SCHEDULER) = "enabled" ]; then
  # Tweak kernel scheduler
  echo "18000000" > /proc/sys/kernel/sched_latency_ns
  echo "3000000" > /proc/sys/kernel/sched_wakeup_granularity_ns
  echo "1500000" > /proc/sys/kernel/sched_min_granularity_ns
fi;

if [ $(getprop $TWEAK_MINFREE) = "enabled" ]; then
  if [ -e /sys/module/lowmemorykiller/parameters/minfree ]; then
    echo "2560,4096,6144,17408,19456,23552" > /sys/module/lowmemorykiller/parameters/minfree
  fi;
fi;

if [ $(getprop $TWEAK_STAGEFRIGHT) = "enabled" ]; then
  setprop media.stagefright.enable-player true;
fi;

if [ $(getprop $TWEAK_GOVERNOR_CONSERVATIVE) = "enabled" ]; then
  echo conservative >/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
  echo 10 >/sys/devices/system/cpu/cpu0/cpufreq/conservative/freq_step
  echo 40 >/sys/devices/system/cpu/cpu0/cpufreq/conservative/down_threshold
  echo 90 >/sys/devices/system/cpu/cpu0/cpufreq/conservative/up_threshold
  echo 0 >/sys/devices/system/cpu/cpu0/cpufreq/conservative/ignore_nice_load
fi;

if [ $(getprop $TWEAK_TOUCHSCREEN) = "enabled" ]; then
  echo 7035 > /sys/class/touch/switch/set_touchscreen
  echo 8002 > /sys/class/touch/switch/set_touchscreen
  echo 11000 > /sys/class/touch/switch/set_touchscreen
  echo 13060 > /sys/class/touch/switch/set_touchscreen
  echo 14005 > /sys/class/touch/switch/set_touchscreen
fi;
