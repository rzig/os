.PHONY: all

override CFILES := $(shell find -L * -type f -name '*.c')
override NASMFILES := $(shell find -L * -type f -name '*.asm')
override HEADERS := $(shell find -L * -type f -name '*.h') 
override OBJ := $(addprefix obj/,$(CFILES:.c=.c.o) $(NASMFILES:.asm=.asm.o))

all: linker.ld ${OBJ} 
	i686-elf-gcc -T linker.ld ${OBJ} -o out/simple_program -nostdlib -static -pie -z text
obj/%.c.o: %.c obj
	i686-elf-gcc -c $< -o $@ -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
obj/%.asm.o: %.asm obj
	nasm -f elf $< -o $@
obj: 
	mkdir obj 

