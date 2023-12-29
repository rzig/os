
#include "tss.h"

tss_entry kernel_tss = { // I believe that these should be set before a context switch to have the most up to date values
    0, // link;
    0, // esp0
    0, // ss0; //stored stack segs go on lower 2 bytes
    0, // esp1;
    0, // ss1;
    0, // esp2;
    0, // ss2;
    0, // cr3;
    0, // eip;
    0, // eflags;
    0, // eax;
    0, // ecx;
    0, // edx;
    0, // ebx;
    0, // esp;
    0, // ebp;
    0, // esi; 
    0, // edi; 
    0, // es; //segments go on the lower 2 bytes
    0, // cs;
    0, // ss;
    0, // ds;
    0, // fs;
    0, // gs; 
    0, // ldtr;
    0, // iopb; // iopb goes on the higher 2 bytes
    0, // ssp;
};


void setup_tss() {

    GDTEntry* tss_entry = get_entry(TSS_IDX);
    set_gdt_entry(tss_entry, &kernel_tss, sizeof(kernel_tss) - 1, tss_entry->access, tss_entry->flags);
    printf("value is: %p\n", &kernel_tss);
    tss_descriptor kernel_tss_desc = {
        TSS_OFFSET,
        *tss_entry 
    };
    init_tss(&kernel_tss_desc);
}