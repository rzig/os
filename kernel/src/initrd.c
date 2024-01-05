#include "../includes/initrd.h"

/**
 * Return the start address of the initrd in memory
 */
void *load_initrd(void *bif_addr) {
  struct multiboot_tag *tag;
  for (tag = (struct multiboot_tag *)(bif_addr + 8);
       tag->type != MULTIBOOT_TAG_TYPE_END;
       tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag +
                                      ((tag->size + 7) & ~7))) {
    switch (tag->type) {
    case MULTIBOOT_TAG_TYPE_MODULE: {
      struct multiboot_tag_module *modtag = (void *)tag;
      // for now there is only one module, and it's the initial ramdisk
      // we will eventaully need to use cmdline to differentiate
      void* fs_start = (void *)modtag->mod_start;
      uint32_t original_end = kernel_physical_end;
      kernel_physical_end = (uint32_t)kernel_physical_end > modtag->mod_end ? kernel_physical_end : modtag->mod_end;
      while (((uint32_t)kernel_physical_end - original_end) / 4096) {
        addKernelPage(); // maps the next 4096 free bytes at the top of the kernel heap(which starts at 0xC0500000) to the next available region of physical memory! 
      }
      return fs_start;
    }
    }
  }
  printf("Could not find initrd, returning null pointer.");
  return NULL;
}
