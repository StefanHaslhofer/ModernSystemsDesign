.globl _start
.globl main

_start:
jal main

# call exit (SYS_EXIT=93) with exit code 0 (argument in a0)
li a7,93
li a0,0
ecall


.globl write
write:     # arguments already in a0 to a2
li a7, 64  # syscall_write == 64
ecall      # call host function
ret        # return to caller
