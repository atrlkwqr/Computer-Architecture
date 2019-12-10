      .data
n: .word  3
      .text
lb 	$a0 , n
jal	sum
add	$v1, $v1, $v0
exit:
li	$v0, 10
syscall

sum:
	lw $v0, n
	lw $s1, n
	addi $sp, $sp, -4
	sw $v0, 0($sp)
	
	loop:
		
	lw $t0, 0($sp)
	
	add $t1, $v0, $t0
	addiu $v0, $v0, -1
	sw $t1, 0($sp)
	
	bne $v0, $0, loop
	
	add $a0, $t1, $0
	
	lw $s0, 0($sp)
	addi $sp, $sp, 4
	
	sub $a0, $a0, $s1
	
	li	$v0, 1
	syscall
	jr $ra