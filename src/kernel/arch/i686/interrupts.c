#include <interrupts.h>
#include <panic.h>

__attribute__((interrupt)) void exc_general_protection_fault(interrupt_frame_t* frame, uint32_t error_code) {
  panic("GPF!");
}
