#include "../includes/tar.h"

unsigned int getsize(const char *in) {
  unsigned int size = 0;
  unsigned int j;
  unsigned int count = 1;

  for (j = 11; j > 0; j--, count *= 8)
    size += ((in[j - 1] - '0') * count);

  return size;
}

void print_files(void *addr) {
  unsigned int i;
  for (i = 0;; i++) {
    struct tar_header *header = (struct tar_header *)addr;
    if (header->filename[0] == '\0') {
      break;
    }

    unsigned int sz = getsize(header->size);
    printf("File: %s \n", header->filename);

    addr += ((sz / 512) + 1) * 512;
    if (sz % 512)
      addr += 512;
  }
  return;
}

struct tar_header *get_file_header(void *addr, char *filename) {
  unsigned int i;
  for (i = 0;; i++) {
    struct tar_header *header = (struct tar_header *)addr;
    if (header->filename[0] == '\0') {
      break;
    }

    if (strcmp(header->filename, filename) == 0) {
      return header;
    }

    unsigned int sz = getsize(header->size);

    addr += ((sz / 512) + 1) * 512;
    if (sz % 512)
      addr += 512;
  }
  return NULL;
}

void *contents(void *addr, char *filename) {
  struct tar_header* header = get_file_header(addr, filename);
  if(header) {
    return (void*) header + 512;
  } else {
    return NULL;
  }
}
