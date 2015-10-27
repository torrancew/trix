#include <serial.h>

#if defined(__linux__)
#error "This kernel cannot be built with a compiler configured for Linux"
#endif

void kernel_main(void) {
  char c;

  serial_init();
  serial_puts("Hello, serial!");
  while ((c = serial_getc()) != '\n') {
    if (c == '\r') {
      serial_putc('\r');
      serial_putc('\n');
    } else {
      serial_putc(c);
    }
  }
}
