#ifndef _PANIC_H
#define _PANIC_H

typedef void (*println_t)(const char*);

void panic_init(println_t);
void panic(const char*);

#endif
