ENTRY(kmain)
SECTIONS {
    . = 0x10000;

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    }

    /* Heap starts right after kernel ends */
    /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
    }
}
