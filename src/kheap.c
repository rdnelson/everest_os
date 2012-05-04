#include <kheap.h>
#include <common.h>
#include <vga_text.h>

extern u32int_t end;
u32int_t placement_addr = (u32int_t)&end;

u32int_t _kmalloc(u32int_t size, int bAlign, u32int_t *phys_addr) {
	monitor_print("kmalloc allocating ");
	monitor_print_dec(size);
	monitor_print(" bytes at location: ");

	if(bAlign != 0 && (placement_addr & 0xFFFFF000) ) {
		monitor_print("(They are page aligned) \n");
		placement_addr &= 0xFFFFF000;
		placement_addr += 0x1000;
	}
	if(phys_addr) {
		*phys_addr = placement_addr;
	}

	monitor_print_hex(placement_addr);
	monitor_put('\n');

	u32int_t tmp = placement_addr;
	placement_addr += size;
	return tmp;
}

u32int_t kmalloc(u32int_t size) {
	return _kmalloc(size, 0, 0);
}

u32int_t kmalloc_a(u32int_t size) { 
	return _kmalloc(size, 1, 0);
}

u32int_t kmalloc_p(u32int_t size, u32int_t *phys_addr) {
	return _kmalloc(size, 0, phys_addr);
}

u32int_t kmalloc_ap(u32int_t size, u32int_t *phys_addr) {
	return _kmalloc(size, 1, phys_addr);
}
