OBJDIR:=obj
ASMOBJDIR:=$(OBJDIR)/asm
BINDIR:=../bin
ISODIR:=..
CONFDIR:=../conf

SOURCES=
ASM=

COBJS:=$(addprefix $(OBJDIR)/,$(SOURCES:.c=.o))
ASMOBJS:=$(addprefix $(ASMOBJDIR)/,$(ASM:.s=.o))
OBJS:=$(COBJS) $(ASMOBJS)

LIBC:=$(BINDIR)/libc.a

INCLUDES=-I../include

PREFIX=i686-elf
CC=$(PREFIX)-gcc
LD=$(PREFIX)-ld
RUNLIB=$(PREFIX)-runlib
RM=rm -rf
NASM=nasm
MKDIR=mkdir -p
CP=cp

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector $(INCLUDES)
ASFLAGS=-felf

.PHONY: all kernel iso clean

all: iso

clean:
	$(RM) $(OBJDIR) $(ASMOBJDIR) $(LIBC)

$(LIBC): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@
	$(RANLIB) $@

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
