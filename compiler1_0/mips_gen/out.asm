addi $s0, $sp, 0
addi $sp, $sp, -80
sw  $sp, 0($sp)

#VAR n i i


#VAR n i k


#VAR a 10 a


#VAR n c c


#VAR a 3 d


#VART   1


#J   begin0

j   begin0

#DEC p  p1

p1:   
sw  $ra, -48($sp)

#VAR n i j


#VART   0


#J   begin1

j   begin1

#DEC f  f1

f1:   
sw  $ra, -48($sp)

#PAR n i i

lw  $t1, 0($s0)
sw  $t1, -52($sp)

#VART   0


#J   begin2

j   begin2

#LABEL   begin2

begin2:   

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin1

begin1:   

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#DEC p  p2

p2:   
sw  $ra, -48($sp)

#PAR n i z

lw  $t1, 0($s0)
sw  $t1, -52($sp)

#PAR n c m

lw  $t1, -8($s0)
sw  $t1, -56($sp)

#VART   0


#J   begin3

j   begin3

#DEC p  f1

f1:   
sw  $ra, -48($sp)

#VART   0


#J   begin4

j   begin4

#LABEL   begin4

begin4:   

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin3

begin3:   

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#DEC f  f1

f1:   
sw  $ra, -48($sp)

#PAR n i a

lw  $t1, 0($s0)
sw  $t1, -52($sp)

#PAR n i b

lw  $t1, -8($s0)
sw  $t1, -56($sp)

#VART   0


#J   begin5

j   begin5

#DEC f  p2

p2:   
sw  $ra, -48($sp)

#VART   0


#J   begin6

j   begin6

#LABEL   begin6

begin6:   

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin5

begin5:   

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin0

begin0:   

#ADD i 1 #0

lw  $t1, -52($sp)
addi $t2, $zero, 1
add $t3, $t1, $t2
sw  $t3, -116($sp)

#ADD 0 #0 i

addi $t1, $zero, 0
lw  $t2, -116($sp)
add $t3, $t1, $t2
sw  $t3, -52($sp)
