[extern isr_handler]

[GLOBAL isr_no_err]
isr_no_err:
  cli
  push byte 0
  push byte %1
  jmp isr_common_stub

[GLOBAL isr_err]
isr_err:
  cli
  push byte %1
  jmp isr_common_stub

isr_common_stub:
  pusha

  mov ax, ds
  push eax

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call isr_handler

  pop eax
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa
  add esp, 8
  sti
  iret

