[GLOBAL gdt_flush]
[GLOBAL idt_flush]
[GLOBAL page_flush]


gdt_flush:
  cli
  mov eax, [esp+4]
  lgdt [eax]

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  jmp 0x08:.flush
.flush:
  sti
  ret

idt_flush:
  cli
  mov eax, [esp+4]
  lidt [eax]
  sti
  ret


page_flush:
  cli
  mov eax, [esp+4]
  mov cr3, eax
  mov eax, cr0
  or  eax, 0x80000000
  mov cr0, eax
  sti
  jmp $
  ret
