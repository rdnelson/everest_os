#include <common.h>

/* The section header table for ELF. */
typedef struct elf_section_header_table
{
u32int_t num;
u32int_t size;
u32int_t addr;
u32int_t shndx;
} elf_section_header_table_t;

/* The Multiboot information. */
typedef struct multiboot_info
{
u32int_t flags;
u32int_t mem_lower;
u32int_t mem_upper;
u32int_t boot_device;
u32int_t cmdline;
u32int_t mods_count;
u32int_t mods_addr;
elf_section_header_table_t elf_sec;
u32int_t mmap_length;
u32int_t mmap_addr;
} multiboot_info_t;

/* The module structure. */
typedef struct module
{
u32int_t mod_start;
u32int_t mod_end;
u32int_t string;
u32int_t reserved;
} module_t;

/* The memory map. Be careful that the offset 0 is base_addr_low
but no size. */
typedef struct memory_map
{
u32int_t size;
u32int_t base_addr_low;
u32int_t base_addr_high;
u32int_t length_low;
u32int_t length_high;
u32int_t type;
} memory_map_t;

