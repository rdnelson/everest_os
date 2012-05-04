#ifndef ISR_H
#define ISR_H

#include <common.h>

#define PIC_MASTER_CMD 0x20
#define PIC_SLAVE_CMD 0xA0
#define PIC_MASTER_DATA PIC_MASTER_CMD + 1
#define PIC_SLAVE_DATA PIC_SLAVE_CMD + 1

#define PIC_INIT 0x11
#define PIC_EOI 0x20
#define PIC_MASTER_OFFSET 0x20
#define PIC_SLAVE_OFFSET PIC_MASTER_OFFSET + 0x08

#define IRQ0	32
#define IRQ1	33
#define IRQ2	34
#define IRQ3	35
#define IRQ4	36
#define IRQ5	37
#define IRQ6	38
#define IRQ7	39
#define IRQ8	40
#define IRQ9	41
#define IRQ10	42
#define IRQ11	43
#define IRQ12	44
#define IRQ13	45
#define IRQ14	46
#define IRQ15	47

typedef struct registers {
	u32int_t ds;
	u32int_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32int_t int_no, err_code;
	u32int_t eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*isr_t)(registers_t);
void register_interrupt_handler(u8int_t n, isr_t handler);

#endif
