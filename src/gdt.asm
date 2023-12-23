[bits 32]

; void __attribute__((cdecl)) i686_GDT_Load(GDTDescriptor* descriptor, uint16_t codeSegment, uint16_t dataSegment);
global setup_gdt
setup_gdt:
    
    ; make new call frame
    push ebp             ; save old call frame
    mov ebp, esp         ; initialize new call frame
    
    ; load gdt
    mov eax, [ebp + 8]
    lgdt [eax] ; load ebp + 8 into gdt
    ; reload code segment
    mov ecx, [ebp + 12]
    push ecx
    push .reload_cs
    retf

.reload_cs:
    ; reload data segments
    mov ax, [ebp + 16]
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; restore old call frame
    mov esp, ebp
    pop ebp
    ret

; we can use this to check that registers contain the values we desire
.check: 
    mov eax, 0x2f592f41
    mov dword [0xb8000], eax
    hlt
    ret