.globl _start
_start:

li a0,50
li a1,100

li a2,0
loop:
bgt a0,a1,end
add a2,a2,a0
addi a0,a0,1
j loop
end:

li a0,1
li a1,0
add a1,a1,a2
li a2,0

squareLoop:
bgt a0,a1,squareEnd
add a2,a2,a1
addi a0,a0,1
j squareLoop
squareEnd:

li a7,93
li a0,0
ecall
