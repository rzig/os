#pragma once
#include <stdint.h>
#include "gdt.h"
#include "utilities.h"
#include "pic.h"
void setupISR();

typedef struct {
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t reserved_sector;
    uint8_t flags;
    uint16_t offset_high;
} __attribute__((packed))IDTEntry; 

typedef struct {
    uint16_t size;
    IDTEntry* offset;
} __attribute__((packed))idtr_entry;

typedef enum {
    PRESENT = (0x01) << 7, 
    KERNEL = (0x00), 
    USER = (0x03) << 5, 
    RING2 = (0x02) << 5, 
    RING1 = (0x01) << 5, 
    TASK_GATE = (0x5), // if this is set then offset should be zero
    INTERRUPT_GATE16 = (0x06), 
    TRAP_GATE16 = (0x07), 
    INTERRUPT_GATE32 = (0x0E), 
    TRAP_GATE32 = (0x0F),
} idt_flags;

typedef struct {
    uint32_t ds; // from push ax but stack is 32 bit aligned
    uint32_t edi, esi, ebp, kern_esp, ebx, edx, ecx, eax; 
    uint32_t exn_code, int_number;
    uint32_t eip;
    uint32_t cs; 
    uint32_t eflags, esp;
    uint32_t ss;
} __attribute__((packed)) exn_info;

void __attribute__((cdecl)) set_idtr(idtr_entry* entry);
void set_entry(int entry_number, uint8_t flags, uint16_t segment_selector, void* offset); 

void start_idt();
void __attribute__((cdecl)) enable_interrupts(); // just calls the STI instruction 
void __attribute__((cdecl)) int_handler(exn_info register_values); 
void __attribute__((cdecl)) exn_handler(); // do nothing for now, some exceptions we may be able to recover from (e.g. page fault but don't have a good method for dealing with this right now)