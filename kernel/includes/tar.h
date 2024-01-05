#pragma once
#include "utilities.h"

typedef struct tar_header {
  char filename[100];
  char mode[8];
  char uid[8];
  char gid[8];
  char size[12];
  char mtime[12];
  char chksum[8];
  char typeflag[1];
} tar_header;

void print_files(void *);
tar_header *get_file_header(void *addr, char *filename);
void *contents(void *, char *);
unsigned int getsize(const char *in);