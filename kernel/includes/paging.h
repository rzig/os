#pragma once
#include <stdint.h>
#include "utilities.h"


/**
 * TODO: 
    * Add support for regions
    * Add support for user allocation of pages (malloc, realloc, calloc)
    * Add support for copy on write pages
    * Add support for storing multiple process page directories and their corresponding page table entries, this should make context switching very easy. 
*/

/**
* Physical memory: 
* 0x00000000 - 0x00100000 (BIOS and GRUB)
* 0x00100000 - 0x0040000(or larger) (Kernel and initrd)
* Rest is theoretical, based on initrd size (though currently we assume file system is less than 3MB)
* 0x00400000 - 0x00800000 (Kernel free page stack)
* 0x00800000 - 0x00C00000 (RDE (stores the mapping of every virtual address to every physical address)
* 0x00C00000 - 0x01000000 (TDE) 
* (free reign for the rest, managed by the kernel page allocator)
* 
* Virtual memory: 
* 0x00000000 - 0xBFFF0000 (Current process) 
* 0xBFFF0000 - 0xC0000000 (Process stack)
* 0xC0000000 - 0xC0100000 (Bootloader and GRUB, can we wipe this eventually?)
* 0xC0100000 - 0xC0400000(or larger) (Kernel)
* Rest is theoretical, based on init-rd size (again current assumption is this is true)
* 0xC0400000 - 0xC0800000 (Kernel free page stack)
* 0xC0800000 - 0xC0C00000 (RDE (stores the mapping of every virtual address to every physical address)
* 0xC0C00000 - 0xC1000000 (TDE) 
* 0xC1000000 - 0xFFFFFFFF (Kernel heap), this should include kernel data structures and stored process page directories(so the theoretical limit of processes is around 100 if we store the page directory and page tables for each process) 

We make the assumption that page directories and page tables are stored in the kernel region of memory(not in the process region, this way the process heap can grow upwards without interfering)

*/
#define KERNEL_END 0x00400000
#define PAGE_SIZE 0x1000
#define PSTACK_IDX 769
#define KERNEL_BIOS_IDX 768
#define PHYS_MEM_SIZE 0xFFFFFFFF
#define PT_ENTRIES 1024
#define PD_ENTRIES 1024
#define LPAGE_SIZE 0x400000
#define HIGHER_HALF 0xC0000000

static const int MAX_PAGES = 1024 * 1024; // we can store at most 4GB of pages

/***
 * Since physical memory must be continous for large page allocation, currently whenever we free a page we can no longer allocate a large page, this should definitely be fixed at some poitn in the future, this is just for basic process creation
*/
void free_page(uint32_t phys_page);

/***
 * If we free a large page this must mean that large pages are still acceptable.
*/
void free_lpage(uint32_t phys_lpage);

//returns the next free page
void* nextPage();

/***
 * Needs some work(on the case where we are not 4MB aligned) but returns the next large page and increments stack_loc appropriately
*/
void* nextLargePage();

/**
 *  adds a page at the top of the kernel heap(which begins at 0xC1000000) to the next avaliable region of free physical memory 
*/ 
void* addKernelPage(); 

/***
 * Adds a 4mb page to the kernel heap (needs to be 4mb aligned)
 * Stored in the following format (31:22 phys addr, 21:9 ignored, 8: global, 7 PS, 6 Dirty, 5 Access, 4 Cache, 3 WT, 2 User / Supervisor, 1 RW, 0 Present)
*/
void* addKernelLargePage(); 
 

/***
 * @param pt_entry stored in the following format (31:12 phys addr, 11:8 Ignored, 7 PS, 6 ignored, 5 Access, 4 Cache, 3 Write Through, 2 User/ Supervisor, 1 RW, 0 Present)
 * @param pd_vaddress the virtual address of our page table, used to index the page directory
 * Use pd_va[pt_va << 22] = pd_ent 
*/
void* addPageDirectoryEntry(uint32_t pd_ent, uint32_t pt_va); 

/***
 * @param pt_ent stored in the following format (31:12 phys addr, 11:9 Ignored, 8 Global, 7 PAT(page attrib table), 6 Dirty, 5 Access, 4 Cache, 3 Write Through, 2 User/Supervisor, 1 RW, 0 Present)
 * First 
*/
void* addPageTableEntry(uint32_t pt_ent, uint32_t ppage_va); 

/***
 * Setup the physical page stack(quite simple, given our assumption that all of the kernel right now is stored below 4MB, we just add another page directory entry mapping 0xC0400000 - 0xC0800000 to 0x00400000 - 0x08000000 and add a bunch of page tables as present)
 * First add several entries to our page directory:
    * Next set up 4MB mapping region(allocate entry in current page directory that maps to Kernel virtual memory)
    * Allocate pages tables in there (just grab physical pages from 4MB +)
    * Copy the current allocations from the page table mapping 0xC0000000 - 0xC0400000 to the new page table that should map this region and do the same for 0xC0400000 - 0xC0800000 
    * Map these new page tables into the page directory, do this in order as page directory virtual address will be updated at the correct time
 * Now create a TDE in the same manner
 * Now that this is done, we have a Kernel heap from 0xC1000000 - 0xFFFFFFFF
*/
void setup_kernel_mem(); 

void set_page_variables(uint32_t page_dir_top, uint32_t page_table_top, uint32_t page_stack_top, uint32_t physical_start, uint32_t virtual_start, uint32_t physical_end, uint32_t virtual_end);


/***
 * Maps a region with Kernel permissions
 * Physical memory doesn't need to be continous, however the virtual region needs to be continous.
 * To simplify things, if a virtual address already has a maping to a page then we will simply unmap it and move it
*/
void mapKernelRegion(uint32_t desired_virt_addr, uint32_t region_size); 

/***
 * Maps a region with User Permissions
*/
void mapUserRegion(uint32_t desired_virt_addr, uint32_t region_size);

