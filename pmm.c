// pmm.c - SINGLE FILE VERSION
#include <stdint.h>

#define PAGE_SIZE 4096
static uint8_t bitmap[32768];
static uint32_t total_pages;

void pmm_init(uint32_t mem_size_kb) {
    total_pages = (mem_size_kb * 1024) / PAGE_SIZE;
    for(uint32_t i=0; i<32768; i++) bitmap[i]=0;
    for(uint32_t i=0; i<256; i++) bitmap[i/8] |= (1 << (i%8));
}

uint32_t pmm_alloc_page() {
    for(uint32_t i=0; i<total_pages; i++) {
        if(!(bitmap[i/8] & (1 << (i%8)))) {
            bitmap[i/8] |= (1 << (i%8));
            return i * PAGE_SIZE;
        }
    }
    return 0;
}

void pmm_free_page(uint32_t addr) {
    uint32_t page = addr / PAGE_SIZE;
    bitmap[page/8] &= ~(1 << (page%8));
}
