# Homework Set 1

By Deng Yufan.

## Prob 1: Number Types and Ranges

Assume $A$ and $B$ are both 32-bit signed integers. Prove the following necessary and sufficient conditions to detect overflow of $A+B$: let $[A+B]$ be the result of $A+B$ represented in 32 bits (bit 31 to bit 0), i.e., after throwing away bit 32. Overflow occurs if and only if $A>0$, $B>0$, $[A+B]<0$; or $A<0$, $B<0$, $[A+B]>0$.

> Since $A, B \in [-2^{31}, 2^{31})$, then $A + B \notin [-2^{31}, 2^{31})$ iff $0<A, B < 2^{31} \le A+B$ or $0 > A, B \ge -2^{31} > A+B$.
>
> In first possibility, we have $2^{31} \le A+B < 2^{32}$, which iff sign bit is 1, thus $[A+B] < 0$.
>
> In second possibility, we have $-2^{32} \le A+B < -2^{31}$, after throwing away bit 32, $0 \le [A+B] < 2^{31}$, which iff sign bit is 0, thus $[A+B] \ge 0$.

---

Identify the bugs in the following pieces of C code. First explain why the code does not follow the expected behavior. Then provide the correct code with minimum changes.

a.
```c
// Loop over an array in the inverse order
for (unsigned int i = 9; i >= 0; i--) {
  printf("data %u = %d\n", i, a[i]);
}
```

> When ``i == 0``, perform ``i--`` will make ``i`` become $2^{32}-1$, and never break the loop.
>
> ```c
> for (int i = 9; i >= 0; i--) {
>   printf("data %u = %d\n", i, a[i]);
> }
> ```

b.
```c
// Check value range; output 1 if and only if value is > 10
constexpr unsigned int lim = 10;
int check_data(int val) {
  return val > lim ? 1 : 0;
}
```

> When ``val < 0``, compare ``val`` and ``lim`` will first turn ``val`` into uint, so always have ``val > lim``.
>
> ```c
> constexpr int lim = 10;
> int check_data(int val) {
>   return val > lim ? 1 : 0;
> }
> ```

c.
```c
// Check if buffer has enough space to keep data
void copy_in(void* buffer, int buffer_size,
             void* data, unsigned int data_size) {
  if (buffer_size – data_size >= 0) memcpy(buf, data, data_size);
}
```

> Likewise, when doing the minus, ``buffer_size`` will turned into uint, so the result always be non-neg.
>
> ```c
> void copy_in(void* buffer, int buffer_size,
>              void* data, unsigned int data_size) {
>   if (buffer_size >= data_size) memcpy(buf, data, data_size);
> }
> ```

## Prob 2. Assembly Code

Write short RISC-V assembly sequences with no more than 3  instructions for the following functionalities. Assume a 32-bit machine and ``sizeof(int) == 4``.

a. Get the value of ``A[3][4]`` into register ``x2``, where ``A`` is a multi-dimensional array ``int A[8][8]``, whose starting address is stored in register ``x1``.

> ```asm
> lw x2 112(x1)
> ```

b. Get the value of ``A[3][4]`` into register ``x2``, where ``A`` is a multi-level array with element type as int, and the starting address of its first level is stored in register ``x1``.

> ```asm
> lw x2 12(x1)
> lw x2 16(x2)
> ```

---

On a 64-bit RISC-V machine, assume the standard LP64 data model and natural alignment. Choose the correct assembly code to load ``nptr->val`` into register ``x4``, where ``nptr`` is a pointer to a linked list node defined as below, and its value (i.e., the address of the node it points to) is stored in register ``x3``.

```c
struct Node {
  char flag;
  int32_t val;
  Node* next;
  short tag;
};
```

> ``lw x4, 4(x3)``

If then in a function, we declare an array using ``Node arr[10];``, how many bytes do we consume on the heap and the stack, respectively?

> heap: 0 bytes, stack: 240 bytes.

Now suppose we want to minimize the total size of ``struct Node`` by reordering its fields. Give one such ordering. Under your reordered layout, how many bytes would ``Node arr[10];`` allocate on the heap and on the stack, respectively?

> ```c
> struct Node {
>   Node* next;
>   int32_t val;
>   short tag;
>   char flag;
> };
> ```
> heap: 0 bytes, stack: 160 bytes.

---

Write out the C code that is functionally equivalent to the following RISC-V assembly.

```asm
    j C
L:  slli x4, x1, 2
    add x4, x4, x2
    lw x4, 0(x4)
    add x3, x3, x4
    addi x1, x1, -1
C:  bne x1, x0, L
```

> ```c
> for (; i != n; i--) {
>   sum += a[i];
> }
> ```
> Where ``n`` is ``x0``, ``i`` is ``x1``, ``a`` is ``x2``, ``sum`` is ``x3``.

---

Fix the following buggy assembly code, which tries to calculate in register ``x3`` the maximum value of an array of 32-bit integers, whose starting address is stored in register ``x1``. The total number of integers in the array is stored in register ``x2``. You may assume ``x2 > 0``. You should not increase the number of instructions in this code.

```asm
    lw x3, 0(x1)
    addi x4, x0, 0
L:  beq x4, x2, E
    lw x5, 0(x1)
    blt x3, x5, U
    add x3, x5, x0
U:  addi x4, x4, 1
    addi x1, x1, 1
    j L
E:
```

> ```asm
>     lw x3, 0(x1)
>     addi x4, x0, 0
> L:  beq x4, x2, E
>     lw x5, 0(x1)
>     blt x5, x3, U
>     add x3, x5, x0
> U:  addi x4, x4, 1
>     addi x1, x1, 4
>     j L
> E:
> ```

## Problem 3: Processor Performance

With a fixed budget of chip area, now we would like to decide between two processor architectures: 1) one big and faster core, vs. 2) $N$ parallel small cores but each is slower. As you may expect, which architecture is better would depend on the available parallelism in the programs.

Assume the total area is $A$. When we use a certain amount of area $a$ to implement a core, the core offers a performance (in terms of number of instructions executed per second) proportional to the square root of the area, e.g., $\eta \sqrt a$ where $\eta$ is a constant coefficient.

Further assume that the program is composed of serial and perfectly parallel portions. The serial portion can only use a single core (no matter big or small), and the parallel portion can be executed on as many cores as available, and enjoy a linear speedup with respect to the number of cores.

Under such scenario, for different values of $N$, calculate the minimum fraction of the parallel portion, $f$, that makes the configuration with multiple small cores perform better than that with a single big core. Fill in the table below. You must show your calculation process details in addition to the table.

Number of small cores $N$ | Parallel portion $f$
:---: | :---:
2 | $2-\sqrt 2 \approx 58.6\%$
4 | $\frac{2}{3} \approx 66.7\%$
8 | $\frac{8-2 \sqrt 2}{7} \approx 73.9\%$

> One core time cost: $1 / \sqrt A$.
>
> Multi core time cost: $f / \sqrt {AN} + (1-f) / \sqrt {A/N} = \sqrt{N/A}(f/N + 1-f)$
>
> When $\sqrt{N/A}(f/N + 1-f) \le 1 / \sqrt A$, we have $f \ge \frac{N-\sqrt N}{N-1} = 1 - \frac{\sqrt N - 1}{N - 1}$.
>
> Then we apply $N=2, 4, 8$ to get answer in the chart.

---

Now assume a given program has 70% parallel portion, i.e., $f = 70\%$. What is the speedup (or slowdown) of 8 small cores vs. 1 big core? The speedup of A vs. B is defined as the execution time of $B$ $/$ the execution time of $A$.

> Apply formula we just derived, we have multi core time cost = $\frac{31 \sqrt 2}{40}$ if $A=1$. So slowdown = $\frac{20 \sqrt 2}{31} < 1$.

---

With the same program as in part 2, consider a hybrid design where we use half of the chip area to build a big core, and the rest half to build 4 small cores. Assume the serial portion runs on the big core, and the parallel portion only runs on the 4 small cores. What are the speedups this hybrid design can achieve, compared to the two onfigurations in part 2, respectively?

> Hybrid time cost: $2f/\sqrt{AN} + (1-f)/\sqrt{A/2} = \sqrt{2/A}(\frac{\sqrt 2 f}{\sqrt N} + 1-f)$.
>
> Apply, we have hybrid time cost = $\frac{13 \sqrt 2}{20}$. Speedup to one core = $\frac{10 \sqrt 2}{13} > 1$, to multi core = $\frac{31}{26} > 1$.

## Problem 4: Cache Organization and Performance

In this problem, use 1k = 1024, 1M = $2^{20}$, 1G = $2^{30}$, and so on.

Assume we would like to build a cache to be able to store 32 kB of data in a system with 48-bit memory address. Each entry contains a valid bit, a tag, and the data block, as we discussed in the lecture. Ignore other metadata fields. For each of the following configurations, how many SRAM bits do you need to build such a cache? You need to include all data, tags, and valid bits in your result, because all these fields need to use SRAM to implement. You can represent your results in kbits.

a. 64-byte block size, 4-way set associative.

> #Block: 512. #Set: 128.
> 
> Offset: 6bit, Index: 7bit, Tag: 35bit.
>
> Space: 512*(35+1) bit + 32 kB = 18 kbit + 256 kbit = 274 kbit.

b. 8-byte block size, 4-way set associative.

> #Block: 4096. #Set: 1024.
> 
> Offset: 3bit, Index: 10bit, Tag: 35bit.
>
> Space: 4096*(35+1) bit + 32 kB = 144 kbit + 256 kbit = 400 kbit.

c. 64-byte block size, 16-way set associative.

> #Block: 512. #Set: 32.
> 
> Offset: 6bit, Index: 5bit, Tag: 37bit.
>
> Space: 512*(37+1) bit + 32 kB = 19 kbit + 256 kbit = 275 kbit.

---

In the lecture we claim that using a multi-level hierarchy of caches is better than using a single cache. Compare the AMAT values of the following three configurations to verify the above conclusion. The memory access latency is 100 ns in all cases. All cases run the same program.

a. One level of a small cache, hit latency = 1 ns, hit rate = 60%.

b. One level of a large cache, hit latency = 20 ns, hit rate = 90%.

c. Two levels, with the first level the same as a), and the second level the same as b). You will need to first figure out the hit rates for the two levels based on known information.

> a. AMAT = 1ns + 40% * 100ns = 41ns.
>
> b. AMAT = 20ns + 10% * 100ns = 30ns.
>
> c. Hit rate = 1 - 10% * 40% = 96%.
> 
> AMAT = 1ns + 40% * (20ns + 10% * 100ns) = 13ns.

---

Consider a full system with a processor, a single cache, and an off-chip memory. We execute different programs, i.e., sequences of instructions, on this system. The processor follows the simple design we discussed in the lecture, i.e., sequentially executing each instruction before moving to the next one. All instructions except loads and stores (i.e., memory access instructions) need 1 unit time (i.e., 1 processor clock cycle). Memory access instructions, if hitting in the cache, also cost 1 unit time. The off-chip memory has a latency of 100 unit time.

We are interested in the slowdown caused by the memory hierarchy, which is measured as the ratio of the execution time on the real system vs. the execution time on an unrealistic perfect memory hierarchy with 100% hit rate. Prove that, for any program, this slowdown depends linearly on the ratio of its cache misses and instruction count.

The above ratio is usually called MPKI, i.e., misses per kilo instructions. Based on your proof, MPKI is usually a better metric than miss rate to analyze performance.

> Assume there is $n$ instructions, and there is $m$ misses.
> 
> Real sys time: $n + 100m$ unit.
>
> Ideal sys time: $n$ unit.
>
> Ratio: $1 + 100 \frac{m}{n}$.
>
> Slowdown: $100 \frac{m}{n}$.
>
> Obviously slowdown is linearly depend on misses per instructions.

---

Now we would like to predict the cache behavior of C code for potential code optimization. Given the following code:

```c
int x[2][128];
int sum = 0;
for (int i = 0; i < 128; i++) {
  sum += x[0][i] * x[1][i];
}
```

Assume ``sizeof(int) == 4``, array ``x`` begins at memory address ``0x10000000`` and is in row-major order. The only memory accesses are to the entries of ``x``, and all other variables are in registers.

Given the following cache configurations, estimate the miss rates. The cache is initially empty in each case.

a. The cache is 512 bytes, direct-mapped, with 16-byte block size.

> The array start at ``0x10000000`` which is a beginning of block.
>
> ``x[0]`` starts at ``0x10000000``, ``x[1]`` starts at ``0x10000200``. #Block = 32, so offset is the last 4 bit, and index is the following 5 bit. Thus ``x[0][0]`` and ``x[1][0]`` are in the same index.
>
> After miss to load ``x[0][0]`` and ``x[1][0]``, the block start with ``x[1][0]`` will take place of block start with ``x[0][0]``. So miss rate will be 100%.

b. The cache capacity is doubled to 1024 bytes from a). Other parameters do not change.

> This case index of ``x[0][0]`` and ``x[1][0]`` are ``0B000000`` and ``0B100000``, so won't kick each other. A block contains 4 int, then miss rate = 25%.

c. The cache is 512 bytes, 2-way set associative using an LRU policy, and with 16-byte block size.

> Even though ``x[0][0]`` and ``x[1][0]`` are in same index, but a set contain 2 set, and kick the old one will take no effect. So miss rate = 25%.

d. In c), will a larger cache size help to reduce the miss rate? Why or why not?

> Will not. In fact, this program don't need too many blocks or sets, only two blocks in the same set which store ``x[0][i]`` and ``x[1][i]`` fit the need.

e. In c), will a larger block size help to reduce the miss rate? Why or why not?

> Will. If block size is larger, can take in more integers in a row, thus miss rate will reduce.

---

Given a set-associativity cache, is an LRU replacement policy (i.e., choosing the least recently used block to evict in the set) always better than a random policy (i.e., randomly choosing one block in the set to evict)? If yes, try to prove your conclusion; if not, please provide a counter-example.

> Not. Following is a example. Consider code:
>
> ```c
> int a[3][128];
> long long s = 0;
> for (int i = 0; i < 128; i++) {
>   s += (a[0][i] & a[1][i]) ^ a[2][i];
> }
> ```
>
> When the cache is 2-way set assoc., every kick will kick the about-to-used block, so miss rate = 100%. But randomly kick will have 50% possibility to keep the about-to-used block, then miss rate will be about 50%.

## Problem 5: Processes and Scheduling

Explain whether the output sequences are valid with the given piece of code.

a.

```c
printf("L0\n");
if (fork() == 0) {
  printf("L1\n");
  if (fork() == 0) {
    printf("L2\n");
  }
}
printf("Bye\n");
```

Candidate output sequences:

```
i.       ii.      iii.     iv.
L0     | L0     | L0     | L0
Bye    | Bye    | L1     | Bye
L1     | L1     | L2     | L1
Bye    | L2     | Bye    | L2
Bye    | Bye    |        |
L2     | Bye    |        |
```

> i. Since there are 3 ``Bye`` but only 2 ``L.`` before the last ``Bye``, it's invalid.
>
> ii. Valid. Possible ending order: Main-process, sub-sub-process, sub-process.
>
> iii. Valid. Possible ending order: Sub-sub-process, main and sub-process (terminated by external, before ``Bye``).
>
> iv. Valid. Possible ending order: Main-process (then terminate sub-process and sub-sub-process before ``Bye``).
>
> If we assume that the program will not termininated by external, then iii. and iv. is invalid, since there is only 1 ``Bye``.

b.

```c
int child_status;
pid_t c1, c2;

printf("S\n");

c1 = fork();
if (c1 == 0) {
  printf("C1\n");
  exit(0);
}

c2 = fork();
if (c2 == 0) {
  printf("C2\n");
  exit(0);
}

printf("P0\n");
waitpid(c1, &child_status, 0);
printf("P1\n");
```

Candidate output sequences:

```
i.      ii.     iii.    iv.
S     | S     | S     | S
P0    | C1    | P0    | C2
C2    | P0    | P1    | P1
C1    | P1    | C1    | P0
P1    | C2    | C2    | C1
```

> i. Valid. Possible ending order: sub2, sub1, main.
>
> ii. Valid. Possible ending order: sub1, sub2, main.
>
> iii. Invalid. ``C1`` can't appear after ``P1``.
>
> iv. Invalid. ``P1`` can't appeat before ``P0``.

---

Assume we have four jobs, $P_i$, $i = 1, 2, 3, 4$, with the execution time of 53, 8, 68,
24, respectively. We compare the three scheduling policies, FCFS, RR (Round Robin), and SJF.

a. Fill in the table below to calculate the wait time of each job, as well as the average wait time, under different policies. The "worst FCFS" assumes the arrival order of the four jobs that results in the worst-case average wait time. The time quantum of RR is given by the value of $q$. All RR policies assume the arrival order of $P_1$ to $P_4$. Assume zero context switch overhead.

> Policy | $P_1$ | $P_2$ | $P_3$ | $P_4$ | Average
> :---: | :---: | :---: | :---: | :---: | :---:
> FCFS | 0 | 53 | 61 | 129 | 60.75
> Worst FCFS | 68 | 145 | 0 | 121 | 83.5
> SJF | 32 | 0 | 85 | 8 | 31.25
> RR (q=5) | 82 | 20 | 85 | 58 | 61.25
> RR (q=8) | 80 | 8 | 85 | 56 | 57.25
> RR (q=10) | 82 | 10 | 85 | 68 | 61.25
> RR (q=20) | 72 | 20 | 85 | 88 | 66.25
>
> Best q: 8.

b. Now assume a context switch overhead of 2 unit time. This overhead is only paid when the next job to run is different from the current running job. Also, the first running job starts at time 0 without a context switch overhead at the very beginning. Re-fill the table below for the RR policies. Does the best time quantum choice change?

> Policy | $P_1$ | $P_2$ | $P_3$ | $P_4$ | Average
> :---: | :---: | :---: | :---: | :---: | :---:
> RR (q=5) | 136 | 30 | 141 | 90 | 99.25
> RR (q=8) | 112 | 10 | 119 | 74 | 78.75
> RR (q=10) | 110 | 12 | 115 | 86 | 80.75
> RR (q=20) | 86 | 22 | 101 | 100 | 77.25
>
> Best q: 20. Changed.
