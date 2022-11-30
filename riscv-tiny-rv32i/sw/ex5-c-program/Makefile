all : main

main : ex5.o
	riscv32-unknown-elf-ld ex5.o -o main
	
ex5.o : ex5.S
	riscv32-unknown-elf-as ex5.S -o ex5.o -march=rv32im -mabi=ilp32
	
dump-elf: all
	riscv32-unknown-elf-readelf -a main
	
dump-code: all
	riscv32-unknown-elf-objdump -D main
	
clean:
	rm -f main ex5.o
