; ============ ZED-OS v2.7 - bootloader.asm - FIXED DRIVE ============
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

    ; SAVE boot drive BIOS gave us - 0x00 = floppy, 0x80 = hard disk
    mov [boot_drive], dl

    mov si, msg_boot
    call print16

    ; Load kernel - 64 sectors from sector 2 to 0x10000
    mov ax, 0x1000
    mov es, ax
    xor bx, bx
    mov ah, 0x02
    mov al, 64
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [boot_drive]  ; USE SAVED DRIVE, NOT 0x00
    int 0x13
    jc disk_error

    in al, 0x92
    or al, 2
    out 0x92, al

    cli
    lgdt [gdt_desc]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode

disk_error:
    mov si, msg_disk
    call print16
    hlt
    jmp $

print16:
    mov ah, 0x0E
.loop:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .loop
.done:
    ret

boot_drive db 0
msg_boot db 'ZED-OS v2.7 Booting..', 13, 10, 0
msg_disk db 'Disk Error!', 13, 10, 0

gdt_start:
    dq 0x0000000000000000
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
gdt_end:

gdt_desc:
    dw gdt_end - gdt_start - 1
    dd gdt_start

[bits 32]
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000
    jmp 0x10000
    hlt
    jmp $

times 510 - ($ - $$) db 0
dw 0xAA55
