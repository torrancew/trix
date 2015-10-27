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
.section .bss.stack, "w", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text

/* Linker Entry Point */
.global _start
.type   _start, @function
_start:
	// Load Stack Pointer
	movl $stack_top, %esp

	// Call C Code
	call kernel_main

/* Halt CPU */
	cli
	hlt
.Lhang:
	jmp .Lhang

.size _start, . - _start

# vim: set ts=2 sts=2 sw=2 noet:
