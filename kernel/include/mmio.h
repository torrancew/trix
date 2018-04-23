#ifndef _MMIO_H
#define _MMIO_H

#include <stdint.h>

static inline uint32_t mmio_read(uint32_t addr) { return *(volatile uint32_t*)addr; }

static inline void mmio_write(uint32_t addr, uint32_t data) { *(volatile uint32_t*)addr = data; }

#endif
