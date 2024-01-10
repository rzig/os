OUTPUT_FORMAT("binary")    /* output flat binary */

SECTIONS
{
    . = 0;                 /* relocate to address 0 */
    .text ALIGN(4):
    {
        obj/entrypoint.asm.o(.text)
        *(.text)           /* include all other .text sections */
    }

    .rodata ALIGN(4):
	{
		*(.rodata)
	}
 
	/* Read-write data (initialized) */
	.data ALIGN(4):
	{
		*(.data)
	}
 
	/* Read-write data (uninitialized) and stack */
	.bss ALIGN(4):
	{
		*(COMMON)
		*(.bss)
	}
}