#include <common.h>

void outb(u16int_t port, u8int_t val) {
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (val));
}

u8int_t inb(u16int_t port) {
	u8int_t ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

u16int_t inw(u16int_t port) {
	u16int_t ret;
	asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}


