# ZED-OS v2.2 — Real x86 OS from Scratch

**Built entirely on a phone in Durban, SA. From Python simulation → Bootable OS in C + ASM.**

> Boots in QEMU. No Linux. Just bootloader + kernel.

### What it is
- `bootloader.asm` — 16-bit → 32-bit protected mode (0x7C00)
- `kernel.c` — VGA driver, paging, shell
- `linker.ld` + `Makefile` — builds bootable ISO
- `legacy/` — v2.1 Internet OS (Python)

### Build
```bash
make
make run  # needs qemu-system-i386
