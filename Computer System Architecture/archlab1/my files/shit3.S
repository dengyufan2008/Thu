.data
# -------------------------------------- TODO: FILL IN YOUR FILE PATH !!! -------------------------------------------
read_path:
		.string "/home/student/archlab1/sample/data.in"
write_path:
		.string "/home/student/archlab1/sample/data.out"
# ------------------------------------------------------------------------------------------------------------------
X:
        .zero   1024

# Y is available for implementations that are not fully in-place. 
# If your code operates fully in-place, you can ignore or remove the Y array.
Y:
	.zero	1024

N:
        .zero   4
        
# expTable is stored same as C code
# Notice the second half is all zero!
expTable:
        .word	8192
        .word	0
        .word	8182
        .word	-401
        .word	8152
        .word	-802
        .word	8103
        .word	-1202
        .word	8034
        .word	-1598
        .word	7946
        .word	-1990
        .word	7839
        .word	-2378
        .word	7713
        .word	-2759
        .word	7568
        .word	-3134
        .word	7405
        .word	-3502
        .word	7224
        .word	-3861
        .word	7026
        .word	-4211
        .word	6811
        .word	-4551
        .word	6579
        .word	-4879
        .word	6332
        .word	-5196
        .word	6069
        .word	-5501
        .word	5792
        .word	-5792
        .word	5501
        .word	-6069
        .word	5196
        .word	-6332
        .word	4879
        .word	-6579
        .word	4551
        .word	-6811
        .word	4211
        .word	-7026
        .word	3861
        .word	-7224
        .word	3502
        .word	-7405
        .word	3134
        .word	-7568
        .word	2759
        .word	-7713
        .word	2378
        .word	-7839
        .word	1990
        .word	-7946
        .word	1598
        .word	-8034
        .word	1202
        .word	-8103
        .word	802
        .word	-8152
        .word	401
        .word	-8182
        .word	0
        .word	-8192
        .word	-401
        .word	-8182
        .word	-802
        .word	-8152
        .word	-1202
        .word	-8103
        .word	-1598
        .word	-8034
        .word	-1990
        .word	-7946
        .word	-2378
        .word	-7839
        .word	-2759
        .word	-7713
        .word	-3134
        .word	-7568
        .word	-3502
        .word	-7405
        .word	-3861
        .word	-7224
        .word	-4211
        .word	-7026
        .word	-4551
        .word	-6811
        .word	-4879
        .word	-6579
        .word	-5196
        .word	-6332
        .word	-5501
        .word	-6069
        .word	-5792
        .word	-5792
        .word	-6069
        .word	-5501
        .word	-6332
        .word	-5196
        .word	-6579
        .word	-4879
        .word	-6811
        .word	-4551
        .word	-7026
        .word	-4211
        .word	-7224
        .word	-3861
        .word	-7405
        .word	-3502
        .word	-7568
        .word	-3134
        .word	-7713
        .word	-2759
        .word	-7839
        .word	-2378
        .word	-7946
        .word	-1990
        .word	-8034
        .word	-1598
        .word	-8103
        .word	-1202
        .word	-8152
        .word	-802
        .word	-8182
        .word	-401
        .zero	512


.text
main:
        addi    sp,sp,-16
        sw      ra,12(sp)
        jal    data_input
        jal    dft_transform_impl
        jal    data_output
        lw      ra,12(sp)
        li      a0,0
        li a7, 10
        ecall
        addi    sp,sp,16
        jr      ra


_printf_num:
# DO NOT MODIFY THIS!!!
        li a7, 1
        ecall 
        ret


_printf_char:
# DO NOT MODIFY THIS!!!
        li a7, 11
        ecall 
        ret


_read_int:
# DO NOT MODIFY THIS!!!
        mv      a5,a1
        mv      a4,a2
        li a7, 1024
        li a1, 0
        ecall
        mv t3, a0
        li a7, 65
        mv a1, a5
        mv a2, a4
        ecall
        li a7, 57
        mv a0, t3
        ecall
        ret


_write_int:
# DO NOT MODIFY THIS!!! 
        mv a5, a1
        mv a4, a2
        li a7, 1024
        li a1, 1
        ecall
        mv t3, a0
        li a7, 66
        mv a1, a5
        mv a2, a4
        ecall
        li a7, 57
        mv a0, t3
        ecall
        ret

dft_transform_impl:
# --------------------------------------- TODO: FILL IN CODE HERE ---------------------------------------
        # Manual
        # Optimize FFT calc parallazing
        # s0 = N, s1 = m, s2 = &X, s3 = &Y, s4 = g, s5 = w
        addi    sp, sp, -48
        sw      ra, 44(sp)
        sw      s0, 40(sp)
        sw      s1, 36(sp)
        sw      s2, 32(sp)
        sw      s3, 28(sp)
        sw      s4, 24(sp)
        sw      s5, 20(sp)
        sw      s6, 16(sp)
        sw      s7, 12(sp)
        sw      s8, 8(sp)
        sw      s9, 4(sp)

        # Read N
        la      t0, N
        lw      s0, 0(t0)           # s0 = N

        # Calc m = log_2 N
        li      s1, 0               # s1 = m
        j       loop_m_con
loop_m:
        addi    s1, s1, 1
loop_m_con:
        li      t0, 1
        sll     t0, t0, s1          # t0 = 1 << m
        blt     t0, s0, loop_m

        # Reverse bits
        la      s2, X               # s2 = &X
        la      s3, Y               # s3 = &Y
        li      s6, 0               # s6 = i
        j       loop_rev_con
loop_rev:
        mv      a0, s6
        mv      a1, s1
        jal     ra, reverse         # a0 = reverse(i, m)

        slli    t0, s6, 3
        add     t0, s2, t0          # t0 = &X[i]
        lw      t1, 0(t0)           # t1 = X[i].x
        lw      t2, 4(t0)           # t2 = X[i].y

        slli    t3, a0, 3
        add     t3, s3, t3          # t3 = &Y[reverse(i, m)]
        sw      t1, 0(t3)
        sw      t2, 4(t3)

        addi    s6, s6, 1
loop_rev_con:
        blt     s6, s0, loop_rev

        # Copy Y into X 
        li      s6, 0               # s6 = i
        j       loop_copy_con
loop_copy:
        slli    t0, s6, 3           # t0 = i * 8
        add     t1, s3, t0          # t1 = &Y[i]
        add     t2, s2, t0          # t2 = &X[i]

        lw      t3, 0(t1)           # t3 = Y[i].x
        lw      t4, 4(t1)           # t4 = Y[i].y
        sw      t3, 0(t2)
        sw      t4, 4(t2)

        addi    s6, s6, 1
loop_copy_con:
        blt     s6, s0, loop_copy

        # -------------------- FFT --------------------
        # for (int i = 1; i < m; i <<= 1)
        li      s6, 1               # s6 = i
        j       loop_i_con
loop_i:
        slli    t0, s6, 1           # t0 = i << 1
        li      t1, 128             # t1 = 128
        div     s4, t1, t0          # s4 = g

        # for (int j = 0; j < m; j += i << 1)
        li      s7, 0               # s7 = j
        j       loop_j_con
loop_j:
        li      s5, 0               # s5 = w

        # for (int k = j; k < j + i; k++)
        mv      s8, s7              # s8 = k
        add     s9, s7, s6          # s9 = j + i
        slli    a2, s7, 3
        slli    a3, s9, 3
        add     a2, s2, a2          # a2 = &X[k]
        add     a3, s2, a3          # a3 = &X[k + i]
        j       loop_k_con
loop_k:
        lw      t0, 0(a2)           # t0 = f0.x
        lw      t1, 4(a2)           # t1 = f0.y
        lw      a4, 0(a3)           # a4 = X[k + i].x
        lw      a5, 4(a3)           # a5 = X[k + i].y

        li      t6, 64              # t6 = 64
        la      t4, expTable        # t4 = &expTable
        bge     s5, t6, first_half_end
        slli    t5, s5, 3
        add     t5, t4, t5          # t5 = &expTable[w]
        lw      a6, 0(t5)           # a6 = expTable[w].x
        lw      a7, 4(t5)           # a7 = expTable[w].y
        j       second_half_end
first_half_end:

        sub     t6, s5, t6          # t6 = w - 64
        slli    t5, t6, 3
        add     t5, t4, t5          # t5 = &expTable[w - 64]
        lw      a6, 0(t5)
        lw      a7, 4(t5)
        sub     a6, zero, a6        # a6 = -expTable[w - 64].x = expTable[w].x
        sub     a7, zero, a7        # a7 = -expTable[w - 64].y = expTable[w].y
second_half_end:

        mul     t4, a4, a6
        mul     t5, a5, a6
        mul     t2, a5, a7
        mul     t3, a4, a7
        srai    t4, t4, 13
        srai    t5, t5, 13
        srai    t2, t2, 13
        srai    t3, t3, 13
        sub     t2, t4, t2          # t2 = f1.x
        add     t3, t5, t3          # t3 = f1.y
        add     t4, t0, t2          # t4 = X[k].x
        add     t5, t1, t3          # t5 = X[k].y
        sub     t6, t0, t2          # t6 = X[k + i].x
        sub     a0, t1, t3          # a0 = X[k + i].y
        sw      t4, 0(a2)
        sw      t5, 4(a2)
        sw      t6, 0(a3)
        sw      a0, 4(a3)

        add     s5, s5, s4
        addi    s8, s8, 1
        addi    a2, a2, 8
        addi    a3, a3, 8
loop_k_con:
        blt     s8, s9, loop_k

        slli    t0, s6, 1           # t0 = i << 1
        add     s7, s7, t0
loop_j_con:
        blt     s7, s0, loop_j

        slli    s6, s6, 1
loop_i_con:
        blt     s6, s0, loop_i
        # -------------------- FFT END --------------------

        # Mod 2^{31}
        li      s6, 0               # s6 = i = 0
        j       loop_fix_con
loop_fix:
        slli    t0, s6, 3
        add     t0, s2, t0          # t0 = &X[i]

        lw      t1, 0(t0)           # t1 = X[i].x
        bge     t1, zero, check_x_end
        lui     t2, 0x80000         # t2 = 0x80000000 = 1LL << 31
        add     t1, t1, t2
        sw      t1, 0(t0)
check_x_end:

        lw      t1, 4(t0)           # t1 = X[i].y
        bge     t1, zero, check_y_end
        lui     t2, 0x80000         # t2 = 0x80000000 = 1LL << 31
        add     t1, t1, t2
        sw      t1, 4(t0)
check_y_end:

        addi    s6, s6, 1
loop_fix_con:
        blt     s6, s0, loop_fix

        lw      s9, 4(sp)
        lw      s8, 8(sp)
        lw      s7, 12(sp)
        lw      s6, 16(sp)
        lw      s5, 20(sp)
        lw      s4, 24(sp)
        lw      s3, 28(sp)
        lw      s2, 32(sp)
        lw      s1, 36(sp)
        lw      s0, 40(sp)
        lw      ra, 44(sp)
        addi    sp, sp, 48
        ret

# reverse(a0 = x, a1 = l) -> a0 = bit_reverse
reverse:
        li      t0, 0               # t0 = res
        li      t1, 0               # t1 = i
        j       rev_loop_con
rev_loop:
        slli    t0, t0, 1
        andi    t2, a0, 1           # t2 = val & 1
        or      t0, t0, t2
        srli    a0, a0, 1
        addi    t1, t1, 1
rev_loop_con:
        blt     t1, a1, rev_loop

        mv      a0, t0              # a0 = res
        ret
# -------------------------------------------------------------------------------------------------------

# The .s code reads and writes data in exactly the same format as C code. 
#  The data is stored in the X array in the same format as a C struct (with real and imaginary parts interleaved).
# DATA_OUTPUT
data_output:
# DO NOT MODIFY THIS!!!
    addi sp,sp,-4
    sw ra,0(sp)

    la a0, write_path
    li a7, 1024
    li a1, 1
    ecall

    mv t3, a0

	la a1, N
	li a2, 1
	li a7, 66
	ecall

	lw t0, N
	la t2, X
	addi t4, zero, 0
OUTPUT_ONE_LINE:
	mv a0, t3
	mv a1, t2
	li a2, 2
	li a7, 66
	ecall
	addi t2, t2, 8
	addi t4, t4, 1
	blt t4, t0, OUTPUT_ONE_LINE

    mv a0, t3
    li a7, 57
    ecall
    lw ra,0(sp)
    addi sp,sp,4
    jr ra
# DATA_OUTPUT_END

# DATA_INPUT
data_input:
# DO NOT MODIFY THIS!!!
    addi sp,sp,-4
    sw ra, 0(sp)

    li a7, 1024
    li a1, 0
    la a0, read_path
    ecall
    
    mv t3, a0
    li a7, 65
    la a1, N
    li a2, 1
    ecall

    li a7, 65
    mv a0, t3
    la a1, X
    li a2, 256
    ecall

    mv a0, t3
    li a7, 57
    ecall
    lw ra, 0(sp)
    addi sp, sp, 4
    mv a0, t4
    mv a1, t5
    jr ra
# DATA_INPUT_END
