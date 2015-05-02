#!/bin/bash
set -e

mkdir -p isodir/boot/grub
cp bin/kernel isodir/boot
cp conf/grub.cfg isodir/boot/grub/
grub-mkrescue -o everest.iso isodir

