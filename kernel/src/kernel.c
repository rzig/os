#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "idt.h"
#include "utilities.h"
#include "pic.h"
#include "paging.h"
#include "keyboard.h"
#include "tss.h"
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
	start_gdt();
	setup_tss();
	init_pagetables();
	start_idt();
	initialize_pic(); // how can I tell if this is working?'
	keyboard_init();
	enable_interrupts();
	dead_hang();
}
