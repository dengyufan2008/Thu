# Week3 Homework

By Deng Yufan.

## 1. Finite Precision

a. $0, \frac{1}{8}, \frac{1}{4}, \frac{3}{8}, \frac{1}{2}, \frac{5}{8}, \frac{3}{4}, \frac{7}{8}, 1$.

b. No. Closet is $\frac{1}{4}$.

c. When $a=0$, $b=\frac{1}{40}$, $c=\frac{1}{20}$, we have $\text{round}(\text{round}(a+b)+c)=0$, $\text{round}(a+\text{round}(b+c))=\frac{1}{8}$.

## 2. Instruction-Level Parallelism

a.

Instruction | Dependency
:---: | :---:
$I_1$ | None
$I_2$ | $I_1$
$I_3$ | $I_2$
$I_4$ | None
$I_5$ | None
$I_6$ | $I_4$ and $I_5$
$I_7$ | $I_3$ and $I_6$

b.

Cycle | Instruction
:---: | :---:
Cycle 1 | $I_1$
Cycle 2 | $I_2$
Cycle 3 | $I_3$ and $I_4$
Cycle 4 | $I_5$
Cycle 5 | $I_6$
Cycle 6 | $I_7$

6 cycles.

c. 

Cycle | Instruction
:---: | :---:
Cycle 1 | $I_1$ and $I_4$
Cycle 2 | $I_2$ and $I_5$
Cycle 3 | $I_3$ and $I_6$
Cycle 4 | $I_7$

Speedup: 1.75x.

d.

4 Cycles. Since $I_1 \rarr I_2 \rarr I_3 \rarr I_7$ is a 4-length dependency chain.

## 3. Cache Memory

a.

Step | Request | Hit/Miss | Line 0 | Line 1 | Line 2 | Line 3
:---: | :---: | :---: | :---: | :---: | :---: | :---: 
1 | 0 | M | 0 | - | - | -
2 | 1 | M | 0 | 1 | - | -
3 | 2 | M | 0 | 1 | 2 | -
4 | 3 | M | 0 | 1 | 2 | 3
5 | 0 | H | 0 | 1 | 2 | 3
6 | 4 | M | 4 | 1 | 2 | 3
7 | 0 | M | 0 | 1 | 2 | 3
8 | 1 | H | 0 | 1 | 2 | 3
9 | 5 | M | 0 | 5 | 2 | 3
10 | 1 | M | 0 | 1 | 2 | 3

Hit rate: 20%.

b. Cache A: All miss. Hit rate: 0%.

Cache B: MHHH, MHHH. Hit rate: 75%.

The difference came from Cache B uses the data's locality.

c. Directed Mapped: All miss. Hit rate: 0%.

2-way set-associative: MMHHHH. Hit rate: 66.7%.

The difference came from 2-way set-associative is more flexible to cache data than directed mapped.

d. When P = 50ns:

Cache X: 1ns + 10% * 50ns = 6ns.

Cache Y: 2ns + 5% * 50ns = 4.5ns.

In general, Cache X: 0.1P+1 ns, cache Y: 0.05P+2 ns. Let two value equal, we have P=20ns. When $P \ge 20$ ns, Y is faster than X.

If miss penalty is low, improve hit rate will not help a lot, but this will rise hit time, make the cache slower.

## Declaration of AI Use

I used AI to translate part of words.
