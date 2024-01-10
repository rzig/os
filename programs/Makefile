.PHONY: .dummy

dummy: out/dummy

out/dummy: out dummy.asm
	nasm -f bin dummy.asm -o out/dummy
out:
	mkdir out
