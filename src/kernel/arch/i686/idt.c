#include <idt.h>
#include <string.h>

static idt_t idt;
static idt_entry_t idt_entries[256];

static void idt_entry_set(idt_entry_t*, uint32_t, uint16_t, uint8_t);
static void idt_load(const idt_t*);

void idt_init(void) {
  idt.limit = 256 * sizeof(idt_entry_t) - 1;
  idt.base  = (uint32_t)&idt_entries;

  memset(&idt_entries, 0x00, 256 * sizeof(idt_entry_t));

  idt_entry_set(&idt_entries[13], (uint32_t)(exc_general_protection_fault), 0x08, 0x8f);

  idt_load(&idt);
}

static void idt_entry_set(idt_entry_t* entry, uint32_t base, uint16_t selector, uint8_t flags) {
  entry->zero     = 0;
  entry->base_lo  = base & 0xffff;
  entry->base_hi  = (base >> 16) & 0xffff;
  entry->selector = selector;
  entry->flags    = flags;
}

static void idt_load(const idt_t* idt) { __asm__ __volatile__("lidt (%[idt])" ::[idt] "r"(idt) : "memory"); }
