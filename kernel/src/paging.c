#include "../includes/paging.h"
#include <stdint.h>

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
} page_table_flags;

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t fpt[1024] __attribute__((aligned(4096)));

void init_pagetables() {
  for (int i = 0; i < 1024; i++) {
    page_directory[i] = 0x0000002; // mark all as not present to start
  }

  for (int i = 0; i < 1024; i++) {
    fpt[i] = (i * 0x1000) | PRESENT | READ_WRITE; // mark each entry as present, readwrite and place the respective address(bits 12 - 31 give physical address (we do logical mapping))
  }

  page_directory[0] = ((unsigned int)fpt) | PRESENT | READ_WRITE; // mark first entry as present (map the first four MB)

  loadPageDirectory(page_directory);
  enablePaging(page_directory);
}
