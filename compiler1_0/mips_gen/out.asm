addi $s0, $sp, 0
addi $sp, $sp, -80
sw  $sp, 0($sp)

#VAR n i a1


#VAR n i a2


#VAR n i a3


#VAR n i a4


#VAR n i a5


#VAR n i g


#VART   0


#J   begin0

j   begin0

#DEC p  p1

p1:   
sw  $ra, -20($sp)

#VAR n i l1


#VAR n i l2


#VAR n i l3


#VAR n i l4


#VAR n i l5


#VAR n i g2


#VART   0


#J   begin1

j   begin1

#DEC p  p2

p2:   
sw  $ra, -20($sp)

#VART   0


#J   begin2

j   begin2

#DEC p  p3

p3:   
sw  $ra, -20($sp)

#PAR v i tmp

lw  $t1, -4($s0)
sw  $t1, -24($sp)

#VART   0


#J   begin3

j   begin3

#DEC p  p4

p4:   
sw  $ra, -20($sp)

#PAR v i tmp

lw  $t1, -4($s0)
sw  $t1, -24($sp)

#VAR n i tmp4


#VART   0


#J   begin4

j   begin4

#DEC p  p5

p5:   
sw  $ra, -20($sp)

#PAR v i tmp

lw  $t1, -4($s0)
sw  $t1, -24($sp)

#VART   0


#J   begin5

j   begin5

#LABEL   begin5

begin5:   

#ADD 0 5 tmp

addi $t1, $zero, 0
addi $t2, $zero, 5
add $t3, $t1, $t2
lw  $t0, -24($sp)
sw  $t3, 0($t0)

#ADD 0 5 a5

addi $t1, $zero, 0
addi $t2, $zero, 5
add $t3, $t1, $t2
lw  $t0, 0($sp)
sw  $t3, -28($t0)

#ADD 0 5 l5

addi $t1, $zero, 0
addi $t2, $zero, 5
add $t3, $t1, $t2
lw  $t0, -4($sp)
sw  $t3, -40($t0)

#JR   

lw  $v0, -16($sp)
lw  $ra, -20($sp)
lw  $sp, -12($sp)
jr   $ra

#LABEL   begin4

begin4:   

#PUSH   tmp4

lw  $t1, -28($sp)
addi $t2, $sp, -28
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   p5

sw  $sp, -44($sp)
lw  $t0, 0($sp)
sw  $t0, -32($sp)
lw  $t0, -4($sp)
sw  $t0, -36($sp)
lw  $t0, -8($sp)
sw  $t0, -40($sp)
sw  $sp, -48($sp)
addi $sp, $sp, -32
jal   p5

#ADD 0 tmp4 tmp

addi $t1, $zero, 0
lw  $t2, -28($sp)
add $t3, $t1, $t2
lw  $t0, -24($sp)
sw  $t3, 0($t0)

#ADD 0 4 a4

addi $t1, $zero, 0
addi $t2, $zero, 4
add $t3, $t1, $t2
lw  $t0, 0($sp)
sw  $t3, -24($t0)

#ADD 0 4 l4

addi $t1, $zero, 0
addi $t2, $zero, 4
add $t3, $t1, $t2
lw  $t0, -4($sp)
sw  $t3, -36($t0)

#JR   

lw  $v0, -16($sp)
lw  $ra, -20($sp)
lw  $sp, -12($sp)
jr   $ra

#LABEL   begin3

begin3:   

#PUSH   tmp

lw  $t2, -24($sp)
lw  $t1, 0($t2)
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   p4

sw  $sp, -40($sp)
lw  $t0, 0($sp)
sw  $t0, -28($sp)
lw  $t0, -4($sp)
sw  $t0, -32($sp)
lw  $t0, -8($sp)
sw  $t0, -36($sp)
sw  $sp, -40($sp)
addi $sp, $sp, -28
jal   p4

#ADD 0 3 a3

addi $t1, $zero, 0
addi $t2, $zero, 3
add $t3, $t1, $t2
lw  $t0, 0($sp)
sw  $t3, -20($t0)

#ADD 0 3 l3

addi $t1, $zero, 0
addi $t2, $zero, 3
add $t3, $t1, $t2
lw  $t0, -4($sp)
sw  $t3, -32($t0)

#JR   

lw  $v0, -16($sp)
lw  $ra, -20($sp)
lw  $sp, -12($sp)
jr   $ra

#LABEL   begin2

begin2:   

#PUSH   g

lw  $t0, 0($sp)
lw  $t1, -32($t0)
addi $t2, $t0, -32
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   p3

sw  $sp, -36($sp)
lw  $t0, 0($sp)
sw  $t0, -24($sp)
lw  $t0, -4($sp)
sw  $t0, -28($sp)
lw  $t0, -8($sp)
sw  $t0, -32($sp)
sw  $sp, -32($sp)
addi $sp, $sp, -24
jal   p3

#PUSH   g2

lw  $t0, -4($sp)
lw  $t1, -44($t0)
addi $t2, $t0, -44
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   p3

sw  $sp, -36($sp)
lw  $t0, 0($sp)
sw  $t0, -24($sp)
lw  $t0, -4($sp)
sw  $t0, -28($sp)
lw  $t0, -8($sp)
sw  $t0, -32($sp)
sw  $sp, -32($sp)
addi $sp, $sp, -24
jal   p3

#ADD 0 2 l2

addi $t1, $zero, 0
addi $t2, $zero, 2
add $t3, $t1, $t2
lw  $t0, -4($sp)
sw  $t3, -28($t0)

#ADD 0 2 a2

addi $t1, $zero, 0
addi $t2, $zero, 2
add $t3, $t1, $t2
lw  $t0, 0($sp)
sw  $t3, -16($t0)

#JR   

lw  $v0, -16($sp)
lw  $ra, -20($sp)
lw  $sp, -12($sp)
jr   $ra

#LABEL   begin1

begin1:   

#CALL   p2

sw  $sp, -60($sp)
lw  $t0, 0($sp)
sw  $t0, -48($sp)
lw  $t0, -4($sp)
sw  $t0, -52($sp)
lw  $t0, -8($sp)
sw  $t0, -56($sp)
sw  $sp, -52($sp)
addi $sp, $sp, -48
jal   p2

#ADD 0 1 a1

addi $t1, $zero, 0
addi $t2, $zero, 1
add $t3, $t1, $t2
lw  $t0, 0($sp)
sw  $t3, -12($t0)

#ADD 0 1 l1

addi $t1, $zero, 0
addi $t2, $zero, 1
add $t3, $t1, $t2
sw  $t3, -24($sp)

#WRITE   l1

addi $v0, $zero, 1
lw  $a0, -24($sp)
syscall   

#WRITE   l2

addi $v0, $zero, 1
lw  $a0, -28($sp)
syscall   

#WRITE   l3

addi $v0, $zero, 1
lw  $a0, -32($sp)
syscall   

#WRITE   l4

addi $v0, $zero, 1
lw  $a0, -36($sp)
syscall   

#WRITE   l5

addi $v0, $zero, 1
lw  $a0, -40($sp)
syscall   

#WRITE   g2

addi $v0, $zero, 1
lw  $a0, -44($sp)
syscall   

#JR   

lw  $v0, -16($sp)
lw  $ra, -20($sp)
lw  $sp, -12($sp)
jr   $ra

#LABEL   begin0

begin0:   

#CALL   p1

sw  $sp, -48($sp)
lw  $t0, 0($sp)
sw  $t0, -36($sp)
lw  $t0, -4($sp)
sw  $t0, -40($sp)
lw  $t0, -8($sp)
sw  $t0, -44($sp)
sw  $sp, -36($sp)
addi $sp, $sp, -36
jal   p1

#WRITE   a1

addi $v0, $zero, 1
lw  $a0, -12($sp)
syscall   

#WRITE   a2

addi $v0, $zero, 1
lw  $a0, -16($sp)
syscall   

#WRITE   a3

addi $v0, $zero, 1
lw  $a0, -20($sp)
syscall   

#WRITE   a4

addi $v0, $zero, 1
lw  $a0, -24($sp)
syscall   

#WRITE   a5

addi $v0, $zero, 1
lw  $a0, -28($sp)
syscall   

#WRITE   g

addi $v0, $zero, 1
lw  $a0, -32($sp)
syscall   
