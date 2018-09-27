#ifndef _KERNEL_SERIAL_H
#define _KERNEL_SERIAL_H

#include <stdint.h>
#include <stddef.h>

void serial_configure(uint16_t);
void serial_write(uint16_t,const char*,size_t);
void serial_writestring(uint16_t,const char*);

#endif
