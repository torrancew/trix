#ifndef _GDT_H
#define _GDT_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  SEG_RDONLY  = 0x00,
  SEG_RDWRITE = 0x02,
  SEG_EXONLY  = 0x08,
  SEG_EXREAD  = 0x0a,
} segment_type_t;

typedef enum {
  DPL_KERN = 0x0,
  DPL_USER = 0x3,
} dpl_t;

typedef struct _gdt_entry {
  uint16_t limit_lo;
  uint16_t base_lo;
  uint8_t base_mid;

  segment_type_t type : 4;
  bool nosystem : 1;
  dpl_t ring : 2;
  bool present : 1;

  uint8_t limit_hi : 4;
  uint8_t unused : 1;
  uint8_t zero : 1;
  uint8_t one : 1;
  bool huge : 1;

  uint8_t base_hi;
} gdt_entry_t;

typedef struct _gdt {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdt_t;

void gdt_init(void);

#endif
