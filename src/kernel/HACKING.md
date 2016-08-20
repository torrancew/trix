# Contributing to the Trix Kernel

## Overview

This is the source code for the Trix kernel. It is intended to be built with
the following toolchain:
  * clang
  * GNU binutils

The following tools are recommended to enable easier debugging:
  * gdb
  * QEMU

Since clang is natively able to cross-compile, this means that a single
compiler can be used for all supported platforms, requiring developers install
only a new binutils+GDB to build for a different platform.

The following two targets are supported:
  * `i686-elf`
  * `arm-none-eabi`

The Makefile generally obscures most of these details, so long as you have the
toolchain installed.  On Arch Linux, `arm-none-eabi-binutils` is available in
the official repositories, while `i686-elf-binutils` is available in the AUR.
On 64-bit Linux, plain `gdb` and `qemu` should suffice for x86 targets.  Other
targets will require appropriate support.

## Contributing

The Trix kernel currently targets the C11 version of the C standard.

Please push patches through the BitBucket Merge Request feature.
