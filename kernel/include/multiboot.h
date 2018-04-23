/*! \file multiboot.h
 *  \brief The Multiboot Header File
 *
 *  `multiboot.h` is derived from the GNU Multiboot v1
 *  [Specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html)
 *  and
 *  [Header](http://git.savannah.gnu.org/cgit/grub.git/tree/doc/multiboot.h?h=multiboot)
 */

#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

#include <stdint.h>

/*! \brief Valid Multiboot "magic" values
 */
typedef enum {
  MB_MAGIC_LOADER = 0x2badb002, //!< Magic value provided by Multiboot loaders
  MB_MAGIC_KERNEL = 0x1badb002, //!< Magic value provided by Multiboot kernels
} multiboot_magic_t;

/*! \brief Offsets for various Multiboot header flags
 */
typedef enum {
  MB_HEADER_ALIGN = 1 << 0,  //!< Bit offset to request alignment
  MB_HEADER_MINFO = 1 << 1,  //!< Bit offset to request memory information
  MB_HEADER_VMAP  = 1 << 2,  //!< Bit offset to request the video mode table
  MB_HEADER_SYMS  = 1 << 16, //!< Bit offset to specify custom load parameters
} multiboot_header_flag_offset_t;

/*! \brief Offsets for various Multiboot info flags
 */
typedef enum {
  MB_INFO_MINFO = 1 << 0,  //!< Bit offset for memory information
  MB_INFO_BOOTD = 1 << 1,  //!< Bit offset for boot device
  MB_INFO_CMDL  = 1 << 2,  //!< Bit offset for command line
  MB_INFO_MODS  = 1 << 3,  //!< Bit offset for Multiboot modules
  MB_INFO_AOUT  = 1 << 4,  //!< Bit offset for AOUT metadata
  MB_INFO_ELF   = 1 << 5,  //!< Bit offset for ELF metadata
  MB_INFO_MMAP  = 1 << 6,  //!< Bit offset for detailed memory map
  MB_INFO_DINFO = 1 << 7,  //!< Bit offset for drive information
  MB_INFO_CTBL  = 1 << 8,  //!< Bit offset for config table
  MB_INFO_NAME  = 1 << 9,  //!< Bit offset for boot loader name
  MB_INFO_APM   = 1 << 10, //!< Bit offset for APM table
  MB_INFO_VBE   = 1 << 11, //!< Bit offset for VBE table
} multiboot_info_flag_offset_t;

/*! \brief The Multiboot header structure
 *
 *  A structure conforming to the Multiboot v1 specification required for the Multiboot header
 */
typedef struct _multiboot_header_t {
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

/*! \brief The Multiboot `ELF` header
 */
typedef struct {
  uint32_t num;
  uint32_t size;
  uint32_t addr;
  uint32_t shndx;
} __attribute__((packed)) multiboot_elf_hdr_t;

/*! \brief The Multiboot `a.out` header
 */
typedef struct {
  uint32_t tabsize;
  uint32_t strsize;
  uint32_t addr;
  uint32_t reserved;
} __attribute__((packed)) multiboot_aout_hdr_t;

/*! \brief The appropriate kernel metadata structure
 */
typedef union {
  multiboot_elf_hdr_t elf_fields;
  multiboot_aout_hdr_t aout_fields;
} multiboot_bin_hdr_t;

/*! \brief The main Multiboot structure
 */
typedef struct {
  uint32_t flags;
  uint32_t mem_lo;
  uint32_t mem_hi;
  uint32_t bootdev;
  uint32_t cmdline;
  uint32_t mods_count;
  uint32_t mods_addr;
  multiboot_bin_hdr_t syms;
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

/*! \brief A Multiboot memory map entry structure
 */
typedef struct {
  uint32_t size;
  uint64_t base_addr;
  uint64_t length;
  uint32_t type;
} __attribute__((packed)) multiboot_mmap_t;

/*! \brief A Multiboot drive structure
 */
typedef struct {
  uint32_t size;
  uint8_t drive_number;
  uint8_t drive_mode;
  uint16_t drive_cylinders;
  uint8_t drive_heads;
  uint8_t drive_sectors;
  uint16_t drive_ports[];
} __attribute__((packed)) multiboot_drive_t;

/*! \brief A Multiboot APM table structure
 */
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
