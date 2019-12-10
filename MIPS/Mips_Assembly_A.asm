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
	add $t0, $a0, $t0
	sub $a0, $a0, 1
	
	bne $a0 $0 sum
	add $a0, $t0, $0
	
	li	$v0, 1
	syscall
	
	jr $ra