#ifndef _IO_H
#define _IO_H

#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
  uint8_t byte;
  __asm__("inb %%dx, %%al" : "=a"(byte) : "d"(port));
  return byte;
}

static inline uint16_t inw(uint16_t port) {
  uint16_t word;
  __asm__("inw %%dx, %%ax" : "=a"(word) : "d"(port));
  return word;
}

static inline void outb(uint16_t port, uint8_t byte) {
  __asm__("outb %%al, %%dx" : : "d"(port), "a"(byte));
}

static inline void outw(uint16_t port, uint16_t word) {
  __asm__("outw %%ax, %%dx" : : "d"(port), "a"(word));
}

#endif
