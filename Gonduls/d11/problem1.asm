## Counted all starting objects, 36 in total

.data

.eqv N_MONKEYS 8
.eqv N_ROUNDS 20

m0: .word -1:36
m1: .word -1:36
m2: .word -1:36
m3: .word -1:36
m4: .word -1:36
m5: .word -1:36
m6: .word -1:36
m7: .word -1:36

operations: .byte '*', '+', '*', '^', '+', '+', '+', '+'
true: .word 6, 7, 5, 0, 6, 7, 2, 3
false: .word 4, 5, 1, 4, 2, 3, 1, 0
last_el: .word 5, 7, 3, 4, 1, 2, 6, 8
monkeys: .space 32
inspections: .word 0:8

end_line: .asciiz "\n"

.text

##### LOAD MONKEYS #####
    # load monkeys with address of array of worry levels, load worry levels
    # this could have been a function reading from file, but this way is faster to code
    la $s0, monkeys

    # monkey 0
    la $s1, m0
    sw $s1, ($s0)
    li $s2, 65
    sw $s2, ($s1)
    li $s2, 58
    sw $s2, 4($s1)
    li $s2, 93
    sw $s2, 8($s1)
    li $s2, 57
    sw $s2, 12($s1)
    li $s2, 66
    sw $s2, 16($s1)

    # monkey 1
    la $s1, m1
    sw $s1, 4($s0)
    li $s2, 76
    sw $s2, ($s1)
    li $s2, 97
    sw $s2, 4($s1)
    li $s2, 58
    sw $s2, 8($s1)
    li $s2, 72
    sw $s2, 12($s1)
    li $s2, 57
    sw $s2, 16($s1)
    li $s2, 92
    sw $s2, 20($s1)
    li $s2, 82
    sw $s2, 24($s1)

    # monkey 2
    la $s1, m2
    sw $s1, 8($s0)
    li $s2, 90
    sw $s2, ($s1)
    li $s2, 89
    sw $s2, 4($s1)
    li $s2, 96
    sw $s2, 8($s1)

    # monkey 3
    la $s1, m3
    sw $s1, 12($s0)
    li $s2, 72
    sw $s2, ($s1)
    li $s2, 63
    sw $s2, 4($s1)
    li $s2, 72
    sw $s2, 8($s1)
    li $s2, 99
    sw $s2, 12($s1)

    # monkey 4
    la $s1, m4
    sw $s1, 16($s0)
    li $s2, 65
    sw $s2, ($s1)

    # monkey 5
    la $s1, m5
    sw $s1, 20($s0)
    li $s2, 97
    sw $s2, ($s1)
    li $s2, 71
    sw $s2, 4($s1)

    # monkey 6
    la $s1, m6
    sw $s1, 24($s0)
    li $s2, 83
    sw $s2, ($s1)
    li $s2, 68
    sw $s2, 4($s1)
    li $s2, 88
    sw $s2, 8($s1)
    li $s2, 55
    sw $s2, 12($s1)
    li $s2, 87
    sw $s2, 16($s1)
    li $s2, 67
    sw $s2, 20($s1)

    # monkey 7
    la $s1, m7
    sw $s1, 28($s0)
    li $s2, 64
    sw $s2, ($s1)
    li $s2, 81
    sw $s2, 4($s1)
    li $s2, 50
    sw $s2, 8($s1)
    li $s2, 96
    sw $s2, 12($s1)
    li $s2, 82
    sw $s2, 16($s1)
    li $s2, 53
    sw $s2, 20($s1)
    li $s2, 62
    sw $s2, 24($s1)
    li $s2, 92
    sw $s2, 28($s1)


##### MAIN #####

    # read last element from each array and print it in terminal in a loop
    la $s0, monkeys
    la $s1, last_el

    li $t0, 0
FOR: 
        beq $t0, N_MONKEYS, END_FOR
        
        # t1 = 4 * t0
        sll $t1, $t0, 2

        ### get last_el[t0]

        # t2 = s1 + t1 = address of index of last element of array
        add $t2, $s1, $t1
        # t2 = *t2 = index of last element of array + 1
        lw $t2, 0($t2)
        # t2 = t2 - 1 = index of last element of array
        addi $t2, $t2, -1
        sll $t2, $t2, 2

        ### get monkeys[t0][last_el[t0]]
        add $t3, $s0, $t1
        lw $t3, 0($t3)
        add $t3, $t3, $t2
        lw $t3, 0($t3)

        ### print monkeys[t0][last_el[t0]] in terminal ###

        li $v0, 1
        move $a0, $t3
        syscall

        li $v0, 4
        la $a0, end_line
        syscall

        addi $t0, $t0, 1
        j FOR

END_FOR:

    li $v0, 10      		# End program
	syscall