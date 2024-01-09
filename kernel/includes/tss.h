#pragma once
#include "gdt.h"
#include "utilities.h"
#include <stdint.h>
#include "paging.h"

#define TSS_OFFSET 0x028

typedef struct {
  uint32_t link;
  uint32_t esp0;
  uint32_t ss0; // stored stack segs go on lower 2 bytes
  uint32_t esp1;
  uint32_t ss1;
  uint32_t esp2;
  uint32_t ss2;
  uint32_t cr3;
  uint32_t eip;
  uint32_t eflags;
  uint32_t eax;
  uint32_t ecx;
  uint32_t edx;
  uint32_t ebx;
  uint32_t esp;
  uint32_t ebp;
  uint32_t esi;
  uint32_t edi;
  uint32_t es; // segments go on the lower 2 bytes
  uint32_t cs;
  uint32_t ss;
  uint32_t ds;
  uint32_t fs;
  uint32_t gs;
  uint32_t ldtr;
  uint32_t iopb; // iopb goes on the higher 2 bytes
  uint32_t ssp;
} __attribute__((packed)) tss_entry;

// what is placed in the Task Register is a bit different from IDT and GDT
// Registers
typedef struct {
  uint16_t segment;
  GDTEntry offset;
} __attribute__((packed)) tss_descriptor;

void __attribute__((cdecl)) init_tss(tss_descriptor *descriptor);

void setup_tss();
