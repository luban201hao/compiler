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
_dist:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi, $sp, $sp, -44
    lw $t0, 16($fp)
    lw $t1, 8($fp)
    sub $t0, $t0, $t1
    sw $t0, -4($fp)
    lw $t0, -4($fp)
    sw $t0, -8($fp)
    lw $t0, 16($fp)
    lw $t1, 8($fp)
    sub $t0, $t0, $t1
    sw $t0, -12($fp)
    lw $t0, -12($fp)
    sw $t0, -16($fp)
    lw $t0, -8($fp)
    lw $t1, -16($fp)
    mul $t0, $t0, $t1
    sw $t0, -20($fp)
    lw $t0, 20($fp)
    lw $t1, 12($fp)
    sub $t0, $t0, $t1
    sw $t0, -24($fp)
    lw $t0, -24($fp)
    sw $t0, -28($fp)
    lw $t0, 20($fp)
    lw $t1, 12($fp)
    sub $t0, $t0, $t1
    sw $t0, -32($fp)
    lw $t0, -32($fp)
    sw $t0, -36($fp)
    lw $t0, -28($fp)
    lw $t1, -36($fp)
    mul $t0, $t0, $t1
    sw $t0, -40($fp)
    lw $t0, -20($fp)
    lw $t1, -40($fp)
    add $t0, $t0, $t1
    sw $t0, -44($fp)
    lw $ra, 4($fp)
    addi $sp, $fp, 8
    lw $t0, -44($fp)
    lw $fp, 0($fp)
    move $v0, $t0
    jr $ra
_check:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi, $sp, $sp, -108
    addi $sp, $sp -4
    lw $t0, 20($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 16($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 12($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 8($fp)
    sw $t0, 0($sp)
    jal _dist
    addi $sp, $sp, 16
    sw $v0, -4($fp)
    lw $t0, -4($fp)
    li $t1, 0
    bgt $t0, $t1, label0
    li $t0, 0
    sw $t0, -12($fp)
    j label1
    label0:
    li $t0, 1
    sw $t0, -12($fp)
    label1:
    addi $sp, $sp -4
    lw $t0, 20($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 16($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 12($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 8($fp)
    sw $t0, 0($sp)
    jal _dist
    addi $sp, $sp, 16
    sw $v0, -16($fp)
    addi $sp, $sp -4
    lw $t0, 28($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 24($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 20($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 16($fp)
    sw $t0, 0($sp)
    jal _dist
    addi $sp, $sp, 16
    sw $v0, -20($fp)
    lw $t0, -16($fp)
    lw $t1, -20($fp)
    beq $t0, $t1, label2
    li $t0, 0
    sw $t0, -28($fp)
    j label3
    label2:
    li $t0, 1
    sw $t0, -28($fp)
    label3:
    lw $t0, -12($fp)
    li $t1, 0
    beq $t0, $t1, label4
    lw $t0, -28($fp)
    li $t1, 0
    beq $t0, $t1, label4
    li $t0, 1
    sw $t0, -36($fp)
    j label5
    label4:
    li $t0, 0
    sw $t0, -36($fp)
    label5:
    addi $sp, $sp -4
    lw $t0, 28($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 24($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 20($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 16($fp)
    sw $t0, 0($sp)
    jal _dist
    addi $sp, $sp, 16
    sw $v0, -40($fp)
    addi $sp, $sp -4
    lw $t0, 36($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 32($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 28($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 24($fp)
    sw $t0, 0($sp)
    jal _dist
    addi $sp, $sp, 16
    sw $v0, -44($fp)
    lw $t0, -40($fp)
    lw $t1, -44($fp)
    beq $t0, $t1, label6
    li $t0, 0
    sw $t0, -52($fp)
    j label7
    label6:
    li $t0, 1
    sw $t0, -52($fp)
    label7:
    lw $t0, -36($fp)
    li $t1, 0
    beq $t0, $t1, label8
    lw $t0, -52($fp)
    li $t1, 0
    beq $t0, $t1, label8
    li $t0, 1
    sw $t0, -60($fp)
    j label9
    label8:
    li $t0, 0
    sw $t0, -60($fp)
    label9:
    addi $sp, $sp -4
    lw $t0, 36($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 32($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 28($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 24($fp)
    sw $t0, 0($sp)
    jal _dist
    addi $sp, $sp, 16
    sw $v0, -64($fp)
    addi $sp, $sp -4
    lw $t0, 12($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 8($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 36($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 32($fp)
    sw $t0, 0($sp)
    jal _dist
    addi $sp, $sp, 16
    sw $v0, -68($fp)
    lw $t0, -64($fp)
    lw $t1, -68($fp)
    beq $t0, $t1, label10
    li $t0, 0
    sw $t0, -76($fp)
    j label11
    label10:
    li $t0, 1
    sw $t0, -76($fp)
    label11:
    lw $t0, -60($fp)
    li $t1, 0
    beq $t0, $t1, label12
    lw $t0, -76($fp)
    li $t1, 0
    beq $t0, $t1, label12
    li $t0, 1
    sw $t0, -84($fp)
    j label13
    label12:
    li $t0, 0
    sw $t0, -84($fp)
    label13:
    addi $sp, $sp -4
    lw $t0, 28($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 24($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 12($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 8($fp)
    sw $t0, 0($sp)
    jal _dist
    addi $sp, $sp, 16
    sw $v0, -88($fp)
    addi $sp, $sp -4
    lw $t0, 36($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 32($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 20($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, 16($fp)
    sw $t0, 0($sp)
    jal _dist
    addi $sp, $sp, 16
    sw $v0, -92($fp)
    lw $t0, -88($fp)
    lw $t1, -92($fp)
    beq $t0, $t1, label14
    li $t0, 0
    sw $t0, -100($fp)
    j label15
    label14:
    li $t0, 1
    sw $t0, -100($fp)
    label15:
    lw $t0, -84($fp)
    li $t1, 0
    beq $t0, $t1, label16
    lw $t0, -100($fp)
    li $t1, 0
    beq $t0, $t1, label16
    li $t0, 1
    sw $t0, -108($fp)
    j label17
    label16:
    li $t0, 0
    sw $t0, -108($fp)
    label17:
    lw $ra, 4($fp)
    addi $sp, $fp, 8
    lw $t0, -108($fp)
    lw $fp, 0($fp)
    move $v0, $t0
    jr $ra
main:
    addi $sp, $sp, -8
    sw $fp, 0($sp)
    sw $ra, 4($sp)
    move $fp, $sp
    addi, $sp, $sp, -584
    addi $t0, $fp, -8
    sw $t0, -36($fp)
    li $t0, 0
    sw $t0, -40($fp)
    li $t0, 1
    sw $t0, -44($fp)
    li $t0, 0
    lw $t1, -44($fp)
    mul $t0, $t0, $t1
    sw $t0, -44($fp)
    lw $t0, -40($fp)
    lw $t1, -44($fp)
    add $t0, $t0, $t1
    sw $t0, -40($fp)
    li $t0, 4
    lw $t1, -40($fp)
    mul $t0, $t0, $t1
    sw $t0, -40($fp)
    lw $t0, -36($fp)
    lw $t1, -40($fp)
    add $t0, $t0, $t1
    sw $t0, -36($fp)
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal read
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    sw $v0, -48($fp)
    lw $t0, -36($fp)
    lw $t1, -48($fp)
    sw $t1, 0($t0)
    addi $t0, $fp, -8
    sw $t0, -52($fp)
    li $t0, 0
    sw $t0, -56($fp)
    li $t0, 1
    sw $t0, -60($fp)
    li $t0, 1
    lw $t1, -60($fp)
    mul $t0, $t0, $t1
    sw $t0, -60($fp)
    lw $t0, -56($fp)
    lw $t1, -60($fp)
    add $t0, $t0, $t1
    sw $t0, -56($fp)
    li $t0, 4
    lw $t1, -56($fp)
    mul $t0, $t0, $t1
    sw $t0, -56($fp)
    lw $t0, -52($fp)
    lw $t1, -56($fp)
    add $t0, $t0, $t1
    sw $t0, -52($fp)
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal read
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    sw $v0, -64($fp)
    lw $t0, -52($fp)
    lw $t1, -64($fp)
    sw $t1, 0($t0)
    addi $t0, $fp, -16
    sw $t0, -68($fp)
    li $t0, 0
    sw $t0, -72($fp)
    li $t0, 1
    sw $t0, -76($fp)
    li $t0, 0
    lw $t1, -76($fp)
    mul $t0, $t0, $t1
    sw $t0, -76($fp)
    lw $t0, -72($fp)
    lw $t1, -76($fp)
    add $t0, $t0, $t1
    sw $t0, -72($fp)
    li $t0, 4
    lw $t1, -72($fp)
    mul $t0, $t0, $t1
    sw $t0, -72($fp)
    lw $t0, -68($fp)
    lw $t1, -72($fp)
    add $t0, $t0, $t1
    sw $t0, -68($fp)
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal read
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    sw $v0, -80($fp)
    lw $t0, -68($fp)
    lw $t1, -80($fp)
    sw $t1, 0($t0)
    addi $t0, $fp, -16
    sw $t0, -84($fp)
    li $t0, 0
    sw $t0, -88($fp)
    li $t0, 1
    sw $t0, -92($fp)
    li $t0, 1
    lw $t1, -92($fp)
    mul $t0, $t0, $t1
    sw $t0, -92($fp)
    lw $t0, -88($fp)
    lw $t1, -92($fp)
    add $t0, $t0, $t1
    sw $t0, -88($fp)
    li $t0, 4
    lw $t1, -88($fp)
    mul $t0, $t0, $t1
    sw $t0, -88($fp)
    lw $t0, -84($fp)
    lw $t1, -88($fp)
    add $t0, $t0, $t1
    sw $t0, -84($fp)
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal read
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    sw $v0, -96($fp)
    lw $t0, -84($fp)
    lw $t1, -96($fp)
    sw $t1, 0($t0)
    addi $t0, $fp, -24
    sw $t0, -100($fp)
    li $t0, 0
    sw $t0, -104($fp)
    li $t0, 1
    sw $t0, -108($fp)
    li $t0, 0
    lw $t1, -108($fp)
    mul $t0, $t0, $t1
    sw $t0, -108($fp)
    lw $t0, -104($fp)
    lw $t1, -108($fp)
    add $t0, $t0, $t1
    sw $t0, -104($fp)
    li $t0, 4
    lw $t1, -104($fp)
    mul $t0, $t0, $t1
    sw $t0, -104($fp)
    lw $t0, -100($fp)
    lw $t1, -104($fp)
    add $t0, $t0, $t1
    sw $t0, -100($fp)
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal read
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    sw $v0, -112($fp)
    lw $t0, -100($fp)
    lw $t1, -112($fp)
    sw $t1, 0($t0)
    addi $t0, $fp, -24
    sw $t0, -116($fp)
    li $t0, 0
    sw $t0, -120($fp)
    li $t0, 1
    sw $t0, -124($fp)
    li $t0, 1
    lw $t1, -124($fp)
    mul $t0, $t0, $t1
    sw $t0, -124($fp)
    lw $t0, -120($fp)
    lw $t1, -124($fp)
    add $t0, $t0, $t1
    sw $t0, -120($fp)
    li $t0, 4
    lw $t1, -120($fp)
    mul $t0, $t0, $t1
    sw $t0, -120($fp)
    lw $t0, -116($fp)
    lw $t1, -120($fp)
    add $t0, $t0, $t1
    sw $t0, -116($fp)
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal read
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    sw $v0, -128($fp)
    lw $t0, -116($fp)
    lw $t1, -128($fp)
    sw $t1, 0($t0)
    addi $t0, $fp, -32
    sw $t0, -132($fp)
    li $t0, 0
    sw $t0, -136($fp)
    li $t0, 1
    sw $t0, -140($fp)
    li $t0, 0
    lw $t1, -140($fp)
    mul $t0, $t0, $t1
    sw $t0, -140($fp)
    lw $t0, -136($fp)
    lw $t1, -140($fp)
    add $t0, $t0, $t1
    sw $t0, -136($fp)
    li $t0, 4
    lw $t1, -136($fp)
    mul $t0, $t0, $t1
    sw $t0, -136($fp)
    lw $t0, -132($fp)
    lw $t1, -136($fp)
    add $t0, $t0, $t1
    sw $t0, -132($fp)
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal read
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    sw $v0, -144($fp)
    lw $t0, -132($fp)
    lw $t1, -144($fp)
    sw $t1, 0($t0)
    addi $t0, $fp, -32
    sw $t0, -148($fp)
    li $t0, 0
    sw $t0, -152($fp)
    li $t0, 1
    sw $t0, -156($fp)
    li $t0, 1
    lw $t1, -156($fp)
    mul $t0, $t0, $t1
    sw $t0, -156($fp)
    lw $t0, -152($fp)
    lw $t1, -156($fp)
    add $t0, $t0, $t1
    sw $t0, -152($fp)
    li $t0, 4
    lw $t1, -152($fp)
    mul $t0, $t0, $t1
    sw $t0, -152($fp)
    lw $t0, -148($fp)
    lw $t1, -152($fp)
    add $t0, $t0, $t1
    sw $t0, -148($fp)
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal read
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    sw $v0, -160($fp)
    lw $t0, -148($fp)
    lw $t1, -160($fp)
    sw $t1, 0($t0)
    addi $t0, $fp, -32
    sw $t0, -164($fp)
    li $t0, 0
    sw $t0, -168($fp)
    li $t0, 1
    sw $t0, -172($fp)
    li $t0, 1
    lw $t1, -172($fp)
    mul $t0, $t0, $t1
    sw $t0, -172($fp)
    lw $t0, -168($fp)
    lw $t1, -172($fp)
    add $t0, $t0, $t1
    sw $t0, -168($fp)
    li $t0, 4
    lw $t1, -168($fp)
    mul $t0, $t0, $t1
    sw $t0, -168($fp)
    lw $t0, -164($fp)
    lw $t1, -168($fp)
    add $t0, $t0, $t1
    sw $t0, -164($fp)
    lw $t0, -164($fp)
    lw $t1, 0($t0)
    sw $t1, -176($fp)
    addi $t0, $fp, -32
    sw $t0, -180($fp)
    li $t0, 0
    sw $t0, -184($fp)
    li $t0, 1
    sw $t0, -188($fp)
    li $t0, 0
    lw $t1, -188($fp)
    mul $t0, $t0, $t1
    sw $t0, -188($fp)
    lw $t0, -184($fp)
    lw $t1, -188($fp)
    add $t0, $t0, $t1
    sw $t0, -184($fp)
    li $t0, 4
    lw $t1, -184($fp)
    mul $t0, $t0, $t1
    sw $t0, -184($fp)
    lw $t0, -180($fp)
    lw $t1, -184($fp)
    add $t0, $t0, $t1
    sw $t0, -180($fp)
    lw $t0, -180($fp)
    lw $t1, 0($t0)
    sw $t1, -192($fp)
    addi $t0, $fp, -24
    sw $t0, -196($fp)
    li $t0, 0
    sw $t0, -200($fp)
    li $t0, 1
    sw $t0, -204($fp)
    li $t0, 1
    lw $t1, -204($fp)
    mul $t0, $t0, $t1
    sw $t0, -204($fp)
    lw $t0, -200($fp)
    lw $t1, -204($fp)
    add $t0, $t0, $t1
    sw $t0, -200($fp)
    li $t0, 4
    lw $t1, -200($fp)
    mul $t0, $t0, $t1
    sw $t0, -200($fp)
    lw $t0, -196($fp)
    lw $t1, -200($fp)
    add $t0, $t0, $t1
    sw $t0, -196($fp)
    lw $t0, -196($fp)
    lw $t1, 0($t0)
    sw $t1, -208($fp)
    addi $t0, $fp, -24
    sw $t0, -212($fp)
    li $t0, 0
    sw $t0, -216($fp)
    li $t0, 1
    sw $t0, -220($fp)
    li $t0, 0
    lw $t1, -220($fp)
    mul $t0, $t0, $t1
    sw $t0, -220($fp)
    lw $t0, -216($fp)
    lw $t1, -220($fp)
    add $t0, $t0, $t1
    sw $t0, -216($fp)
    li $t0, 4
    lw $t1, -216($fp)
    mul $t0, $t0, $t1
    sw $t0, -216($fp)
    lw $t0, -212($fp)
    lw $t1, -216($fp)
    add $t0, $t0, $t1
    sw $t0, -212($fp)
    lw $t0, -212($fp)
    lw $t1, 0($t0)
    sw $t1, -224($fp)
    addi $t0, $fp, -16
    sw $t0, -228($fp)
    li $t0, 0
    sw $t0, -232($fp)
    li $t0, 1
    sw $t0, -236($fp)
    li $t0, 1
    lw $t1, -236($fp)
    mul $t0, $t0, $t1
    sw $t0, -236($fp)
    lw $t0, -232($fp)
    lw $t1, -236($fp)
    add $t0, $t0, $t1
    sw $t0, -232($fp)
    li $t0, 4
    lw $t1, -232($fp)
    mul $t0, $t0, $t1
    sw $t0, -232($fp)
    lw $t0, -228($fp)
    lw $t1, -232($fp)
    add $t0, $t0, $t1
    sw $t0, -228($fp)
    lw $t0, -228($fp)
    lw $t1, 0($t0)
    sw $t1, -240($fp)
    addi $t0, $fp, -16
    sw $t0, -244($fp)
    li $t0, 0
    sw $t0, -248($fp)
    li $t0, 1
    sw $t0, -252($fp)
    li $t0, 0
    lw $t1, -252($fp)
    mul $t0, $t0, $t1
    sw $t0, -252($fp)
    lw $t0, -248($fp)
    lw $t1, -252($fp)
    add $t0, $t0, $t1
    sw $t0, -248($fp)
    li $t0, 4
    lw $t1, -248($fp)
    mul $t0, $t0, $t1
    sw $t0, -248($fp)
    lw $t0, -244($fp)
    lw $t1, -248($fp)
    add $t0, $t0, $t1
    sw $t0, -244($fp)
    lw $t0, -244($fp)
    lw $t1, 0($t0)
    sw $t1, -256($fp)
    addi $t0, $fp, -8
    sw $t0, -260($fp)
    li $t0, 0
    sw $t0, -264($fp)
    li $t0, 1
    sw $t0, -268($fp)
    li $t0, 1
    lw $t1, -268($fp)
    mul $t0, $t0, $t1
    sw $t0, -268($fp)
    lw $t0, -264($fp)
    lw $t1, -268($fp)
    add $t0, $t0, $t1
    sw $t0, -264($fp)
    li $t0, 4
    lw $t1, -264($fp)
    mul $t0, $t0, $t1
    sw $t0, -264($fp)
    lw $t0, -260($fp)
    lw $t1, -264($fp)
    add $t0, $t0, $t1
    sw $t0, -260($fp)
    lw $t0, -260($fp)
    lw $t1, 0($t0)
    sw $t1, -272($fp)
    addi $t0, $fp, -8
    sw $t0, -276($fp)
    li $t0, 0
    sw $t0, -280($fp)
    li $t0, 1
    sw $t0, -284($fp)
    li $t0, 0
    lw $t1, -284($fp)
    mul $t0, $t0, $t1
    sw $t0, -284($fp)
    lw $t0, -280($fp)
    lw $t1, -284($fp)
    add $t0, $t0, $t1
    sw $t0, -280($fp)
    li $t0, 4
    lw $t1, -280($fp)
    mul $t0, $t0, $t1
    sw $t0, -280($fp)
    lw $t0, -276($fp)
    lw $t1, -280($fp)
    add $t0, $t0, $t1
    sw $t0, -276($fp)
    lw $t0, -276($fp)
    lw $t1, 0($t0)
    sw $t1, -288($fp)
    addi $sp, $sp -4
    lw $t0, -176($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -192($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -208($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -224($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -240($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -256($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -272($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -288($fp)
    sw $t0, 0($sp)
    jal _check
    addi $sp, $sp, 32
    sw $v0, -292($fp)
    lw $t0, -292($fp)
    sw $t0, -296($fp)
    addi $t0, $fp, -32
    sw $t0, -300($fp)
    li $t0, 0
    sw $t0, -304($fp)
    li $t0, 1
    sw $t0, -308($fp)
    li $t0, 1
    lw $t1, -308($fp)
    mul $t0, $t0, $t1
    sw $t0, -308($fp)
    lw $t0, -304($fp)
    lw $t1, -308($fp)
    add $t0, $t0, $t1
    sw $t0, -304($fp)
    li $t0, 4
    lw $t1, -304($fp)
    mul $t0, $t0, $t1
    sw $t0, -304($fp)
    lw $t0, -300($fp)
    lw $t1, -304($fp)
    add $t0, $t0, $t1
    sw $t0, -300($fp)
    lw $t0, -300($fp)
    lw $t1, 0($t0)
    sw $t1, -312($fp)
    addi $t0, $fp, -32
    sw $t0, -316($fp)
    li $t0, 0
    sw $t0, -320($fp)
    li $t0, 1
    sw $t0, -324($fp)
    li $t0, 0
    lw $t1, -324($fp)
    mul $t0, $t0, $t1
    sw $t0, -324($fp)
    lw $t0, -320($fp)
    lw $t1, -324($fp)
    add $t0, $t0, $t1
    sw $t0, -320($fp)
    li $t0, 4
    lw $t1, -320($fp)
    mul $t0, $t0, $t1
    sw $t0, -320($fp)
    lw $t0, -316($fp)
    lw $t1, -320($fp)
    add $t0, $t0, $t1
    sw $t0, -316($fp)
    lw $t0, -316($fp)
    lw $t1, 0($t0)
    sw $t1, -328($fp)
    addi $t0, $fp, -16
    sw $t0, -332($fp)
    li $t0, 0
    sw $t0, -336($fp)
    li $t0, 1
    sw $t0, -340($fp)
    li $t0, 1
    lw $t1, -340($fp)
    mul $t0, $t0, $t1
    sw $t0, -340($fp)
    lw $t0, -336($fp)
    lw $t1, -340($fp)
    add $t0, $t0, $t1
    sw $t0, -336($fp)
    li $t0, 4
    lw $t1, -336($fp)
    mul $t0, $t0, $t1
    sw $t0, -336($fp)
    lw $t0, -332($fp)
    lw $t1, -336($fp)
    add $t0, $t0, $t1
    sw $t0, -332($fp)
    lw $t0, -332($fp)
    lw $t1, 0($t0)
    sw $t1, -344($fp)
    addi $t0, $fp, -16
    sw $t0, -348($fp)
    li $t0, 0
    sw $t0, -352($fp)
    li $t0, 1
    sw $t0, -356($fp)
    li $t0, 0
    lw $t1, -356($fp)
    mul $t0, $t0, $t1
    sw $t0, -356($fp)
    lw $t0, -352($fp)
    lw $t1, -356($fp)
    add $t0, $t0, $t1
    sw $t0, -352($fp)
    li $t0, 4
    lw $t1, -352($fp)
    mul $t0, $t0, $t1
    sw $t0, -352($fp)
    lw $t0, -348($fp)
    lw $t1, -352($fp)
    add $t0, $t0, $t1
    sw $t0, -348($fp)
    lw $t0, -348($fp)
    lw $t1, 0($t0)
    sw $t1, -360($fp)
    addi $t0, $fp, -24
    sw $t0, -364($fp)
    li $t0, 0
    sw $t0, -368($fp)
    li $t0, 1
    sw $t0, -372($fp)
    li $t0, 1
    lw $t1, -372($fp)
    mul $t0, $t0, $t1
    sw $t0, -372($fp)
    lw $t0, -368($fp)
    lw $t1, -372($fp)
    add $t0, $t0, $t1
    sw $t0, -368($fp)
    li $t0, 4
    lw $t1, -368($fp)
    mul $t0, $t0, $t1
    sw $t0, -368($fp)
    lw $t0, -364($fp)
    lw $t1, -368($fp)
    add $t0, $t0, $t1
    sw $t0, -364($fp)
    lw $t0, -364($fp)
    lw $t1, 0($t0)
    sw $t1, -376($fp)
    addi $t0, $fp, -24
    sw $t0, -380($fp)
    li $t0, 0
    sw $t0, -384($fp)
    li $t0, 1
    sw $t0, -388($fp)
    li $t0, 0
    lw $t1, -388($fp)
    mul $t0, $t0, $t1
    sw $t0, -388($fp)
    lw $t0, -384($fp)
    lw $t1, -388($fp)
    add $t0, $t0, $t1
    sw $t0, -384($fp)
    li $t0, 4
    lw $t1, -384($fp)
    mul $t0, $t0, $t1
    sw $t0, -384($fp)
    lw $t0, -380($fp)
    lw $t1, -384($fp)
    add $t0, $t0, $t1
    sw $t0, -380($fp)
    lw $t0, -380($fp)
    lw $t1, 0($t0)
    sw $t1, -392($fp)
    addi $t0, $fp, -8
    sw $t0, -396($fp)
    li $t0, 0
    sw $t0, -400($fp)
    li $t0, 1
    sw $t0, -404($fp)
    li $t0, 1
    lw $t1, -404($fp)
    mul $t0, $t0, $t1
    sw $t0, -404($fp)
    lw $t0, -400($fp)
    lw $t1, -404($fp)
    add $t0, $t0, $t1
    sw $t0, -400($fp)
    li $t0, 4
    lw $t1, -400($fp)
    mul $t0, $t0, $t1
    sw $t0, -400($fp)
    lw $t0, -396($fp)
    lw $t1, -400($fp)
    add $t0, $t0, $t1
    sw $t0, -396($fp)
    lw $t0, -396($fp)
    lw $t1, 0($t0)
    sw $t1, -408($fp)
    addi $t0, $fp, -8
    sw $t0, -412($fp)
    li $t0, 0
    sw $t0, -416($fp)
    li $t0, 1
    sw $t0, -420($fp)
    li $t0, 0
    lw $t1, -420($fp)
    mul $t0, $t0, $t1
    sw $t0, -420($fp)
    lw $t0, -416($fp)
    lw $t1, -420($fp)
    add $t0, $t0, $t1
    sw $t0, -416($fp)
    li $t0, 4
    lw $t1, -416($fp)
    mul $t0, $t0, $t1
    sw $t0, -416($fp)
    lw $t0, -412($fp)
    lw $t1, -416($fp)
    add $t0, $t0, $t1
    sw $t0, -412($fp)
    lw $t0, -412($fp)
    lw $t1, 0($t0)
    sw $t1, -424($fp)
    addi $sp, $sp -4
    lw $t0, -312($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -328($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -344($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -360($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -376($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -392($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -408($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -424($fp)
    sw $t0, 0($sp)
    jal _check
    addi $sp, $sp, 32
    sw $v0, -428($fp)
    lw $t0, -428($fp)
    sw $t0, -432($fp)
    addi $t0, $fp, -24
    sw $t0, -436($fp)
    li $t0, 0
    sw $t0, -440($fp)
    li $t0, 1
    sw $t0, -444($fp)
    li $t0, 1
    lw $t1, -444($fp)
    mul $t0, $t0, $t1
    sw $t0, -444($fp)
    lw $t0, -440($fp)
    lw $t1, -444($fp)
    add $t0, $t0, $t1
    sw $t0, -440($fp)
    li $t0, 4
    lw $t1, -440($fp)
    mul $t0, $t0, $t1
    sw $t0, -440($fp)
    lw $t0, -436($fp)
    lw $t1, -440($fp)
    add $t0, $t0, $t1
    sw $t0, -436($fp)
    lw $t0, -436($fp)
    lw $t1, 0($t0)
    sw $t1, -448($fp)
    addi $t0, $fp, -24
    sw $t0, -452($fp)
    li $t0, 0
    sw $t0, -456($fp)
    li $t0, 1
    sw $t0, -460($fp)
    li $t0, 0
    lw $t1, -460($fp)
    mul $t0, $t0, $t1
    sw $t0, -460($fp)
    lw $t0, -456($fp)
    lw $t1, -460($fp)
    add $t0, $t0, $t1
    sw $t0, -456($fp)
    li $t0, 4
    lw $t1, -456($fp)
    mul $t0, $t0, $t1
    sw $t0, -456($fp)
    lw $t0, -452($fp)
    lw $t1, -456($fp)
    add $t0, $t0, $t1
    sw $t0, -452($fp)
    lw $t0, -452($fp)
    lw $t1, 0($t0)
    sw $t1, -464($fp)
    addi $t0, $fp, -32
    sw $t0, -468($fp)
    li $t0, 0
    sw $t0, -472($fp)
    li $t0, 1
    sw $t0, -476($fp)
    li $t0, 1
    lw $t1, -476($fp)
    mul $t0, $t0, $t1
    sw $t0, -476($fp)
    lw $t0, -472($fp)
    lw $t1, -476($fp)
    add $t0, $t0, $t1
    sw $t0, -472($fp)
    li $t0, 4
    lw $t1, -472($fp)
    mul $t0, $t0, $t1
    sw $t0, -472($fp)
    lw $t0, -468($fp)
    lw $t1, -472($fp)
    add $t0, $t0, $t1
    sw $t0, -468($fp)
    lw $t0, -468($fp)
    lw $t1, 0($t0)
    sw $t1, -480($fp)
    addi $t0, $fp, -32
    sw $t0, -484($fp)
    li $t0, 0
    sw $t0, -488($fp)
    li $t0, 1
    sw $t0, -492($fp)
    li $t0, 0
    lw $t1, -492($fp)
    mul $t0, $t0, $t1
    sw $t0, -492($fp)
    lw $t0, -488($fp)
    lw $t1, -492($fp)
    add $t0, $t0, $t1
    sw $t0, -488($fp)
    li $t0, 4
    lw $t1, -488($fp)
    mul $t0, $t0, $t1
    sw $t0, -488($fp)
    lw $t0, -484($fp)
    lw $t1, -488($fp)
    add $t0, $t0, $t1
    sw $t0, -484($fp)
    lw $t0, -484($fp)
    lw $t1, 0($t0)
    sw $t1, -496($fp)
    addi $t0, $fp, -16
    sw $t0, -500($fp)
    li $t0, 0
    sw $t0, -504($fp)
    li $t0, 1
    sw $t0, -508($fp)
    li $t0, 1
    lw $t1, -508($fp)
    mul $t0, $t0, $t1
    sw $t0, -508($fp)
    lw $t0, -504($fp)
    lw $t1, -508($fp)
    add $t0, $t0, $t1
    sw $t0, -504($fp)
    li $t0, 4
    lw $t1, -504($fp)
    mul $t0, $t0, $t1
    sw $t0, -504($fp)
    lw $t0, -500($fp)
    lw $t1, -504($fp)
    add $t0, $t0, $t1
    sw $t0, -500($fp)
    lw $t0, -500($fp)
    lw $t1, 0($t0)
    sw $t1, -512($fp)
    addi $t0, $fp, -16
    sw $t0, -516($fp)
    li $t0, 0
    sw $t0, -520($fp)
    li $t0, 1
    sw $t0, -524($fp)
    li $t0, 0
    lw $t1, -524($fp)
    mul $t0, $t0, $t1
    sw $t0, -524($fp)
    lw $t0, -520($fp)
    lw $t1, -524($fp)
    add $t0, $t0, $t1
    sw $t0, -520($fp)
    li $t0, 4
    lw $t1, -520($fp)
    mul $t0, $t0, $t1
    sw $t0, -520($fp)
    lw $t0, -516($fp)
    lw $t1, -520($fp)
    add $t0, $t0, $t1
    sw $t0, -516($fp)
    lw $t0, -516($fp)
    lw $t1, 0($t0)
    sw $t1, -528($fp)
    addi $t0, $fp, -8
    sw $t0, -532($fp)
    li $t0, 0
    sw $t0, -536($fp)
    li $t0, 1
    sw $t0, -540($fp)
    li $t0, 1
    lw $t1, -540($fp)
    mul $t0, $t0, $t1
    sw $t0, -540($fp)
    lw $t0, -536($fp)
    lw $t1, -540($fp)
    add $t0, $t0, $t1
    sw $t0, -536($fp)
    li $t0, 4
    lw $t1, -536($fp)
    mul $t0, $t0, $t1
    sw $t0, -536($fp)
    lw $t0, -532($fp)
    lw $t1, -536($fp)
    add $t0, $t0, $t1
    sw $t0, -532($fp)
    lw $t0, -532($fp)
    lw $t1, 0($t0)
    sw $t1, -544($fp)
    addi $t0, $fp, -8
    sw $t0, -548($fp)
    li $t0, 0
    sw $t0, -552($fp)
    li $t0, 1
    sw $t0, -556($fp)
    li $t0, 0
    lw $t1, -556($fp)
    mul $t0, $t0, $t1
    sw $t0, -556($fp)
    lw $t0, -552($fp)
    lw $t1, -556($fp)
    add $t0, $t0, $t1
    sw $t0, -552($fp)
    li $t0, 4
    lw $t1, -552($fp)
    mul $t0, $t0, $t1
    sw $t0, -552($fp)
    lw $t0, -548($fp)
    lw $t1, -552($fp)
    add $t0, $t0, $t1
    sw $t0, -548($fp)
    lw $t0, -548($fp)
    lw $t1, 0($t0)
    sw $t1, -560($fp)
    addi $sp, $sp -4
    lw $t0, -448($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -464($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -480($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -496($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -512($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -528($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -544($fp)
    sw $t0, 0($sp)
    addi $sp, $sp -4
    lw $t0, -560($fp)
    sw $t0, 0($sp)
    jal _check
    addi $sp, $sp, 32
    sw $v0, -564($fp)
    lw $t0, -564($fp)
    sw $t0, -568($fp)
    lw $t0, -296($fp)
    li $t1, 0
    bne $t0, $t1, label18
    lw $t0, -432($fp)
    li $t1, 0
    bne $t0, $t1, label18
    li $t0, 0
    sw $t0, -576($fp)
    j label19
    label18:
    li $t0, 1
    sw $t0, -576($fp)
    label19:
    lw $t0, -576($fp)
    li $t1, 0
    bne $t0, $t1, label20
    lw $t0, -568($fp)
    li $t1, 0
    bne $t0, $t1, label20
    li $t0, 0
    sw $t0, -584($fp)
    j label21
    label20:
    li $t0, 1
    sw $t0, -584($fp)
    label21:
    lw $t0, -584($fp)
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
