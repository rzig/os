[bits 32]

global init_tss

init_tss:
    cli
    mov eax, 0x28
    ltr ax
    ret