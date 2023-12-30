#include "../includes/paging.h"
#include <stdint.h>
uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t fpt[1024] __attribute__((aligned(4096)));

void init_pagetables() {
  for (int i = 0; i < 1024; i++) {
    page_directory[i] = 0x0000002; // mark all as not present to start
  }

  for (int i = 0; i < 1024; i++) {
    fpt[i] = (i * 0x1000) | 3;
  }

  page_directory[0] = ((unsigned int)fpt) | 3;

  loadPageDirectory(page_directory);
  enablePaging();
}
