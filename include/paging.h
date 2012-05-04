#ifndef PAGING_H
#define PAGING_H

#include <common.h>
#include <isr.h>

typedef struct page {
	u32int_t present	: 1;
	u32int_t rw		: 1;
	u32int_t user		: 1;
	u32int_t accessed	: 1;
	u32int_t dirty		: 1;
	u32int_t unused		: 7;
	u32int_t frame		: 20;
} page_t;

typedef struct page_table {
	page_t pages[1024];
} page_table_t;

typedef struct page_dir {
	page_table_t *tables[1024];
	u32int_t tables_physical[1024];
	u32int_t physical_addr;
} page_dir_t;


//functions
void init_paging();
void switch_page_dir(page_dir_t *new);
page_t *get_page(u32int_t addr, int bMake, page_dir_t *dir);
void page_fault(registers_t regs);

#endif
