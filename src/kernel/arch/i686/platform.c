#include <gdt.h>
#include <idt.h>
#include <platform.h>

void platform_init(void) {
  gdt_init();
  idt_init();
}
