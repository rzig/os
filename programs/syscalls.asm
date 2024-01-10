[bits 32]
global halt
halt: ;(uint8_t status);
    mov eax, 0
    mov ebx, [esp + 4]
    int 0x80
    ret ; assuming cdecl works how I expect the return value should be in eax

global execute
execute: ;(const uint8_t* command);
    mov eax, 1
    mov ebx, [esp + 8]
    int 0x80
    ret
global read
read: ;(uint32_t fd, void* buf, uint32_t nbytes);
    mov eax, 2
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    int 0x80
    ret
global write
write: ;(uint32_t fd, const void* buf, uint32_t nbytes);
    mov eax, 3
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    int 0x80
    ret
global open
open: ;(const uint8_t* filename);
    mov eax, 4
    mov ebx, [esp + 4]
    int 0x80
    ret

global close
close: ;(uint32_t fd);
    mov eax, 5
    mov ebx, [esp + 4]
    int 0x80
    ret
global getargs
getargs ;(uint8_t* buf, uint32_t nbytes);
    mov eax, 6
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    int 0x80
    ret

global vidmap
vidmap: ;(uint8_t** screen_start);
    mov eax, 7
    mov ebx, [esp + 4]
    int 0x80
    ret

global set_handler
set_handler: ;(int32_t signum, void* handler_address);
    mov eax, 8
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    int 0x80
    ret

global sigreturn
sigreturn: ;(void);
    mov eax, 9
    int 0x80
    ret