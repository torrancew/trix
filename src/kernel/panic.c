#include <panic.h>
#include <stddef.h>
#include <stdbool.h>

static println_t panic_puts = NULL;

void panic_init(println_t puts) {
  panic_puts = puts;
}

void panic(const char *msg) {
  panic_puts(msg);
  while (true) { };
}
