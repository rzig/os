#pragma once
#include <stdint.h>

uint32_t __attribute__((cdecl)) halt (uint8_t status);
uint32_t __attribute__((cdecl)) execute (const uint8_t* command);
uint32_t __attribute__((cdecl)) read (uint32_t fd, void* buf, uint32_t nbytes);
uint32_t __attribute__((cdecl)) write (uint32_t fd, const void* buf, uint32_t nbytes);
uint32_t __attribute__((cdecl)) open (const uint8_t* filename);
uint32_t __attribute__((cdecl)) close (uint32_t fd);
uint32_t __attribute__((cdecl)) getargs (uint8_t* buf, uint32_t nbytes);
uint32_t __attribute__((cdecl)) vidmap (uint8_t** screen_start);
uint32_t __attribute__((cdecl)) set_handler(int32_t signum, void* handler_address);
uint32_t __attribute__((cdecl)) sigreturn (void);