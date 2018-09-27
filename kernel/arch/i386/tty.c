#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/ports.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static uint16_t const VGA_CTRL = (uint16_t) 0x3d4;
static uint16_t const VGA_DATA = (uint16_t) 0x3d5;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void update_cursor();
void set_cursor(size_t x, size_t y);

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
    update_cursor();
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll() {
    size_t i;
    for (i=0; i < VGA_HEIGHT - 1; i++){
        const size_t index = i * VGA_WIDTH;
        memcpy(terminal_buffer + index, terminal_buffer + index + VGA_WIDTH, \
            sizeof(terminal_buffer) * VGA_WIDTH);
    }
    const size_t index = i * VGA_WIDTH;
    for (i=0; i < VGA_WIDTH; i++){
        terminal_buffer[index + i] = vga_entry(' ',terminal_color);
    }
	
	if (terminal_row != 0){
		--terminal_row; 
	}
}

void terminal_putchar(char c) {
    if (c == '\n'){
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_scroll();
    }
    else if (c == '\b'){
        if (terminal_column-- == 0){
            terminal_column = VGA_WIDTH - 1;
            if (terminal_row-- == 0){
                terminal_row = 0;
                terminal_column = 0;
            }
        }
		terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_scroll();
		}
    }
	else{
		unsigned char uc = c;
		terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_scroll();
		}
	}
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++){
		terminal_putchar(data[i]);
    }
    update_cursor();
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void set_cursor(size_t x, size_t y){
	const size_t index = y * VGA_WIDTH + x;
    port_byte_out(VGA_CTRL, 14);
    port_byte_out(VGA_DATA, (uint8_t)(index >> 8));
    port_byte_out(VGA_CTRL, 15);
    port_byte_out(VGA_DATA, (uint8_t)(index & 0xFF));
}

void update_cursor(){
    set_cursor(terminal_column, terminal_row);
}
