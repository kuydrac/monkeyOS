switch_to_kernel:
    cli                     ; 1. disable interrupts
    lgdt [gdt_descriptor]   ; 2. load the GDT descriptor
;    mov eax, cr0
;    or eax, 0x1
;    mov cr0, eax            ; 3. set 32-bit mode bit in cr0
    jmp CODE_SEG:stk_done   ; 4. far jump by using a different segment

stk_done:
    mov ax, DATA_SEG        ; 5. update the segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000        ; 6. update stack at top of the free space
    mov esp, ebp

    call kernel_entry       ; 7. call a well-known label with useful code
