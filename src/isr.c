#include <common.h>
#include <isr.h>
#include <vga_text.h>

void isr_handler(registers_t regs) {
	monitor_print("recieved interrupt: ");
	monitor_print_dec(regs.int_no);
	monitor_put('\n');
}

