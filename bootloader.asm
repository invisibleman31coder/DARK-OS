; ZED-OS v2.7 BOOTLOADER - Fixed
[BITS 16]
[ORG 0x7C00]
start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    mov si, msg_boot
    call print16

    ; Load kernel - 100 sectors = 51KB, enough for v2.7
    ; ES:BX = 0x1000:0x0000 = 0x10000
    mov ah, 0x02
    mov al, 100      ; <-- WAS 20, NOW 100
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, 0x1000
    mov es, bx
    xor bx, bx
    int 0x13
    jc disk_error    ; <-- NEW: if carry, disk failed

    lgdt [gdt_desc]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode

disk_error:
    mov si, msg_error
    call print16
    hlt
    jmp $

print16:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print16
.done: ret

[BITS 32]
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x90000
    jmp 0x08:0x10000   ; Jump to kernel_main at 0x10000

gdt_start:
    dq 0
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
gdt_end:
gdt_desc:
    dw gdt_end - gdt_start -1
    dd gdt_start

msg_boot db 'ZED-OS v2.7 Booting...',13,10,0
msg_error db 'Disk Read Error!',13,10,0
times 510-($-$$) db 0
dw 0xAA55
