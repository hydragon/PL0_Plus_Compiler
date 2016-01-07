addi $s0, $sp, 0
addi $sp, $sp, -80
sw  $sp, 0($sp)

#CON 19  listlength

addi $t0, $zero, 19
sw  $t0, -52($sp)

#VAR n i x


#VAR n i y


#VAR n i p


#VAR n i searchr


#VAR n c c1


#VAR n c c2


#VAR a 20 list


#VART   5


#J   begin0

j   begin0

#DEC p  sort

sort:   
sw  $ra, -48($sp)

#VAR n i i


#VAR n i j


#VAR n i tmp


#VART   8


#J   begin1

j   begin1

#LABEL   begin1

begin1:   

#ADD 0 0 i

addi $t1, $zero, 0
addi $t2, $zero, 0
add $t3, $t1, $t2
sw  $t3, -52($sp)

#LABEL   for0

for0:   

#SUB listlength 1 #0

lw  $t0, 0($sp)
lw  $t1, -52($t0)
addi $t2, $zero, 1
sub $t3, $t1, $t2
sw  $t3, -64($sp)

#BGTZ i #0 forend0

lw  $t1, -52($sp)
lw  $t2, -64($sp)
sub $t3, $t1, $t2
bgtz $t3,  forend0

#ADD i 1 #1

lw  $t1, -52($sp)
addi $t2, $zero, 1
add $t3, $t1, $t2
sw  $t3, -68($sp)

#ADD 0 #1 j

addi $t1, $zero, 0
lw  $t2, -68($sp)
add $t3, $t1, $t2
sw  $t3, -56($sp)

#LABEL   for1

for1:   

#BGTZ j listlength forend1

lw  $t1, -56($sp)
lw  $t0, 0($sp)
lw  $t2, -52($t0)
sub $t3, $t1, $t2
bgtz $t3,  forend1

#ARRAY list i %2

lw  $t0, 0($sp)
addi $t1 $t0, -80
lw  $t2, -52($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -72($sp)

#ARRAY list j %3

lw  $t0, 0($sp)
addi $t1 $t0, -80
lw  $t2, -56($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -76($sp)

#BLEZ %2 %3 if0

lw  $t0, -72($sp)
lw  $t1, 0($t0)
lw  $t0, -76($sp)
lw  $t2, 0($t0)
sub $t3, $t1, $t2
blez $t3,  if0

#ARRAY list i %4

lw  $t0, 0($sp)
addi $t1 $t0, -80
lw  $t2, -52($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -80($sp)

#ADD 0 %4 tmp

addi $t1, $zero, 0
lw  $t0, -80($sp)
lw  $t2, 0($t0)
add $t3, $t1, $t2
sw  $t3, -60($sp)

#ARRAY list i %5

lw  $t0, 0($sp)
addi $t1 $t0, -80
lw  $t2, -52($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -84($sp)

#ARRAY list j %6

lw  $t0, 0($sp)
addi $t1 $t0, -80
lw  $t2, -56($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -88($sp)

#ADD 0 %6 %5

addi $t1, $zero, 0
lw  $t0, -88($sp)
lw  $t2, 0($t0)
add $t3, $t1, $t2
lw  $t0, -84($sp)
sw  $t3, 0($t0)

#ARRAY list j %7

lw  $t0, 0($sp)
addi $t1 $t0, -80
lw  $t2, -56($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -92($sp)

#ADD 0 tmp %7

addi $t1, $zero, 0
lw  $t2, -60($sp)
add $t3, $t1, $t2
lw  $t0, -92($sp)
sw  $t3, 0($t0)

#LABEL   if0

if0:   

#ADD j 1 j

lw  $t1, -56($sp)
addi $t2, $zero, 1
add $t3, $t1, $t2
sw  $t3, -56($sp)

#J   for1

j   for1

#LABEL   forend1

forend1:   

#ADD i 1 i

lw  $t1, -52($sp)
addi $t2, $zero, 1
add $t3, $t1, $t2
sw  $t3, -52($sp)

#J   for0

j   for0

#LABEL   forend0

forend0:   

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#DEC f  halfsearch

halfsearch:   
sw  $ra, -48($sp)

#PAR n i i

lw  $t1, 0($s0)
sw  $t1, -52($sp)

#PAR n i j

lw  $t1, -8($s0)
sw  $t1, -56($sp)

#PAR n i no

lw  $t1, -16($s0)
sw  $t1, -60($sp)

#PAR v i place

lw  $t1, -28($s0)
sw  $t1, -64($sp)

#VAR n i half


#VART   11


#J   begin2

j   begin2

#LABEL   begin2

begin2:   

#BLTZ i j if1

lw  $t1, -52($sp)
lw  $t2, -56($sp)
sub $t3, $t1, $t2
bltz $t3,  if1

#ARRAY list i %0

lw  $t0, 0($sp)
addi $t1 $t0, -80
lw  $t2, -52($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -72($sp)

#BNE %0 no if2

lw  $t0, -72($sp)
lw  $t1, 0($t0)
lw  $t2, -60($sp)
bne $t1, $t2, if2

#ADD 0 i place

addi $t1, $zero, 0
lw  $t2, -52($sp)
add $t3, $t1, $t2
lw  $t0, -64($sp)
sw  $t3, 0($t0)

#ADD 0 place halfsearch

addi $t1, $zero, 0
lw  $t0, -64($sp)
lw  $t2, 0($t0)
add $t3, $t1, $t2
sw  $t3, -44($sp)

#J   else0

j   else0

#LABEL   if2

if2:   

#SUB 0 1 #1

addi $t1, $zero, 0
addi $t2, $zero, 1
sub $t3, $t1, $t2
sw  $t3, -76($sp)

#ADD 0 #1 place

addi $t1, $zero, 0
lw  $t2, -76($sp)
add $t3, $t1, $t2
lw  $t0, -64($sp)
sw  $t3, 0($t0)

#SUB 0 1 #2

addi $t1, $zero, 0
addi $t2, $zero, 1
sub $t3, $t1, $t2
sw  $t3, -80($sp)

#ADD 0 #2 halfsearch

addi $t1, $zero, 0
lw  $t2, -80($sp)
add $t3, $t1, $t2
sw  $t3, -44($sp)

#LABEL   else0

else0:   

#J   else1

j   else1

#LABEL   if1

if1:   

#ADD i j #3

lw  $t1, -52($sp)
lw  $t2, -56($sp)
add $t3, $t1, $t2
sw  $t3, -84($sp)

#DIV #3 2 #4

lw  $t1, -84($sp)
addi $t2, $zero, 2
div $t1, $t2 
mflo   $t3
sw  $t3, -88($sp)

#ADD 0 #4 half

addi $t1, $zero, 0
lw  $t2, -88($sp)
add $t3, $t1, $t2
sw  $t3, -68($sp)

#ARRAY list half %5

lw  $t0, 0($sp)
addi $t1 $t0, -80
lw  $t2, -68($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -92($sp)

#BNE %5 no if3

lw  $t0, -92($sp)
lw  $t1, 0($t0)
lw  $t2, -60($sp)
bne $t1, $t2, if3

#ADD 0 half place

addi $t1, $zero, 0
lw  $t2, -68($sp)
add $t3, $t1, $t2
lw  $t0, -64($sp)
sw  $t3, 0($t0)

#ADD 0 place halfsearch

addi $t1, $zero, 0
lw  $t0, -64($sp)
lw  $t2, 0($t0)
add $t3, $t1, $t2
sw  $t3, -44($sp)

#J   else2

j   else2

#LABEL   if3

if3:   

#ARRAY list half %6

lw  $t0, 0($sp)
addi $t1 $t0, -80
lw  $t2, -68($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -96($sp)

#BLEZ %6 no if4

lw  $t0, -96($sp)
lw  $t1, 0($t0)
lw  $t2, -60($sp)
sub $t3, $t1, $t2
blez $t3,  if4

#SUB half 1 #7

lw  $t1, -68($sp)
addi $t2, $zero, 1
sub $t3, $t1, $t2
sw  $t3, -100($sp)

#ADD 0 #7 j

addi $t1, $zero, 0
lw  $t2, -100($sp)
add $t3, $t1, $t2
sw  $t3, -56($sp)

#PUSH   i

lw  $t1, -52($sp)
addi $t2, $sp, -52
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#PUSH   j

lw  $t1, -56($sp)
addi $t2, $sp, -56
sw  $t1, -8($s0)
sw  $t2, -12($s0)

#PUSH   no

lw  $t1, -60($sp)
addi $t2, $sp, -60
sw  $t1, -16($s0)
sw  $t2, -20($s0)

#PUSH   place

lw  $t2, -64($sp)
lw  $t1, 0($t2)
sw  $t1, -24($s0)
sw  $t2, -28($s0)

#CALL   halfsearch

sw  $sp, -156($sp)
lw  $t0, 0($sp)
sw  $t0, -116($sp)
lw  $t0, -4($sp)
sw  $t0, -120($sp)
lw  $t0, -8($sp)
sw  $t0, -124($sp)
lw  $t0, -12($sp)
sw  $t0, -128($sp)
lw  $t0, -16($sp)
sw  $t0, -132($sp)
lw  $t0, -20($sp)
sw  $t0, -136($sp)
lw  $t0, -24($sp)
sw  $t0, -140($sp)
lw  $t0, -28($sp)
sw  $t0, -144($sp)
lw  $t0, -32($sp)
sw  $t0, -148($sp)
lw  $t0, -36($sp)
sw  $t0, -152($sp)
addi $sp, $sp, -116
jal   halfsearch

#ADD halfsearch 0 #8

addi $t1, $v0, 0
addi $t2, $zero, 0
add $t3, $t1, $t2
sw  $t3, -104($sp)

#ADD 0 #8 searchr

addi $t1, $zero, 0
lw  $t2, -104($sp)
add $t3, $t1, $t2
lw  $t0, 0($sp)
sw  $t3, -68($t0)

#J   else3

j   else3

#LABEL   if4

if4:   

#ADD half 1 #9

lw  $t1, -68($sp)
addi $t2, $zero, 1
add $t3, $t1, $t2
sw  $t3, -108($sp)

#PUSH   #9

lw  $t1, -108($sp)
addi $t2, $sp, -108
sw  $t1, 0($s0)
sw  $t2, -4($s0)

#PUSH   j

lw  $t1, -56($sp)
addi $t2, $sp, -56
sw  $t1, -8($s0)
sw  $t2, -12($s0)

#PUSH   no

lw  $t1, -60($sp)
addi $t2, $sp, -60
sw  $t1, -16($s0)
sw  $t2, -20($s0)

#PUSH   place

lw  $t2, -64($sp)
lw  $t1, 0($t2)
sw  $t1, -24($s0)
sw  $t2, -28($s0)

#CALL   halfsearch

sw  $sp, -156($sp)
lw  $t0, 0($sp)
sw  $t0, -116($sp)
lw  $t0, -4($sp)
sw  $t0, -120($sp)
lw  $t0, -8($sp)
sw  $t0, -124($sp)
lw  $t0, -12($sp)
sw  $t0, -128($sp)
lw  $t0, -16($sp)
sw  $t0, -132($sp)
lw  $t0, -20($sp)
sw  $t0, -136($sp)
lw  $t0, -24($sp)
sw  $t0, -140($sp)
lw  $t0, -28($sp)
sw  $t0, -144($sp)
lw  $t0, -32($sp)
sw  $t0, -148($sp)
lw  $t0, -36($sp)
sw  $t0, -152($sp)
addi $sp, $sp, -116
jal   halfsearch

#ADD halfsearch 0 #10

addi $t1, $v0, 0
addi $t2, $zero, 0
add $t3, $t1, $t2
sw  $t3, -112($sp)

#ADD 0 #10 searchr

addi $t1, $zero, 0
lw  $t2, -112($sp)
add $t3, $t1, $t2
lw  $t0, 0($sp)
sw  $t3, -68($t0)

#LABEL   else3

else3:   

#LABEL   else2

else2:   

#LABEL   else1

else1:   

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#DEC p  testcase

testcase:   
sw  $ra, -48($sp)

#VAR n c rc


#VAR n i ri


#VART   1


#J   begin3

j   begin3

#LABEL   begin3

begin3:   

#READ   rc

addi $v0, $zero, 12
syscall   
sw  $v0, -52($sp)

#ADD 0 10 ri

addi $t1, $zero, 0
addi $t2, $zero, 10
add $t3, $t1, $t2
sw  $t3, -56($sp)

#BNE rc 49 case0

lw  $t1, -52($sp)
addi $t2, $zero, 49
bne $t1, $t2, case0

#WRITE   rc

addi $v0, $zero, 11
lw  $a0, -52($sp)
syscall   

#ADD 0 1 ri

addi $t1, $zero, 0
addi $t2, $zero, 1
add $t3, $t1, $t2
sw  $t3, -56($sp)

#J   caseend0

j   caseend0

#LABEL   case0

case0:   

#BNE rc 50 case1

lw  $t1, -52($sp)
addi $t2, $zero, 50
bne $t1, $t2, case1

#WRITE   "Itis2"

addi $v0, $zero, 11
addi $a0, $zero, 73
syscall   
addi $a0, $zero, 116
syscall   
addi $a0, $zero, 105
syscall   
addi $a0, $zero, 115
syscall   
addi $a0, $zero, 50
syscall   

#ADD 0 2 ri

addi $t1, $zero, 0
addi $t2, $zero, 2
add $t3, $t1, $t2
sw  $t3, -56($sp)

#J   caseend0

j   caseend0

#LABEL   case1

case1:   

#BNE rc 51 case2

lw  $t1, -52($sp)
addi $t2, $zero, 51
bne $t1, $t2, case2

#WRITE   "It is 3"

addi $v0, $zero, 11
addi $a0, $zero, 73
syscall   
addi $a0, $zero, 116
syscall   
addi $a0, $zero, 32
syscall   
addi $a0, $zero, 105
syscall   
addi $a0, $zero, 115
syscall   
addi $a0, $zero, 32
syscall   
addi $a0, $zero, 51
syscall   

#ADD 0 3 ri

addi $t1, $zero, 0
addi $t2, $zero, 3
add $t3, $t1, $t2
sw  $t3, -56($sp)

#J   caseend0

j   caseend0

#LABEL   case2

case2:   

#LABEL   caseend0

caseend0:   

#MUL ri 2 #0

lw  $t1, -56($sp)
addi $t2, $zero, 2
mul $t3, $t1, $t2
sw  $t3, -60($sp)

#ADD 0 #0 y

addi $t1, $zero, 0
lw  $t2, -60($sp)
add $t3, $t1, $t2
lw  $t0, 0($sp)
sw  $t3, -60($t0)

#JR   

lw  $v0, -44($sp)
lw  $ra, -48($sp)
lw  $sp, -40($sp)
jr   $ra

#LABEL   begin0

begin0:   

#ADD 0 0 y

addi $t1, $zero, 0
addi $t2, $zero, 0
add $t3, $t1, $t2
sw  $t3, -60($sp)

#CALL   testcase

sw  $sp, -220($sp)
lw  $t0, 0($sp)
sw  $t0, -180($sp)
lw  $t0, -4($sp)
sw  $t0, -184($sp)
lw  $t0, -8($sp)
sw  $t0, -188($sp)
lw  $t0, -12($sp)
sw  $t0, -192($sp)
lw  $t0, -16($sp)
sw  $t0, -196($sp)
lw  $t0, -20($sp)
sw  $t0, -200($sp)
lw  $t0, -24($sp)
sw  $t0, -204($sp)
lw  $t0, -28($sp)
sw  $t0, -208($sp)
lw  $t0, -32($sp)
sw  $t0, -212($sp)
lw  $t0, -36($sp)
sw  $t0, -216($sp)
sw  $sp, -180($sp)
addi $sp, $sp, -180
jal   testcase

#ADD 0 19 x

addi $t1, $zero, 0
addi $t2, $zero, 19
add $t3, $t1, $t2
sw  $t3, -56($sp)

#LABEL   for2

for2:   

#BLTZ x 0 forend2

lw  $t1, -56($sp)
addi $t2, $zero, 0
sub $t3, $t1, $t2
bltz $t3,  forend2

#ARRAY list x %0

addi $t1, $sp, -80
lw  $t2, -56($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -160($sp)

#MUL x 2 #1

lw  $t1, -56($sp)
addi $t2, $zero, 2
mul $t3, $t1, $t2
sw  $t3, -164($sp)

#ADD 0 #1 %0

addi $t1, $zero, 0
lw  $t2, -164($sp)
add $t3, $t1, $t2
lw  $t0, -160($sp)
sw  $t3, 0($t0)

#SUB x 1 x

lw  $t1, -56($sp)
addi $t2, $zero, 1
sub $t3, $t1, $t2
sw  $t3, -56($sp)

#J   for2

j   for2

#LABEL   forend2

forend2:   

#CALL   sort

sw  $sp, -220($sp)
lw  $t0, 0($sp)
sw  $t0, -180($sp)
lw  $t0, -4($sp)
sw  $t0, -184($sp)
lw  $t0, -8($sp)
sw  $t0, -188($sp)
lw  $t0, -12($sp)
sw  $t0, -192($sp)
lw  $t0, -16($sp)
sw  $t0, -196($sp)
lw  $t0, -20($sp)
sw  $t0, -200($sp)
lw  $t0, -24($sp)
sw  $t0, -204($sp)
lw  $t0, -28($sp)
sw  $t0, -208($sp)
lw  $t0, -32($sp)
sw  $t0, -212($sp)
lw  $t0, -36($sp)
sw  $t0, -216($sp)
sw  $sp, -180($sp)
addi $sp, $sp, -180
jal   sort

#PUSH   1

addi $t1, $zero, 1
sw  $t1, 0($s0)

#PUSH   20

addi $t1, $zero, 20
sw  $t1, -8($s0)

#PUSH   y

lw  $t1, -60($sp)
addi $t2, $sp, -60
sw  $t1, -16($s0)
sw  $t2, -20($s0)

#PUSH   p

lw  $t1, -64($sp)
addi $t2, $sp, -64
sw  $t1, -24($s0)
sw  $t2, -28($s0)

#CALL   halfsearch

sw  $sp, -220($sp)
lw  $t0, 0($sp)
sw  $t0, -180($sp)
lw  $t0, -4($sp)
sw  $t0, -184($sp)
lw  $t0, -8($sp)
sw  $t0, -188($sp)
lw  $t0, -12($sp)
sw  $t0, -192($sp)
lw  $t0, -16($sp)
sw  $t0, -196($sp)
lw  $t0, -20($sp)
sw  $t0, -200($sp)
lw  $t0, -24($sp)
sw  $t0, -204($sp)
lw  $t0, -28($sp)
sw  $t0, -208($sp)
lw  $t0, -32($sp)
sw  $t0, -212($sp)
lw  $t0, -36($sp)
sw  $t0, -216($sp)
sw  $sp, -180($sp)
addi $sp, $sp, -180
jal   halfsearch

#ADD halfsearch 0 #2

addi $t1, $v0, 0
addi $t2, $zero, 0
add $t3, $t1, $t2
sw  $t3, -168($sp)

#ADD 0 #2 searchr

addi $t1, $zero, 0
lw  $t2, -168($sp)
add $t3, $t1, $t2
sw  $t3, -68($sp)

#ADD 0 0 x

addi $t1, $zero, 0
addi $t2, $zero, 0
add $t3, $t1, $t2
sw  $t3, -56($sp)

#LABEL   for3

for3:   

#BGTZ x 19 forend3

lw  $t1, -56($sp)
addi $t2, $zero, 19
sub $t3, $t1, $t2
bgtz $t3,  forend3

#WRITE   " "

addi $v0, $zero, 11
addi $a0, $zero, 32
syscall   

#ARRAY list x %3

addi $t1, $sp, -80
lw  $t2, -56($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -172($sp)

#WRITE   %3

addi $v0, $zero, 1
lw  $t0, -172($sp)
lw  $a0, 0($t0)
syscall   

#ADD x 1 x

lw  $t1, -56($sp)
addi $t2, $zero, 1
add $t3, $t1, $t2
sw  $t3, -56($sp)

#J   for3

j   for3

#LABEL   forend3

forend3:   

#WRITE   " "

addi $v0, $zero, 11
addi $a0, $zero, 32
syscall   

#BLTZ p 0 if5

lw  $t1, -64($sp)
addi $t2, $zero, 0
sub $t3, $t1, $t2
bltz $t3,  if5

#WRITE   " "

addi $v0, $zero, 11
addi $a0, $zero, 32
syscall   

#ARRAY list p %4

addi $t1, $sp, -80
lw  $t2, -64($sp)
mul $t2, $t2, 4
sub $t0, $t1, $t2
sw  $t0, -176($sp)

#WRITE   %4

addi $v0, $zero, 1
lw  $t0, -176($sp)
lw  $a0, 0($t0)
syscall   

#LABEL   if5

if5:   

#WRITE   " "

addi $v0, $zero, 11
addi $a0, $zero, 32
syscall   

#WRITE   y

addi $v0, $zero, 1
lw  $a0, -60($sp)
syscall   

#ADD 0 0 x

addi $t1, $zero, 0
addi $t2, $zero, 0
add $t3, $t1, $t2
sw  $t3, -56($sp)
