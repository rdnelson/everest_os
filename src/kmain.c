#include <kmain.h>
#include <vga_text.h>
#include <descriptor_tables.h>
#include <timer.h>
#include <paging.h>

int kmain(multiboot_info_t *mboot_ptr) {
	monitor_clear();
	vga_printk("Lower memory: %d KB\n", mboot_ptr->mem_lower);
	monitor_print_dec(mboot_ptr->mem_lower);
	vga_printk("Upper memory: %d MB\n", mboot_ptr->mem_upper/1024);
	init_gdt_idt();
	vga_printk("Hello printk\nString: %s\nHex: %x\nInteger: %d\n", "I'm Text!", 0xB005ED06, 12345);
	asm volatile("sti");
	//init_timer(50);
	init_paging(mboot_ptr->mem_upper * 1024);
	u32int_t *ptr = 0xA0000000;
	//*ptr = 5;
	monitor_print("Finished successfully! Deliberately Page faulting now...");
	*ptr = 5;
	return 0xDEADBEEF;
}
