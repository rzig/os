#include "../includes/gdt.h"

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

// only declare the top flags, use limit base below
typedef enum {
  GRANULARITY_4K = (0x01) << 7,
  GRANULARITY_1B = (0x00),
  PROTMODE = (0x02) << 5,
  LONGMODE = (0x01) << 5,
  REALMODE = 0x0,
} gdt_flags;

#define LIMIT_LOW(limit) (limit & 0xFFFF)
#define BASE_LOW(base) (base & 0xFFFF)
#define BASE_MED(base) ((base >> 16) & 0xFF)
#define LIMIT_HIGH(limit) ((limit >> 16) & 0x0f)
#define BASE_HIGH(base) ((base >> 24) & 0xFF)

#define GDTEntry(base, limit, access, flags)                                   \
  {                                                                            \
    LIMIT_LOW(limit), BASE_LOW(base), BASE_MED(base), (access),                \
        (((flags) & 0xF0) | LIMIT_HIGH(limit)), BASE_HIGH(base)                \
  }

GDTEntry gdt_main[] = {
    GDTEntry(0, 0, 0, 0), // start with the null descriptor
    GDTEntry(0, 0xFFFFF, CODE_READABLE | CODE | KERNEL | PRESENT,
             GRANULARITY_4K | PROTMODE),
    GDTEntry(0, 0xFFFFF, DATA_WRITEABLE | DATA | KERNEL | PRESENT,
             GRANULARITY_4K | PROTMODE),
    GDTEntry(0, 0xFFFFF, CODE_READABLE | CODE | USER | PRESENT,
             GRANULARITY_4K | PROTMODE),
    GDTEntry(0, 0xFFFFF, DATA_WRITEABLE | DATA | USER | PRESENT,
             GRANULARITY_4K | PROTMODE),
    GDTEntry(0, 0, KERNEL | PRESENT | 0b01 | 0b1000,
             0x0), // set tss to zero for now and update later
};

GTDDescriptor curr_desc = {sizeof(gdt_main) - 1, // limit is size - 1
                           gdt_main};

void start_gdt() {
  setup_gdt(&curr_desc, KERNEL_CODE_SEGMENT, KERNEL_DATA_SEGMENT);
  return;
}

void set_gdt_entry(GDTEntry *current, uint32_t base, uint32_t limit,
                   uint8_t access, uint8_t flags) {
  current->limit_low = LIMIT_LOW(limit);
  current->base_low = BASE_LOW(base);
  current->base_med = BASE_MED(base);
  current->access = access;
  current->flags = (((flags) & 0xF0) | LIMIT_HIGH(limit));
  current->base_high = BASE_HIGH(base);
}
GDTEntry *get_entry(int idx) { return gdt_main + idx; }
