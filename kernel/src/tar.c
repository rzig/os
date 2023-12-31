#include "../includes/tar.h"
struct tar_header {
  char filename[100];
  char mode[8];
  char uid[8];
  char gid[8];
  char size[12];
  char mtime[12];
  char chksum[8];
  char typeflag[1];
};

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

void *contents(void *addr, char *filename) {
  unsigned int i;
  for (i = 0;; i++) {

    struct tar_header *header = (struct tar_header *)addr;
    if (header->filename[0] == '\0') {
      break;
    }

    printf("File: %s\n", header->filename);

    if (strcmp(header->filename, filename) == 0) {
      return (void*)header + 512; // headers padded to 512b, content after
    }

    unsigned int sz = getsize(header->size);

    addr += ((sz / 512) + 1) * 512;
    if (sz % 512)
      addr += 512;
  }
  return 0;
}
