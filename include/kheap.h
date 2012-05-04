#ifndef KHEAP_H
#define KHEAP_H

#include <common.h>

u32int_t kmalloc(u32int_t);
u32int_t kmalloc_a(u32int_t);
u32int_t kmalloc_p(u32int_t, u32int_t*);
u32int_t kmalloc_ap(u32int_t, u32int_t*);

#endif
