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

> d. ``lw x4, 8(x3)``

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
