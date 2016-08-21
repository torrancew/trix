# Trix Kernel

## Overview

This is the kernel for the Trix operating system. The intent behind this kernel
is to build a minimal micro-kernel capable of supporting an OS based on
capability-driven security, and (somewhat/mostly) compatible with POSIX. There
is currently a serial driver embedded for I/O, which may one day be moved into
userland -- when there *is* a userland.

The current available feature list is available in `FEATURES.md`, and the guide
for contributing is available in `HACKING.md`.

## Building

To build the Trix kernel, set the desired architecture when invoking `make`
should suffice:

    $ make ARCH=i686 # Default
    ...

    $ make ARCH=arm
    ...

If desired, additional flags can be passed to the various tools via the
following environment variables:

  * CFLAGS  (clang)
  * ASFLAGS (GNU as)
  * LDFLAGS (GNU ld)
  * QFLAGS  (QEMU)

## Running

The kernel by itself is not useful for much other than debugging, but since
there is currently no available userland (or support for one), debugging is
about all you can do. To run the kernel under QEMU, set `ARCH` to the desired
architecture, and run:

    $ make run
    ...

This will fire up QEMU, but the CPU will be paused. It is possible to use the
QEMU monitor interface to resume the CPU, but it is recommended to use GDB to
have more visibility and control, where desired. Furthermore, GDB is capable of
sending QEMU monitor commands. To run GDB, in another terminal, ensure `ARCH`
is set to the same value as above, and run:

    $ make debug
    ...
    (gdb) b kernel_main
    ...
    (gdb) c
    ...
    (gdb) p some_variable
    ...
    (gdb) info registers
    ...

You can then use GDB in any desired way to interact with the kernel. To run a
QEMU monitor command, simply prefix it with `monitor`:

    ...
    (gdb) monitor info cpus
    ...
    (gdb) monitor info registers
    ...
