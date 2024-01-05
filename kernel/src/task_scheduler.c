#include "../includes/task_scheduler.h"

int create_process(char* executable_fname) {
    tar_header* executable = get_file_header(get_initrd_loc(), executable_fname);
    if (executable == NULL) {
        printf("returning\n");
        return -1;
    }
    uint32_t exec_size = getsize(executable->size);
    mapUserRegion(0x00000000, exec_size);
    printf("opcodes working?\n");
    unsigned int stack_pointer;
    unsigned int stack_segment;
    void* exec_code = contents(get_initrd_loc(), executable_fname);
    int* test = 0x00000004; 
    printf("still fine?\n");
    printf("exec size is: %u and exec code loc is: %p\n", exec_size, exec_code);
    *test = 3;
    memcpy(0x00000000, exec_code, exec_size);
    mapUserRegion(0xBFFFF000, PAGE_SIZE); // stack
    call_user(); 
    return 0;
}