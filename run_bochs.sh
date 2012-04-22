#!/bin/bash

if [ bin/floppy.img -nt bin/kernel ]
then 
	./update_image.sh
fi
sudo losetup /dev/loop0 bin/floppy.img
sudo bochs -f conf/bochsrc.txt
sudo losetup -d /dev/loop0

