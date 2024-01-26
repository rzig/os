#pragma once
#include "utilities.h"
#include "process.h"
#include "task_scheduler.h"

void __attribute__((cdecl)) sysc_parser(); 
uint32_t handle_execute (const uint8_t* command);
uint32_t handle_read (uint32_t fd, void* buf, uint32_t nbytes);
uint32_t handle_write (uint32_t fd, const void* buf, uint32_t nbytes);
uint32_t handle_open (const uint8_t* filename);
uint32_t handle_close (uint32_t fd);
uint32_t handle_getargs (uint8_t* buf, uint32_t nbytes);
uint32_t handle_vidmap (uint8_t** screen_start);
uint32_t handle_set_handler(int32_t signum, void* handler_address);
uint32_t handle_sigreturn (void);

void handle_syscall(exn_info register_values);
