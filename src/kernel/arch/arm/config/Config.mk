TARGET := $(ARCH)-none-eabi

CPU   := arm1176jzf-s
QARCH := arm
QCPU  := arm1176

CFLAGS  := $(CFLAGS) -target $(TARGET)
ASFLAGS := $(ASFLAGS)
LDFLAGS := $(LDFLAGS)
QFLAGS  := $(QFLAGS) -machine raspi -nographic -S

# vim: set ts=2 sts=2 sw=2 noet:
