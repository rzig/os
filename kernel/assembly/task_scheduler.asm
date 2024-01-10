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
    pushf                  ;interrupts are off
    push 0x18 | 3
    push 0x0
    iret

test_fun:
    mov eax, 0xaaaaaaaa
    jmp dead_hang