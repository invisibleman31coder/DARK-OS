all: ZED-OS.img
bootloader.bin: bootloader.asm
	nasm -f bin bootloader.asm -o bootloader.bin
kernel.o: kernel.c
	i686-elf-gcc -ffreestanding -c kernel.c -o kernel.o
kernel.bin: kernel.o linker.ld
	i686-elf-ld -o kernel.bin -T linker.ld kernel.o --oformat binary
ZED-OS.img: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > ZED-OS.img
run: ZED-OS.img
	qemu-system-i386 -fda ZED-OS.img
clean:
	rm -f *.bin *.o *.img
