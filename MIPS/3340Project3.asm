	.globl main

main: 	li $v0 5		#load input [1,10000] from keyboard
	syscall
	
	addi $t0, $v0, 0	#load input from keyboard into t0
	addi $t1, $0, 0		#initialize t1 to zero for base of summation
	addi $t4, $0, 0		#intiialize t4 to zero for limit of summation		
	addi $t2, $0, 0		#initialize t2 to zero for result of summation
	addi $t3, $0, 0		#initialize t3 to zero for internal use in calculating sum
	add $a0, $t0, $0
	jal func

	addi $t4, $t4, -1	#decrement t4 by 1
	li $v0 36		#print an unsigned int
	addi $a0, $t4, 0	#load t4 to a0 to print
	syscall
	
	li $v0 10		#exit the program
	syscall

func:	
	sum:	beq $t1, $t4, comp	#if summation limit is reached, branch to compare sum to input
		addi $t1, $t1, 1	#increment t1 by 1
		addu $t3, $t1, $t1	#double t1 and add it into t3
		addi $t3, $t3, -1	#decrement the value in t3 by 1
		addu $t2, $t2, $t3	#add the value of 2i-1 to the sum
		addi $t3, $0, 0		#reset t3 to zero
		j sum
	
	comp:	bgt $t2, $a0, end	#if sum is greater than input, branch to end
		addi $t4, $t4, 1	#increment t4 if not and recalculate the sum
		addi $t1, $0, 0		#reset t1 to zero
		addi $t2, $0, 0		#reset t2 to zero
		addi $t3, $0, 0		#reset t3 to zero
		j sum			#recalculate sum
		
	end: jr $ra

	

	
