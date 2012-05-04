#include <kmain.h>
#include <vga_text.h>
#include <descriptor_tables.h>
#include <timer.h>
#include <paging.h>

int kmain(multiboot_info_t *mboot_ptr) {
	monitor_clear();
	monitor_print("Hello World\n");
	monitor_print("This is a test of the newline stuff!\n\n");
	monitor_print("Testing hex out: ");
	monitor_print_hex(0xDEADBEEF);
	monitor_print("\nTesting dec out: ");
	monitor_print_dec(123456789);
	monitor_put('\n');
	monitor_print("Lower memory: ");
	monitor_print_dec(mboot_ptr->mem_lower);
	monitor_print(" KB\nUpper memory: ");
	monitor_print_dec(mboot_ptr->mem_upper/1024);
	monitor_print(" MB\n");
	monitor_put('\n');
	init_gdt_idt();
	asm volatile("sti");
	//init_timer(50);
	init_paging(mboot_ptr->mem_upper * 1024);
	u32int_t *ptr = 0xA0000000;
	//*ptr = 5;
	monitor_print("Finished successfully! Deliberately Page faulting now...");
	*ptr = 5;
	return 0xDEADBEEF;
}
