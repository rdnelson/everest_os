#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H

#include <common.h>

struct gdt_entry {
	u16int_t	limit_low;
	u16int_t	base_low;
	u8int_t		base_middle;
	u8int_t		access;
	u8int_t		granularity;
	u8int_t		base_high;
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr {
	u16int_t 	limit;
	u32int_t 	base;
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

struct idt_entry {
	u16int_t	base_low;
	u16int_t	seg_select;
	u8int_t		reserved;
	u8int_t		flags;
	u16int_t	base_high;
}__attribute__((packed));
typedef struct idt_entry idt_entry_t;

struct idt_ptr {
	u16int_t limit;
	u32int_t base;
}__attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

typedef void (*isr_ptr)();

extern void isr_no_err();
extern void isr_err();

void isr_common();

void init_gdt_idt();

#endif
