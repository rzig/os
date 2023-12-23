#pragma once

#define KERNEL_CODE_SEGMENT 0x08
#define KERNEL_DATA_SEGMENT 0x10

typedef struct {
    uint16_t limit_low; 
    uint16_t base_low;
    uint8_t base_med;
    uint8_t access;
    uint8_t flags;
    uint8_t base_high;
} __attribute__((packed))GDTEntry;

typedef enum {
    PRESENT = (0x01) << 7,
    USER = (0x03) << 5,
    RING2 = (0x02) << 5,
    RING1 = (0x01) << 5,
    KERNEL = 0x0, 
    CODE = (0x03) << 3,
    DATA = (0x02) << 3,
    CODE_READABLE = 0x02, 
    DATA_WRITEABLE = 0x02,

} gdt_access; 

//only declare the top flags, use limit base below
typedef enum {
    GRANULARITY_4K = (0x01) << 7,
    GRANULARITY_1B = (0x00), 
    PROTMODE = (0x02) << 5,
    LONGMODE = (0x01) << 5, 
    REALMODE = 0x0, 
} gdt_flags;

typedef struct {
    uint16_t limit;
    GDTEntry* ptr;
} __attribute__((packed)) GTDDescriptor; // lower 16 bits are the size of gdt, upper 32 are the loc(32 bit mode so 32 bit pointers)

#define LIMIT_LOW(limit) (limit & 0xFFFF)
#define BASE_LOW(base) (base & 0xFFFF)
#define BASE_MED(base) ((base >> 16) & 0xFF)
#define LIMIT_HIGH(limit) ((limit >> 16) & 0x0f)
#define BASE_HIGH(base) ((base >> 24) & 0xFF)

#define GDTEntry(base, limit, access, flags) {\
    LIMIT_LOW(limit),\
    BASE_LOW(base),\
    BASE_MED(base),\
    (access),\
    (((flags) & 0xF0)  | LIMIT_HIGH(limit)),\
    BASE_HIGH(base)\
}


void __attribute__((cdecl)) setup_gdt(GTDDescriptor* descriptor, uint16_t CODE_SEG, uint16_t DATA_SEG);