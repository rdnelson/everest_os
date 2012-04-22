SOURCES=boot.o kmain.o
KERNELOUT=../bin/kernel

LD=ld
RM=rm -rf
NASM=nasm

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32
LDFLAGS=-Tlink.ld -melf_i386
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	$(RM) *.o kernel

link:
	$(LD) $(LDFLAGS) -o $(KERNELOUT) $(SOURCES)

.s.o:
	$(NASM) $(ASFLAGS) $<
