all:
	cd kernel && make
	cd bootloader && make
	cd kernel && make run
