#!/bin/bash

#if [ ! -e everest.iso ] || [ bin/kernel -nt everest.iso ]
#then
#	./update_image.sh
#fi

export LD_PRELOAD=/usr/lib/i386-linux-gnu/libXpm.so.4
sudo LD_PRELOAD=/usr/lib/i386-linux-gnu/libXpm.so.4 bochs -f conf/bochsrc.txt

