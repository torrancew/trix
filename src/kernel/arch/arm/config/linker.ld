/* Set Entry Point */
ENTRY(_start)

/* Organize Final Image */
SECTIONS
{
	/* Start at 32KiB */
	. = 0x00008000;

	/* Executable Code */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-Only Data */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-Write Data (Initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Read-Write Data (Uninitialized) */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
		*(.bss.stack)
	}
}

/* vim: set ts=2 sts=2 sw=2 noet: */
