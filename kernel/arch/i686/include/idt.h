#ifndef _IDT_H
#define _IDT_H

#include <interrupts.h>
#include <stdint.h>

typedef struct _idt_entry {
  uint16_t base_lo;
  uint16_t selector;
  uint8_t zero;
  uint8_t flags;
  uint16_t base_hi;
} idt_entry_t;

typedef struct _idt {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_t;

void idt_init(void);

#endif
