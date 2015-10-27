/* Multiboot Constants */
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1badb002
.set CHECKSUM, -(MAGIC + FLAGS)

/* Multiboot Header */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Stack Allocation */
.section .bss.stack
stack_bottom:
.skip 16384
stack_top:

.section .text

/* Linker Entry Point */
.global _start
_start:
  // Load Stack Pointer
  ldr sp, =stack_top

	// Call kernel_main
	ldr r4, =kernel_main
	blx r4

/* Halt CPU */
halt:
	wfe
	b halt

.size _start, . - _start

# vim: set ts=2 sts=2 sw=2 noet:
