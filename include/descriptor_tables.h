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

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void isr_common();

void init_gdt_idt();

#endif
