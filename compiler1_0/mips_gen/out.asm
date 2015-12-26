addi $s0, $sp, 0
addi $sp, $sp, -80
sw  $sp, 0($sp)

#CON 'a'  defa

addi $t0, $zero, 97
sw  $t0, -52($sp)

#VART   0


#J   begin0

j   begin0

#DEC f  genchar

genchar:   
sw  $ra, -48($sp)

#VART   0


#J   begin1

j   begin1

#LABEL   begin1

begin1:   

#ADD 0 defa genchar

addi $t1, $zero, 0
lw  $t0, 0($sp)
lw  $t2, -52($t0)
add $t3, $t1, $t2
sw  $t3, -44($sp)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin0

begin0:   

#WRITE   defa

addi $v0, $zero, 11
lw  $a0, -52($sp)
syscall   
