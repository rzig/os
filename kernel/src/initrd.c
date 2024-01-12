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
      return fs_start + HIGHER_HALF;
    }
    }
  }
  printf("Could not find initrd, returning null pointer.");
  return NULL;
}

void set_initrd_loc(void* new_loc) {
  initrd_loc = new_loc;
}
void* get_initrd_loc() {
  return initrd_loc;
}