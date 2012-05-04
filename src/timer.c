#include <timer.h>
#include <isr.h>
#include <vga_text.h>

u32int_t tick = 0;

static void timer_callback(registers_t regs) {
	tick++;
	monitor_print("Tick: ");
	monitor_print_dec(tick);
	monitor_put('\n');
}

void init_timer(u32int_t freq) {
	register_interrupt_handler(IRQ0, &timer_callback);

	u32int_t divisor = 1193180 / freq;

	outb(TIMER_CMD, 0x36);
	outb(TIMER_CHAN1, (u8int_t)(divisor & 0xFF));
	outb(TIMER_CHAN1, (u8int_t)((divisor >> 8) & 0xFF));
}
