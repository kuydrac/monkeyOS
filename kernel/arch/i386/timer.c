#include <kernel/timer.h>
#include <kernel/isr.h>
#include <kernel/ports.h>

uint32_t tick = 0;

static void timer_callback(__attribute__((unused)) registers_t *regs){
    tick++;
}

void init_timer(uint32_t freq){
    // Install IRQ
    register_interrupt_handler(IRQ0, timer_callback);

    // Get the PIT value: hardware clock at 1193180 Hz
    uint32_t divisor = 1193180 / freq;
    // Send the command
    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, divisor & 0xFF);
    port_byte_out(0x40, (divisor >> 8) & 0xFF);
}

uint32_t get_tick(){
    return tick;
}
