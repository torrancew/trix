#ifndef _SERIAL_H
#define _SERIAL_H

#include <stddef.h>

void serial_init(void);
char serial_getc(void);
void serial_putc(unsigned char);
void serial_puts(const char*);
void serial_write(const char*, size_t);

#endif
