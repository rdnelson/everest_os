OBJDIR:=obj
ASMOBJDIR:=$(OBJDIR)/asm
BINDIR:=../bin
ISODIR:=..
CONFDIR:=../conf

SOURCES=kmain.c common.c vga_text.c string.c descriptor_tables.c isr.c
ASM=boot.s gdt_idt_tables.s interrupts.s

COBJS:=$(addprefix $(OBJDIR)/,$(SOURCES:.c=.o))
ASMOBJS:=$(addprefix $(ASMOBJDIR)/,$(ASM:.s=.o))
OBJS:=$(COBJS) $(ASMOBJS)

KERNELOUT=$(BINDIR)/kernel
ISOOUT=$(ISODIR)/everest.iso
INCLUDES=-I../include

PREFIX=i686-elf
CC=$(PREFIX)-gcc
LD=$(PREFIX)-ld
RM=rm -rf
NASM=nasm
MKDIR=mkdir -p
CP=cp

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector $(INCLUDES)
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

.PHONY: all kernel iso clean

all: iso

iso: $(ISOOUT)

$(ISOOUT): $(KERNELOUT) $(CONFDIR)/grub.cfg
	$(MKDIR) $(ISODIR)/iso/boot/grub
	$(CP) $(KERNELOUT) $(ISODIR)/iso/boot
	$(CP) $(CONFDIR)/grub.cfg $(ISODIR)/iso/boot/grub/
	grub-mkrescue -o $(ISOOUT) $(ISODIR)/iso
	touch $@

kernel: $(KERNELOUT)

clean:
	$(RM) $(OBJDIR) $(ASMOBJDIR) $(KERNELOUT) $(ISOOUT)

$(KERNELOUT): $(OBJS) | $(BINDIR)
	$(LD) $(LDFLAGS) $^ -o $@

$(BINDIR):
	$(MKDIR) $@

$(OBJDIR):
	$(MKDIR) $@

$(ASMOBJDIR):
	$(MKDIR) $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/asm/%.o: %.s | $(ASMOBJDIR)
	$(NASM) $(ASFLAGS) $< -o $@
