addi $s0, $sp, 0
addi $sp, $sp, -80
sw  $sp, 0($sp)

#VART   0


#J   begin0

j   begin0

#DEC p  heh

heh:   
sw  $ra, -48($sp)

#VAR n i vn


#VAR n i out


#VAR n i i


#VAR a 10 a


#VART   0


#J   begin1

j   begin1

#DEC p  outter

outter:   
sw  $ra, -48($sp)

#PAR n i y

lw  $t1, 0($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin2

j   begin2

#DEC p  writeoo

writeoo:   
sw  $ra, -48($sp)

#VART   0


#J   begin3

j   begin3

#LABEL   begin3

begin3:   

#WRITE   "  "

addi $v0, $zero, 11
addi $a0, $zero, 32
syscall   
addi $a0, $zero, 32
syscall   

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#DEC p  foo

foo:   
sw  $ra, -48($sp)

#PAR n i y

lw  $t1, 0($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin4

j   begin4

#DEC p  pcd

pcd:   
sw  $ra, -48($sp)

#PAR n i x

lw  $t1, 0($s0)
sw  $t1, -52($sp)

#VAR n i t


#VART   1


#J   begin5

j   begin5

#DEC f  sum

sum:   
sw  $ra, -48($sp)

#PAR v i x

lw  $t1, -4($s0)
sw  $t1, -52($sp)

#VAR n i t


#VART   3


#J   begin6

j   begin6

#LABEL   begin6

begin6:   

#SUB x 1 #0

lw  $t0, -52($sp)
lw  $t1, 0($t0)
addi $t2, $zero, 1
sub $t3, $t1, $t2
sw  $t3, -60($sp)

#ADD 0 #0 t

addi $t1, $zero, 0
lw  $t2, -60($sp)
add $t3, $t1, $t2
sw  $t3, -56($sp)

#BNE x 1 if0

lw  $t0, -52($sp)
lw  $t1, 0($t0)
addi $t2, $zero, 1
bne $t1, $t2, if0

#ADD 0 1 sum

addi $t1, $zero, 0
addi $t2, $zero, 1
add $t3, $t1, $t2
sw  $t3, -44($sp)

#J   else0

j   else0

#LABEL   if0

if0:   

#PUSH   t

lw  $t1, -56($sp)
addi $t2, $sp, -56
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   sum

sw  $sp, -112($sp)
lw  $t0, 0($sp)
sw  $t0, -72($sp)
lw  $t0, -4($sp)
sw  $t0, -76($sp)
lw  $t0, -8($sp)
sw  $t0, -80($sp)
lw  $t0, -12($sp)
sw  $t0, -84($sp)
lw  $t0, -16($sp)
sw  $t0, -88($sp)
lw  $t0, -20($sp)
sw  $t0, -92($sp)
lw  $t0, -24($sp)
sw  $t0, -96($sp)
lw  $t0, -28($sp)
sw  $t0, -100($sp)
lw  $t0, -32($sp)
sw  $t0, -104($sp)
lw  $t0, -36($sp)
sw  $t0, -108($sp)
addi $sp, $sp, -72
jal   sum

#ADD sum 0 #1

addi $t1, $v0, 0
addi $t2, $zero, 0
add $t3, $t1, $t2
sw  $t3, -64($sp)

#ADD #1 x #2

lw  $t1, -64($sp)
lw  $t0, -52($sp)
lw  $t2, 0($t0)
add $t3, $t1, $t2
sw  $t3, -68($sp)

#ADD 0 #2 sum

addi $t1, $zero, 0
lw  $t2, -68($sp)
add $t3, $t1, $t2
sw  $t3, -44($sp)

#LABEL   else0

else0:   

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin5

begin5:   

#ADD 0 x t

addi $t1, $zero, 0
lw  $t2, -52($sp)
add $t3, $t1, $t2
sw  $t3, -56($sp)

#PUSH   t

lw  $t1, -56($sp)
addi $t2, $sp, -56
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   sum

sw  $sp, -104($sp)
lw  $t0, 0($sp)
sw  $t0, -64($sp)
lw  $t0, -4($sp)
sw  $t0, -68($sp)
lw  $t0, -8($sp)
sw  $t0, -72($sp)
lw  $t0, -12($sp)
sw  $t0, -76($sp)
lw  $t0, -16($sp)
sw  $t0, -80($sp)
lw  $t0, -20($sp)
sw  $t0, -84($sp)
lw  $t0, -24($sp)
sw  $t0, -88($sp)
lw  $t0, -28($sp)
sw  $t0, -92($sp)
lw  $t0, -32($sp)
sw  $t0, -96($sp)
lw  $t0, -36($sp)
sw  $t0, -100($sp)
sw  $sp, -80($sp)
addi $sp, $sp, -64
jal   sum

#ADD sum 0 #0

addi $t1, $v0, 0
addi $t2, $zero, 0
add $t3, $t1, $t2
sw  $t3, -60($sp)

#ADD 0 #0 out

addi $t1, $zero, 0
lw  $t2, -60($sp)
add $t3, $t1, $t2
lw  $t0, -4($sp)
sw  $t3, -56($t0)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin4

begin4:   

#PUSH   y

lw  $t1, -52($sp)
addi $t2, $sp, -52
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   pcd

sw  $sp, -96($sp)
lw  $t0, 0($sp)
sw  $t0, -56($sp)
lw  $t0, -4($sp)
sw  $t0, -60($sp)
lw  $t0, -8($sp)
sw  $t0, -64($sp)
lw  $t0, -12($sp)
sw  $t0, -68($sp)
lw  $t0, -16($sp)
sw  $t0, -72($sp)
lw  $t0, -20($sp)
sw  $t0, -76($sp)
lw  $t0, -24($sp)
sw  $t0, -80($sp)
lw  $t0, -28($sp)
sw  $t0, -84($sp)
lw  $t0, -32($sp)
sw  $t0, -88($sp)
lw  $t0, -36($sp)
sw  $t0, -92($sp)
sw  $sp, -68($sp)
addi $sp, $sp, -56
jal   pcd

#CALL   writeoo

sw  $sp, -96($sp)
lw  $t0, 0($sp)
sw  $t0, -56($sp)
lw  $t0, -4($sp)
sw  $t0, -60($sp)
lw  $t0, -8($sp)
sw  $t0, -64($sp)
lw  $t0, -12($sp)
sw  $t0, -68($sp)
lw  $t0, -16($sp)
sw  $t0, -72($sp)
lw  $t0, -20($sp)
sw  $t0, -76($sp)
lw  $t0, -24($sp)
sw  $t0, -80($sp)
lw  $t0, -28($sp)
sw  $t0, -84($sp)
lw  $t0, -32($sp)
sw  $t0, -88($sp)
lw  $t0, -36($sp)
sw  $t0, -92($sp)
addi $sp, $sp, -56
jal   writeoo

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin2

begin2:   

#PUSH   y

lw  $t1, -52($sp)
addi $t2, $sp, -52
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   foo

sw  $sp, -96($sp)
lw  $t0, 0($sp)
sw  $t0, -56($sp)
lw  $t0, -4($sp)
sw  $t0, -60($sp)
lw  $t0, -8($sp)
sw  $t0, -64($sp)
lw  $t0, -12($sp)
sw  $t0, -68($sp)
lw  $t0, -16($sp)
sw  $t0, -72($sp)
lw  $t0, -20($sp)
sw  $t0, -76($sp)
lw  $t0, -24($sp)
sw  $t0, -80($sp)
lw  $t0, -28($sp)
sw  $t0, -84($sp)
lw  $t0, -32($sp)
sw  $t0, -88($sp)
lw  $t0, -36($sp)
sw  $t0, -92($sp)
sw  $sp, -64($sp)
addi $sp, $sp, -56
jal   foo

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin1

begin1:   

#ADD 0 100 vn

addi $t1, $zero, 0
addi $t2, $zero, 100
add $t3, $t1, $t2
sw  $t3, -52($sp)

#PUSH   vn

lw  $t1, -52($sp)
addi $t2, $sp, -52
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   outter

sw  $sp, -144($sp)
lw  $t0, 0($sp)
sw  $t0, -104($sp)
lw  $t0, -4($sp)
sw  $t0, -108($sp)
lw  $t0, -8($sp)
sw  $t0, -112($sp)
lw  $t0, -12($sp)
sw  $t0, -116($sp)
lw  $t0, -16($sp)
sw  $t0, -120($sp)
lw  $t0, -20($sp)
sw  $t0, -124($sp)
lw  $t0, -24($sp)
sw  $t0, -128($sp)
lw  $t0, -28($sp)
sw  $t0, -132($sp)
lw  $t0, -32($sp)
sw  $t0, -136($sp)
lw  $t0, -36($sp)
sw  $t0, -140($sp)
sw  $sp, -108($sp)
addi $sp, $sp, -104
jal   outter

#WRITE   out

addi $v0, $zero, 1
lw  $a0, -56($sp)
syscall   

#PUSH   99

addi $t1, $zero, 99
sw  $t1, 0($s0)

#CALL   outter

sw  $sp, -144($sp)
lw  $t0, 0($sp)
sw  $t0, -104($sp)
lw  $t0, -4($sp)
sw  $t0, -108($sp)
lw  $t0, -8($sp)
sw  $t0, -112($sp)
lw  $t0, -12($sp)
sw  $t0, -116($sp)
lw  $t0, -16($sp)
sw  $t0, -120($sp)
lw  $t0, -20($sp)
sw  $t0, -124($sp)
lw  $t0, -24($sp)
sw  $t0, -128($sp)
lw  $t0, -28($sp)
sw  $t0, -132($sp)
lw  $t0, -32($sp)
sw  $t0, -136($sp)
lw  $t0, -36($sp)
sw  $t0, -140($sp)
sw  $sp, -108($sp)
addi $sp, $sp, -104
jal   outter

#WRITE   out

addi $v0, $zero, 1
lw  $a0, -56($sp)
syscall   

#PUSH   98

addi $t1, $zero, 98
sw  $t1, 0($s0)

#CALL   outter

sw  $sp, -144($sp)
lw  $t0, 0($sp)
sw  $t0, -104($sp)
lw  $t0, -4($sp)
sw  $t0, -108($sp)
lw  $t0, -8($sp)
sw  $t0, -112($sp)
lw  $t0, -12($sp)
sw  $t0, -116($sp)
lw  $t0, -16($sp)
sw  $t0, -120($sp)
lw  $t0, -20($sp)
sw  $t0, -124($sp)
lw  $t0, -24($sp)
sw  $t0, -128($sp)
lw  $t0, -28($sp)
sw  $t0, -132($sp)
lw  $t0, -32($sp)
sw  $t0, -136($sp)
lw  $t0, -36($sp)
sw  $t0, -140($sp)
sw  $sp, -108($sp)
addi $sp, $sp, -104
jal   outter

#WRITE   out

addi $v0, $zero, 1
lw  $a0, -56($sp)
syscall   

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin0

begin0:   

#CALL   heh

sw  $sp, -92($sp)
lw  $t0, 0($sp)
sw  $t0, -52($sp)
lw  $t0, -4($sp)
sw  $t0, -56($sp)
lw  $t0, -8($sp)
sw  $t0, -60($sp)
lw  $t0, -12($sp)
sw  $t0, -64($sp)
lw  $t0, -16($sp)
sw  $t0, -68($sp)
lw  $t0, -20($sp)
sw  $t0, -72($sp)
lw  $t0, -24($sp)
sw  $t0, -76($sp)
lw  $t0, -28($sp)
sw  $t0, -80($sp)
lw  $t0, -32($sp)
sw  $t0, -84($sp)
lw  $t0, -36($sp)
sw  $t0, -88($sp)
sw  $sp, -52($sp)
addi $sp, $sp, -52
jal   heh
