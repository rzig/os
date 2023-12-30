[bits 32]

global init_tss

init_tss:
    cli
    mov eax, [esp + 4]
    ltr [eax] ; we pass a pointer into the stack so we need to dereference it
    ret