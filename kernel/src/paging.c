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
static bool lpage_allocable; // if we do at some point want to handle large pages we will need to do better

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
} paging_info;

bool entryIs(paging_info input, uint32_t page_entry) {
  return page_entry & input;
}


void free_lpage(uint32_t phys_page) {
  for (size_t i = 0; i < PT_ENTRIES; i++) {
    pmem_stack_start[pmem_stack_loc--] = phys_page + 4*i*PAGE_SIZE;
  }
}
void free_page(uint32_t phys_page) {
  pmem_stack_start[pmem_stack_loc--] = phys_page;
}
void* nextPage() {
  return pmem_stack_start[pmem_stack_loc++];
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
  if (!entryIs(PRESENT, kernel_pd[(uint32_t)kernel_virtual_end >> 22])) {
    kernel_pd[(uint32_t)kernel_virtual_end >> 22] |= PRESENT;
  }
  if (!entryIs(READ_WRITE, kernel_pd[(uint32_t)kernel_virtual_end >> 22])) {
    kernel_pd[(uint32_t)kernel_virtual_end >> 22] |= READ_WRITE;
  }
  rde_start[(uint32_t)kernel_virtual_end >> 12] = phys_addr | READ_WRITE | PRESENT; // for user page we will need to add the user flag 
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
  for (int i = 0; i < PT_ENTRIES; i++) {
    int page_offset = KERNEL_END + (PAGE_SIZE * i); // 0x
    kernel_pstack_pt[i] = page_offset | READ_WRITE | PRESENT; // we now have our page stack
  }
  pmem_stack_start = HIGHER_HALF + KERNEL_END;
  kernel_physical_end = 2*LPAGE_SIZE; // this is how far our last offset takes us 
  kernel_virtual_end = HIGHER_HALF + 2*LPAGE_SIZE;
  for (uint32_t i = 0; (uint32_t) kernel_physical_end + (PAGE_SIZE * i) < PHYS_MEM_SIZE && i < PT_ENTRIES*PD_ENTRIES; i++) {
    pmem_stack_start[i] = kernel_physical_end + (PAGE_SIZE * i); // each entry should store the next available physical page
  }
  rde_start = addKernelLargePage();
  for (uint32_t i = 0; i  < PT_ENTRIES; i++) {
    rde_start[PSTACK_IDX*PT_ENTRIES + i] = kernel_pstack_pt[i]; 
    rde_start[KERNEL_BIOS_IDX*PT_ENTRIES + i] = kernel_init_pt[i];
  }

  for (unsigned int i = 0; i < PD_ENTRIES; i++) {
    if (!entryIs(PAGE_4MB, kernel_pd[i])) {
      kernel_pd[i] = ((uint32_t)rde_start + 4*i*PT_ENTRIES - HIGHER_HALF) | (0x0F & kernel_pd[i]); // pointer to the start of each page table, keep the present / read-write flags 
    }
  }
  tde_start = addKernelLargePage(); // use this for setting up process PD? 
}

void copy_rde_tde() {
  memcpy(tde_start, rde_start, LPAGE_SIZE);
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


void* addPageAt(uint32_t virt_addr) {
  if (!entryIs(PRESENT, kernel_pd[virt_addr >> 22])) {
    kernel_pd[virt_addr >> 22] |=  PRESENT | READ_WRITE;
    uint32_t pt_ent = rde_start[virt_addr >> 12]; // again this is not ideal. we should not map page tables unless nescessary but I don't currently have a better way to do this(so right now the page directory is in essence not being utilized properly as all mappings are stored in memory)
    if (!entryIs(PRESENT, pt_ent)) {
      uint32_t page_padr = (uint32_t) nextPage();
      rde_start[virt_addr >> 12] = page_padr | READ_WRITE | PRESENT; 
    }
  } else {
      kernel_pd[virt_addr >> 22] |= USER_MODE;
      uint32_t pt_ent = rde_start[virt_addr >> 12];
      if (!entryIs(PRESENT, pt_ent)) {
        rde_start[virt_addr >> 12] = (uint32_t) nextPage() | READ_WRITE | PRESENT; 
      }
  }
  return virt_addr;
}

void* addUserPageAt(uint32_t virt_addr) {
  if (!entryIs(PRESENT, kernel_pd[virt_addr >> 22])) {
    kernel_pd[virt_addr >> 22] |=  PRESENT | READ_WRITE | USER_MODE;
    uint32_t pt_ent = rde_start[virt_addr >> 12]; // again this is not ideal. we should not map page tables unless nescessary but I don't currently have a better way to do this(so right now the page directory is in essence not being utilized properly as all mappings are stored in memory)
    if (!entryIs(PRESENT, pt_ent)) {
      uint32_t page_padr = (uint32_t) nextPage();
      rde_start[virt_addr >> 12] = page_padr | READ_WRITE | PRESENT | USER_MODE; 
    } else {
      rde_start[virt_addr >> 12] |= USER_MODE | READ_WRITE;
    }
  } else {
      kernel_pd[virt_addr >> 22] |= USER_MODE | READ_WRITE;
      uint32_t pt_ent = rde_start[virt_addr >> 12];
      if (!entryIs(PRESENT, pt_ent)) {
        rde_start[virt_addr >> 12] = (uint32_t) nextPage() | READ_WRITE | PRESENT | USER_MODE; 
      } else {
        rde_start[virt_addr >> 12] |= USER_MODE | READ_WRITE;
      }
  }
  return virt_addr;
}


void mapKernelRegion(uint32_t desired_virt_addr, uint32_t region_size) {
  if (desired_virt_addr % PAGE_SIZE) {
    addPageAt(desired_virt_addr - (desired_virt_addr % PAGE_SIZE));
    if (PAGE_SIZE - (desired_virt_addr % PAGE_SIZE) > region_size) {
      return;
    } 
    region_size -= PAGE_SIZE - (desired_virt_addr % PAGE_SIZE);  
    desired_virt_addr += PAGE_SIZE - (desired_virt_addr % PAGE_SIZE);
  }
  while (region_size) {
    addPageAt(desired_virt_addr);
    if (PAGE_SIZE > region_size) {
      break;
    }
    region_size -= PAGE_SIZE;
    desired_virt_addr += PAGE_SIZE;
  }
}

void mapUserRegion(uint32_t desired_virt_addr, uint32_t region_size) {
  if (desired_virt_addr % PAGE_SIZE) {
    addUserPageAt(desired_virt_addr - (desired_virt_addr % PAGE_SIZE));
    if (PAGE_SIZE - (desired_virt_addr % PAGE_SIZE) > region_size) {
      return;
    } 
    region_size -= PAGE_SIZE - (desired_virt_addr % PAGE_SIZE);  
    desired_virt_addr += PAGE_SIZE - (desired_virt_addr % PAGE_SIZE);
  }
  while (region_size) {
    uint32_t ret_val = addUserPageAt(desired_virt_addr);
    if (PAGE_SIZE >= region_size) {
      break;
    }
    region_size -= PAGE_SIZE;
    desired_virt_addr += PAGE_SIZE;
  }
}

void* extendKernelHeap(uint32_t size) {
  mapKernelRegion(kernel_virtual_end, size);
  void* old_top = kernel_virtual_end;
  kernel_virtual_end += size;
  return old_top;
}


uint32_t* get_kernel_pd() {
  return kernel_pd;
}

uint32_t* get_rde() {
  return rde_start;
}

uint32_t* get_tde() {
  return tde_start;
}

void page_align_kernel_heap() {
  if ((uint32_t)kernel_virtual_end % PAGE_SIZE != 0) {
    kernel_virtual_end += PAGE_SIZE - (((uint32_t) kernel_virtual_end) % PAGE_SIZE);
  }
}