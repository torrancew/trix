ARCH ?= i686

SRCDIR  := $(CURDIR)
ARCHDIR := $(SRCDIR)/arch/$(ARCH)
TOPDIR  := $(SRCDIR)/../..
OBJDIR  := $(TOPDIR)/obj/$(ARCH)/kernel
BINDIR  := $(TOPDIR)/obj/$(ARCH)/kernel

CFLAGS  ?= -O0 -g
ASFLAGS ?= --gstabs
LDFLAGS ?=
QFLAGS  ?= -S -s

include $(ARCHDIR)/config/Config.mk

CC      := clang
AS      := $(TARGET)-as
LD      := $(TARGET)-ld
GDB     ?= $(TARGET)-gdb
QEMU    := qemu-system-$(QARCH)
OBJCOPY := $(TARGET)-objcopy

CFLAGS  := $(CFLAGS) -std=c11 -Wall -Werror -fpic -ffreestanding -fno-builtin -nostdlibinc
CFLAGS  := $(CFLAGS) -Iinclude -I$(ARCHDIR)/include
ASFLAGS := $(ASFLAGS)
LDFLAGS := $(LDFLAGS) -Tarch/$(ARCH)/config/linker.ld -z max-page-size=0x1000
QFLAGS  := $(QFLAGS) -nographic -cpu $(QCPU)
DBFLAGS := -x util/gdb/helpers.gdb

KRN_SRCS := $(wildcard $(SRCDIR)/*.c)
KRN_ARCH := $(wildcard $(ARCHDIR)/*.c)
KRN_ASMS := $(wildcard $(ARCHDIR)/*.s)

KRN_OBJS  := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(KRN_SRCS))
ARCH_OBJS := $(patsubst $(ARCHDIR)/%.c,$(OBJDIR)/%.o,$(KRN_ARCH))
ASM_OBJS  := $(patsubst $(ARCHDIR)/%.s,$(OBJDIR)/%.o,$(KRN_ASMS))

KRN_ELF := $(BINDIR)/kernel.elf
KRN_IMG := $(BINDIR)/kernel.img

.PHONY: all dirs kernel clean run debug

all: kernel

dirs: $(OBJDIR) $(BINDIR)

kernel: dirs $(KRN_ELF) $(KRN_IMG)

clean:
	rm -f $(KRN_OBJS) $(ARCH_OBJS) $(ASM_OBJS)

run: $(KRN_ELF)
	$(QEMU) $(QFLAGS) -kernel $<

debug: $(KRN_ELF)
	$(GDB) $(DBFLAGS) $(KRN_ELF)

$(OBJDIR):
	@mkdir -p $@

$(BINDIR):
	@mkdir -p $@

$(KRN_IMG): $(KRN_ELF)
	$(OBJCOPY) -Obinary $< $@

$(KRN_ELF): $(ASM_OBJS) $(KRN_OBJS) $(ARCH_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(ARCHDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(ARCHDIR)/%.s
	$(AS) $(ASFLAGS) -o $@ $<

# vim: set ts=2 sts=2 sw=2 noet:
