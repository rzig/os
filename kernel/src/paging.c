#include "../includes/paging.h"
#include <stdint.h>

static uint32_t* kernel_pd;
static uint32_t* kernel_init_pt;
static uint32_t* kernel_pstack_pt;

static void* kernel_physical_start; 
static void* kernel_physical_end;
static void* kernel_virtual_start;
static void* kernel_virtual_end;
static uint32_t* rde_start;
static uint32_t* tde_start;
static uint32_t* pmem_stack_start;
static int pmem_stack_loc;

typedef enum {
    PRESENT = 0x01,
    READ_WRITE = 0x02, 
    USER_MODE = 0x04,
    KERNEL_MODE = 0x00,
    WRITE_THROUGH = 0x08, 
    CACHE_DISABLE = 0x10,
    ACCESSED = 0x20, 
    PAGE_TABLE = 0x00, 
    PAGE_4MB = 0x80, // can either be a large page or a page table!
    RESERVATION_MASK = 0xFFC00FFF
} page_table_flags;

bool isLPage(uint32_t pd_entry) {
  return pd_entry & PAGE_4MB;
}

void* nextPage() {
  return pmem_stack_start[++pmem_stack_loc];
}

void* nextLargePage() {
  if (pmem_stack_start[pmem_stack_loc] % LPAGE_SIZE != 0) {
    return NULL; // don't want to deal with this right now but the physical address needs to be 4 MB aligned (bc we only store the top 10 bits in the entry :/)
  }
  uint32_t old_stack_loc = pmem_stack_loc;
  pmem_stack_loc += PT_ENTRIES; // basically like adding a page table 
  return pmem_stack_start[old_stack_loc];
}

/***
 * Adds page to kernel heap!
*/
void* addKernelPage() {
  uint32_t phys_addr = nextPage();
  if (phys_addr == NULL) {
    return NULL;
  }
  if ((uint32_t) kernel_virtual_end % PAGE_SIZE != 0) {
    pmem_stack_loc -= 1;
    return NULL;
  }
  //rde contains all the page tables(again this is sorta lazy we don't really want all page tables mapped in memory but later we shall clean this up). Also this does not take into account how large pages will deactivate some of the page tables... so we need to watch for that and come up with a soln. Theoretically should be fine until we add deallocation

  rde_start[phys_addr >> 12] = phys_addr | READ_WRITE | PRESENT; // for user page we will need to add the user flag 
  void* old_addr = kernel_virtual_end;
  kernel_virtual_end += PAGE_SIZE;
  return old_addr;
}
/**
 * Adds large page to kernel heap!
*/
void* addKernelLargePage() {
  uint32_t phys_addr = nextLargePage(); 
  if (phys_addr == NULL) {
    return NULL;
  }
  if ((uint32_t)kernel_virtual_end % LPAGE_SIZE != 0) {
    pmem_stack_loc -= PT_ENTRIES; // need to reverse the page size
    return NULL; // again not dealing with the annoying case 
  }
  kernel_pd[((uint32_t)kernel_virtual_end >> 22)] = ((phys_addr & 0xFFC00000) | READ_WRITE | PRESENT | PAGE_4MB ) & RESERVATION_MASK;
  void* old_addr = kernel_virtual_end;
  kernel_virtual_end += LPAGE_SIZE;
  return old_addr; // return the new end of the kernel heap
}
void setup_kernel_mem() {
  // setup page stack (map 0xC0400000 - 0xC0800000 to 0x00400000 - 0x00800000) 
  kernel_pd[PSTACK_IDX] = ((uint32_t)kernel_pstack_pt - HIGHER_HALF) | READ_WRITE | PRESENT; // pds and pts store phys addrs
  printf("kernel_pd addr: %p\n", kernel_pd);

  for (int i = 0; i < PT_ENTRIES; i++) {
    int page_offset = KERNEL_END + (PAGE_SIZE * i); // 0x
    kernel_pstack_pt[i] = page_offset | READ_WRITE | PRESENT; // we now have our page stack
  }
  int* test = 0xC05FF008;
  *test = 4;
  pmem_stack_start = HIGHER_HALF + KERNEL_END;
  kernel_physical_end = 2*LPAGE_SIZE; // this is how far our last offset takes us 
  kernel_virtual_end = HIGHER_HALF + 2*LPAGE_SIZE;
  for (uint32_t i = 0; (uint32_t) kernel_physical_end + (PAGE_SIZE * i) < PHYS_MEM_SIZE && i < PT_ENTRIES*PD_ENTRIES; i++) {
    pmem_stack_start[i] = kernel_physical_end + (PAGE_SIZE * i); // each entry should store the next available physical page
  }
  rde_start = addKernelLargePage();
  int* test2 = rde_start;
  *test2 = 3;
  for (uint32_t i = 0; i  < PT_ENTRIES; i++) {
    rde_start[PSTACK_IDX*PT_ENTRIES + i] = kernel_pstack_pt[i];
    rde_start[KERNEL_BIOS_IDX*PT_ENTRIES + i] = kernel_init_pt[i];
  }

  for (unsigned int i = 0; i < PD_ENTRIES; i++) {
    if (!isLPage(kernel_pd[i]) && i != KERNEL_BIOS_IDX) {
      kernel_pd[i] = rde_start[i*PT_ENTRIES]; // pointer to the start of each page table
    }
  }
  tde_start = addKernelLargePage(); // this should be zero
}
void report_pd() {
  printf("pd is: %h, value: %h\n", &kernel_pd, kernel_pd);
}

void set_page_variables(uint32_t page_dir_top, uint32_t page_table_top, uint32_t page_stack_top, uint32_t physical_start, uint32_t virtual_start, uint32_t physical_end, uint32_t virtual_end) {
  kernel_pd = page_dir_top;
	kernel_init_pt = page_table_top;
	kernel_pstack_pt = page_stack_top;
	kernel_physical_start = physical_start;
	kernel_virtual_start = virtual_start;
	kernel_physical_end = physical_end;
	kernel_virtual_end = virtual_end;
}