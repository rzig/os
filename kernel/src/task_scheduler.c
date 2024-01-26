#include "../includes/task_scheduler.h"

typedef struct process_info process_info;

struct process_info {
    int pid;
    void* process_addr;
    process_info* next_process; 
    process_info* prev_process;
};

static int current_pid;
static uint32_t* current_pd;
static int last_pid_assigned; // use this for assigning unique pids
static process_info* first_process;
static void* current_process;




int create_process(char* executable_fname, int argc, char** argv) {
    // we need the start address. So the kernel will store the start address of some process struct then process.h can process the process(lol)
    tar_header* executable = get_file_header(get_initrd_loc(), executable_fname);
    if (executable == NULL) {
        printf("couldn't find executable %s\n", executable_fname);
        return -1;
    }
    uint32_t exec_size = getsize(executable->size);
    mapUserRegion(0x00000000, exec_size);
    unsigned int stack_pointer;
    unsigned int stack_segment;
    void* exec_code = contents(get_initrd_loc(), executable_fname);
    memcpy(0x00000000, exec_code, exec_size);
    mapUserRegion(0xBFFFF000, PAGE_SIZE); // stack
    call_user(); 
    return 0;
}
int setup_task_space() {
    current_pd = get_kernel_pd(); // start off with  the kernel pd as our page directory

}

int swap_process_in(int process_id) {
    process_info* current = first_process;
    while (current != NULL) {
        if (current->pid == process_id) {
            break;
        }
        current = current->next_process;
    }        
    if (current == NULL) {
        return -1;
    }
    current_pd = get_page_dir(current->process_addr);
    collect_mappings();    
    
}

void* get_current_process() {
    return current_process;
}
