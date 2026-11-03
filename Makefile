all: ZED-OS.img

bootloader.bin: bootloader.asm
	nasm -f bin bootloader.asm -o bootloader.bin

kernel.o: kernel.c
	gcc -m32 -ffreestanding -c kernel.c -o kernel.o -fno-pie -fno-stack-protector

kernel.bin: kernel.o
	ld -m elf_i386 -T linker.ld -o kernel.bin kernel.o --oformat binary -nostdlib

ZED-OS.img: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > ZED-OS.img
	truncate -s 1474560 ZED-OS.img

clean:
	rm -f *.bin *.o *.img
