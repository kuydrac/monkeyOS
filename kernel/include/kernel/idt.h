#ifndef _KERNEL_IDT_H
#define _KERNEL_IDT_H

#include <stdint.h>

// Segment selectors
#define KERNEL_CS 0x08

// Define interrupt gate (handler)
typedef struct {
    uint16_t low_offset;    // Lower 16 bits of handler function address
    uint16_t sel;           // Kernel segment selector
    uint8_t always0;        // [7] - "Interrupt is present"
                            // [6:5] - Privilege level of caller (0=kernel..3=user)
                            // [4] - Set to 0 for interrupt gates
                            // [3:0] - 1110b = "32 bit interrupt gate"
    uint8_t flags;
    uint16_t high_offset;   // Higher 16 bits of handler function address
} __attribute__((packed)) idt_gate_t;

// Pointer to the array of interrupt handlers
typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256

void set_idt_gate(int n, uint32_t handler);
void set_idt();

#endif
