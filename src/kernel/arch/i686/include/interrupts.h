#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include <stdint.h>

typedef struct _interrupt_frame {
  uint32_t ip;
  uint32_t cs;
  uint32_t flags;
  uint32_t sp;
  uint32_t ss;
} interrupt_frame_t;

__attribute__((interrupt)) void exc_general_protection_fault(interrupt_frame_t*, uint32_t);

#endif
