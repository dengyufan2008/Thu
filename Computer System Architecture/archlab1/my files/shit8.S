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
        jal     data_input
        jal     dft_transform_impl
        jal     data_output
        lw      ra,12(sp)
        li      a0,0
        li      a7, 10
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
        # Dynamic calc s8-s11 and some calc optimize
        # s0 = N, s1 = m, s2 = &X, s3 = &expTable, s4 = 8g
        # s5 = i, s6 = j, s7 = k

        addi    sp, sp, -64
        sw      ra, 52(sp)
        sw      s0, 48(sp)
        sw      s1, 44(sp)
        sw      s2, 40(sp)
        sw      s3, 36(sp)
        sw      s4, 32(sp)
        sw      s5, 28(sp)
        sw      s6, 24(sp)
        sw      s7, 20(sp)
        sw      s8, 16(sp)
        sw      s9, 12(sp)
        sw      s10, 8(sp)
        sw      s11, 4(sp)

        la      t0, N
        lw      s0, 0(t0)           # s0 = N
        li      s1, 0               # s1 = m
        j       loop_m_con
loop_m:
        addi    s1, s1, 1
loop_m_con:
        li      t0, 1
        sll     t0, t0, s1          # t0 = 1 << m
        blt     t0, s0, loop_m

        la      s2, X               # s2 = &X
        li      s5, 0               # s5 = i
        mv      s6, s2              # s6 = &X[i]
        j       loop_rev_con
loop_rev:
        # Calc a0 = reverse(i, m)
        li      a0, 0
        li      s7, 0               # s7 = k
        mv      t4, s5              # t4 = val
        j       rev_con
rev:
        slli    a0, a0, 1
        andi    a1, t4, 1           # a1 = val & 1
        or      a0, a0, a1
        srli    t4, t4, 1
        addi    s7, s7, 1
rev_con:
        blt     s7, s1, rev

        # Swap
        bge     s5, a0, loop_rev_nxt
        slli    a0, a0, 3
        add     a0, s2, a0          # a0 = &X[reverse(i, m)]
        lw      t0, 0(s6)           # t0 = X[i].x
        lw      t1, 4(s6)           # t1 = X[i].y
        lw      t2, 0(a0)           # t2 = X[reverse(i, m)].x
        lw      t3, 4(a0)           # t3 = X[reverse(i, m)].y
        sw      t0, 0(a0)
        sw      t1, 4(a0)
        sw      t2, 0(s6)
        sw      t3, 4(s6)
loop_rev_nxt:
        addi    s5, s5, 1
        addi    s6, s6, 8
loop_rev_con:
        blt     s5, s0, loop_rev

        # -------------------- RADIX-4 FFT --------------------
        la      s3, expTable        # s3 = &expTable
        li      s4, 256             # s4 = 8g
        li      s5, 1               # s5 = i
        j       loop_r4_i_con

loop_r4_i:
        li      s6, 0               # s6 = j
        j       loop_r4_j_con

loop_r4_j:
        mv      s7, s6              # s7 = k
        li      t0, 0               # t0 = 8w
        slli    t1, s5, 3           # t1 = 8i
        slli    s8, s6, 3
        add     s8, s2, s8          # s8 = &X[k]
        add     s9, s8, t1          # s9 = &X[k + i]
        add     s10, s9, t1         # s10 = &X[k + 2i]
        add     s11, s10, t1        # s11 = &X[k + 3i]
        j       loop_r4_k_con

loop_r4_k:

        # ---------- 1. Calc f0 = X[k] ----------
        lw      t2, 0(s8)           # t2 = f0.x
        lw      t3, 4(s8)           # t3 = f0.y
        mv      a0, t2              # a0 = f0.x
        mv      a1, t3              # a1 = f0.y
        mv      a2, t2              # a2 = f0.x
        mv      a3, t3              # a3 = f0.y

        # ---------- 2. Calc f1 = X[k + i] * expTable[2w] ----------
        slli    t1, t0, 1
        add     t1, s3, t1          # t1 = &expTable[2w]
        lw      t3, 0(t1)           # t3 = E1.x
        lw      t4, 4(t1)           # t4 = E1.y
        lw      t5, 0(s9)           # t5 = X1.x
        lw      t6, 4(s9)           # t6 = X1.y

        mul     t1, t5, t3
        mul     t2, t6, t4
        srai    t1, t1, 13
        srai    t2, t2, 13
        sub     t1, t1, t2          # t1 = f1.x
        add     a0, a0, t1          # a0 = f0.x + f1.x
        sub     a2, a2, t1          # a2 = f0.x - f1.x

        mul     t1, t5, t4
        mul     t2, t6, t3
        srai    t1, t1, 13
        srai    t2, t2, 13
        add     t1, t1, t2          # t1 = f1.y
        add     a1, a1, t1          # a1 = f0.y + f1.y
        sub     a3, a3, t1          # a3 = f0.y - f1.y

        # ---------- 3. Calc f2 = X[k + 2i] * expTable[w] ----------
        add     t1, s3, t0          # t1 = &expTable[w]
        lw      t3, 0(t1)           # t3 = E2.x
        lw      t4, 4(t1)           # t4 = E2.y
        lw      t5, 0(s10)          # t5 = X2.x
        lw      t6, 4(s10)          # t6 = X2.y

        mul     t1, t5, t3
        mul     t2, t6, t4
        srai    t1, t1, 13
        srai    t2, t2, 13
        sub     t1, t1, t2          # t1 = f2.x
        mv      a4, t1              # a4 = f2.x
        mv      a6, t1              # a6 = f2.x

        mul     t1, t5, t4
        mul     t2, t6, t3
        srai    t1, t1, 13
        srai    t2, t2, 13
        add     t1, t1, t2          # t1 = f2.y
        mv      a5, t1              # a5 = f2.y
        mv      a7, t1              # a7 = f2.y

        # ---------- 4. Calc f3 = X[k + 3i] * expTable[3w] ----------
        slli    t1, t0, 1
        add     t1, t1, t0          # t1 = 24w
        andi    t2, t1, 512
        slli    t2, t2, 22
        srai    t2, t2, 31          # t2 = -1 if t1 >= 512 else 0
        andi    t1, t1, 511
        add     t1, s3, t1          # t1 = &expTable[3w % 64]
        lw      t3, 0(t1)           # t3 = E3.x
        lw      t4, 4(t1)           # t4 = E3.y
        lw      t5, 0(s11)          # t5 = X3.x
        lw      t6, 4(s11)          # t6 = X3.y

        xor     t3, t3, t2
        sub     t3, t3, t2          # t3 = -E3.x if t2 is -1 else E3.x
        xor     t4, t4, t2
        sub     t4, t4, t2          # t4 = -E3.y if t2 is -1 else E3.y

        mul     t1, t5, t3
        mul     t2, t6, t4
        srai    t1, t1, 13
        srai    t2, t2, 13
        sub     t1, t1, t2          # t1 = f3.x
        add     a4, a4, t1          # a4 = f2.x + f3.x
        sub     a6, a6, t1          # a6 = f2.x - f3.x

        mul     t1, t5, t4
        mul     t2, t6, t3
        srai    t1, t1, 13
        srai    t2, t2, 13
        add     t1, t1, t2          # t1 = f3.y
        add     a5, a5, t1          # a5 = f2.y + f3.y
        sub     a7, a7, t1          # a6 = f2.y - f3.y

        # ---------- 5. Save Ans ----------
        add     t1, a0, a4
        add     t2, a1, a5           # X[k] = (f0 + f1) + (f2 + f3)
        add     t3, a2, a7
        sub     t4, a3, a6           # X[k + i] = (f0 - f1) + (f2 - f3) * (-i)
        sub     t5, a0, a4
        sub     t6, a1, a5           # X[k + 2i] = (f0 + f1) - (f2 + f3)
        sub     a0, a2, a7
        add     a1, a3, a6           # X[k + 3i] = (f0 - f1) - (f2 - f3) * (-i)

        sw      t1, 0(s8)
        sw      t2, 4(s8)
        sw      t3, 0(s9)
        sw      t4, 4(s9)
        sw      t5, 0(s10)
        sw      t6, 4(s10)
        sw      a0, 0(s11)
        sw      a1, 4(s11)

        addi    s7, s7, 1
        addi    s8, s8, 8
        addi    s9, s9, 8
        addi    s10, s10, 8
        addi    s11, s11, 8
        add     t0, t0, s4
loop_r4_k_con:
        add     t1, s6, s5          # t1 = j + i
        blt     s7, t1, loop_r4_k

        slli    t0, s5, 2           # t0 = 4i
        add     s6, s6, t0
loop_r4_j_con:
        blt     s6, s0, loop_r4_j

        slli    s5, s5, 2
        srli    s4, s4, 2
loop_r4_i_con:
        slli    t0, s5, 1           # t0 = 2i
        blt     t0, s0, loop_r4_i

        # -------------------- RADIX-2 FFT --------------------
        bge     s5, s0, skip_r2

        li      s7, 0               # s7 = k
        mv      a1, s3              # a1 = &expTable[w]
        mv      a2, s2              # a2 = &X[k]
        slli    a3, s5, 3
        add     a3, s2, a3          # a3 = &X[k + i]
        j       loop_r2_k_con

loop_r2_k:
        lw      t0, 0(a2)           # t0 = f0.x
        lw      t1, 4(a2)           # t1 = f0.y
        lw      a4, 0(a3)           # a4 = X[k + i].x
        lw      a5, 4(a3)           # a5 = X[k + i].y
        lw      a6, 0(a1)           # a6 = expTable[w].x
        lw      a7, 4(a1)           # a7 = expTable[w].y

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

        addi    s7, s7, 1
        addi    a1, a1, 8
        addi    a2, a2, 8
        addi    a3, a3, 8
loop_r2_k_con:
        blt     s7, s5, loop_r2_k

skip_r2:
        # -------------------- FFT END --------------------

        # Stack Restore
        lw      s11, 4(sp)
        lw      s10, 8(sp)
        lw      s9, 12(sp)
        lw      s8, 16(sp)
        lw      s7, 20(sp)
        lw      s6, 24(sp)
        lw      s5, 28(sp)
        lw      s4, 32(sp)
        lw      s3, 36(sp)
        lw      s2, 40(sp)
        lw      s1, 44(sp)
        lw      s0, 48(sp)
        lw      ra, 52(sp)
        addi    sp, sp, 64
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
