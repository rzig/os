#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "idt.h"
#include "utilities.h"
#include "pic.h"
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 

 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
 
	/* Newline support is left as an exercise. */
	terminal_writestring("Heyo this works \n");
	terminal_writestring("What the heck\n");
	start_gdt();
	terminal_writestring("setup the gdt!\n");
	start_idt();
	terminal_writestring("omg idt works maybe??\n");
	initialize_pic();
	terminal_writestring("hmm okay\n");
	enable_interrupts();
	__asm("int $0x1D");
	__asm("int $0x1F");
}