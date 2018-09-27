#include <kernel/serial.h>
#include <kernel/ports.h>
#include <string.h>

// I/O ports
#define SERIAL_COM1_BASE                0x3F8

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

// Commands
#define SERIAL_LINE_ENABLE_DLAB         0x80

uint16_t serial_get_com(uint16_t com){
    switch(com){
        case 1:
            return SERIAL_COM1_BASE;
            break;
        default:
            return SERIAL_COM1_BASE;
    }
}

void serial_configure_baud_rate(uint16_t com, uint16_t divisor){
    port_byte_out(SERIAL_LINE_COMMAND_PORT(com),
        SERIAL_LINE_ENABLE_DLAB);
    port_byte_out(SERIAL_DATA_PORT(com), (divisor >> 8) & 0xFF);
    port_byte_out(SERIAL_DATA_PORT(com), divisor & 0xFF);
}

void serial_configure_line(uint16_t com){
    port_byte_out(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffer(uint16_t com){
    port_byte_out(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(uint16_t com){
    port_byte_out(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

void serial_configure(uint16_t com){
    uint16_t com_num = serial_get_com(com);
    serial_configure_baud_rate(com_num, 0x1);
    serial_configure_line(com_num);
    serial_configure_buffer(com_num);
    serial_configure_modem(com_num);
}

uint8_t serial_is_transmit_fifo_empty(uint16_t com){
    return port_byte_in(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_data_out(uint16_t com, uint8_t data){
    while (!serial_is_transmit_fifo_empty(com));
    port_byte_out(SERIAL_DATA_PORT(com), data);
}

void serial_write(uint16_t com, const char* data, size_t size){
    uint16_t com_num = serial_get_com(com);
    for (size_t i=0; i < size; i++){
        serial_data_out(com_num, data[i]);
    }
}

void serial_writestring(uint16_t com, const char* data){
    serial_write(com, data, strlen(data));
}
