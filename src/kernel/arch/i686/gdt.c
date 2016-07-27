#include <gdt.h>
#include <stddef.h>
#include <string.h>

static gdt_t gdt;
static gdt_entry_t gdt_entries[5];

static void gdt_entry_set(gdt_entry_t*, uint32_t, uint32_t, segment_type_t, dpl_t);
static void gdt_load(const gdt_t*);

void gdt_init(void) {
  size_t entry_count;

  entry_count = sizeof(gdt_entries) / sizeof(gdt_entry_t);
  gdt.limit   = sizeof(gdt_entry_t) * entry_count - 1;
  gdt.base    = (uint32_t)&gdt_entries;

  memset(&gdt_entries[0], 0x00, sizeof(gdt_entry_t)); // NULL Descriptor

  gdt_entry_set(&gdt_entries[1], 0x00, 0xffffffff, SEG_EXREAD, DPL_KERN);  // Ring 0 Code
  gdt_entry_set(&gdt_entries[2], 0x00, 0xffffffff, SEG_RDWRITE, DPL_KERN); // Ring 0 Data
  gdt_entry_set(&gdt_entries[3], 0x00, 0xffffffff, SEG_EXREAD, DPL_USER);  // Ring 3 Code
  gdt_entry_set(&gdt_entries[4], 0x00, 0xffffffff, SEG_RDWRITE, DPL_USER); // Ring 3 Data

  gdt_load(&gdt);
}

static void gdt_entry_set(gdt_entry_t* entry, uint32_t base, uint32_t limit, segment_type_t type, dpl_t ring) {
  entry->base_lo  = base & 0xffff;
  entry->base_mid = (base >> 16) & 0xff;
  entry->base_hi  = (base >> 24) & 0xff;
  entry->limit_lo = limit & 0xffff;
  entry->limit_hi = (limit >> 16) & 0xff;

  entry->type     = type;
  entry->nosystem = true;
  entry->ring     = ring;
  entry->present  = true;
  entry->unused   = 0x00;
  entry->zero     = 0x00;
  entry->one      = 0x01;
  entry->huge     = true;
}

static void gdt_load(const gdt_t* gdt) {
  __asm__ __volatile__("lgdt (%[gdt])\n\t"
                       "movw %[ds], %%ax\n\t"
                       "movw %%ax,  %%ds\n\t"
                       "movw %%ax,  %%es\n\t"
                       "movw %%ax,  %%fs\n\t"
                       "movw %%ax,  %%gs\n\t"
                       "movw %%ax,  %%ss\n\t"
                       "ljmp %[cs], $.Lcontinue\n"
                       ".Lcontinue:\n\t" ::[gdt] "r"(gdt),
                       [ds] "N"(0x10), [cs] "N"(0x08)
                       : "eax", "memory");
}
