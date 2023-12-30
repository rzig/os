#include "../includes/initrd.h"

/**
  * Return the start address of the initrd in memory
  */
void* load_initrd() {
  struct multiboot_tag* tag;
  uint32_t* addr;
  asm ("mov %%ebx, %0" : "=r" (addr));
  uint32_t bif_size = *addr;
  printf("bif_size is %d \n", bif_size);
  return 0;
}
