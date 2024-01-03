#add includes to include path
export C_INCLUDE_PATH=kernel/includes

# Nuke built-in rules and variables.
override MAKEFLAGS += -rR

# This is the name that our final kernel executable will have.
# Change as needed.
override KERNEL := kernel
override OS := glados
# Convenience macro to reliably declare user overridable variables.
define DEFAULT_VAR =
    ifeq ($(origin $1),default)
        override $(1) := $(2)
    endif
    ifeq ($(origin $1),undefined)
        override $(1) := $(2)
    endif
endef

# It is suggested to use a custom built cross toolchain to build a kernel.
# We are using the standard "cc" here, it may work by using
# the host system's toolchain, but this is not guaranteed.
override DEFAULT_CC := i686-elf-gcc
$(eval $(call DEFAULT_VAR,CC,$(DEFAULT_CC)))

# Same thing for "ld" (the linker).
override DEFAULT_LD := i686-elf-gcc
$(eval $(call DEFAULT_VAR,LD,$(DEFAULT_LD)))

# User controllable C flags.
override DEFAULT_CFLAGS := -g -O2 -pipe
$(eval $(call DEFAULT_VAR,CFLAGS,$(DEFAULT_CFLAGS)))

# User controllable C preprocessor flags. We set none by default.
override DEFAULT_CPPFLAGS :=
$(eval $(call DEFAULT_VAR,CPPFLAGS,$(DEFAULT_CPPFLAGS)))

# User controllable nasm flags.
override DEFAULT_NASMFLAGS := -F dwarf -g
$(eval $(call DEFAULT_VAR,NASMFLAGS,$(DEFAULT_NASMFLAGS)))

# User controllable linker flags. We set none by default.
override DEFAULT_LDFLAGS :=
$(eval $(call DEFAULT_VAR,LDFLAGS,$(DEFAULT_LDFLAGS)))

# Internal C flags that should not be changed by the user.
override CFLAGS += \
    -Wall \
    -Wextra \
    -std=gnu11 \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fPIE \
    -march=x86-64 \
    -mno-80387 \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-red-zone


# Internal linker flags that should not be changed by the user.
override LDFLAGS += \
    -nostdlib \
    -static \
    -pie \
    -z text \
    -T linker.ld

# Internal nasm flags that should not be changed by the user.
override NASMFLAGS += \
    -Wall \
    -f elf

# Use "find" to glob all *.c, *.S, and *.asm files in the tree and obtain the
# object and header dependency file names.
override CFILES := $(shell cd kernel/src && find -L * -type f -name '*.c')
override ASFILES := $(shell cd kernel/assembly && find -L * -type f -name '*.S')
override NASMFILES := $(shell cd kernel/assembly && find -L * -type f -name '*.asm')
override HEADERS := $(shell cd kernel/includes && find -L * -type f -name '*.h')
override OBJ := $(addprefix obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o))

# Default target.
.PHONY: all
all: bin/$(OS)

run: bin/$(OS)
	qemu-system-x86_64 -M q35 -m 8G -cdrom $(OS).iso -boot d -monitor stdio

bin/$(OS): bin/$(KERNEL).bin $(OS).initrd
	cp bin/$(KERNEL).bin isodir/boot/$(KERNEL).bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	cp $(OS).initrd isodir/boot/$(OS).initrd
	grub-mkrescue -o $(OS).iso isodir

$(OS).initrd: programs
	tar cf $(OS).initrd initrd

# Link rules for the final kernel executable.
bin/$(KERNEL).bin: linker.ld $(OBJ)
	mkdir -p "$$(dirname $@)"
	$(LD) $(OBJ) $(LDFLAGS) -o $@

# Compilation rules for *.c files.
obj/%.c.o: kernel/src/%.c
	mkdir -p "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Compilation rules for *.S files.
obj/%.S.o: kernel/assembly/%.S
	mkdir -p "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Compilation rules for *.asm (nasm) files.
obj/%.asm.o: kernel/assembly/%.asm
	mkdir -p "$$(dirname $@)"
	nasm $(NASMFLAGS) $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf bin obj
	rm -rf programs/out
	rm -rf initrd/programs
	rm -rf $(OS).initrd

# Generate user-space programs
.PHONY: programs
programs: initrd/programs
	cd programs && make && cd ..
	cp -r programs/out/* initrd/programs/

initrd/programs:
	mkdir initrd/programs
