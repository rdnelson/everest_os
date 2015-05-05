#include <descriptor_tables.h>
#include <common.h>
#include <vga_text.h>
#include <string.h>

extern void gdt_flush(uint32_t);
extern void idt_flush(uint32_t);

static void init_gdt();
static void init_idt();

static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

gdt_entry_t	gdt_entries[5];
gdt_ptr_t	gdt_ptr;

idt_entry_t	idt_entries[256];
idt_ptr_t	idt_ptr;

void init_gdt_idt() {
    init_idt();
    init_gdt();
}

static void init_gdt() {

    gdt_ptr.limit = sizeof(gdt_entries) - 1;
    gdt_ptr.base = (uint32_t)gdt_entries;
    //monitor_printf("gdt address: %x\n", gdt_ptr.base);

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); //Data Segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0x9A, 0xCF); //User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0x92, 0xCF); //User Mode data segment

    gdt_flush((uint32_t)&gdt_ptr);
}

static void init_idt() {
    idt_ptr.limit = sizeof(idt_entries) - 1;
    idt_ptr.base = (uint32_t)idt_entries;

    //memset(idt_entries, 0, sizeof(idt_entry_t) * 256);

    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
    idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
    idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
    idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
    idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
    idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
    idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
    idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
    idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
    idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);
    for(uint32_t i = 32; i < 256; i++) {
        idt_set_gate(i, (uint32_t)isr32, 0x08, 0x8E);
    }

    idt_flush((uint32_t)&idt_ptr);
}

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {

    if (limit > 0x10000 && (limit & 0xFFF) != 0xFFF) {
        while(1);
    }

    if (limit > 0x10000) {
        limit >>= 12;
        gran = 0xc0;
    } else {
        gran = 0x40;
    }

    gdt_entries[num].base_low 	= (base & 0xFFFF);
    gdt_entries[num].base_middle	= (base >> 16) & 0xFF;
    gdt_entries[num].base_high	= (base >> 24) & 0xFF;
    
    gdt_entries[num].limit_low	= (limit & 0xFFFF);
    gdt_entries[num].granularity	= (limit >> 16) & 0x0F;
    gdt_entries[num].granularity 	|= gran & 0xF0;
    gdt_entries[num].access		= access;
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;

    idt_entries[num].seg_select = sel;
    idt_entries[num].reserved = 0;
    idt_entries[num].flags = flags;
}

