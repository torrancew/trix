TARGET := $(ARCH)-elf

GDB ?= gdb

CPU   := $(ARCH)
QARCH := i386
QCPU  := pentium3

CFLAGS  := $(CFLAGS) -target $(TARGET) -march=$(CPU)
ASFLAGS := $(ASFLAGS) -march=$(ARCH) -mtune=$(CPU)
LDFLAGS := $(LDFLAGS)
QFLAGS  := $(QFLAGS) -machine pc

# vim: set ts=2 sts=2 sw=2 noet:
