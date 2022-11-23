all : test.o
	riscv32-unknown-elf-ld test.o -o main
	
test.o : test.S
	riscv32-unknown-elf-as test.S -o test.o -march=rv32i -mabi=ilp32
	
dump-elf: all
	riscv32-unknown-elf-readelf -a main
	
dump-code: all
	riscv32-unknown-elf-objdump -D main
	
sim: all
	../../isa/build/lib/riscv-tiny-isa main
	
clean:
	rm -f main test.o
