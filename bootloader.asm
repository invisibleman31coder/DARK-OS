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
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode
[bits 32]
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000
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
gdt_start:
    dd 0x0
    dd 0x0
gdt_code:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0
gdt_data:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start
times 510 - ($ - $$) db 0
dw 0xAA55
