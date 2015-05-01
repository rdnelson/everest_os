#!/bin/bash

if [ ! -e bin/floppy.img ]
then
    dd if=/dev/zero of=bin/floppy.img bs=1024 count=1440
    sudo losetup /dev/loop0 bin/floppy.img
    sudo mkfs.fat /dev/loop0
    sudo grub-install /dev/loop0
else
    sudo losetup /dev/loop0 bin/floppy.img
fi

sudo mount /dev/loop0 /mnt
sudo cp bin/kernel /mnt/kernel
sudo umount /dev/loop0
sudo losetup -d /dev/loop0

