/*
The multiboot standard does not define the value of the stack pointer register
(esp) and it is up to the kernel to provide a stack. This allocates room for a
small stack by creating a symbol at the bottom of it, then allocating 16384
bytes for it, and finally creating a symbol at the top. The stack grows
downwards on x86. The stack is in its own section so it can be marked nobits,
which means the kernel file is smaller because it does not contain an
uninitialized stack. The stack on x86 must be 16-byte aligned according to the
System V ABI standard and de-facto extensions. The compiler will assume the
stack is properly aligned and failure to align the stack will result in
undefined behavior.
*/
page_start:
	jmp page_entry
page_entry:
	mov $1024, %ecx
	cmp %eax, %ecx
	je page_assign
	mov %eax, %edx 
	imul $0x04, %edx
	add $page_dir_top, %edx
	sub $0xC0000000, %edx
	mov $0x02, %ecx
	mov %ecx, 0(%edx)
	mov $0x1000, %ecx
	imul %eax, %ecx
	add $0x03, %ecx
	mov %eax, %edx 
	imul $0x04, %edx
	add $page_table_top, %edx
	sub $0xC0000000, %edx
	mov %ecx, 0(%edx)
	add $1, %eax
	jmp page_entry
page_assign:
	mov $page_table_top, %eax
	sub $0xC0000000, %eax
	mov $page_dir_top, %edx
	sub $0xC0000000, %edx
	or $0x03, %eax
	mov %eax, 0(%edx)
	mov %eax, 3072(%edx)
	mov $page_dir_top, %eax
	sub $0xC0000000, %eax
    mov %eax, %cr3
    mov %cr0, %eax
    or $(1<<31), %eax
    mov %eax, %cr0
	lea .kernel_continue, %eax
	jmp %eax


gdt_null:
	.quad 0
kernel_code:
	.quad 0x00C09A000000FFFF
kernel_data:
	.quad 0x00C092000000FFFF
gdt_end:

gdt_desc:
	.word (. - gdt_null)
gdt_desc_loc:
	.double 0

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.align 4096
page_dir_top:
.skip 4096
page_dir_bottom:

.align 4096
page_table_top:
.skip 4096
page_table_bottom:


/*
The linker script specifies _start as the entry point to the kernel and the
bootloader will jump to this position once the kernel has been loaded. It
doesn't make sense to return from this function as the bootloader is gone.
*/
.section .text
.global _start
.type _start, @function
_start:
	/*
	To set up a stack, we set the esp register to point to the top of the
	stack (as it grows downwards on x86 systems). This is necessarily done
	in assembly as languages such as C cannot function without a stack.
	*/
	xor %eax, %eax
	jmp page_start

.kernel_continue:
	/*
	This is a good place to initialize crucial processor state before the
	high-level kernel is entered. It's best to minimize the early
	environment where crucial features are offline. Note that the
	processor is not fully initialized yet: Features such as floating
	point instructions and instruction set extensions are not initialized
	yet. The GDT should be loaded here. Paging should be enabled here.
	C++ features such as global constructors and exceptions will require
	runtime support to work as well.
	*/
	mov $stack_top, %esp
	push %ebx
	call kernel_init
	/*
	Enter the high-level kernel. The ABI requires the stack is 16-byte
	aligned at the time of the call instruction (which afterwards pushes
	the return pointer of size 4 bytes). The stack was originally 16-byte
	aligned above and we've pushed a multiple of 16 bytes to the
	stack since (pushed 0 bytes so far), so the alignment has thus been
	preserved and the call is well defined.
	*/
	call kernel_main

/*
Set the size of the _start symbol to the current location '.' minus its start.
This is useful when debugging or when you implement call tracing.
*/
.size _start, . - _start
