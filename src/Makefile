SOURCES=boot.o kmain.o common.o vga_text.o string.o descriptor_tables.o gdt_idt_tables.o isr.o interrupts.o timer.o paging.o kheap.o
KERNELOUT=../bin/kernel
INCLUDES=-I../include

LD=ld
RM=rm -rf
NASM=nasm

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 $(INCLUDES) -Wall
LDFLAGS=-Tlink.ld -melf_i386
ASFLAGS=-felf

all: link

clean:
	$(RM) *.o kernel

link: $(KERNELOUT)

$(KERNELOUT): $(SOURCES)
	$(LD) $(LDFLAGS) -o $(KERNELOUT) $(SOURCES) $(LIBSOURCES)

.s.o:
	$(NASM) $(ASFLAGS) $<
