      	.globl main

main:	li $v0 5		#load input [1,1000] from keyboard into v0
	syscall
      
	addi $t0, $v0, 0	#load user input from v0 to t0
	addi $t1, $0, 0		#initialize t1 with 0 for start of summation
	addi $t2, $0, 0		#initialize t2 with 0 for sum total
	
loop:	addu $t2, $t2, $t1	#add the value of t1 to the sum
	addi $t1, $t1, 1	#increment t1 by 1
	bne $t0, $t1, loop	#if t1 =/= t0, loop again
      	
      	addu $t2, $t2, $t1	#after the increment limit has been reached, add the final t1 value to t2
      	
      	li $v0 36		#load v0 with 36 to print an unsigned integer
      	addi $a0, $t2, 0	#add the result from t2 to a0
      	syscall
      	
	li $v0 10		#load v0 with 10 to exit the program
	syscall
