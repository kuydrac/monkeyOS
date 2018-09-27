gdt_start:
    ; GDT start with a null 8-byte
    dd 0x0
    dd 0x0

; GDT for code segment. base = 0x00000000, length = 0xffffffff
; for flags, refer to os-dev.pdf doc, page 36
; G=1   (Granularity)               1-> limit * 4K 
; D/B=1 (Default operation size)    1->32b segment  0->16b segment
; L=0                               1->64b code segment (IA-32e mode only)
; AVL=0 (Available)                 1->Available for use by system software
; P=1   (Present)                   1->segment present
; DPL=00    (Descriptor privilege level)    00-> ring 0
; S=1   (Descriptor type)           1->code or data  0->system
; Type=1010 (Code)                  1->code
;           (Conforming)        0->code segment in lower DPL may not call this segment
;           (Readable)              1->readible     0->execute-only
;           (Accessed)              0->CPU sets this bit when accessing this segment
gdt_code:
    dw 0xffff       ; segment length, bits 0-15
    dw 0x0          ; segment base, bits 0-15
    db 0x0          ; segment base, bits 16-23
    db 10011010b    ; flags (8 bits)
    db 11001111b    ; flags (4 bits_ + segment length, bits 16-19
    db 0x0          ; segment base, bits 24-31

; GDT for data segment. base and length identicla to code segment
; Type=0010 (Code)                  0->not code (data)
;           (Expand down)           0->don't allow segment to expand down
;           (Writable)              1->writable     0->read-only
;           (Accessed)              0->same as code type 
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

; GDT descriptor
global gdt_descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1      ; size (16 bit), always 1 less that actual size
    dd gdt_start                    ; base address (32 bit)

; define offsets
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
