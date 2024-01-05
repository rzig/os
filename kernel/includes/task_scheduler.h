#pragma once
#include "utilities.h"
#include "tar.h"
#include "paging.h"
#include "initrd.h"

/**
 * NOTE: For now we only support flat binaries
 * First find the file in initrd(or the real filesystem once we implement that)
 * Next allocate a region on the kernel heap to store the contents of the process code 
 * Map this region to 0x00000000
 * Allocate a page at 0xC0000000 for the stack
 * Move the appropriate data into the appropriate registers 
 * Setup the TLB with the right entries 
 * Execute iret
 * -1 = error, 0 = success, though I suppose this shouldn't happen
*/
int create_process(char* executable_fname); 

void __attribute__((cdecl)) call_user();