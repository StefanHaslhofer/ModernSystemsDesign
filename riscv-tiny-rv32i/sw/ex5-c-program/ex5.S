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
    mv t0, x0			# t0 = 0 -> counter
    lw t1, source		# t1 = source
    addi t2, t1, 7*4	# t2 = start address of t1 + 7 elements * 4 byte = start address of dest

loop:
    slli t3, t0, 2		# shift counter one word (4 bytes) to the left to get exact number of index
    add t4, t1, t3		# 
    lw t5, 0(t4)
    beq t5, x0, exit	# exit on zero in source
    add t6, t2, t3
    sw t5, 0(t6)    
    addi t0, t0, 1		# increment counter (t0++)
    j loop

exit:
    li a7, 93
    li a0, 0
    ecall
