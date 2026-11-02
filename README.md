# ZED-OS v2.5

Lightweight x86 operating system written in C and x86 Assembly.

https://img.shields.io/badge/build-passing-brightgreen
https://img.shields.io/badge/C-76%25-blue
https://img.shields.io/badge/Assembly-14%25-orange

## Features

- Custom x86 bootloader
- Freestanding kernel
- VGA text mode output
- Keyboard driver
- Interactive shell
- Bare-metal execution
- QEMU support
- Automated GitHub Actions builds

## Overview

ZED-OS boots directly from bare metal into a fully interactive shell. The system is developed from scratch using C and x86 Assembly without relying on an existing operating system.

## Shell Commands

| Command | Description |
|----------|------------|
| help | Show available commands |
| clear | Clear screen |
| version | Display OS version |
| echo | Print text |
| reboot | Restart system |

## Project Structure

```text
bootloader.asm   - Boot sector
kernel.c         - Kernel core
keyboard.c       - Keyboard driver
linker.ld        - Linker configuration
Makefile         - Build system
```

## Building

```bash
make
```

## Running

```bash
qemu-system-i386 -drive format=raw,file=zedos.img
```

## Screenshots

Add screenshots of:
- Boot process
- Shell interface
- Command execution

## Roadmap

- [x] Bootloader
- [x] Kernel
- [x] Keyboard Input
- [x] VGA Output
- [x] Interactive Shell
- [ ] Memory Manager
- [ ] FAT Filesystem
- [ ] Multitasking
- [ ] Process Scheduler
- [ ] Networking

## Author

Sandile (Invisibleman31coder)

## License

MIT License
