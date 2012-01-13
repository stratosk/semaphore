  # Remount all partitions with noatime, nodiratime
  for k in $(busybox mount | grep relatime | cut -d " " -f3)
  do
    sync;
    busybox mount -o remount,noatime,nodiratime $k;
  done

