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
    addi $t0, $fp, 0
    sw $t0, -8($fp)
    li $t0, 0
    sw $t0, -12($fp)
    li $t0, 1
    sw $t0, -16($fp)
    li $t0, 1
    lw $t1, -16($fp)
    mul $t0, $t0, $t1
    sw $t0, -16($fp)
    lw $t0, -12($fp)
    lw $t1, -16($fp)
    add $t0, $t0, $t1
    sw $t0, -12($fp)
    li $t0, 4
    lw $t1, -12($fp)
    mul $t0, $t0, $t1
    sw $t0, -12($fp)
    lw $t0, -8($fp)
    lw $t1, -12($fp)
    add $t0, $t0, $t1
    sw $t0, -8($fp)

   # print -8(fp)
    lw $t0, -8($fp)
    move $a0, $t0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal write
    lw $ra, 0($sp)
    addi $sp, $sp, 4  

    # addi $t0, $fp, -8
    # li $t1, 2
    # sw $t1, 0($t0)
    addi $t0, $fp, -8
    lw $t1, 0($t0)
    li $t2, 2
    sw $t2, 0($t1)

   # print -4(fp)
    lw $t0, -4($fp)
    move $a0, $t0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal write
    lw $ra, 0($sp)
    addi $sp, $sp, 4  

    addi $t0, $fp, 0
    sw $t0, -20($fp)
   # print t3
    lw $t0, -20($fp)
    move $a0, $t0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal write
    lw $ra, 0($sp)
    addi $sp, $sp, 4


    li $t0, 0
    sw $t0, -24($fp)
    li $t0, 1
    sw $t0, -28($fp)
    li $t0, 1
    lw $t1, -28($fp)
    mul $t0, $t0, $t1
    sw $t0, -28($fp)
    lw $t0, -24($fp)
    lw $t1, -28($fp)
    add $t0, $t0, $t1
    sw $t0, -24($fp)
    li $t0, 4
    lw $t1, -24($fp)
    mul $t0, $t0, $t1
    sw $t0, -24($fp)

    lw $t0, -20($fp)
    lw $t1, -24($fp)
    add $t0, $t0, $t1
    sw $t0, -20($fp)
    
   # print t3 after
    lw $t0, -20($fp)
    move $a0, $t0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal write
    lw $ra, 0($sp)
    addi $sp, $sp, 4


    lw $t0, -20($fp)
    lw $t1, ($t0)
    sw $t1, -32($fp)
    
    lw $t0, -32($fp)
    move $a0, $t0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal write
    lw $ra, 0($sp)
    addi $sp, $sp, 4


    li $t0, 0
    move $v0, $t0
    addi $sp, $fp, 8
    lw $ra, 4($fp)
    lw $fp, 0($fp)
    jr $ra
