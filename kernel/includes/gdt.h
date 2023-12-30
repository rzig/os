#pragma once
#include <stdint.h>

#define KERNEL_CODE_SEGMENT 0x08
#define KERNEL_DATA_SEGMENT 0x10
#define TSS_IDX 5

typedef struct {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_med;
  uint8_t access;
  uint8_t flags;
  uint8_t base_high;
} __attribute__((packed)) GDTEntry;

typedef struct {
  uint16_t limit;
  GDTEntry *ptr;
} __attribute__((packed))
GTDDescriptor; // lower 16 bits are the size of gdt, upper 32 are the loc(32 bit
               // mode so 32 bit pointers)

void __attribute__((cdecl))
setup_gdt(GTDDescriptor *descriptor, uint16_t CODE_SEG, uint16_t DATA_SEG);
void start_gdt();

GDTEntry *get_entry(int idx);
void set_gdt_entry(GDTEntry *current, uint32_t base, uint32_t limit,
                   uint8_t access, uint8_t flags);
