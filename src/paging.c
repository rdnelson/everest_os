#include <paging.h>
#include <string.h>
#include <vga_text.h>
#include <kheap.h>

u32int_t *frames;
u32int_t nframes;

extern u32int_t placement_addr;
extern u32int_t code;

#define INDEX_FROM_BIT(a) (a/(32))
#define OFFSET_FROM_BIT(a) (a%(32))

#define PANIC(msg) monitor_print("======< PANIC >======\n"); \
	monitor_print(msg); \
	monitor_print("Error Occured at: "); \
	monitor_print(__FILE__); \
	monitor_put(':'); \
	monitor_print_dec(__LINE__); \
	monitor_put('\n'); \
       	asm volatile("1:;" "jmp 1b;") //causes an infinite loop

page_dir_t* kernel_dir;
page_dir_t* cur_dir;

static void set_frame(u32int_t frame_addr) {
	u32int_t frame = frame_addr / 0x1000;
	frames[INDEX_FROM_BIT(frame)] |= (0x1 << OFFSET_FROM_BIT(frame));
}

static void clear_frame(u32int_t frame_addr) {
	u32int_t frame = frame_addr / 0x1000;
	frames[INDEX_FROM_BIT(frame)] &= ~(0x1 << OFFSET_FROM_BIT(frame));
}

static u32int_t test_frame(u32int_t frame_addr) { 
	u32int_t frame = frame_addr / 0x1000;
	return frames[INDEX_FROM_BIT(frame)] & (0x1 << OFFSET_FROM_BIT(frame));
}

static u32int_t first_frame() {
	u32int_t i, j;
	for(i = 0; i < INDEX_FROM_BIT(nframes); i++) {
		if(frames[i] != 0xFFFFFFFF) { //at least one bit isn't set
			for(j = 0; j < 32; j++) {
				if(!(frames[i] & (0x1 << j))) {
					return i*32 + j;
				}
			}
		}
	}
	return (u32int_t)-1;
}

void _alloc_frame(page_t *page, int is_kernel, int is_writable, u32int_t frame) {
	if(page->frame) {
		return;
	}
	u32int_t idx = frame; 

	if(idx == (u32int_t)-1) {
		PANIC("No Free Frames.");
	}

	set_frame(idx * 0x1000);
	page->present = 1;
	page->rw = is_writable ? 1 : 0;
	page->user = is_kernel ? 0 : 1;
	page->frame = idx;
}

void alloc_frame(page_t *page, int is_kernel, int is_writable) {
	_alloc_frame(page, is_kernel, is_writable, first_frame());
}

void free_frame(page_t *page) {
	u32int_t frame;
	if(!(frame=page->frame)) {
		return;
	}
	clear_frame(frame);
	page->frame = 0x0;
}

void init_paging(u32int_t mem_size) {
	nframes = mem_size / 0x1000; //number of frames occupied by memory
	frames = (u32int_t*)kmalloc(INDEX_FROM_BIT(nframes)); //create bitmap
	memset(frames, 0, INDEX_FROM_BIT(nframes)); //initialize bitmap to zero (no pages/frames occupied)

	kernel_dir = (page_dir_t*)kmalloc_a(sizeof(page_dir_t)); //create kernel directory (page aligned)
	memset(kernel_dir, 0, sizeof(page_dir_t)); //clear it
	kernel_dir->physical_addr = (u32int_t)kernel_dir; //store it's physical address
	cur_dir = kernel_dir;

	int i = 0;
	u32int_t frame = first_frame();
	while(i < placement_addr) {
		_alloc_frame(get_page(i, 1, kernel_dir) , 0, 0, frame++);
		i += 0x1000;
	}

	register_interrupt_handler(14, page_fault);

	switch_page_dir(kernel_dir);
}

void switch_page_dir(page_dir_t *dir) {
	cur_dir = dir;
	asm volatile("mov %0, %%cr3":: "r"(dir->tables_physical));
	u32int_t cr0;
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(u32int_t addr, int make, page_dir_t *dir) {
	addr /= 0x1000;
	u32int_t table_idx = addr / 1024;
	if(dir->tables[table_idx]) {
		return &dir->tables[table_idx]->pages[addr % 1024];
	} else if(make) {
		u32int_t tmp_phys_addr;
		dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp_phys_addr);
		memset(dir->tables[table_idx], 0, 0x1000);
		dir->tables_physical[table_idx] = tmp_phys_addr | 0x7;
		return &dir->tables[table_idx]->pages[addr % 1024];
	}
	return 0;
}

void page_fault(registers_t regs) { 
	u32int_t fault_addr;
	asm volatile("mov %%cr2, %0" : "=r" (fault_addr));

	monitor_print("Page Fault! ( ");
	if(!(regs.err_code & 0x01)) monitor_print("present ");
	if(!(regs.err_code & 0x02)) monitor_print("read-only ");
	if(regs.err_code & 0x04) monitor_print("user-mode ");
	if(regs.err_code & 0x08) monitor_print("reserved ");
	monitor_print(") at ");
	monitor_print_hex(fault_addr);
	monitor_put('\n');
	PANIC("Page Fault");
}	
