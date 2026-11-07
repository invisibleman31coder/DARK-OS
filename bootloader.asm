; ============ DARK-OS v2.5 - bootloader.asm ============
; Powered by SAIDER AI
; LBA Fix - Loads kernel from disk

[org 0x7C00]
[bits 16]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    ; Clear screen + print boot message
    mov ah, 0x00
    mov al, 0x03
    int 0x10

    mov si, msg_boot
    call print_string

    ; Load kernel from disk - LBA 1, 30 sectors -> 0x1000
    mov bx, 0x1000
    mov dh, 0
    mov dl, 0x00        ; floppy drive 0
    mov ch, 0           ; cylinder 0
    mov cl, 2           ; sector 2 (sector 1 = bootloader)
    mov al, 30          ; read 30 sectors
    mov ah, 0x02        ; BIOS read sectors
    int 0x13
    jc disk_error

    mov si, msg_ok
    call print_string

    ; Jump to kernel
    jmp 0x1000

disk_error:
    mov si, msg_error
    call print_string
    jmp $

print_string:
    mov ah, 0x0E
.loop:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .loop
.done:
    ret

msg_boot db 'DARK-OS v2.5 Booting..', 13, 10, 0
msg_ok   db 'Kernel loaded. Starting DARK-OS...', 13, 10, 
