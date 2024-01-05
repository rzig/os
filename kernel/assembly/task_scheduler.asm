[bits 32]
global call_user
call_user:
    cli
    hlt
    hlt
	mov ax, (4 * 8) | 3 ; ring 3 data with bottom 2 bits set for ring 3
	mov ds, ax
	mov es, ax 
	mov fs, ax 
	mov gs, ax ; SS is handled by iret
	; set up the stack frame iret expects
	mov eax, esp
	push (4 * 8) | 3 ; data selector
	push 0xC0000000 ; current esp
	pushf ; eflags
	push (3 * 8) | 3 ; code selector (ring 3 code with bottom 2 bits set for ring 3)
	push 0x00000000 ; instruction address to return to
	iret