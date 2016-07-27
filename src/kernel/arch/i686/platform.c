#include <gdt.h>
#include <platform.h>

void platform_init(void) {
  gdt_init();
}
