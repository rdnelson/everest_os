#ifndef VGA_TEXT_H
#define VGA_TEXT_H

#include <common.h>

#define CONSOLE_HEIGHT	25
#define CONSOLE_WIDTH	80

#define CONSOLE_COLOR(fg, bg) (((bg << 4) | (fg & 0x0F)) & 0xFF)
#define CONSOLE_CHAR(c, attr) (c | (attr << 8))

#define COLOR_BLACK	0
#define COLOR_BLUE	1
#define COLOR_GREEN	2
#define COLOR_CYAN	3
#define COLOR_RED	4
#define COLOR_MAGENTA	5
#define COLOR_BROWN	6
#define COLOR_LGREY	7
#define COLOR_GREY	8
#define COLOR_LBLUE	9
#define COLOR_LGREEN	10
#define COLOR_LCYAN	11
#define COLOR_LRED	12
#define COLOR_LMAGENTA	13
#define COLOR_LBROWN	14
#define COLOR_WHITE	15

void monitor_clear();
void monitor_put(char c);
void monitor_print(char* c);
void monitor_print_hex(u32int_t);
void monitor_print_dec(u32int_t);
void vga_printk(char* fmt, ...);

//extern u16int_t* vid_mem;
//extern int cursor_x;
//extern int cursor_y;

#endif
