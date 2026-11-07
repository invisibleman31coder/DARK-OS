; ============ DARK-OS v2.5 - bootloader.asm - LBA FIX ============
; Powered by SAIDER AI
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
    mov [boot_drive], dl

    mov si, msg_boot
    call print16

    ; LBA Read - load kernel LBA 1 (sector 2) -> 0x10000
    mov si, dap
    mov ah, 0x42
    mov dl, [boot_drive]
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
msg_boot db 'DARK-OS v2.5 Booting..', 13, 10, 0
msg_disk db 'Disk Error!', 13, 10, 0

; Disk Address Packet for int 0x13 AH=0x42
dap:
    db 0x10      ; size
    db 0         ; reserved
    dw 64        ; sectors to read
    dw 0x0000    ; offset 0x0000
    dw 0x1000    ; segment 0x1000 = 0x10000
    dq 1         ; LBA 1 = sector 2

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
