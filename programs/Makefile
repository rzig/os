.PHONY: .all

SRCFILES := $(wildcard *.c)
ASFILES := $(wildcard *.S)
NASMFILES := $(wildcard *.asm)
OBJS := $(addprefix obj/,$(SRCFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o))

override TARGET := simple_program

all: $(OBJS)
	i686-elf-gcc -T linker.ld $^ -nostdlib -o out/$(TARGET)

obj/%.asm.o: %.asm
	nasm -f elf -o $@ $<

obj/%.c.o: %.c
	i686-elf-gcc -c $< -o $@ -Wall -Wextra -std=gnu11 -ffreestanding -fno-stack-protector -fno-stack-check -fno-lto -mno-80387 -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -fno-pie

.PHONY: .dummy

dummy: out/dummy

out/dummy: out dummy.asm
	nasm -f bin dummy.asm -o out/dummy
out:
	mkdir out
	mkdir obj
