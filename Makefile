all:
	$(MAKE) -C src/

clean:
	$(MAKE) -C src/ clean

run: all
	./update_image.sh
	./run_bochs.sh
