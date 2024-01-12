[bits 32]
extern dead_hang

global call_user
call_user:
    cli
    mov ax, 0x20 | 3
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	push 0x20 | 3
    push 0xBFFFFFFC
    pushfd
    or dword [esp], 0x200
    push 0x18 | 3
    push 0x0
    iret

test_user:
    jmp test_user