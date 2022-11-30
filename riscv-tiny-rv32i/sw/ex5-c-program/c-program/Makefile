all : main
	
main : ex5.c bootstrap.S
	riscv32-unknown-elf-gcc ex5.c bootstrap.S -o main -O0 -nostartfiles -Wl,--no-relax -march=rv32im -mabi=ilp32
	
dump-elf: all
	riscv32-unknown-elf-readelf -a main
	
dump-code: all
	riscv32-unknown-elf-objdump -D main
	
clean:
	rm -f main
