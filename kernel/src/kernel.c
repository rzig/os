#include <stdbool.h>
#include "../includes/gdt.h"
#include "../includes/idt.h"
#include "../includes/utilities.h"
#include "../includes/pic.h"
#include "../includes/keyboard.h"
#include "../includes/tss.h"
#include "../includes/rtc.h"
#include "../includes/initrd.h"
#include "../includes/tar.h"

static void* boot_info_loc;

void kernel_init(void* bif_addr) {
	boot_info_loc = bif_addr;
}
 
void kernel_main(void) 
{
	start_gdt();
	/* Initialize terminal interface */
	terminal_initialize(); // this likely clobbers ebx
	void* initrd_loc = load_initrd(boot_info_loc);
	// printf("Loaded initrd at %d \n", initrd_loc);
	// print_files(initrd_loc);
	// void* hello_contents = contents(initrd_loc, "initrd/hello.txt");
	// if(hello_contents == 0) {
	// 	printf("Could not get file\n");
	// } else {
	// 	printf("initrd/hello.txt contains %s \n", hello_contents);
	// }
	setup_tss();
	start_idt();
	initialize_pic(); // L PIC
	keyboard_init();
	set_rtc_freq(128);
	start_rtc();
	set_timezone(EST);
	enable_interrupts(); // after everything has been completed enable interrupts
	callable_program dummy = contents(initrd_loc, "initrd/programs/dummy");
	if(dummy == NULL) {
		printf("Error retrieving dummy program");
	} else {
		printf("Executing dummy program");
		dummy();
	}
	dead_hang(); // idk what else to call this, just loop indefinitely?
}
