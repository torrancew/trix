#include <paging.h>
#include <string.h>

extern void __data_start;
extern void __data_end;
extern void __bss_start;
extern void __bss_end;
extern void __kernel_end;

static page_dir_t kernel_page_dir __attribute__((aligned(4096)));
static page_tbl_t kernel_page_tbl __attribute__((aligned(4096)));

static inline uint32_t page_align(uint32_t);

static void page_dir_entry_init(page_dir_entry_t*, bool, bool, uint32_t);
static void page_tbl_entry_init(page_tbl_entry_t*, bool, bool, uint32_t);

/* Identity map memory from 0 to the end of the kernel */
void paging_init(void) {
  bool writeable;
  uint32_t idx = 0;

  for (uint32_t addr = 0x00; addr < (uint32_t)(&__kernel_end); addr += 4096) {
    if (((addr >= (uint32_t)(&__data_start)) && (addr < (uint32_t)(&__data_end))) ||
        ((addr >= (uint32_t)(&__bss_start)) && (addr < (uint32_t)(&__bss_end))))
      writeable = true;
    else
      writeable = false;

    page_tbl_entry_init(&kernel_page_tbl[idx++], writeable, false, addr);
  }

  page_dir_entry_init(&kernel_page_dir[0], true, false, (uint32_t)(&kernel_page_tbl));
  page_dir_load(&kernel_page_dir);
}

void page_dir_load(const page_dir_t* const dir) {
  __asm__ __volatile__("movl %[pgdir], %%cr3\n\t"
                       "movl %%cr0,    %%eax\n\t"
                       "orl  %[magic], %%eax\n\t"
                       "movl %%eax,    %%cr0\n\t"
                       "lea  .Lcont,   %%eax\n\t"
                       "jmp  *%%eax\n\n"
                       ".Lcont:\n" ::[pgdir] "r"(dir),
                       [magic] "n"(0x80010000)
                       : "eax", "memory");
}

static inline uint32_t page_align(uint32_t addr) { return (addr & 0xfffff000); }

static void page_dir_entry_init(page_dir_entry_t* ent, bool writeable, bool user, uint32_t tbl_addr) {
  memset(ent, 0x00, sizeof(page_dir_entry_t));
  ent->present   = true;
  ent->writeable = writeable;
  ent->user      = user;
  ent->addr      = page_align(tbl_addr) >> 12;
}

static void page_tbl_entry_init(page_tbl_entry_t* ent, bool writeable, bool user, uint32_t paddr) {
  memset(ent, 0x00, sizeof(page_tbl_entry_t));
  ent->present   = true;
  ent->writeable = writeable;
  ent->user      = user;
  ent->addr      = page_align(paddr) >> 12;
}
