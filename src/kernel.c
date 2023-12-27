#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "idt.h"
#include "utilities.h"
#include "pic.h"
#include "paging.h"
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
	init_pagetables();
	terminal_writestring("setup the gdt!\n");
	start_idt();
	terminal_writestring("omg idt works maybe??\n");
	initialize_pic(); // how can I tell if this is working?
	terminal_writestring("hmm okay\n");
	enable_interrupts();
	terminal_writestring("paging init\n");
	uint16_t output1 = 42;
	uint16_t output2 = pic_get_isr();
	char buffer1[10]; 
	char buffer2[10];
	itoa(buffer1, 'd', output1);
	itoa(buffer2, 'd', output2);
	buffer1[strlen(buffer1)] = '\n';
	buffer2[strlen(buffer2)] = '\n';
	terminal_writestring("buffer1: ");
	terminal_writestring(buffer1);
	terminal_writestring("buffer 2:");
	terminal_writestring(buffer2);
	dead_hang();
}
