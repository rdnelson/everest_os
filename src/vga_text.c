#include <vga_text.h>
#include <common.h>
#include <string.h>

static u16int_t* vid_mem = 0xB8000;
static int cursor_x = 0;
static int cursor_y = 0;

// internal only
static void move_cursor() {
	u16int_t cursor_loc = cursor_y * CONSOLE_WIDTH + cursor_x;
	outb(0x3D4, 14); 	// Set High VGA cursor byte
	outb(0x3D5, cursor_loc >> 8);
	outb(0x3D4, 15);	// Set Low VGA cursor byte
	outb(0x3D5, cursor_loc & 0xFF);
}

// internal only
static void scroll() {
	u8int_t attr_byte = (COLOR_BLACK << 4) | (COLOR_WHITE & 0xF);
	u16int_t blank = 0x20 | (attr_byte << 8);

	if(cursor_y >= CONSOLE_HEIGHT) {
		int i;
		for(i = 0; i < (CONSOLE_HEIGHT - 1); i++) {
			memcpy(vid_mem + i*CONSOLE_WIDTH, vid_mem + (i+1)*CONSOLE_WIDTH, CONSOLE_WIDTH*sizeof(u16int_t));
		}
		memset(vid_mem + (CONSOLE_HEIGHT - 1)*CONSOLE_WIDTH, 0, CONSOLE_WIDTH*sizeof(u16int_t));

		cursor_y = CONSOLE_HEIGHT - 1;
	}
}

void monitor_put(char c) {

	u8int_t bg_color = COLOR_BLACK;
	u8int_t fg_color = COLOR_WHITE;

	u8int_t attr_byte = (bg_color << 4) | (fg_color & 0xF);

	u16int_t attr = attr_byte << 8;
	u16int_t* loc;

	if(c == 0x08 && cursor_x) { //backspace
		cursor_x--;
	}else if(c == 0x09) { //tab
		cursor_x = (cursor_x + 8) & ~(7); //round to nearest 8th column
	}else if(c == '\n') {
		cursor_x = 0;
		cursor_y++;
	}else if(c >= ' ') { //the printables
		loc = vid_mem + (cursor_y*CONSOLE_WIDTH + cursor_x);
		*loc = c | attr;
		cursor_x++;
	}

	if(cursor_x >= CONSOLE_WIDTH) {
		cursor_x = 0;
		cursor_y++;
	}

	move_cursor();

	scroll();
}

void monitor_clear() {
	int i;
	for(i = 0; i < CONSOLE_WIDTH*CONSOLE_HEIGHT; i++)
		vid_mem[i] = CONSOLE_CHAR(' ', CONSOLE_COLOR(COLOR_WHITE, COLOR_BLACK));
}

void monitor_print(char* str) {
	if(str != NULL) {
		while(*str != 0)
			monitor_put(*(str++));
	}
}

void monitor_print_hex(u32int_t val) {
	char* map = "0123456789ABCDEF";
	int i;
	monitor_print("0x");
	for(i = sizeof(val) * 2 - 1; i >= 0; i--) {
		monitor_put(map[(val >> (i * 4)) & 0xF]);
	}
}

void monitor_print_dec(u32int_t val) {
	char buf[10] = {0};
	int i = 0;
	do {
		buf[i++] = ('0' + (val % 10));
		val /= 10;
	} while(val != 0);

	for(;i>0; i--)
		monitor_put(buf[i-1]);

}
