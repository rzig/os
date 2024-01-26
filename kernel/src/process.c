#include "process.h"


typedef enum {
    PRESENT = 0x01,
    READ_WRITE = 0x02, 
    USER_MODE = 0x04,
    KERNEL_MODE = 0x00,
    WRITE_THROUGH = 0x08, 
    CACHE_DISABLE = 0x10,
    ACCESSED = 0x20, 
    PAGE_TABLE = 0x00, 
    PAGE_4MB = 0x80, // can either be a large page or a page table!
    RESERVATION_MASK = 0xFFC00FFF
} paging_info;

/***
 * Think how this needs to work
 * There first must be a file descriptor table (this is quite simple, just allocate a page)
 * We probably also want some sort of process state, e.g. stack pointer and heap pointer
*/

typedef struct {
    int id;
    void* file_start; // this is in memory file system for now so we can just have a pointer. Otherwise this will be a little more complicated 
    void* next;
} file_descriptor;

typedef struct {
    size_t size;
    void* region_start;
} mapping;

typedef struct {
    file_descriptor* first_fd;
    int state;
    int argc; 
    char** argv;
    uint32_t* page_dir; 
    uint32_t* page_table_mapping_page; // offset is the same (virt_addr >> 20) will give the virt addr of the page containing the page table.
    void* code_pointer; 
} process_info;

void* init_process(char* executable_fname, int argc, char** argv) {
    tar_header* executable = get_file_header(get_initrd_loc(), executable_fname);
    if (executable == NULL) {
        printf("couldn't find executable %s\n", executable_fname);
        return -1;
    }
    uint32_t exec_size = getsize(executable->size);
    void* code_pointer = extendKernelHeap(exec_size);
    process_info* process_data = extendKernelHeap(sizeof(process_info));
    process_data->first_fd = setup_files(process_data);
    process_data->page_dir = setup_pagedir(process_data);
    process_data->page_table_mapping_page = setup_page_tables(process_data); 
    process_data->argc = argc;
    process_data->argv = setup_args(argv, argc); 
    return process_data;
}

char** setup_args(char** argv, int argc) {
    char** output = extendKernelHeap(argc * sizeof(char*));
    for(size_t i = 0; i < argc; i++) {
        output[i] = extendKernelHeap(strlen(argv[i]));
        memcpy(output[i], argv[i], strlen(argv[i]));
    }
    return output;
}

void* setup_files(void* process_addr) {
    file_descriptor* std_in = extendKernelHeap(sizeof(file_descriptor));
    file_descriptor* std_out = extendKernelHeap(sizeof(file_descriptor));
    std_in->id = 0;
    std_in->next = std_out;
    std_out->id = 1;
    std_out->next = NULL;
    return std_in;
}
void* setup_pagedir(void* process_addr) {
    page_align_kernel_heap();
    uint32_t* page_dir_start = extendKernelHeap(PAGE_SIZE);
} 

void* setup_page_tables(void* process_addr) {
    page_align_kernel_heap(); // need to align the kernel heap before we allocate a page for the page tables and page direcotry
    uint32_t* page_tables_start = extendKernelHeap(PAGE_SIZE); // allocate atleast a page
    uint32_t* kernel_pd = get_kernel_pd();
    for (size_t i = 0; i < PD_ENTRIES; i++) {
        if (i*LPAGE_SIZE < HIGHER_HALF) {
            page_tables_start[i] = USER_MODE | READ_WRITE; // set 0x00000000 - 0xC0000000 to user accessible
        } else {
            page_tables_start[i] = kernel_pd[i]; // copy these mappings over 
        }
    }
    return page_tables_start;
}

void map_region(void* process_addr);
void pass_args(void* process_addr, int argc, char** argv); // perhaps we just store these above the stack and pass a pointer
void setup_memory(void* process_addr);

void* get_page_dir(void* process_addr) {
    return ((process_info*) process_addr)->page_dir;
}

void* get_file(void* process_addr, int fd) {
    return NULL;
}
void* write_file(void* process_addr,int fd, char* info, size_t size) {
    return NULL;
}
char* read_file(void* process_addr,int fd, size_t size) {
    return NULL;
}
int open_file(void* process_addr) {
    return 0;
}
void close_file(void* process_addr,int fd) {
    
}


uint32_t* get_page_table(void* process_addr, uint32_t virtual_address) {
    process_info* process = (process_info*) process_addr;
    uint32_t* page_table = process->page_table_mapping_page[virtual_address >> 20];
    return page_table;
}

// add a page and map it into the processes page directory and page tables

// Kernel mappings for the higher half are more confusing. We are theoretically copying them over 
void addProcessUserPage(void* process_addr, uint32_t virt_addr) {
    if (virt_addr >= HIGHER_HALF) {
        return; // don't allocate a page in kernel space
    }
    uint32_t* page_dir = get_page_dir(process_addr);
    uint32_t* page_table = get_page_table(process_addr, virt_addr);

    if (!entryIs(PRESENT, page_dir[virt_addr >> 22])) {
    page_dir[virt_addr >> 22] |=  PRESENT | READ_WRITE | USER_MODE;
    uint32_t pt_ent = page_table[(virt_addr << 10) >> 22]; // again this is not ideal. we should not map page tables unless nescessary but I don't currently have a better way to do this(so right now the page directory is in essence not being utilized properly as all mappings are stored in memory)
    if (!entryIs(PRESENT, pt_ent)) {
      uint32_t page_padr = (uint32_t) nextPage();
      page_table[(virt_addr << 10) >> 22] = page_padr | READ_WRITE | PRESENT | USER_MODE; 
    } else {
      page_table[(virt_addr << 10) >> 22] |= USER_MODE | READ_WRITE;
    }
  } else {
      page_dir[virt_addr >> 22] |= USER_MODE | READ_WRITE;
      uint32_t pt_ent = page_table[(virt_addr << 10) >> 22];
      if (!entryIs(PRESENT, pt_ent)) {
        page_table[(virt_addr << 10) >> 22] = (uint32_t) nextPage() | READ_WRITE | PRESENT | USER_MODE; 
      } else {
        page_table[(virt_addr << 10) >> 22] |= USER_MODE | READ_WRITE;
      }
  }
  return virt_addr;
}

void mapProcessUserRegion(void* process_addr, uint32_t* page_dir, uint32_t* page_table_mapping, uint32_t desired_virt_addr, uint32_t region_size) {
    if (desired_virt_addr % PAGE_SIZE) {
        addProcessUserPage(process_addr, desired_virt_addr - (desired_virt_addr % PAGE_SIZE));
        if (PAGE_SIZE - (desired_virt_addr % PAGE_SIZE) > region_size) {
        return;
        } 
        region_size -= PAGE_SIZE - (desired_virt_addr % PAGE_SIZE);  
        desired_virt_addr += PAGE_SIZE - (desired_virt_addr % PAGE_SIZE);
    }
    while (region_size) {
        addProcessUserPage(process_addr, desired_virt_addr);
        if (PAGE_SIZE >= region_size) {
            break;
        }
        region_size -= PAGE_SIZE;
        desired_virt_addr += PAGE_SIZE;
    }
}

char** get_argv(void* process_addr) {
    process_info* proc = (process_info*)process_addr;
    return proc->argv;
}

int get_argc(void* process_addr) {
    process_info* proc = (process_info*)process_addr;
    return proc->argc;
}