[bits 32]
global call_user
call_user:
    cli
    mov   ax, 0x23
    mov   ds, eax
    push  dword 0x23
    push  dword 0x0C
    pushfd
    push  dword 0x1B
    push  dword 0x0
    iret