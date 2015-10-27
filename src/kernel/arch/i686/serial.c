#include <io.h>
#include <serial.h>
#include <string.h>

/* COM Port Base Addresses */
enum {
  COM1 = 0x03f8,
};

/* RS-232 DLAB I/O Port Offsets */
enum {
  DVLS = 0, // LSB of Divisor (when DLAB is set)
  DVMS,     // MSB of Divisor (when DLAB is set)
};

/* RS-232 I/O Port Offsets */
enum {
  DATA = 0, // Data Register
  INTR,     // Interrupt Enable Register
  IFCR,     // Interrupt/FIFO Control Register
  LNCR,     // Line Control Register
  MDCR,     // Modem Control Register
  LNSR,     // Line Status Register
  SCSR,     // Scratch Register
};

/* Enable COM1 */
void serial_init(void) {
  outb(COM1 + INTR, 0x00); // Disable Interrupts
  outb(COM1 + LNCR, 0x80); // Enable DLAB
  outb(COM1 + DATA, 0x01); // 115200 Baud (LSB => 1)
  outb(COM1 + INTR, 0x00); //             (MSB => 0)
  outb(COM1 + LNCR, 0x03); // 8n1
  outb(COM1 + IFCR, 0xc7); // Enable Interrupts
  outb(COM1 + MDCR, 0x0b); // Set RTS/DSR
}

char serial_getc(void) { return (char)(inb(COM1 + DATA)); }

void serial_putc(unsigned char c) { outb(COM1 + DATA, c); }

void serial_puts(const char* str) {
  serial_write(str, strlen(str));
  serial_putc('\n');
}

void serial_write(const char* str, size_t sz) {
  int i;
  for (i = 0; i < sz; i++) {
    serial_putc(str[i]);
  }
}
