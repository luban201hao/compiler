.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
   li $v0, 4
   la $a0, _prompt
   syscall
   li $v0, 5
   syscall
   jr $ra
write:
   li $v0, 1
   syscall
   li $v0, 4
   la $a0, _ret
   syscall
   move $v0, $0
   jr $ra
main:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi, $sp, $sp, -36
    
    addi $t0, $fp, -8  # t0 = &v0
    sw $t0, -12($fp) 

    li $t0, 0  # t1 = #0
    sw $t0, -16($fp)
    li $t0, 1  # t2 = #1
    sw $t0, -20($fp)
    li $t0, 1  # t2 = #1 * t2
    lw $t1, -20($fp)
    mul $t0, $t0, $t1
    sw $t0, -20($fp)

    lw $t0, -16($fp) # t1 = t1 + t2
    lw $t1, -20($fp)
    add $t0, $t0, $t1
    sw $t0, -16($fp) 

    li $t0, 4  # t1 = #4 * t1
    lw $t1, -16($fp)
    mul $t0, $t0, $t1
    sw $t0, -16($fp)

    lw $t0, -12($fp) # t0 = t0 + t1
    lw $t1, -16($fp)
    add $t0, $t0, $t1
    sw $t0, -12($fp)

    # print t0
    lw $t0, -12($fp)
    move $a0, $t0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal write
    lw $ra, 0($sp)
    addi $sp, $sp, 4  

    lw $t0 -12($fp) # *t0 = #2
    li $t1, 2
    sw $t1, 0($t0)

    # print t0
    lw $t0, -12($fp)
    move $a0, $t0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal write
    lw $ra, 0($sp)
    addi $sp, $sp, 4  

    # print x[1]
    lw $t0, -4($fp)
    move $a0, $t0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal write
    lw $ra, 0($sp)
    addi $sp, $sp, 4  


    addi $t0, $fp, -8
    sw $t0, -24($fp)
    li $t0, 0
    sw $t0, -28($fp)
    li $t0, 1
    sw $t0, -32($fp)
    li $t0, 1
    lw $t1, -32($fp)
    mul $t0, $t0, $t1
    sw $t0, -32($fp)
    lw $t0, -28($fp)
    lw $t1, -32($fp)
    add $t0, $t0, $t1
    sw $t0, -28($fp)
    li $t0, 4
    lw $t1, -28($fp)
    mul $t0, $t0, $t1
    sw $t0, -28($fp)
    lw $t0, -24($fp)
    lw $t1, -28($fp)
    add $t0, $t0, $t1
    sw $t0, -24($fp)
    lw $t0, -24($fp)
    lw $t1, 0($t0)
    sw $t1, -36($fp)
    lw $t0, -36($fp)
    move $a0, $t0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal write
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    lw $ra, 4($fp)
    addi $sp, $fp, 8
    li $t0, 0
    lw $fp, 0($fp)
    move $v0, $t0
    jr $ra
