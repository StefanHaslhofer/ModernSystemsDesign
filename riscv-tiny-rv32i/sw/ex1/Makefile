all : ex1.o
	riscv32-unknown-elf-ld ex1.o -o main
	
ex1.o : ex1.S
	riscv32-unknown-elf-as ex1.S -o ex1.o -march=rv32i -mabi=ilp32
	
dump-elf: all
	riscv32-unknown-elf-readelf -a main
	
dump-code: all
	riscv32-unknown-elf-objdump -D main
	
sim: all
	../../isa/build/lib/riscv-tiny-isa main
	
clean:
	rm -f main ex1.o
