#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>

extern uint32_t page_directory[1024];
extern uint32_t page_table[1024];

void paging_init(void);

#endif
