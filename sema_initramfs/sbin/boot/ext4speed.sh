for k in $(busybox mount | grep ext4 | cut -d " " -f3)
do
  sync;
  if [ "$k" = "/system" ]; then
    busybox mount -o remount,noauto_da_alloc,barrier=1 $k;
  elif [ "$k" = "/dbdata" ]; then
    busybox mount -o remount,noauto_da_alloc,barrier=0,nodelalloc $k;
  elif [ "$k" = "/data" ]; then
    busybox mount -o remount,noauto_da_alloc,barrier=1 $k;
  elif [ "$k" = "/cache" ]; then
    busybox mount -o remount,noauto_da_alloc,barrier=1 $k;
  fi;
done
