[bits 32]

global fail_cpu
fail_cpu:
    mov eax, 0
    div eax
    ret

global dead_hang
dead_hang:
    jmp dead_hang