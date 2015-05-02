MKDIR=mkdir -p
RM:=rm -rf
BINDIR:=bin

all: | $(BINDIR)
	$(MAKE) -C src/

$(BINDIR):
	$(MKDIR) $(BINDIR)

clean:
	$(MAKE) -C src/ clean
	$(RM) $(ISODIR) $(BINDIR) $(ISO)

run: all
	#./update_image.sh
	./run_bochs.sh
