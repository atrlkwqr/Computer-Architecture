	.data
n: .word 5
	.text
lb	$a0,	n
jal	fib
addi	$v1,	$v0,	0

exit:
li 	$v0,	10
syscall

twoterm:
    addi $a0, $a0, -1
    jr $ra
    
fib: 
    lw $s1, n
    addi $t0, $s1, -1
    beq $t0, $0, exit
    addi $t1, $s1, -2
    beq $t1, $0, twoterm
    addi $s1, $s1, -2
    addi $v1 ,$v1, 1
    addi $v0 ,$v0, 1
    
    addi $sp $sp -16
    sw $ra, 12($sp)  
    sw $s1, 8($sp) # n�� �� (��� 1�� ����)
    sw $v1, 4($sp) # 1�� ° ��
    sw $v0, 0($sp) # 2�� ° ��

    loop: 
    
    lw $s1, 8($sp)
    lw $v1, 4($sp)
    lw $v0, 0($sp)
    add $t0, $v0, $0
    addi $s1, $s1, -1
    add $v0, $v1, $v0
    sw $s1, 8($sp)
    sw $t0, 4($sp)
    sw $v0, 0($sp)
    
    bne $s1, $0, loop
    				#v0 ������������ϱ� �״� ���ÿ� �߰�
    add $a0, $v0, $0
    jr $ra
    