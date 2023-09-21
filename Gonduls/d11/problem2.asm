## Counted all starting objects, 36 in total

.data

.eqv N_MONKEYS 8
.eqv N_ROUNDS 10000

# we can use the remainder of the division of the product of all 'divisible_by' numbers to keep worry levels low
division: .word 9699690

m0: .word -1:36
m1: .word -1:36
m2: .word -1:36
m3: .word -1:36
m4: .word -1:36
m5: .word -1:36
m6: .word -1:36
m7: .word -1:36


operations: .byte '*', '+', '*', '^', '+', '+', '+', '+'
arguments: .word 7, 4, 5, -1, 1, 8, 2, 5
op_t: .byte '*'
op_p: .byte '+'
op_e: .byte '^'
true: .word 6, 7, 5, 0, 6, 7, 2, 3
false: .word 4, 5, 1, 4, 2, 3, 1, 0
last_el: .word 5, 7, 3, 4, 1, 2, 6, 8
divisible_by: .word 19, 3, 13, 17, 2, 11, 5, 7
monkeys: .space 32
inspections: .word 0:8

end_line: .asciiz "\n"
final_string: .asciiz "Result part 2: "
times_st: .asciiz " times "

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

    li $t9, N_ROUNDS
    ROUND_LOOP:

        beq $t9, $zero, END_ROUND
        subi $t9, $t9, 1

        # for each monkey
        move $t8, $zero

        # t8 = monkey index
        # t7 = t8 * 4
        # s0 = monkeys
        # s1 = specific monkey address
        # s6 = operation 
        # s5 = operation argument
        MONKEY_LOOP:
            subi $t0, $t8, N_MONKEYS
            beq $t0, $zero, END_MONKEY_LOOP

            # get monkey address
            sll $t7, $t8, 2
            la $s0, monkeys
            add $t0, $t7, $s0
            lw $s1, ($t0)

            # get operation
            move $s6, $zero
            la $s6, operations
            add $t0, $t8, $s6
            lb $s6, ($t0)

            # get operation argument
            la $s5, arguments
            add $t0, $t7, $s5
            lw $s5, ($t0)

            # for each worry level
            la $t0, last_el
            li $t6, 0
            add $t5, $t0, $t7
            lw $t5, ($t5)

            # t5 = last element index
            # t6 = worry index
            # t4 = new worry level
            WORRY_LOOP:
                beq $t6, $t5, END_WORRY_LOOP
                
                # get inspection index
                la $s2, inspections
                add $t0, $s2, $t7
                lw $t1, ($t0)
                addi $t1, $t1, 1
                sw $t1, ($t0)

                # get worry level
                sll $t0, $t6, 2
                add $t0, $t0, $s1
                lw $t1, ($t0)

                # index ++
                addi $t6, $t6, 1

                # if operation is plus jump to case plus
                lb $t0, op_p
                beq $s6, $t0, CASE_PLUS

                # if operation is times jump to case times
                lb $t0, op_t
                beq $s6, $t0, CASE_TIMES

                CASE_EL:
                    lw $t0, division
                    mult $t1, $t1

                    # loop to get remainder of division from hi and lo
                    # t1 = mask of bit to add
                    # t2 = lo
                    # t3 = index
                    # t4 = remainder

                    # first step: get remainder of division from hi
                    mfhi $t4
                    mflo $t2
                    div $t4, $t0
                    mfhi $t4

                    # second step: loop for all bits in lo and get remainder of division
                    li $t3, 32
                    li $t1, 2147483648 # 2^31
                    LOOP:
                        beq $t3, $zero, THROW
                        subi $t3, $t3, 1
                        sll $t4, $t4, 1
                        
                        and $t0, $t2, $t1

                        beq $t0, $zero, NEW_REMAINDER
                        CASE_1:
                            addi $t4, $t4, 1
                        NEW_REMAINDER:
                            lw $t0, division
                            div $t4, $t0
                            mfhi $t4
                        
                        srl $t1, $t1, 1
                        j LOOP

                CASE_PLUS:
                    add $t4, $t1, $s5
                    j THROW
                CASE_TIMES:
                    mul $t4, $t1, $s5
                THROW:

                    lw $t0, division
                    div $t4, $t0
                    mfhi $t4

                # check whether the new worry level is divisible by divisible_by
                la $s3, divisible_by
                add $t0, $t7, $s3
                lw $t0, ($t0)
                div $t4, $t0
                mfhi $t0
                beq $t0, $zero, DIVISIBLE

                NOT_DIVISIBLE:
                    la $s4, false
                    j PUT_IN_NEW_MONKEY
                DIVISIBLE:
                    la $s4, true
                
                PUT_IN_NEW_MONKEY:
                    add $t0, $t7, $s4       # t0 = address of index of new monkey
                    lw $t0, ($t0)           # t0 = index of new monkey
                    sll $t0, $t0, 2

                    # grab last index of new monkey
                    la $t1, last_el
                    add $t1, $t1, $t0
                    lw $t1, ($t1)
                    sll $t1, $t1, 2

                    # grab new monkey address
                    la $t2, monkeys
                    add $t2, $t2, $t0
                    lw $t2, ($t2)

                    # store new worry level
                    add $t3, $t1, $t2
                    sw $t4, ($t3)

                    # increment last index of new monkey and store it
                    srl $t1, $t1, 2
                    addi $t1, $t1, 1
                    la $t2, last_el
                    add $t2, $t2, $t0
                    sw $t1, ($t2)

                    j WORRY_LOOP
            END_WORRY_LOOP:
                # set last element to 0
                la $t0, last_el
                add $t0, $t0, $t7
                sw $zero, ($t0)

            addi $t8, $t8, 1
            j MONKEY_LOOP
        END_MONKEY_LOOP:

        j ROUND_LOOP

    END_ROUND:

    ## find the two highest inspections and put them in $s0 and $s1
    la $s2, inspections
    li $s0, 0
    li $s1, 0

    # for each inspection
    li $t9, N_MONKEYS

INSPECTION_LOOP:
        beq $t9, $zero, END_INSPECTION
        subi $t9, $t9, 1
        sll $t8, $t9, 2
        add $t8, $t8, $s2
        lw $t8, ($t8)

        # if inspection lower than s1, continue
        blt $t8, $s1, INSPECTION_LOOP
        add $s1, $zero, $t8

        # if inspection lower than s0, continue
        blt $t8, $s0, INSPECTION_LOOP
        add $s1, $zero, $s0
        add $s0, $zero, $t8

        j INSPECTION_LOOP

END_INSPECTION:

    # print final string
    la $a0, final_string
    li $v0, 4
    syscall

    # print $s0 and $s1
    move $a0, $s0
    li $v0, 1
    syscall

    la $a0, times_st
    li $v0, 4
    syscall

    move $a0, $s1
    li $v0, 1
    syscall

    la $a0, end_line
    li $v0, 4
    syscall

    li $v0, 10      		# End program
	syscall