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
  
## Why I Built ZED-OS

I didn't build ZED-OS to replace Windows.

I built it to understand how computers actually work — not just how to use them.

Most developers learn how to build apps that run ON an operating system.
I wanted to learn how to build the operating system itself.

ZED-OS is built from scratch in C and Assembly. No libraries, no shortcuts.
I wrote the bootloader, the kernel, the memory manager, the keyboard driver,
and the shell myself.

### What This Project Proves

If you can build an OS, you can learn any technology.
This project is my proof that I understand:

- How a CPU boots
- How memory is managed
- How hardware talks to software
- How a shell runs commands

### What It Will Help Me Do In Future

This is not just a school project. It's my foundation to become a
Systems / Embedded / Cybersecurity Engineer.

ZED-OS prepares me for:
- Embedded & Firmware Development
- Kernel & Systems Programming
- Cybersecurity
- Cloud & DevOps
- Building lightweight systems for old hardware in South Africa

In the future, I want ZED-OS to become a lightweight system that can
run on old PCs in schools and small businesses — no heavy Windows,
no viruses, just boots and works.

ZED-OS is not the end goal. It's the proof that I can build anything.

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

screenshots/boot.png

screenshots/shell.png


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
