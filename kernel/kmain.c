#include <vga_text.h>
#include <descriptor_tables.h>
#include <multiboot.h>
#include <mboot.h>
#include <stdint.h>
#include <common.h>

int kmain(struct multiboot_info *mboot_ptr) {
    uint32_t mmap_entries;

    init_gdt_idt();
    monitor_clear();
    monitor_print("Hello World\n");

    monitor_printf("Cmd line: %s\n", (char*)mboot_ptr->cmdline);
    monitor_printf("Testing hex out: %x\n", 0xDEADBEEF);
    monitor_printf("Testing dec out: %d\n", 123456789);

    // Get number of memory map entries
    mmap_entries = mboot_ptr->mmap_length / sizeof(struct multiboot_mmap_entry);

    //setup_paging();

    monitor_printf("Memory Map Length: %d (Entries: %d)\n",
            mboot_ptr->mmap_length,
            mboot_ptr->mmap_length / sizeof(struct multiboot_mmap_entry));

    for(uint32_t i = 0; i < mmap_entries; i++) {
        print_entry(mboot_ptr->mmap_addr + (i * sizeof(struct multiboot_mmap_entry)));
    }

    monitor_print("I'm frozen now, goodbye.\n");
    //kmain(mboot_ptr);
    return 0xDEADB00F;
}

