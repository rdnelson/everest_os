/* Linker script */

ENTRY(_kaslow)
SECTIONS
{
  . = 0xC0100000;

  .text : AT ( ADDR(.text) - 0xC0000000 )
  {
    text = .; _text = .; __text = .;
    *(.text)
    . = ALIGN(4096);
  } 

  .data : AT ( ADDR(.data) - 0xC0000000 )
  {
    data = .; _data = .; __data = .;
    *(.data)
    *(.rodata)
    . = ALIGN(4096);
  }

  .bss : AT ( ADDR(.bss) - 0xC0000000 )
  {
    bss = .; _bss = .; __bss = .;
    *(.bss)
    . = ALIGN(4096);
  }

  /* .text 0xC0000000 : */

  end = .; _end = .; __end = .;
}

