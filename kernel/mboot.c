#include <mboot.h>
#include <vga_text.h>

char* mem_types[] = { "Invalid Type", "Usable", "Reserved", "Reclaimable", "Non-volatile", "Bad" };

void print_entry(multiboot_uint32_t entry_addr) {
    struct multiboot_mmap_entry* entry = (struct multiboot_mmap_entry*)entry_addr;

    monitor_printf("Addr: %x   Len: %x  Type: %s\n", (uint32_t)entry->addr, (uint32_t)entry->len, mem_types[entry->type]);
}
