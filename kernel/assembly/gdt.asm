[bits 32]

global setup_gdt
setup_gdt:
    cli ; we will turn this back on with sti after we finish setting up the idt(and paging?)
    ; make new call frame
    mov eax, [esp + 4]
    lgdt [eax] ; load ebp + 8 into gdt
    ; reload code segment
    mov ecx, [esp + 8]
    push ecx
    push .reload_cs
    retf ; does a far return which will load value of ecx into code segment

.reload_cs:
    ; reload data segments (both code and data should be set after gdt loaded)
    mov ax, [esp + 12]
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax 
    ret