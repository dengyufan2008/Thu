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
        # 1. 栈帧保存
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

        # 2. 读取 N 并计算 m = log2(N)
        la      t0, N
        lw      s0, 0(t0)           # s0 = N
        li      s1, 0               # s1 = m
        li      t0, 1
calc_m_loop:
        bge     t0, s0, calc_m_done
        slli    t0, t0, 1
        addi    s1, s1, 1
        j       calc_m_loop
calc_m_done:

        # 特判：N == 1 直接跳到结尾
        li      t0, 1
        beq     s0, t0, fft_finish

        # 3. 初始化基址与指针
        la      s2, X               # s2 = src_base (初始指向 X)
        la      s3, Y               # s3 = dst_base (初始指向 Y)
        la      s4, expTable        # s4 = &expTable

        # 特判：N == 2，无 Radix-4，直接跳到尾部 Radix-2（Pass 1 融合 Bit-Reverse）
        li      t0, 2
        beq     s0, t0, pass_radix2_only

        # =========================================================================
        # ------------------- RADIX-4 PASS 1 (特判 + 免 reverse) -------------------
        # 说明：Pass 1 时 i=1, 旋转因子均为 (8192, 0)，缩放后等于 1。
        #       输入来自 X[rev(k)]，直接写入 Y[k]。消除了 expTable 读取和复数乘法。
        # =========================================================================
        li      s5, 1               # s5 = i = 1
        li      s8, 0               # s8 = k (0, 4, 8, ... N-4)

loop_p1_k:
        # ----- 计算 4 个点的 bit-reverse 索引并换算为字节偏移 -----
        # 点 0: rev(k)
        li      a0, 0
        li t0, 0
        mv t4, s8
rev_p1_0:
        slli    a0, a0, 1
        andi a1, t4, 1
        or a0, a0, a1
        srli t4, t4, 1
        addi t0, t0, 1
        blt     t0, s1, rev_p1_0
        slli    a0, a0, 3
        add     s9, s2, a0          # s9 = &X[rev(k)]

        # 点 1: rev(k + 1)
        addi    t5, s8, 1
        li      a0, 0
        li t0, 0
        mv t4, t5
rev_p1_1:
        slli    a0, a0, 1
        andi a1, t4, 1
        or a0, a0, a1
        srli t4, t4, 1
        addi t0, t0, 1
        blt     t0, s1, rev_p1_1
        slli    a0, a0, 3
        add     s10, s2, a0         # s10 = &X[rev(k + 1)]

        # 点 2: rev(k + 2)
        addi    t5, s8, 2
        li      a0, 0
        li t0, 0
        mv t4, t5
rev_p1_2:
        slli    a0, a0, 1
        andi a1, t4, 1
        or a0, a0, a1
        srli t4, t4, 1
        addi t0, t0, 1
        blt     t0, s1, rev_p1_2
        slli    a0, a0, 3
        add     s11, s2, a0         # s11 = &X[rev(k + 2)]

        # 点 3: rev(k + 3)
        addi    t5, s8, 3
        li      a0, 0
        li t0, 0
        mv t4, t5
rev_p1_3:
        slli    a0, a0, 1
        andi a1, t4, 1
        or a0, a0, a1
        srli t4, t4, 1
        addi t0, t0, 1
        blt     t0, s1, rev_p1_3
        slli    a0, a0, 3
        add     a0, s2, a0          # a0 = &X[rev(k + 3)]

        # ----- 指令重排加载数据 (Load 流水化) -----
        lw      a1, 0(s9)           # a1 = f0.x
        lw      a2, 4(s9)           # a2 = f0.y
        lw      a3, 0(s10)          # a3 = f1.x
        lw      a4, 4(s10)          # a4 = f1.y
        lw      a5, 0(s11)          # a5 = f2.x
        lw      a6, 4(s11)          # a6 = f2.y
        lw      a7, 0(a0)           # a7 = f3.x
        lw      t6, 4(a0)           # t6 = f3.y

        # ----- 蝶形运算组合 (Radix-4 Butterfly with W=1) -----
        # a0..a3 存放临时和差
        add     t0, a1, a3          # t0 = f0.x + f1.x
        sub     t1, a1, a3          # t1 = f0.x - f1.x
        add     t2, a2, a4          # t2 = f0.y + f1.y
        sub     t3, a2, a4          # t3 = f0.y - f1.y

        add     t4, a5, a7          # t4 = f2.x + f3.x
        sub     t5, a5, a7          # t5 = f2.x - f3.x
        add     a1, a6, t6          # a1 = f2.y + f3.y
        sub     a2, a6, t6          # a2 = f2.y - f3.y

        # 计算 4 个输出点 (写回 Y[k], Y[k+1], Y[k+2], Y[k+3])
        # Output 0: Y[k]
        add     a3, t0, t4          # Out0.x = (f0.x + f1.x) + (f2.x + f3.x)
        add     a4, t2, a1          # Out0.y = (f0.y + f1.y) + (f2.y + f3.y)

        # Output 1: Y[k + 1]
        add     a5, t1, a2          # Out1.x = (f0.x - f1.x) + (f2.y - f3.y)
        sub     a6, t3, t5          # Out1.y = (f0.y - f1.y) - (f2.x - f3.x)

        # Output 2: Y[k + 2]
        sub     a7, t0, t4          # Out2.x = (f0.x + f1.x) - (f2.x + f3.x)
        sub     t6, t2, a1          # Out2.y = (f0.y + f1.y) - (f2.y + f3.y)

        # Output 3: Y[k + 3]
        sub     t0, t1, a2          # Out3.x = (f0.x - f1.x) - (f2.y - f3.y)
        add     t1, t3, t5          # Out3.y = (f0.y - f1.y) + (f2.x - f3.x)

        # 指令重排写回 Y 数组
        slli    t2, s8, 3
        add     t2, s3, t2          # t2 = &Y[k]
        sw      a3, 0(t2)
        sw      a4, 4(t2)
        sw      a5, 8(t2)
        sw      a6, 12(t2)
        sw      a7, 16(t2)
        sw      t6, 20(t2)
        sw      t0, 24(t2)
        sw      t1, 28(t2)

        addi    s8, s8, 4
        blt     s8, s0, loop_p1_k

        # Pass 1 完成后交换 Ping-Pong 指针：当前有效数据在 Y (s3) 中
        mv      t0, s2
        mv      s2, s3              # s2 现在指向 Y (src)
        mv      s3, t0              # s3 现在指向 X (dst)

        # 更新 Pass 2 参数
        li      s5, 4               # s5 = i = 4
        li      s6, 64              # s6 = 8g = 256 / 4 = 64
        j       loop_r4_i_con

        # =========================================================================
        # ------------------ RADIX-4 PASS 2+ (常规 Ping-Pong) --------------------
        # =========================================================================
loop_r4_i:
        li      s7, 0               # s7 = j

loop_r4_j:
        mv      s8, s7              # s8 = k
        li      t0, 0               # t0 = 8w = 0
        slli    t1, s5, 3           # t1 = 8i
        slli    s9, s7, 3
        add     s9, s2, s9          # s9 = &src[k]
        add     s10, s9, t1         # s10 = &src[k + i]
        add     s11, s10, t1        # s11 = &src[k + 2i]

loop_r4_k:
        # ---------- 1. 加载 f0 = src[k] ----------
        lw      a0, 0(s9)           # a0 = f0.x
        lw      a1, 4(s9)           # a1 = f0.y

        # ---------- 2. 计算 f1 = src[k + i] * expTable[2w] ----------
        slli    t1, t0, 1
        add     t1, s4, t1          # t1 = &expTable[2w]
        lw      t3, 0(t1)           # t3 = E1.x
        lw      t4, 4(t1)           # t4 = E1.y
        lw      t5, 0(s10)          # t5 = X1.x
        lw      t6, 4(s10)          # t6 = X1.y

        # 指令重排交叉乘法与移位
        mul     t1, t5, t3
        mul     t2, t6, t4
        srai    t1, t1, 13
        srai    t2, t2, 13
        sub     a2, t1, t2          # a2 = f1.x

        mul     t1, t5, t4
        mul     t2, t6, t3
        srai    t1, t1, 13
        srai    t2, t2, 13
        add     a3, t1, t2          # a3 = f1.y

        # ---------- 3. 计算 f2 = src[k + 2i] * expTable[w] ----------
        add     t1, s4, t0          # t1 = &expTable[w]
        lw      t3, 0(t1)           # t3 = E2.x
        lw      t4, 4(t1)           # t4 = E2.y
        lw      t5, 0(s11)          # t5 = X2.x
        lw      t6, 4(s11)          # t6 = X2.y

        mul     t1, t5, t3
        mul     t2, t6, t4
        srai    t1, t1, 13
        srai    t2, t2, 13
        sub     a4, t1, t2          # a4 = f2.x

        mul     t1, t5, t4
        mul     t2, t6, t3
        srai    t1, t1, 13
        srai    t2, t2, 13
        add     a5, t1, t2          # a5 = f2.y

        # ---------- 4. 计算 f3 = src[k + 3i] * expTable[3w] ----------
        slli    t1, s5, 3
        add     t2, s11, t1         # t2 = &src[k + 3i]
        lw      t5, 0(t2)           # t5 = X3.x
        lw      t6, 4(t2)           # t6 = X3.y

        slli    t1, t0, 1
        add     t1, t1, t0          # t1 = 24w
        andi    t2, t1, 512
        slli    t2, t2, 22
        srai    t2, t2, 31          # t2 = -1 if t1 >= 512 else 0
        andi    t1, t1, 511
        add     t1, s4, t1          # t1 = &expTable[3w % 64]
        lw      t3, 0(t1)           # t3 = E3.x
        lw      t4, 4(t1)           # t4 = E3.y

        xor     t3, t3, t2
        sub     t3, t3, t2          # 符号修正
        xor     t4, t4, t2
        sub     t4, t4, t2

        mul     t1, t5, t3
        mul     t2, t6, t4
        srai    t1, t1, 13
        srai    t2, t2, 13
        sub     a6, t1, t2          # a6 = f3.x

        mul     t1, t5, t4
        mul     t2, t6, t3
        srai    t1, t1, 13
        srai    t2, t2, 13
        add     a7, t1, t2          # a7 = f3.y

        # ---------- 5. 组合蝶形并写回 dst 数组 ----------
        # 预计算 (f0 + f1) 和 (f0 - f1)
        add     t1, a0, a2          # t1 = f0.x + f1.x
        sub     t2, a0, a2          # t2 = f0.x - f1.x
        add     t3, a1, a3          # t3 = f0.y + f1.y
        sub     t4, a1, a3          # t4 = f0.y - f1.y

        # 预计算 (f2 + f3) 和 (f2 - f3)
        add     t5, a4, a6          # t5 = f2.x + f3.x
        sub     t6, a4, a6          # t6 = f2.x - f3.x
        add     a0, a5, a7          # a0 = f2.y + f3.y
        sub     a1, a5, a7          # a1 = f2.y - f3.y

        # 计算 Out0 ~ Out3
        add     a2, t1, t5          # dst[k].x
        add     a3, t3, a0          # dst[k].y
        add     a4, t2, a1          # dst[k + i].x
        sub     a5, t4, t6          # dst[k + i].y
        sub     a6, t1, t5          # dst[k + 2i].x
        sub     a7, t3, a0          # dst[k + 2i].y
        sub     t5, t2, a1          # dst[k + 3i].x
        add     t6, t4, t6          # dst[k + 3i].y

        # 写入 dst 数组
        slli    t1, s8, 3
        add     t1, s3, t1          # t1 = &dst[k]
        slli    t2, s5, 3           # t2 = 8i
        add     t3, t1, t2          # t3 = &dst[k + i]
        add     t4, t3, t2          # t4 = &dst[k + 2i]
        add     t2, t4, t2          # t2 = &dst[k + 3i]

        sw      a2, 0(t1)
        sw a3, 4(t1)
        sw      a4, 0(t3)
        sw a5, 4(t3)
        sw      a6, 0(t4)
        sw a7, 4(t4)
        sw      t5, 0(t2)
        sw t6, 4(t2)

        # 推进指针与索引
        addi    s8, s8, 1
        addi    s9, s9, 8
        addi    s10, s10, 8
        addi    s11, s11, 8
        add     t0, t0, s6

loop_r4_k_con:
        add     t1, s7, s5          # t1 = j + i
        blt     s8, t1, loop_r4_k

        slli    t0, s5, 2           # t0 = 4i
        add     s7, s7, t0
loop_r4_j_con:
        blt     s7, s0, loop_r4_j

        slli    s5, s5, 2           # i *= 4
        srli    s6, s6, 2           # 8g /= 4

        # 交换 Ping-Pong 指针 (src <-> dst)
        mv      t0, s2
        mv      s2, s3
        mv      s3, t0

loop_r4_i_con:
        slli    t0, s5, 1           # t0 = 2i
        blt     t0, s0, loop_r4_i

        # =========================================================================
        # -------------------- RADIX-2 PASS (尾部可能存在的轮次) -------------------
        # =========================================================================
        bge     s5, s0, check_final_copy

        li      s8, 0               # s8 = k
        mv      a1, s4              # a1 = &expTable[w]
        mv      a2, s2              # a2 = &src[k]
        slli    a3, s5, 3
        add     a3, s2, a3          # a3 = &src[k + i]

loop_r2_k:
        lw      t0, 0(a2)           # t0 = f0.x
        lw      t1, 4(a2)           # t1 = f0.y
        lw      a4, 0(a3)           # a4 = src[k + i].x
        lw      a5, 4(a3)           # a5 = src[k + i].y
        lw      a6, 0(a1)           # a6 = expTable[w].x
        lw      a7, 4(a1)           # a7 = expTable[w].y

        # 指令重排交叉乘法
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

        add     t4, t0, t2          # dst[k].x
        add     t5, t1, t3          # dst[k].y
        sub     t6, t0, t2          # dst[k + i].x
        sub     a0, t1, t3          # dst[k + i].y

        # 写回 dst 数组
        slli    t1, s8, 3
        add     t1, s3, t1          # t1 = &dst[k]
        slli    t2, s5, 3
        add     t2, t1, t2          # t2 = &dst[k + i]

        sw      t4, 0(t1)
        sw      t5, 4(t1)
        sw      t6, 0(t2)
        sw      a0, 4(t2)

        li      t4, 1
        slli    t4, t4, 10
        div     t4, t4, s0
        addi    s8, s8, 1
        add     a1, a1, t4
        addi    a2, a2, 8
        addi    a3, a3, 8

loop_r2_k_con:
        blt     s8, s5, loop_r2_k

        # Radix-2 结束后再次交换，确保最终指向最新结果
        mv      t0, s2
        mv      s2, s3
        mv      s3, t0

check_final_copy:
        # 如果最终数据落在 Y 中（即 s2 == &Y），需要把 Y 搬移复制回 X
        la      t0, X
        beq     s2, t0, fft_finish

        li      t1, 0               # t1 = i
copy_y_to_x:
        lw      t2, 0(s2)
        lw      t3, 4(s2)
        sw      t2, 0(t0)
        sw      t3, 4(t0)
        addi    t1, t1, 1
        addi    s2, s2, 8
        addi    t0, t0, 8
        blt     t1, s0, copy_y_to_x

fft_finish:
        # 4. 恢复栈帧并返回
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

# 特殊处理：N=2 时的 Radix-2 Pass 1（带 bit-reverse 与特判）
pass_radix2_only:
        lw      t0, 0(s2)           # X[0].x
        lw      t1, 4(s2)           # X[0].y
        lw      t2, 8(s2)           # X[1].x
        lw      t3, 12(s2)          # X[1].y

        add     t4, t0, t2
        add     t5, t1, t3
        sub     t6, t0, t2
        sub     a0, t1, t3

        sw      t4, 0(s2)
        sw      t5, 4(s2)
        sw      t6, 8(s2)
        sw      a0, 12(s2)
        j       fft_finish

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
