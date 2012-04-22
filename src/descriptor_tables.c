#include <descriptor_tables.h>
#include <common.h>
#include <vga_text.h>

extern void gdt_flush(u32int_t);
extern void idt_flush(u32int_t);

static void init_gdt();
static void init_idt();

static void gdt_set_gate(s32int_t, u32int_t, u32int_t, u8int_t, u8int_t);
static void idt_set_gate(u8int_t, u32int_t, u16int_t, u8int_t);

gdt_entry_t	gdt_entries[5];
gdt_ptr_t	gdt_ptr;

idt_entry_t	idt_entries[256];
idt_ptr_t	idt_ptr;

void init_gdt_idt() {

	init_gdt();
	init_idt();
}

static void init_gdt() {

	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base = (u32int_t)gdt_entries; //Huh? Extra dereference...
	monitor_print("\ngdt address: ");
	monitor_print_hex(gdt_ptr.base);
	monitor_put('\n');

	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); //Data Segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); //User mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); //User Mode data segment

	gdt_flush((u32int_t)&gdt_ptr);
}

static void init_idt() {
	idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
	idt_ptr.base = (u32int_t)idt_entries;

	memset(idt_entries, 0, sizeof(idt_entry_t) * 256);

	idt_set_gate(0, (u32int_t)isr0, 0x08, 0x8E);
	idt_set_gate(1, (u32int_t)isr1, 0x08, 0x8E);
	idt_set_gate(2, (u32int_t)isr2, 0x08, 0x8E);
	idt_set_gate(3, (u32int_t)isr3, 0x08, 0x8E);
	idt_set_gate(4, (u32int_t)isr4, 0x08, 0x8E);
	idt_set_gate(5, (u32int_t)isr5, 0x08, 0x8E);
	idt_set_gate(6, (u32int_t)isr6, 0x08, 0x8E);
	idt_set_gate(7, (u32int_t)isr7, 0x08, 0x8E);
	idt_set_gate(8, (u32int_t)isr8, 0x08, 0x8E);
	idt_set_gate(9, (u32int_t)isr9, 0x08, 0x8E);
	idt_set_gate(10, (u32int_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (u32int_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (u32int_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (u32int_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (u32int_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (u32int_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (u32int_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (u32int_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (u32int_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (u32int_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (u32int_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (u32int_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (u32int_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (u32int_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (u32int_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (u32int_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (u32int_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (u32int_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (u32int_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (u32int_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (u32int_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (u32int_t)isr31, 0x08, 0x8E);

	idt_flush((u32int_t)&idt_ptr);
}

static void gdt_set_gate(s32int_t num, u32int_t base, u32int_t limit, u8int_t access, u8int_t gran) {
	gdt_entries[num].base_low 	= (base & 0xFFFF);
	gdt_entries[num].base_middle	= (base >> 16) & 0xFF;
	gdt_entries[num].base_high	= (base >> 24) & 0xFF;
	
	gdt_entries[num].limit_low	= (limit & 0xFFFF);
	gdt_entries[num].granularity	= (limit >> 16) & 0x0F;
	gdt_entries[num].granularity 	|= gran & 0xF0;
	gdt_entries[num].access		= access;
}

static void idt_set_gate(u8int_t num, u32int_t base, u16int_t sel, u8int_t flags) {
	idt_entries[num].base_low = base & 0xFFFF;
	idt_entries[num].base_high = (base >> 16) & 0xFFFF;

	idt_entries[num].seg_select = sel;
	idt_entries[num].reserved = 0;
	idt_entries[num].flags = flags;
}

