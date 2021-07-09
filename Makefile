

all:
	gcc -m32 -c kernel/kernel.c -o output/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	nasm -felf32 boot/boot.asm -o output/boot.o
	gcc -T linker.ld -o output/os.bin -ffreestanding -m32 -O2 -nostdlib output/boot.o output/kernel.o -lgcc
	qemu-system-x86_64 -kernel output/os.bin