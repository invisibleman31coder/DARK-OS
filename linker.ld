ENTRY(kernel_main)
SECTIONS {
    . = 0x10000;
    .text.kernel_main : { *(.text.kernel_main) }
    .text : { *(.text) }
    .rodata : { *(.rodata*) }
    .data : { *(.data) }
    .bss : { *(.bss) *(COMMON) }
}
