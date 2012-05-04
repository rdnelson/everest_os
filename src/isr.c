#include <common.h>
#include <isr.h>
#include <vga_text.h>

isr_t interrupt_handlers[256] = {0};
u32int_t prev_int = 0xFFFF;

void isr_handler(registers_t regs) {
	if(regs.int_no != prev_int) {
	monitor_print("recieved interrupt: ");
	monitor_print_dec(regs.int_no);
	monitor_put('\n');
	prev_int = regs.int_no;
	}

	if(interrupt_handlers[regs.int_no] != 0) {
		interrupt_handlers[regs.int_no](regs);
	}
}

void irq_handler(registers_t regs) {
	if(regs.int_no >= 40) {
		outb(PIC_SLAVE_CMD, PIC_EOI);
	}

	outb(PIC_MASTER_CMD, PIC_EOI);

	if(interrupt_handlers[regs.int_no] != 0) {
		interrupt_handlers[regs.int_no](regs);
	}
}

void register_interrupt_handler(u8int_t n, isr_t handler) {
	interrupt_handlers[n] = handler;
}
