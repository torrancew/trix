/* Set Entry Point */
ENTRY(_start)

/* Organize Final Image */
SECTIONS
{
	/* Start at 1MiB */
	. = 0x00100000;
	__kernel_start = .;

	/* Executable Code */
	.text BLOCK(4K) : ALIGN(4K)
	{
		__text_start = .;
		*(.multiboot)
		*(.text)
	}
	__text_end =.;

	/* Read-Only Data */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		__rodata_start = .;
		*(.rodata)
	}
	__rodata_end = .;

	/* Read-Write Data (Initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		__data_start = .;
		*(.data)
	}
	__data_end = .;

	/* Read-Write Data (Uninitialized) */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		__bss_start = .;
		*(COMMON)
		*(.bss)
		*(.bss.stack)
	}
	__bss_end = .;
	__kernel_end = .;
}

/* vim: set ts=2 sts=2 sw=2 noet: */
