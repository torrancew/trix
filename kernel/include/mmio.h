/*! \file mmio.h
 *  \brief The mmio.h file contains functions for interfacing with memory-mapped I/O devices
 */
#ifndef _MMIO_H
#define _MMIO_H

#include <stdint.h>

/* \brief Read 32 bits from a memory-mapped I/O device
 */
static inline uint32_t mmio_read(uint32_t addr) { return *(volatile uint32_t*)addr; }

/* \brief Write 32 bits to a memory-mapped I/O device
 */
static inline void mmio_write(uint32_t addr, uint32_t data) { *(volatile uint32_t*)addr = data; }

#endif
