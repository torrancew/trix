/*! \file arch/i686/include/gdt.h
 *  \brief GDT Support Code
 *
 *  `gdt.h` provides the API for code needed to initialize & use the Global Descriptor Table
 */
#ifndef _GDT_H
#define _GDT_H

#include <stdbool.h>
#include <stdint.h>

/*! \brief Valid values for the `type` field of a GDT entry structure
 */
typedef enum {
  SEG_RDONLY  = 0x00,
  SEG_RDWRITE = 0x02,
  SEG_EXONLY  = 0x08,
  SEG_EXREAD  = 0x0a,
} segment_type_t;

/*! \brief Valid values for the `ring` field of a GDT entry structure
 */
typedef enum {
  DPL_KERN = 0x0,
  DPL_USER = 0x3,
} dpl_t;

/*! \brief A GDT entry structure
 */
typedef struct _gdt_entry {
  uint16_t limit_lo; //!< The lower 16 bits of the GDT entry limit
  uint16_t base_lo;  //!< The lower 16 bits of the GDT entry base address
  uint8_t base_mid;  //!< The "middle" 8 bits of the GDT entry base address

  segment_type_t type : 4; //!< The "type" of the GDT entry
  bool nosystem : 1;
  dpl_t ring : 2; //!< The data protection level of the GDT entry
  bool present : 1;

  uint8_t limit_hi : 4;
  uint8_t unused : 1;
  uint8_t zero : 1;
  uint8_t one : 1;
  bool huge : 1;

  uint8_t base_hi;
} gdt_entry_t;

/*! \brief A GDT structure
 */
typedef struct _gdt {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdt_t;

/*! \brief Initialize the GDT
 */
void gdt_init(void);

#endif
