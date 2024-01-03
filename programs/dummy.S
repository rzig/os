[bits 32]

mov eax, 0xDEADBEEF

done:
        hlt
        jmp done 
