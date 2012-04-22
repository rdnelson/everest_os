#ifndef COMMON_H
#define COMMON_H

typedef unsigned int	u32int_t;
typedef 	 int	s32int_t;
typedef unsigned short	u16int_t;
typedef 	 short	s16int_t;
typedef unsigned char	u8int_t;
typedef 	 char	s8int_t;

typedef 	 int	size_t;

#define NULL	0

//port access commands
void outb(u16int_t port, u8int_t val);
u8int_t inb(u16int_t port);
u16int_t inw(u16int_t port);

#endif
