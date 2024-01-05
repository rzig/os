#include "utilities.h"
#include "multiboot2.h"
#include "paging.h"

static void* initrd_loc;

void set_initrd_loc(void* new_loc);
void* get_initrd_loc();
void* load_initrd(void*);

void* load_bif_start();
