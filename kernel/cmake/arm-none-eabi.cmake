set(ARCH      "arm")
set(CPU       "arm1176jzf-s")
set(QEMU_ARCH "arm")
set(QEMU_CPU  "arm1176")

set(CFLAGS "${CFLAGS} -target ${TARGET}")
set(QFLAGS "${QFLAGS} -machine raspi2")
