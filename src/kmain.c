#include <vga_text.h>
#include <descriptor_tables.h>

int kmain(struct multiboot *mboot_ptr) {
	monitor_clear();
	monitor_print("Hello World\n");
	monitor_print("This is a test of the newline stuff!\n\n");
	monitor_print("Testing hex out: ");
	monitor_print_hex(0xDEADBEEF);
	monitor_print("\nTesting dec out: ");
	monitor_print_dec(123456789);
	monitor_put('\n');
	init_gdt_idt();
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");
	monitor_print("I'm frozen now, goodbye.\n");
	return 0xDEADBEEF;
}
