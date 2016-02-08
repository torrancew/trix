#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

#include <stdint.h>

enum {
  MB_MAGIC_LOADER = 0x2badb002,
  MB_MAGIC_KERNEL = 0x1badb002,
};

enum {
  MB_HEADER_ALIGN = 1 << 0,
  MB_HEADER_MINFO = 1 << 1,
  MB_HEADER_VMAP  = 1 << 2,
  MB_HEADER_SYMS  = 1 << 16,
};

enum {
  MB_INFO_MINFO = 1 << 0,
  MB_INFO_BOOTD = 1 << 1,
  MB_INFO_CMDL  = 1 << 2,
  MB_INFO_MODS  = 1 << 3,
  MB_INFO_AOUT  = 1 << 4,
  MB_INFO_ELF   = 1 << 5,
  MB_INFO_MMAP  = 1 << 6,
  MB_INFO_DINFO = 1 << 7,
  MB_INFO_CTBL  = 1 << 8,
  MB_INFO_NAME  = 1 << 9,
  MB_INFO_APM   = 1 << 10,
  MB_INFO_VBE   = 1 << 11,
};

typedef struct {
  uint32_t magic;
  uint32_t flags;
  uint32_t cksum;
  uint32_t header_addr;
  uint32_t load_addr;
  uint32_t load_end_addr;
  uint32_t bss_end_addr;
  uint32_t entry_addr;
  uint32_t mode_type;
  uint32_t width;
  uint32_t height;
  uint32_t depth;
} __attribute__((packed)) multiboot_header_t;

typedef struct {
  uint32_t num;
  uint32_t size;
  uint32_t addr;
  uint32_t shndx;
} __attribute__((packed)) multiboot_elf_hdr_t;

typedef struct {
  uint32_t tabsize;
  uint32_t strsize;
  uint32_t addr;
  uint32_t reserved;
} __attribute__((packed)) multiboot_aout_hdr_t;

typedef struct {
  uint32_t flags;
  uint32_t mem_lo;
  uint32_t mem_hi;
  uint32_t bootdev;
  uint32_t cmdline;
  uint32_t mods_count;
  uint32_t mods_addr;
  union {
    multiboot_elf_hdr_t elf_fields;
    multiboot_aout_hdr_t aout_fields;
  } syms;
  uint32_t mmap_length;
  uint32_t mmap_addr;
  uint32_t drives_length;
  uint32_t drives_addr;
  uint32_t config_table;
  uint32_t boot_loader_name;
  uint32_t apm_table;
  uint32_t vbe_ctrl_info;
  uint32_t vbe_mode_info;
  uint32_t vbe_mode;
  uint32_t vbe_interface_seg;
  uint32_t vbe_interface_off;
  uint32_t vbe_interface_length;
} multiboot_info_t;

typedef struct {
  uint32_t size;
  uint64_t base_addr;
  uint64_t length;
  uint32_t type;
} __attribute__((packed)) multiboot_mmap_t;

typedef struct {
  uint32_t size;
  uint8_t drive_number;
  uint8_t drive_mode;
  uint16_t drive_cylinders;
  uint8_t drive_heads;
  uint8_t drive_sectors;
  uint16_t drive_ports[];
} __attribute__((packed)) multiboot_drive_t;

typedef struct {
  uint16_t version;
  uint16_t cseg;
  uint32_t offset;
  uint16_t cseg_16;
  uint16_t dseg;
  uint16_t flags;
  uint16_t cseg_len;
  uint16_t cseg_16_len;
  uint16_t dseg_len;
} __attribute__((packed)) multiboot_apm_table_t;

#endif
