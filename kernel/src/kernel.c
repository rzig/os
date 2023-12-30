#include <stdbool.h>
#include "../includes/gdt.h"
#include "../includes/idt.h"
#include "../includes/utilities.h"
#include "../includes/pic.h"
#include "../includes/paging.h"
#include "../includes/keyboard.h"
#include "../includes/tss.h"
#include "../includes/rtc.h"
#include "../includes/initrd.h"
 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	load_initrd();
	start_gdt();
	setup_tss();
	init_pagetables();
	start_idt();
	initialize_pic(); // L PIC
	keyboard_init();
	set_rtc_freq(128);
	start_rtc();
	set_timezone(EST);
	enable_interrupts(); // after everything has been completed enable interrupts
	dead_hang(); // idk what else to call this, just loop indefinitely?
}
