#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>
#include <stdint.h>

int8_t memcmp(const void*, const void*, size_t);
void* memset(void*, uint8_t, size_t);
void* memcpy(void*, const void*, size_t);
void* memmove(void*, const void*, size_t);

size_t strlen(const char*);

#endif
