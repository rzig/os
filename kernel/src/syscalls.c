#include "../includes/syscalls.h"
uint32_t handle_halt (uint8_t status) {
    printf("halt with status: %h\n", status);
    // add some code to squash the process?
    asm volatile("hlt");
    return 0;
}
uint32_t handle_execute (const uint8_t* command){
    return 0;
}
uint32_t handle_read (uint32_t fd, void* buf, uint32_t nbytes){
    return 0;
}
uint32_t handle_write (uint32_t fd, const void* buf, uint32_t nbytes){
    return 0;
}
uint32_t handle_open (const uint8_t* filename){
    return 0;
}
uint32_t handle_close (uint32_t fd){
    return 0;
}
uint32_t handle_getargs (uint8_t* buf, uint32_t nbytes){
    return 0;
}
uint32_t handle_vidmap (uint8_t** screen_start){
    return 0;
}
uint32_t handle_set_handler(int32_t signum, void* handler_address){
    return 0;
}
uint32_t handle_sigreturn (void){
    return 0;
}


void handle_syscall(exn_info register_values) {
    int ret_val = 0; 
    switch (register_values.eax)
    {
    case 0:
        ret_val = handle_halt(register_values.ebx);
        break;
    case 1: 
        ret_val = handle_execute(register_values.ebx);
        break;
    case 2:
        ret_val = handle_read(register_values.ebx, register_values.ecx, register_values.edx);
        break;
    case 3:
        ret_val = handle_write(register_values.ebx, register_values.ecx, register_values.edx);
        break;
    case 4:
        ret_val = handle_open(register_values.ebx);
        break;
    case 5:
        ret_val = handle_close(register_values.ebx);
        break;
    case 6: 
        ret_val = handle_getargs(register_values.ebx, register_values.ecx);
        break;
    case 7:
        ret_val = handle_vidmap(register_values.ebx);
        break;
    case 8: 
        ret_val = handle_set_handler(register_values.ebx, register_values.ecx);
        break;
    case 9: 
        ret_val = handle_sigreturn();
        break;
    default:
        break;
    }
    return ret_val;
}