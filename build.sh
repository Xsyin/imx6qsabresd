#!/bin/bash

#  mount -o loop,offset=1048576 rootfs.img  /mnt/
# sudo dd if=u-boot-dtb.imx of=/dev/sdc bs=512 seek=2 conv=sync conv=notrunc
#make all
make linux-imx-cleaner
make linux-imx
cd out
cp imx6q-sabresd.dtb zImage /media/yin/BOOT

cd ../linux-imx
sudo make modules_install INSTALL_MOD_PATH=/media/yin/rootfs/ ARCH=arm CROSS_COMPILE=../aarch32/bin/arm-linux-gnueabihf-
sudo make ARCH=arm CROSS_COMPILE=../aarch32/bin/arm-linux-gnueabihf- headers_install INSTALL_HDR_PATH=/media/yin/rootfs/usr

sync
