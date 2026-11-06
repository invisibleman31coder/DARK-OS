; ============ ZED-OS v2.7 - bootloader.asm - CLEAN WHOLE FILE ============
; Loads kernel.bin from sector 2 -> 0x10000, then jumps to kernel_main
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

    ; Print "Booting.."
    mov si, msg_boot
    call print16

    ; Load kernel - 64 sectors (32KB) from sector 2 to 0x10000
    ; ES:BX = 0x1000:0x0000 = 0x10000 physical
    mov ax, 0x1000
    mov es, ax
    xor bx, bx
    mov ah, 0x02      ; read sectors
    mov al, 64        ; 64 sectors
    mov ch, 0         ; cylinder 0
    mov cl, 2         ; sector 2 (sector 1 = bootloader)
    mov dh, 0         ; head 0
    mov dl, 0x00      ; floppy drive
    int 0x13
    jc disk_error

    ; Enable A20
    in al, 0x92
    or al, 2
    out 0x92, al

    ; Load GDT and switch to protected mode
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

msg_boot db 'ZED-OS v2.7 Booting..', 13, 10, 0
msg_disk db 'Disk Error!', 13, 10, 0

; ---------- GDT ----------
gdt_start:
    dq 0x0000000000000000 ; null
    dq 0x00CF9A000000FFFF ; code: base 0, limit 4GB, exec/read
    dq 0x00CF92000000FFFF ; data: base 0, limit 4GB, read/write
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

    ; Jump to kernel at 0x10000 - this is kernel_main
    jmp 0x10000

    hlt
    jmp $

times 510 - ($ - $$) db 0
dw 0xAA55
