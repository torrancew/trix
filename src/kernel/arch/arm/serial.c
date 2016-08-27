#include <mmio.h>
#include <serial.h>
#include <string.h>

/* GPIO&UART Port Base Addresses */
enum {
  GPIO  = 0x3f200000,
  UART0 = 0x3f201000,
};

/* GPIO Offsets */
enum {
  PUD      = 0x94,
  PUD_CLK0 = 0x98,
};

/* UART Offsets */
enum {
  DR     = 0x00,
  RSRECR = 0x04,
  FR     = 0x18,
  ILPR   = 0x20,
  IBRD   = 0x24,
  FBRD   = 0x28,
  LCRH   = 0x2c,
  CR     = 0x30,
  IFLS   = 0x34,
  IMSC   = 0x38,
  RIS    = 0x3c,
  MIS    = 0x40,
  ICR    = 0x44,
  DMACR  = 0x48,
  ITCR   = 0x80,
  ITIP   = 0x84,
  ITOP   = 0x88,
  TDR    = 0x8c,
};

/* Delay for <count> CPU Cycles */
static void delay(uint32_t count) {
  __asm__ __volatile__("__delay_%=: subs %0, %0, #1; bne __delay_%=" : : "r"(count) : "cc", "memory");
}

/* Enable UART0 */
void serial_init(void) {
  mmio_write(UART0 + CR, 0x00); // Disable UART0
  mmio_write(GPIO + PUD, 0x00); // Disable Pull Up/Down for All GPIO Pins
  delay(150);                   // Delay 150 Cycles

  mmio_write(GPIO + PUD_CLK0, (1 << 14) | (1 << 15)); // Disable Pull Up/Down for Pins 14&15

  delay(150);                        // Delay 150 Cycles
  mmio_write(GPIO + PUD_CLK0, 0x00); // Flush Changes
  mmio_write(UART0 + ICR, 0x07ff);   // Clear Pending Interrupts

  mmio_write(UART0 + IBRD, 0x01); // Set Baud Rate Numerator
  mmio_write(UART0 + FBRD, 0x28); // Set Baud Rate Divisor

  mmio_write(UART0 + LCRH, (1 << 4) | (1 << 5) | (1 << 6)); // Enable FIFO & 8n1

  // Mask All Interrupts
  mmio_write(UART0 + IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

  mmio_write(UART0 + CR, (1 << 0) | (1 << 8) | (1 << 9)); // Enable Tx&Rx
}

char serial_getc(void) {
  while (mmio_read(UART0 + FR) & (1 << 4)) {
    // Wait for UART0
  }
  return mmio_read(UART0 + DR);
}

void serial_putc(const unsigned char c) {
  while (mmio_read(UART0 + FR) & (1 << 5)) {
    // Wait for UART0
  }
  mmio_write(UART0 + DR, c);
}

void serial_puts(const char* str) {
  serial_write(str, strlen(str));
  serial_putc('\n');
}

void serial_write(const char* str, size_t sz) {
  for (int i = 0; i < sz; i++) {
    serial_putc(str[i]);
  }
}
