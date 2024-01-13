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
#include "../includes/paging.h"
#include "../includes/task_scheduler.h"

static void* boot_info_loc;

void kernel_init(void* bif_addr) {
	boot_info_loc = bif_addr;
}
 
void kernel_main(uint32_t page_dir_top, uint32_t page_table_top, uint32_t page_stack_top, uint32_t physical_start, uint32_t virtual_start, uint32_t physical_end, uint32_t virtual_end) 
{
	start_gdt();
	terminal_initialize(); // this likely clobbers ebx
	printf("hello\n");
	// set_page_variables(page_dir_top, page_table_top, page_stack_top, physical_start, virtual_start, physical_end, virtual_end);
	// printf("page dir top: %h, page table top %h, page stack top: %h, physical start: %h, virtual start: %h, physical end: %h, virtual end: %h\n", page_dir_top, page_table_top, page_stack_top, physical_start, virtual_start, physical_end, virtual_end);
	// setup_kernel_mem();
	
	// boot_info_loc += HIGHER_HALF;
	// /* Initialize terminal interface */
	
	// printf("boot loc is : %h\n", boot_info_loc);
	// set_initrd_loc(load_initrd(boot_info_loc));
	// printf("Loaded initrd at %h \n", get_initrd_loc());
	// print_files(get_initrd_loc());
	// // void* hello_contents = contents(initrd_loc, "initrd/hello.txt");
	// // if(hello_contents == 0) {
	// // 	printf("Could not get file\n");
	// // } else {
	// // 	printf("initrd/hello.txt contains %s \n", hello_contents);
	// // }
	
	// start_idt();
	// setup_tss();
	// initialize_pic(); // L PIC
	// keyboard_init();
	// set_rtc_freq(128);
	// start_rtc();
	// set_timezone(CST);
	// enable_interrupts(); // after everything has been completed enable interrupts
	// create_process("initrd/programs/dummy");
	// dead_hang(); // idk what else to call this, just loop indefinitely?
}
