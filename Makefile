MKDIR=mkdir -p
BINDIR:=bin

all: | $(BINDIR)
	$(MAKE) -C src/

$(BINDIR):
	$(MKDIR) $(BINDIR)

clean:
	$(MAKE) -C src/ clean

run: all
	./update_image.sh
	./run_bochs.sh
