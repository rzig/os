section .multiboot
header_start:
    dd 0xe85250d6                ; magic number
    dd 0                         ; architecture = i386
    dd header_end - header_start ; header length

    ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    request_start:
    ; request modules
    dw 1 ; type = 1
    dw 1 ; flags = 1 (not optional)
    dd request_end - request_start ; size (8 for type and flags, 32 to request tag 3)
    dw 3; tag type 3 (modules)
    request_end:

    ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
header_end:
