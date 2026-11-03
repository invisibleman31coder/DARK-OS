// paging.c - simplified
#include "pmm.h"

uint32_t page_directory[1024] __attribute__((aligned(4096)));

void paging_init() {
    for(int i=0; i<1024; i++) {
        page_directory[i] = 0x00000002; // supervisor, rw, not present
    }
    // Identity map first 4MB so kernel keeps working
    uint32_t page_table[1024] __attribute__((aligned(4096)));
    for(int i=0; i<1024; i++) {
        page_table[i] = (i * 4096) | 3; // present, rw
    }
    page_directory[0] = ((uint32_t)page_table) | 3;

    // Load CR3 and enable paging
    asm volatile("mov %0, %%cr3" :: "r"(page_directory));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0" :: "r"(cr0));
}
