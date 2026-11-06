ENTRY(kernel_main)
SECTIONS {
    . = 0x10000;
    .text : {
        *(.text.kernel_main)
        *(.text)
        *(.text.*)
    }
    .rodata : {
        *(.rodata)
        *(.rodata.*)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }
}
