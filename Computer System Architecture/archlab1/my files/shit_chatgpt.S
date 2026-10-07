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

        # s0  = N
        # s1  = current radix stride i
        # s2  = &X
        # s3  = &Y
        # s4  = &expTable
        # s5  = current source-buffer base
        # s6  = current destination-buffer base
        # s7  = current source group base
        # s8  = p0
        # s9  = p1
        # s10 = p2
        # s11 = p3
        #
        # t0  = current twiddle byte offset w
        # t1-t5 = butterfly/address temporaries
        # t6  = twiddle byte step
        #
        # a0..a7 = f0.r,f0.i,f1.r,f1.i,f2.r,f2.i,f3.r,f3.i

        la      t1, N
        lw      s0, 0(t1)
        la      s2, X
        la      s3, Y
        la      s4, expTable

        li      t1, 1
        beq     s0, t1, fft_done

        # N = 2: only the final radix-2 remains.
        li      t1, 2
        beq     s0, t1, setup_r2_n2

        # ================================================================
        #              FUSED FIRST RADIX-4 PASS
        # ================================================================
        # Fuse the bit-reversal permutation with pass 1.
        #
        # For group r:
        #   rev = reverse_{log2(N)-2}(r)
        #
        # and the four original inputs are:
        #   rev
        #   rev + N/2
        #   rev + N/4
        #   rev + 3N/4
        #
        # All four twiddles are 1, therefore expTable is never accessed.

        mv      s5, s2                  # source = X

        li      t1, 4
        beq     s0, t1, first_dst_x

        mv      s6, s3                  # N > 4: X -> Y
        j       first_pass_setup

first_dst_x:
        mv      s6, s2                  # N = 4: X -> X

first_pass_setup:
        mv      s7, s6                  # destination pointer
        li      t0, 0                   # reversed group index
        srli    t6, s0, 2              # number of butterflies = N/4

first_pass_k:
        # p0 = X[rev]
        slli    t1, t0, 3
        add     s8, s5, t1

        # p1 = p0 + N/2 elements
        slli    t2, s0, 2
        add     s9, s8, t2

        # p2 = p0 + N/4 elements
        slli    t3, s0, 1
        add     s10, s8, t3

        # p3 = p0 + 3N/4 elements
        add     s11, s9, t3

        # Load all four source values before any store.
        lw      a0, 0(s8)
        lw      a1, 4(s8)
        lw      a2, 0(s9)
        lw      a3, 4(s9)
        lw      a4, 0(s10)
        lw      a5, 4(s10)
        lw      a6, 0(s11)
        lw      a7, 4(s11)

        # A = f0 + f1
        # C = f2 + f3
        add     t2, a0, a2
        add     t3, a1, a3
        add     t4, a4, a6
        add     t5, a5, a7

        # B = f0 - f1
        # D = f2 - f3
        sub     a0, a0, a2
        sub     a1, a1, a3
        sub     a4, a4, a6
        sub     a5, a5, a7

        # out0 = A + C
        # out2 = A - C
        add     a2, t2, t4
        add     a3, t3, t5
        sub     a6, t2, t4
        sub     a7, t3, t5

        # out3 = B + iD
        # out1 = B - iD
        #
        # out3 must be computed before B is overwritten by out1.
        sub     t4, a0, a5             # out3.r
        add     t5, a1, a4             # out3.i
        add     a0, a0, a5             # out1.r
        sub     a1, a1, a4             # out1.i

        sw      a2, 0(s7)
        sw      a3, 4(s7)

        addi    s7, s7, 8
        sw      a0, 0(s7)
        sw      a1, 4(s7)

        addi    s7, s7, 8
        sw      a6, 0(s7)
        sw      a7, 4(s7)

        addi    s7, s7, 8
        sw      t4, 0(s7)
        sw      t5, 4(s7)

        addi    s7, s7, 8

        addi    t6, t6, -1
        beq     t6, zero, first_pass_done

        # Increment reversed group index.
        #
        # The highest bit in the reversed (log2(N)-2)-bit counter
        # is N/8.
        srli    t4, s0, 3

first_rev_carry:
        and     t5, t0, t4
        beq     t5, zero, first_rev_flip

        xor     t0, t0, t4
        srli    t4, t4, 1
        j       first_rev_carry

first_rev_flip:
        xor     t0, t0, t4
        j       first_pass_k

first_pass_done:
        # First pass wrote the next DIT state into s6.
        mv      s5, s6                  # new source
        mv      s6, s2                  # new destination = X
        mv      s7, s5

        li      s1, 4
        li      t6, 64                  # 256 / 4
        j       radix4_check

setup_r2_n2:
        li      s1, 1
        li      t6, 512                 # w step; only k=0 is used
        mv      s5, s2
        mv      s6, s2
        j       radix4_done

        # ================================================================
        #                       RADIX-4 PASSES
        # ================================================================
radix4_check:
        # Continue iff 2*i < N.
        slli    t1, s1, 1
        bge     t1, s0, radix4_done

        # 4*i == N -> final radix-4 pass.
        slli    t1, s1, 2
        beq     t1, s0, radix4_final_setup

radix4_nonfinal_setup:
        mv      s7, s5                  # first group of source
        j       radix4_stage_begin

radix4_final_setup:
        mv      s6, s2                  # final radix-4 pass -> X
        mv      s7, s5

radix4_stage_begin:

radix4_group:
        mv      s8, s7                  # p0

        slli    t1, s1, 3               # i * 8
        add     s9, s8, t1              # p1
        add     s10, s9, t1             # p2
        add     s11, s10, t1            # p3

        li      t0, 0                   # w = 0

radix4_k:

        # -------------------- f0 --------------------
        lw      a0, 0(s8)
        lw      a1, 4(s8)

        # -------------------- f1 = X[p1] * E[2w] --------------------
        slli    t1, t0, 1
        add     t1, s4, t1
        lw      t2, 0(t1)               # E1.x
        lw      t3, 4(t1)               # E1.y

        lw      a2, 0(s9)               # X1.x
        lw      a3, 4(s9)               # X1.y

        # f1.r
        mul     t4, a2, t2
        mul     t5, a3, t3
        srai    t4, t4, 13
        srai    t5, t5, 13
        sub     t4, t4, t5

        # f1.i
        #
        # IMPORTANT:
        # a2/a3 must still contain the original X1 values here.
        mul     t1, a2, t3
        mul     t2, a3, t2
        srai    t1, t1, 13
        srai    t2, t2, 13
        add     a3, t1, t2
        mv      a2, t4

        # -------------------- f2 = X[p2] * E[w] --------------------
        add     t1, s4, t0
        lw      t2, 0(t1)               # E2.x
        lw      t3, 4(t1)               # E2.y

        lw      a4, 0(s10)              # X2.x
        lw      a5, 4(s10)              # X2.y

        # f2.r
        mul     t4, a4, t2
        mul     t5, a5, t3
        srai    t4, t4, 13
        srai    t5, t5, 13
        sub     t4, t4, t5

        # f2.i
        mul     t1, a4, t3
        mul     t2, a5, t2
        srai    t1, t1, 13
        srai    t2, t2, 13
        add     a5, t1, t2
        mv      a4, t4

        # -------------------- f3 = X[p3] * E[3w] --------------------
        #
        # Only expTable[0..63] is materialized.  For the second half,
        # negate the corresponding first-half entry.
        slli    t1, t0, 1
        add     t1, t1, t0              # 3w

        andi    t2, t1, 512
        slli    t2, t2, 22
        srai    t2, t2, 31              # 0 or -1

        andi    t1, t1, 511
        add     t1, s4, t1

        lw      t3, 0(t1)               # E3.x
        lw      t4, 4(t1)               # E3.y

        xor     t3, t3, t2
        sub     t3, t3, t2

        xor     t4, t4, t2
        sub     t4, t4, t2

        lw      a6, 0(s11)              # X3.x
        lw      a7, 4(s11)              # X3.y

        # f3.r
        mul     t5, a6, t3
        mul     t1, a7, t4
        srai    t5, t5, 13
        srai    t1, t1, 13
        sub     t5, t5, t1

        # f3.i
        mul     t1, a6, t4
        mul     t2, a7, t3
        srai    t1, t1, 13
        srai    t2, t2, 13
        add     t1, t1, t2

        mv      a6, t5
        mv      a7, t1

        # -------------------- radix-4 combination --------------------
        # A = f0 + f1
        # B = f0 - f1
        # C = f2 + f3
        # D = f2 - f3

        add     t1, a0, a2              # A.r
        add     t2, a1, a3              # A.i
        add     t3, a4, a6              # C.r
        add     t4, a5, a7              # C.i

        sub     a0, a0, a2              # B.r
        sub     a1, a1, a3              # B.i
        sub     a4, a4, a6              # D.r
        sub     a5, a5, a7              # D.i

        # out0 = A + C
        add     a2, t1, t3
        add     a3, t2, t4

        # out2 = A - C
        sub     a6, t1, t3
        sub     a7, t2, t4

        # out3 = B + iD
        # out1 = B - iD
        #
        # First preserve out3, then overwrite B with out1.
        sub     t3, a0, a5              # out3.r
        add     t4, a1, a4              # out3.i

        add     a0, a0, a5              # out1.r
        sub     a1, a1, a4              # out1.i

        # Destination offset equals source p0's offset
        # within the current group.
        sub     t1, s8, s5
        add     t1, s6, t1

        slli    t2, s1, 3               # i * 8

        sw      a2, 0(t1)
        sw      a3, 4(t1)

        add     t1, t1, t2
        sw      a0, 0(t1)
        sw      a1, 4(t1)

        add     t1, t1, t2
        sw      a6, 0(t1)
        sw      a7, 4(t1)

        add     t1, t1, t2
        sw      t3, 0(t1)
        sw      t4, 4(t1)

        # Next butterfly.
        addi    s8, s8, 8
        addi    s9, s9, 8
        addi    s10, s10, 8
        addi    s11, s11, 8

        add     t0, t0, t6

        # For every radix-4 stage, i * step = 256 bytes.
        li      t5, 256
        bne     t0, t5, radix4_k

        # Next group.
        slli    t1, s1, 5               # 4*i*8
        add     s7, s7, t1

        # Continue while group offset < N*8.
        slli    t2, s0, 3
        sub     t3, s7, s5
        blt     t3, t2, radix4_group

        # Was this the final radix-4 pass?
        slli    t1, s1, 2
        beq     t1, s0, radix4_final_done

        # Ping-pong buffers.
        mv      t1, s5
        mv      s5, s6
        mv      s6, t1
        mv      s7, s5

        slli    s1, s1, 2
        srli    t6, t6, 2
        j       radix4_check

radix4_final_done:
        # The original Radix-4 loop advances i after every pass.
        # Mark the radix-4 decomposition as complete so that a final
        # radix-2 is NOT executed for N = 16, 64, ...
        mv      s1, s0
        j       radix4_done

        # ================================================================
        #                         TAIL RADIX-2
        # ================================================================
radix4_done:
        bge     s1, s0, fft_done

        # Current t6 is the radix-4 fixed-table byte step.
        # Tail radix-2 needs W_N^k, hence the byte step is 2*t6.
        #
        # N=2 is the only exception: only k=0 is executed, so its step
        # is irrelevant and is already initialized to 512.
        li      t1, 2
        beq     s0, t1, radix2_step_ready

        slli    t6, t6, 1

radix2_step_ready:
        mv      s8, s5                  # source p0

        slli    t1, s1, 3
        add     s9, s8, t1              # source p1

        mv      s10, s2                 # destination X p0
        add     s11, s2, t1             # destination X p1

        li      t0, 0                   # w = 0

radix2_k:
        # f0
        lw      a0, 0(s8)
        lw      a1, 4(s8)

        # E[w]
        add     t1, s4, t0
        lw      t2, 0(t1)
        lw      t3, 4(t1)

        # f1 source
        lw      a2, 0(s9)
        lw      a3, 4(s9)

        # f1.r
        mul     t4, a2, t2
        mul     t5, a3, t3
        srai    t4, t4, 13
        srai    t5, t5, 13
        sub     a4, t4, t5

        # f1.i
        mul     t1, a2, t3
        mul     t2, a3, t2
        srai    t1, t1, 13
        srai    t2, t2, 13
        add     a5, t1, t2

        # radix-2 butterfly
        add     t4, a0, a4
        add     t5, a1, a5
        sub     t2, a0, a4
        sub     t3, a1, a5

        sw      t4, 0(s10)
        sw      t5, 4(s10)
        sw      t2, 0(s11)
        sw      t3, 4(s11)

        addi    s8, s8, 8
        addi    s9, s9, 8
        addi    s10, s10, 8
        addi    s11, s11, 8

        add     t0, t0, t6

        # Every legal tail has i * step = 512 bytes.
        li      t1, 512
        bne     t0, t1, radix2_k

fft_done:
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
