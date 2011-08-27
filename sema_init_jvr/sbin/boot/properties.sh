/sbin/ext/busybox mount -t rootfs -o remount,rw rootfs 
mkdir -p /customkernel/property 
echo true >> /customkernel/property/customkernel.cf-root 
echo true >> /customkernel/property/customkernel.base.cf-root 
echo CF-Root >> /customkernel/property/customkernel.name 
echo "CF-Root 4.1" >> /customkernel/property/customkernel.namedisplay 
echo 80 >> /customkernel/property/customkernel.version.number 
echo 4.1 >> /customkernel/property/customkernel.version.name 
echo true >> /customkernel/property/customkernel.bootani.zip 
echo true >> /customkernel/property/customkernel.bootani.bin 
echo true >> /customkernel/property/customkernel.cwm 
echo 3.0.0.5 >> /customkernel/property/customkernel.cwm.version 
echo true >> /customkernel/property/customkernel.fs.rfs 
echo true >> /customkernel/property/customkernel.fs.ext4 
echo true >> /customkernel/property/customkernel.fs.ext4.sd.int 
echo true >> /customkernel/property/customkernel.fs.ext4.sd.ext 
/sbin/ext/busybox mount -t rootfs -o remount,ro rootfs 
