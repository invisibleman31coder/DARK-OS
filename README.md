# ZED-OS v2.2 — Real x86 Operating System from Scratch

ZED-OS is a custom x86 operating system written from scratch in C and Assembly. No Linux dependencies. Boots directly in QEMU from a custom bootloader.

> Boots in QEMU. Custom bootloader + C kernel.

### Architecture

- `bootloader.asm` — 16-bit real mode to 32-bit protected mode bootloader (0x7C00), GDT setup
- `kernel.c` — VGA text-mode driver, memory paging, basic shell
- `linker.ld` — ELF linker script for kernel entry point
- `Makefile` — Build system for bootable ISO image
- `legacy/` — ZED-OS v2.1 Internet OS simulation (archived)

### Features (v2.2)

- Custom boot sector
- Protected mode transition
- VGA driver
- Memory paging initialization
- Buildable ISO image

### Build & Run

```bash
make          # builds zed-os.iso
make run      # runs in qemu-system-i386
make clean
