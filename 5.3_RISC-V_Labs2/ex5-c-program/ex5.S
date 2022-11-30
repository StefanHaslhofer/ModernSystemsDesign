#NOTE: based on example from https://inst.eecs.berkeley.edu/~cs61c/fa17/

.data
source:
	.word	3
	.word	1
	.word	4
	.word	1
	.word	5
	.word	9
	.word	0
dest:
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0


.text
.globl _start
_start:
main:
    mv t0, x0
    la t1, source
    addi t2, t1, 7*4

loop:
    slli t3, t0, 2
    add t4, t1, t3
    lw t5, 0(t4)
    beq t5, x0, exit	# TODO: implement beq command in ISS to execute this program
    add t6, t2, t3
    sw t5, 0(t6)    
    addi t0, t0, 1
    j loop

exit:
    li a7, 93
    li a0, 0
    ecall
