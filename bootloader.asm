; DARK-OS v2.5 bootloader.asm
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
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    mov si, msg_boot
    call print_string
    mov bx, 0x1000
    mov dh, 0
    mov dl, 0x00
    mov ch, 0
    mov cl, 2
    mov al, 30
    mov ah, 0x02
    int 0x13
    jc disk_error
    mov si, msg_ok
    call print_string
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
msg_ok db 'Kernel loaded. Starting DARK-OS...', 13, 10, 0
msg_error db 'Disk read error! Press reset.', 13, 10, 0
times 510 - ($ - $$) db 0
dw 0xAA55
