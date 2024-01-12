[bits 32]
mov eax, 0x0
mov ebx, 0xeeee
int 0x80
done:
        jmp done 

