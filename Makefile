MKDIR=mkdir -p
RM:=rm -rf
BINDIR:=bin

.PHONY: all clean run libc kernel

all: libc kernel

libc:
	$(MAKE) -C libc/

kernel: | $(BINDIR)
	$(MAKE) -C kernel/

$(BINDIR):
	$(MKDIR) $(BINDIR)

clean:
	$(MAKE) -C kernel/ clean
	$(MAKE) -C libc/ clean
	$(RM) $(ISODIR) $(BINDIR) $(ISO)

run: all
	#./update_image.sh
	./run_bochs.sh
