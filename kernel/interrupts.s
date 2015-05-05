%macro ISR_NOERRCODE 2
  %ifnidn %2,isr_nothing
    [EXTERN %2]
  %endif
  [GLOBAL isr%1]
  isr%1:
    pushad
    cld
    call %2
    popad
    iret
%endmacro

%macro ISR_ERRCODE 2
  %ifnidn %2,isr_nothing
    [EXTERN %2]
  %endif
  [GLOBAL isr%1]
  isr%1:
    pushad
    mov eax, [esp + 32]
    cld
    push eax
    call %2
    add esp, 4
    popad
    add esp, 4
    iret
%endmacro

isr_nothing:
  ret

ISR_NOERRCODE 0,  isr_nothing
ISR_NOERRCODE 1,  isr_nothing
ISR_NOERRCODE 2,  isr_nothing
ISR_NOERRCODE 3,  isr_nothing
ISR_NOERRCODE 4,  isr_nothing
ISR_NOERRCODE 5,  isr_nothing
ISR_NOERRCODE 6,  isr_nothing
ISR_NOERRCODE 7,  isr_nothing
ISR_ERRCODE   8,  isr_nothing
ISR_NOERRCODE 9,  isr_nothing
ISR_ERRCODE   10, isr_nothing
ISR_ERRCODE   11, isr_nothing
ISR_ERRCODE   12, isr_nothing
ISR_ERRCODE   13, isr_nothing
ISR_ERRCODE   14, isr_nothing
ISR_NOERRCODE 15, isr_nothing
ISR_NOERRCODE 16, isr_nothing
ISR_ERRCODE   17, isr_nothing
ISR_NOERRCODE 18, isr_nothing
ISR_NOERRCODE 19, isr_nothing
ISR_NOERRCODE 20, isr_nothing
ISR_NOERRCODE 21, isr_nothing
ISR_NOERRCODE 22, isr_nothing
ISR_NOERRCODE 23, isr_nothing
ISR_NOERRCODE 24, isr_nothing
ISR_NOERRCODE 25, isr_nothing
ISR_NOERRCODE 26, isr_nothing
ISR_NOERRCODE 27, isr_nothing
ISR_NOERRCODE 28, isr_nothing
ISR_NOERRCODE 29, isr_nothing
ISR_NOERRCODE 30, isr_nothing
ISR_NOERRCODE 31, isr_nothing
ISR_NOERRCODE 32, isr_nothing

