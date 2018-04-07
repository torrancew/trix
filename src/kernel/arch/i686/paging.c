#include <paging.h>
#include <string.h>

extern const uint32_t* __kernel_start;
extern const uint32_t* __text_start;
extern const uint32_t* __text_end;
extern const uint32_t* __rodata_start;
extern const uint32_t* __rodata_end;
extern const uint32_t* __data_start;
extern const uint32_t* __data_end;
extern const uint32_t* __bss_start;
extern const uint32_t* __bss_end;
extern const uint32_t* __kernel_end;

static page_dir_t kernel_page_dir __attribute__((aligned(4096)));
static page_tbl_t kernel_page_tbl __attribute__((aligned(4096)));

/* Identity map first 4MB of memory */
void paging_init(void) {
  uint16_t idx  = 0;
  uint32_t addr = 0x00;
  while (addr < 0x00400000) {
    bool writeable = false;
    if (((addr >= (uint32_t)(__data_start)) && (addr < (uint32_t)(__data_end))) ||
        ((addr >= (uint32_t)(__bss_start)) && (addr < 0x00400000)))
      writeable = true;
    page_tbl_entry_init(&kernel_page_tbl[idx], writeable, false, addr);
    addr += 0x1000;
    idx++;
  }

  page_dir_entry_init(&kernel_page_dir[0], true, false, (uint32_t)(&kernel_page_tbl));

  __asm__ __volatile__("movl %[pgdir], %%cr3\n\t"
                       "movl %%cr0,    %%ecx\n\t"
                       "orl  %[magic], %%ecx\n\t"
                       "movl %%ecx,    %%cr0\n\t"
                       "lea  .Lcont,   %%ecx\n\t"
                       "jmp  *%%ecx\n\n"
                       ".Lcont:\n" ::[pgdir] "r"(&kernel_page_dir),
                       [magic] "n"(0x80010000)
                       : "ecx", "memory");
}

void page_dir_entry_init(page_dir_entry_t* ent, bool writeable, bool user, uint32_t tbl_addr) {
  memset(ent, 0x00, sizeof(page_dir_entry_t));
  ent->present   = true;
  ent->writeable = writeable;
  ent->user      = user;
  ent->addr      = (tbl_addr ^ (tbl_addr & (0x1000 - 1))) >> 12;
}

void page_tbl_entry_init(page_tbl_entry_t* ent, bool writeable, bool user, uint32_t paddr) {
  memset(ent, 0x00, sizeof(page_tbl_entry_t));
  ent->present   = true;
  ent->writeable = writeable;
  ent->user      = user;
  ent->addr      = (paddr ^ (paddr & (0x1000 - 1))) >> 12;
}
