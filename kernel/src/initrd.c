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
      return (void *)modtag->mod_start;
    }
    }
  }
  printf("Could not find initrd, returning null pointer.");
  return NULL;
}
