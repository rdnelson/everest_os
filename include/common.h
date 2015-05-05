#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#define NULL	0

//port access commands
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

#endif
