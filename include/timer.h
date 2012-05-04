#ifndef TIMER_H
#define TIMER_H

#include <common.h>

#define TIMER_CHAN1 0x40
#define TIMER_CMD 0x43

void init_timer(u32int_t freq);

#endif
