# DARK-OS v2.5

Lightweight x86 OS in C and Assembly

### Features
- Bootloader in Assembly
- Kernel in C
- Interactive shell
- Custom commands
- VGA text mode display
- Keyboard input handling

### Why I Built DARK-OS

I built DARK-OS to understand how computers actually work - from boot to shell. Not just using an OS, but building one.

- How a bootloader works
- How a kernel runs
- How a shell runs commands

### What It Will Help Me Do In Future

This is not just a school project. It's my foundation to become a Systems / Embedded / Cybersecurity Engineer.

DARK-OS prepares me for:
- Embedded & Firmware Development
- Kernel & Systems Programming
- Cybersecurity
- Cloud & DevOps
- Building lightweight systems for old hardware in South Africa

In the future, I want DARK-OS to become a lightweight system that can run on old PCs in schools and small businesses — no heavy Windows, no viruses, just boots and works.

DARK-OS is not the end goal. It's the proof that I can build anything.

### Overview

DARK-OS boots directly from bare metal into a fully interactive shell. The system is developed from scratch using C and x86 Assembly without relying on an existing operating system.

### Shell Commands

- **help** - Show available commands
- **clear** - Clear screen
- **version** - Display OS version
- **echo** - Print text
- **reboot** - Restart system

### Project Structure

- `bootloader.asm` - Boot sector
- `kernel.c` - Kernel core
