#include <serial.h>
#include <multiboot.h>

#if defined(__linux__)
#error "This kernel cannot be built with a compiler configured for Linux"
#endif

void kernel_main(uint32_t magic, uint32_t mb_info_addr) {
  multiboot_mmap_t* mbmmp = NULL;
  multiboot_info_t* mbinf = NULL;

  serial_init();

  if (magic == MB_MAGIC_LOADER) {
    mbinf = (multiboot_info_t*)(mb_info_addr);
    serial_puts("Multiboot-Compliant Boot Loader Detected!");

    if (mbinf != NULL) {
      if ((mbinf->flags & MB_INFO_MINFO) == MB_INFO_MINFO) {
        serial_puts("Multiboot Memory Info Detected!");

        if ((mbinf->flags & MB_INFO_MMAP) == MB_INFO_MMAP) {
          mbmmp = (multiboot_mmap_t*)(mbinf->mmap_addr);
          serial_puts("Multiboot Memory Map Detected!");

          while ((uint64_t)mbmmp < mbinf->mmap_addr + mbinf->mmap_length) {
            if (mbmmp->type == 1) {
              /* Usable */
            } else {
              /* Reserved */
            }
            mbmmp = (multiboot_mmap_t*)((uint64_t)mbmmp + mbmmp->size + sizeof(mbmmp->size));
          }
        }
      }
    }
  } else {
    serial_puts("Error: This kernel must be loaded by a multiboot-compliant bootloader!");
  }
}
