addi $s0, $sp, 0
addi $sp, $sp, -80
sw  $sp, 0($sp)

#VAR n i p


#VART   0


#J   begin0

j   begin0

#DEC p  test1

test1:   
sw  $ra, -48($sp)

#PAR n i p

lw  $t1, 0($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin1

j   begin1

#DEC p  test2

test2:   
sw  $ra, -48($sp)

#PAR v i p

lw  $t1, -4($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin2

j   begin2

#DEC p  test3

test3:   
sw  $ra, -48($sp)

#PAR v i p

lw  $t1, -4($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin3

j   begin3

#DEC p  test4

test4:   
sw  $ra, -48($sp)

#PAR v i p

lw  $t1, -4($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin4

j   begin4

#DEC p  test5

test5:   
sw  $ra, -48($sp)

#PAR v i p

lw  $t1, -4($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin5

j   begin5

#DEC p  test6

test6:   
sw  $ra, -48($sp)

#PAR v i p

lw  $t1, -4($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin6

j   begin6

#DEC p  test7

test7:   
sw  $ra, -48($sp)

#PAR v i p

lw  $t1, -4($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin7

j   begin7

#DEC p  test8

test8:   
sw  $ra, -48($sp)

#PAR v i p

lw  $t1, -4($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin8

j   begin8

#DEC p  test9

test9:   
sw  $ra, -48($sp)

#PAR v i p

lw  $t1, -4($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin9

j   begin9

#LABEL   begin9

begin9:   

#WRITE   p

addi $v0, $zero, 1
lw  $t0, -52($sp)
lw  $a0, 0($t0)
syscall   

#ADD 0 9 p

addi $t1, $zero, 0
addi $t2, $zero, 9
add $t3, $t1, $t2
lw  $t0, -52($sp)
sw  $t3, 0($t0)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin8

begin8:   

#PUSH   p

lw  $t2, -52($sp)
lw  $t1, 0($t2)
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   test9

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
sw  $sp, -88($sp)
addi $sp, $sp, -56
jal   test9

#WRITE   p

addi $v0, $zero, 1
lw  $t0, -52($sp)
lw  $a0, 0($t0)
syscall   

#ADD 0 8 p

addi $t1, $zero, 0
addi $t2, $zero, 8
add $t3, $t1, $t2
lw  $t0, -52($sp)
sw  $t3, 0($t0)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin7

begin7:   

#PUSH   p

lw  $t2, -52($sp)
lw  $t1, 0($t2)
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   test8

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
sw  $sp, -84($sp)
addi $sp, $sp, -56
jal   test8

#WRITE   p

addi $v0, $zero, 1
lw  $t0, -52($sp)
lw  $a0, 0($t0)
syscall   

#ADD 0 7 p

addi $t1, $zero, 0
addi $t2, $zero, 7
add $t3, $t1, $t2
lw  $t0, -52($sp)
sw  $t3, 0($t0)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin6

begin6:   

#PUSH   p

lw  $t2, -52($sp)
lw  $t1, 0($t2)
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   test7

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
sw  $sp, -80($sp)
addi $sp, $sp, -56
jal   test7

#WRITE   p

addi $v0, $zero, 1
lw  $t0, -52($sp)
lw  $a0, 0($t0)
syscall   

#ADD 0 6 p

addi $t1, $zero, 0
addi $t2, $zero, 6
add $t3, $t1, $t2
lw  $t0, -52($sp)
sw  $t3, 0($t0)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin5

begin5:   

#PUSH   p

lw  $t2, -52($sp)
lw  $t1, 0($t2)
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   test6

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
sw  $sp, -76($sp)
addi $sp, $sp, -56
jal   test6

#WRITE   p

addi $v0, $zero, 1
lw  $t0, -52($sp)
lw  $a0, 0($t0)
syscall   

#ADD 0 5 p

addi $t1, $zero, 0
addi $t2, $zero, 5
add $t3, $t1, $t2
lw  $t0, -52($sp)
sw  $t3, 0($t0)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin4

begin4:   

#PUSH   p

lw  $t2, -52($sp)
lw  $t1, 0($t2)
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   test5

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
sw  $sp, -72($sp)
addi $sp, $sp, -56
jal   test5

#WRITE   p

addi $v0, $zero, 1
lw  $t0, -52($sp)
lw  $a0, 0($t0)
syscall   

#ADD 0 4 p

addi $t1, $zero, 0
addi $t2, $zero, 4
add $t3, $t1, $t2
lw  $t0, -52($sp)
sw  $t3, 0($t0)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin3

begin3:   

#PUSH   p

lw  $t2, -52($sp)
lw  $t1, 0($t2)
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   test4

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
jal   test4

#WRITE   p

addi $v0, $zero, 1
lw  $t0, -52($sp)
lw  $a0, 0($t0)
syscall   

#ADD 0 3 p

addi $t1, $zero, 0
addi $t2, $zero, 3
add $t3, $t1, $t2
lw  $t0, -52($sp)
sw  $t3, 0($t0)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin2

begin2:   

#PUSH   p

lw  $t2, -52($sp)
lw  $t1, 0($t2)
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   test3

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
jal   test3

#WRITE   p

addi $v0, $zero, 1
lw  $t0, -52($sp)
lw  $a0, 0($t0)
syscall   

#ADD 0 2 p

addi $t1, $zero, 0
addi $t2, $zero, 2
add $t3, $t1, $t2
lw  $t0, -52($sp)
sw  $t3, 0($t0)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin1

begin1:   

#PUSH   p

lw  $t1, -52($sp)
addi $t2, $sp, -52
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   test2

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
sw  $sp, -60($sp)
addi $sp, $sp, -56
jal   test2

#WRITE   p

addi $v0, $zero, 1
lw  $a0, -52($sp)
syscall   

#ADD 0 1 p

addi $t1, $zero, 0
addi $t2, $zero, 1
add $t3, $t1, $t2
sw  $t3, -52($sp)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin0

begin0:   

#ADD 0 10 p

addi $t1, $zero, 0
addi $t2, $zero, 10
add $t3, $t1, $t2
sw  $t3, -52($sp)

#PUSH   p

lw  $t1, -52($sp)
addi $t2, $sp, -52
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#CALL   test1

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
sw  $sp, -56($sp)
addi $sp, $sp, -56
jal   test1

#WRITE   p

addi $v0, $zero, 1
lw  $a0, -52($sp)
syscall   
