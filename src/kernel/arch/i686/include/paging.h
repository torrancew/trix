#ifndef _PAGING_H
#define _PAGING_H

#include <stdbool.h>
#include <stdint.h>

typedef struct _pd_entry {
  bool present : 1;
  bool writeable : 1;
  bool user : 1;
  bool writethru : 1;
  bool nocache : 1;
  bool accessed : 1;
  bool zero : 1;
  bool large : 1;
  bool ignored : 1;
  uint8_t unused : 3;
  uint32_t addr : 20;
} page_dir_entry_t;

typedef page_dir_entry_t page_dir_t[1024];

typedef struct _pt_entry {
  bool present : 1;
  bool writeable : 1;
  bool user : 1;
  bool writethru : 1;
  bool nocache : 1;
  bool accessed : 1;
  bool dirty : 1;
  bool zero : 1;
  bool global : 1;
  uint8_t unused : 3;
  uint32_t addr : 20;
} page_tbl_entry_t;

typedef page_tbl_entry_t page_tbl_t[1024];

void paging_init(void);
void page_dir_entry_init(page_dir_entry_t*, bool, bool, uint32_t);
void page_tbl_entry_init(page_tbl_entry_t*, bool, bool, uint32_t);

#endif
