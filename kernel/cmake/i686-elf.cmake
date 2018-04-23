set(ARCH       "i686")
set(CPU        "i686")
set(QEMU_ARCH  "i386")
set(QEMU_CPU   "pentium3")
set(QFLAGS     "${QFLAGS} -machine pc")

include_directories("arch/${ARCH}/include")

add_compile_options(
  $<$<COMPILE_LANGUAGE:C>:-target>
  $<$<COMPILE_LANGUAGE:C>:${TARGET}>
  $<$<COMPILE_LANGUAGE:C>:-march=${ARCH}>
  $<$<COMPILE_LANGUAGE:ASM>:-march=${ARCH}>
  $<$<COMPILE_LANGUAGE:ASM>:-mtune=${CPU}>
)

add_library(
  platform OBJECT
  "arch/${ARCH}/serial.c"
  "arch/${ARCH}/platform.c"
  "arch/${ARCH}/gdt.c"
  "arch/${ARCH}/idt.c"
  "arch/${ARCH}/interrupts.c"
  "arch/${ARCH}/paging.c"
)
