all : main.c sum.c bootstrap.S
	riscv32-unknown-elf-gcc main.c sum.c bootstrap.S -o main -march=rv32i -mabi=ilp32 -nostartfiles -Wl,-no-relax
	
dump-elf: all
	riscv32-unknown-elf-readelf -a main
	
dump-code: all
	riscv32-unknown-elf-objdump -D main
	
dump-asm: all
	riscv32-unknown-elf-objdump -S main
	
sim: all
	../../isa/build/lib/riscv-tiny-isa main
	
dump-comment: all
	objdump -s --section .comment main
	
clean:
	rm -f main
