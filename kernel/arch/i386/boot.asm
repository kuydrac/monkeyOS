global _start

F_ALIGN     equ 0x1                 ; align loaded modules on page boundaries
F_MEMINFO   equ 0x2                 ; provide memory map
FLAGS       equ F_ALIGN | F_MEMINFO ; Multiboot flag field
MAGIC       equ 0x1BADB002          ; Multiboot magic number
CHECKSUM    equ -(MAGIC + FLAGS)

; Declare header in Multiboot Standard
section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

KERNEL_STACK_SIZE equ 4096          ; 4 KiB
section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text
%include "gdt.asm"
%include "switch_kernel.asm"
_start:
;    mov esp, kernel_stack + KERNEL_STACK_SIZE
    call switch_to_kernel
kernel_entry:
    [extern kernel_main]
    call kernel_main 
loop:
    jmp loop
