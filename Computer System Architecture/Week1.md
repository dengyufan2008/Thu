# Week1 Homework

By Deng Yufan.

## Prob 1

### Part A

We have $G(\frac{y_i}{x_i}) = (\prod \frac{y_i}{x_i})^\frac{1}{n} = \frac{(\prod y_i)^\frac{1}{n}}{(\prod x_i)^\frac{1}{n}} = \frac{G(y_i)}{G(x_i)}$.

And $S_{C/B}=G(\frac{b_i}{c_i})=G(\frac{\frac{a_i}{c_i}}{\frac{a_i}{b_i}})=\frac{G(\frac{a_i}{c_i})}{G(\frac{a_i}{b_i})}=\frac{S_{C/A}}{S_{B/A}}$.

### Part B

a. One processor: $T\eta$. $N$ processor: $T(fN\eta + (1-f)\eta) = T(fN+1-f)\eta$. Speedup: $fN+1-f=1+f(N-1)$.

b. Strong: $\frac{1}{1-f+\frac{f}{N}}=\frac{N}{N-f(N-1)}$. Weak: $1+f(N-1)$. Weak/Strong: $\frac{1}{N}(1+f(N-1))(N-f(N-1))=\frac{1}{N}(N+f(1-f)(N-1)^2) \ge 1$. Only when $f=0$, $f=1$, or $N=1$, we have strong = weak.

### Part C

a. 1 Core: 0.64+3.2+0.32=4.16s.

$p$ Cores for $p>1$: (0.8+4)/p+0.32=4.8/p+0.32s.

2 Cores: 2.72s, speedup: ~1.53x.

4 Cores: 1.52s, speedup: ~2.74x.

8 Cores: 0.92s, speedup: ~4.52x.

b. Time for l/s: 1.52-0.64-0.32=0.56s. CPI for l/s: 0.56*4/1.28=1.75.

## Prob 2

a. t0=&A[i]. t1=&B[j]. s2=A[i]. t2=&A[i+4]. t0=A[i+4]+A[i]. t1=&B[j+1]. B[j+1]=A[i+4]+A[i].

So the single C statement is ``B[j + 1] = A[i + 4] + A[i];``.

b. This code only need 8 instructions.

```asm
slli    t0, s0, 2
add     t0, s6, t0        # t0 = &A[i]
lw      s2, 0(t0)         # s2 = A[i]
lw      s3, 16(t0)        # s3 = A[i + 4]
add     s2, s3, s2        # s2 = A[i + 4] + A[i]
slli    t1, s1, 2
add     t1, s7, t1        # t1 = &B[j]
sw      s2, 4(t1)         # B[j + 1] = s2 = A[i + 4] + A[i]
```

## Prob 3

a.
```asm
lw      rd, -1
sub     rd, rd, rs         # rd = -1 - rs = ~rs
```
```asm
lui     rd, BIG_HI         # BIG_HI = BIG[31...12] + BIG[11]
addi    rd, rd, BIG_LO     # BIG_LO = BIG[11...0]
```
```asm
sltiu   rd, rs, 1
```
```asm
sltu    rd, zero, rs
```
```asm
bge     rs2, rs1, L
```
This code uses ``rd`` as extra register.
```asm
lui     rd, OFFSET_HI      # OFFSET_HI = OFFSET[31...12] + OFFSET[11]
jalr    ra, rd, OFFSET_LO  # OFFSET_LO = OFFSET[11...0]
```

b.

```asm
mv      s1, zero           # s1 = l
subi    s2, a1, 1          # s2 = r
subi    s0, zero, 1        # s0 = i

loop:
add     t0, s1, s2
srai    t0, t0, 1          # t0 = m
add     t1, a0, t0
slli    t1, t1, 2          # t1 = &A[m]
lw      t2, 0(t1)          # t2 = A[m]

bne     t2, a2, elif
mv      s0, t0             # s0 = m
j       endloop

elif:
bge     t2, a2, else
addi    s1, t0, 1          # s1 = m + 1
j       endif

else:
subi    s2, t0, 1          # s2 = m - 1

endif:
bge     s2, s1, loop

endloop:
```

c.

```asm
subi    sp, 16
sw      ra, 12(sp)
sw      s0, 8(sp)
sw      s1, 4(sp)
sw      s2, 0(sp)

mv      s0, zero           # s0 = sum
mv      s1, zero           # s1 = i
mv      s2, a0             # s2 = n
j       cond

loop:
addi    s1, s1, 1          # s1++
jal     ra, putchar
add     s0, s0, s1         # s0 += s1
cond:
blt     s1, a0, loop

mv      a0, s0
lw      s2, 0(sp)
lw      s1, 4(sp)
lw      s0, 8(sp)
lw      ra, 12(sp)
addi    sp, 16
ret
```

## Prob 4

a. The assembly code is equivlant to following C code:

```c
// A = a0, N = a1
unsigned mnc = -1, mnw = 0, mnc2 = -1, mnw2 = None;  // 8 instr, 17 cyc
// mnc = s5, mnw = s4, mnc2 = s3, mnw2 = s2
for (int i = 0;;) {               // i = t0
  unsigned cnt = 0;               // cnt = t5, 2 instr, 4 cyc
  for (int j = 0; j != N; j++) {  // j = t1
    if (A[j] == A[i]) {           // 4 instr, 8 cyc
      cnt++;                      // 1 instr, 2 cyc
    }                             // 2 instr, 4 cyc, 2 cyc in new ISA
  }
  if (mnc >= cnt) {                                 // 2 instr, 3 cyc
    mnc2 = mnc, mnw2 = mnw, mnc = cnt, mnw = A[i];  // 5 instr, 9 cyc
  } else if (mnc2 >= cnt) {                         // 2 instr, 3 cyc
    mnc2 = cnt, mnw2 = A[i];                        // 2 instr, 4 cyc
  }
  for (i++;; i++) {     // 1 instr, 2 cyc
    if (i == N) {       // 1 instr, 2 cyc
      return;           // 1 instr, 1 cyc
    }
    if (A[i] != mnw) {  // 3 instr, 7 cyc
      break;
    }                   // 1 instr, 1 cyc
  }
}
```

So the code calculates the value that occurs the second least, and the occuring times of the value. Specially, s2 is the value and s3 is the occuring times.

b. When there are 150 $x$ and 150 $y$, where $x \ne y$, arranged as: $x, y, x, y, \cdots, x, y$, this assembly code will cost 8 + (2 + (4 + 2) * 300 + 1 * 150 + 2 + 5 + 1 + 1 + 3 + 1) * 300 - 3 = 589505 instructions. Method to calculate the number of instructions is marked in the C code, every time execute the statement will cost instructions as marked.

c. It costs 17 + (4 + (8 + 4) * 300 + 2 * 150 + 3 + 9 + 2 + 2 + 7 + 1) * 300 - 7 = 1178410 cycles. So 1178410 / 1.8G $\approx$ 654 $\mu$s = 6.54 $\times 10^{-4}$s.

d. It costs 17 + (4 + (8 + 2) * 300 + 2 * 150 + 3 + 9 + 2 + 2 + 7 + 1) * 300 - 7 = 998410 cycles. So 998410 / 1.8G * 1.25 $\approx$ 693 $\mu$s = 6.93 $\times 10^{-4}$s. Speedup (in fact, slowdown): 654 / 693 $\approx$ 0.94x.
