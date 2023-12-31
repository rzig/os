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

static void* boot_info_loc;

void kernel_init(void* bif_addr) {
	boot_info_loc = bif_addr;
}
 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize(); // this likely clobbers ebx
	void* initrd_loc = load_initrd(boot_info_loc);
	printf("Loaded initrd at %d \n", initrd_loc);
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
