# Lab 2: Scaled Dot-Product Attention on Raspberry Pi 4B

In this lab you will implement and progressively optimize **Scaled Dot-Product Attention (SDPA)** -- the core computational kernel of the Transformer architecture that powers modern large language models.

You will work through four tasks, each building on the previous:

| Task | Description | Key Concept | Points |
|------|-------------|-------------|--------|
| 1 | Naive scalar SDPA | Algorithm correctness, tensor indexing | 15 |
| 2 | Online (blocked) softmax | FlashAttention insight, numerical stability | 20 |
| 3 | ARM NEON SIMD | Vectorization, instruction-level parallelism | 25 |
| 4 | Multi-threaded SDPA | pthreads, work partitioning, cache optimization | 25 |
| Report | Analysis & discussion | Performance evaluation | 15 |
| **Total** | | | **100** |

**Target platform**: Raspberry Pi 4B (4x Cortex-A72 @ 1.5 GHz, ARMv8-A, 128-bit NEON SIMD, 32 KB L1d per core, 1 MB shared L2).

## 0. Setup

### Prerequisites

- GCC with C11 support (pre-installed on Raspberry Pi OS)
- Python 3 with NumPy: `pip3 install numpy` (if not already installed)
- (Optional) PyTorch for upper-bound benchmarks: installed automatically by `make upper_bound`

### Generate test data

> **You must run this before building or testing any task.**

```bash
make gen_data
```

This creates four datasets (`tiny`, `small`, `medium`, `large`) in `data/` with binary Q, K, V tensors and pre-computed reference outputs (~10 MB total). The generated binary files are not tracked by git; you must regenerate them after cloning.

### Build and test a task

```bash
make task1            # compile Task 1
make check_task1      # run correctness check
```

### Build all tasks and grade

```bash
make all              # compile all four tasks
make check            # correctness check for all tasks
make grade            # full correctness + performance evaluation
```

## 1. Background

### Scaled Dot-Product Attention

Given query matrix **Q**, key matrix **K**, and value matrix **V**:

```
Attention(Q, K, V) = softmax(Q @ K^T / sqrt(D)) @ V
```

In this lab, the tensors have 4 dimensions: **[B, H, M/N, D/DV]** where:
- **B** = batch size
- **H** = number of attention heads
- **M** = query sequence length, **N** = key/value sequence length
- **D** = dimension of Q and K per head, **DV** = dimension of V per head

For each query row `(b, h, m)`:
1. Compute `scores[j] = Q[b,h,m,:] . K[b,h,j,:] * scale` for j in [0, N)
2. Apply softmax over `scores[0..N-1]` to get `weights[0..N-1]`
3. Compute `out[b,h,m,:] = sum_j weights[j] * V[b,h,j,:]`

The `scale` factor is typically `1 / sqrt(D)`.

### The Numerical Stability Problem

A naive softmax computes `exp(x_i) / sum(exp(x_j))`.  When scores are large, `exp()` overflows to infinity.  The standard fix subtracts the maximum:

```
max_s = max(scores)
weights[j] = exp(scores[j] - max_s) / sum_k exp(scores[k] - max_s)
```

This requires **two passes** over all N scores: one to find the max, one to compute exp and sum.

### Online Softmax (Task 2)

The key insight of FlashAttention is that we can compute the softmax **incrementally** by processing K/V in small blocks and maintaining running statistics:

- `m_prev`: running maximum of all scores seen so far
- `l_prev`: running sum of `exp(score - m_prev)` for all scores seen so far
- `acc[DV]`: running weighted sum of V rows

When processing a new block with block maximum `block_max`:
1. Compute `m_new = max(m_prev, block_max)`
2. Rescale previous accumulation: `alpha = exp(m_prev - m_new)`, then `acc *= alpha` and `l_prev *= alpha`
3. For each score `s` in the block: `w = exp(s - m_new)`, accumulate `l_prev += w` and `acc += w * V[row]`

At the end: `out = acc / l_prev`

This uses only `O(kv_block + DV)` memory per row instead of `O(N)`.

### ARM NEON SIMD (Task 3)

The Cortex-A72 processor in the Raspberry Pi 4B has 128-bit NEON SIMD units that can process 4 `float32` values in parallel.  Key intrinsics:

| Intrinsic | Description |
|-----------|-------------|
| `float32x4_t vld1q_f32(const float *p)` | Load 4 floats |
| `void vst1q_f32(float *p, float32x4_t v)` | Store 4 floats |
| `float32x4_t vdupq_n_f32(float a)` | Broadcast scalar to all 4 lanes |
| `float32x4_t vfmaq_f32(acc, a, b)` | Fused multiply-add: `acc + a * b` |
| `float32x4_t vmulq_f32(a, b)` | Element-wise multiply |
| `float32x4_t vaddq_f32(a, b)` | Element-wise add |
| `float vaddvq_f32(float32x4_t v)` | Horizontal sum (all 4 lanes) |

**Optimization strategy**: Process 16 elements per loop iteration (4 NEON registers x 4 floats) using 4 independent accumulators to hide the FMA pipeline latency (~4 cycles on Cortex-A72).

Include `<arm_neon.h>` to use NEON intrinsics.

## 2. Task 1: Naive SDPA (15 pts)

**File to edit**: `src/task1.c`

Implement `sdpa_naive()` -- a straightforward, single-threaded SDPA using scalar C code.

### Algorithm

For each query row `(b, h, m)`:
1. **Compute scores**: `scores[j] = dot(Q_row, K[j]) * scale` for j = 0..N-1
2. **Softmax**: Find max, compute `exp(score - max)`, sum, normalize
3. **Weighted V sum**: `out[dv] = sum_j weights[j] * V[j, dv]` for dv = 0..DV-1

### Tensor indexing

Use the provided `qkv_offset()` helper to compute the starting offset of a row:

```c
const float *q_row  = params->q + qkv_offset(b, h, m, H, M, D);
const float *k_base = params->k + qkv_offset(b, h, 0, H, N, D);
const float *v_base = params->v + qkv_offset(b, h, 0, H, N, DV);
float       *o_row  = params->out + qkv_offset(b, h, m, H, M, DV);

// K row j starts at: k_base + j * D
// V row j starts at: v_base + j * DV
```

### Build & test

```bash
make task1
make check_task1
```

### Grading

- 15 pts for correctness (output matches reference within tolerance `1e-4`).
- No performance requirement for this task.

## 3. Task 2: Online Softmax (20 pts)

**File to edit**: `src/task2.c`

Implement `sdpa_online()` using the online (blocked) softmax algorithm described in the Background section.

### Key differences from Task 1

- Process K/V in blocks of `params->kv_block` rows at a time
- Maintain running state `(m_prev, l_prev, acc[DV])` across blocks
- Workspace is only `kv_block + DV` floats (not N floats)

### Pseudocode

```
memset(acc, 0, DV)
m_prev = -infinity
l_prev = 0

for kb = 0 to N step kv_block:
    cur = min(kv_block, N - kb)

    // Phase A: compute scores, find block max
    for t = 0 to cur:
        scores[t] = dot(q_row, K[kb+t]) * scale
    block_max = max(scores[0..cur-1])

    // Phase B: online softmax update
    m_new = max(m_prev, block_max)
    alpha = isfinite(m_prev) ? exp(m_prev - m_new) : 0
    acc *= alpha
    l_new = l_prev * alpha
    for t = 0 to cur:
        w = exp(scores[t] - m_new)
        l_new += w
        acc += w * V[kb+t]
    m_prev = m_new
    l_prev = l_new

// Final normalization
out = acc / l_prev
```

### Build & test

```bash
make task2
make check_task2
```

### Grading

- 10 pts correctness
- 10 pts performance: your implementation should not be significantly slower than Task 1 (speedup >= 0.9x). The online approach typically runs at comparable speed or faster due to better cache utilization.

## 4. Task 3: NEON SIMD (25 pts)

**Files to edit**: `src/simd.c` (NEON helper functions) + `src/task3.c` (attention kernel)

### Part A: NEON helper functions (`src/simd.c`)

Implement NEON-optimized versions of these 6 functions:

| Function | Description |
|----------|-------------|
| `dot_f32_neon(a, b, n)` | Dot product of two vectors |
| `dot4_f32_neon(q, k0..k3, d, s0..s3)` | 4 dot products at once (share Q loads) |
| `vec_scale_f32_neon(x, a, n)` | In-place scale: `x *= a` |
| `vec_fma_f32_neon(dst, src, a, n)` | Fused multiply-add: `dst += a * src` |
| `vec_fma4_f32_neon(dst, x0,a0, ..., x3,a3, n)` | 4-way FMA |
| `vec_copy_scaled_f32_neon(dst, src, a, n)` | Copy with scale: `dst = a * src` |

Each function starts with a scalar fallback that produces correct results.  Replace each with a NEON implementation using the pattern:

```c
#if defined(__aarch64__)
    int i = 0;
    float32x4_t av = vdupq_n_f32(a);  // broadcast scalar

    for (; i + 15 < n; i += 16) {     // main loop: 16 elements
        // Load, compute, store using NEON intrinsics
        // Use 4 accumulators to hide pipeline latency
    }
    for (; i < n; ++i) {              // scalar tail
        // Handle remaining elements
    }
#else
    // Scalar fallback
#endif
```

**Tip**: Implement and test one function at a time.  The scalar fallbacks ensure correctness while you work on NEON.

### Part B: NEON attention kernel (`src/task3.c`)

Implement `attention_row_neon()` -- the same online softmax as Task 2, but calling your NEON helpers:
- Use `dot4_f32_neon` to compute 4 scores at a time
- Use `vec_fma4_f32_neon` to accumulate 4 weighted V rows at a time
- Use `vec_scale_f32_neon` for rescaling
- Use `vec_copy_scaled_f32_neon` for final normalization
- Fall back to single-row versions (`dot_f32_neon`, `vec_fma_f32_neon`) for remainders

### Build & test

```bash
make task3
make check_task3
```

### Grading

- 10 pts correctness
- 15 pts performance: speedup S = time(Task 1) / time(Task 3).
  Points = `(min(S, 3) - 1) / 2 * 15`.  Full marks at S >= 3x.

## 5. Task 4: Multi-Threaded SDPA (25 pts)

**File to edit**: `src/task4.c`

Implement `sdpa_threaded()` -- distribute query rows across multiple pthreads, each using your NEON-accelerated kernel from Task 3.

### Design

The B\*H\*M query rows are independent and can be processed in parallel.  However, **how you distribute rows across threads matters enormously** for performance:

**Naive approach** (DON'T do this): Give each thread a contiguous block of all B\*H\*M rows.  With 4 threads, each thread works on a different attention head simultaneously.  Each head's K+V working set is ~256 KB, so 4 heads need 1 MB in the shared L2 cache -> **cache thrashing**.  Result: 4 threads is *slower* than 2.

**Cache-friendly approach** (DO this): Have all threads cooperate on the **same head** at a time, splitting the M query rows among them.  Use `pthread_barrier_wait()` to synchronize between heads:

```
for each (b, h):                        // iterate over heads
    thread 0 processes rows [0, M/4)     // all threads share the same K, V
    thread 1 processes rows [M/4, M/2)   // in L2 cache (only 256 KB)
    thread 2 processes rows [M/2, 3M/4)
    thread 3 processes rows [3M/4, M)
    pthread_barrier_wait(&barrier)       // wait for all threads to finish this head
```

This keeps only **one head's K+V (256 KB)** in the 1 MB shared L2 at any time, enabling good scaling to 3-4 threads.

### Implementation steps

1. Define a `WorkerArgs` struct with: SDPAParams pointer, thread id, row range, workspace pointers
2. Copy your NEON attention row function from Task 3 (or refactor to share)
3. Write `worker_entry()`:
   - (Optional) Pin to CPU core: `pthread_setaffinity_np`
   - For each `(b, h)` head: process assigned M rows, then barrier-sync
4. In `sdpa_threaded()`:
   - Allocate `num_threads` pthreads and WorkerArgs
   - Allocate per-thread workspace (use `aligned_alloc_f32`)
   - Initialize `pthread_barrier_t`
   - Launch threads with `pthread_create`, join with `pthread_join`
   - Free everything

### CPU core pinning (recommended)

```c
#ifdef __linux__
if (p->pin_threads_to_cores) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(tid % num_cpus, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
}
#endif
```

This improves cache locality by keeping each thread on a dedicated core.

### Useful pthread references

- [`pthread.h` overview](https://man7.org/linux/man-pages/man0/pthread.h.0p.html) -- list of all POSIX thread functions
- [`pthread_create`](https://man7.org/linux/man-pages/man3/pthread_create.3.html) -- create a new thread
- [`pthread_join`](https://man7.org/linux/man-pages/man3/pthread_join.3.html) -- wait for a thread to finish
- [`pthread_barrier_init`](https://man7.org/linux/man-pages/man3/pthread_barrier_init.3p.html) / [`pthread_barrier_wait`](https://man7.org/linux/man-pages/man3/pthread_barrier_wait.3p.html) -- synchronize threads at a barrier
- [`pthread_setaffinity_np`](https://man7.org/linux/man-pages/man3/pthread_setaffinity_np.3.html) -- pin a thread to specific CPU cores

### Build & test

```bash
make task4
make check_task4

# Test with different thread counts:
./task4 --data data/large/meta.txt --threads 1
./task4 --data data/large/meta.txt --threads 2
./task4 --data data/large/meta.txt --threads 4 --pin-cores
```

### Grading

- 10 pts correctness
- 15 pts performance: speedup S = time(Task 1) / time(Task 4).
  Points = `(min(S, 6) - 1) / 5 * 15`.  Full marks at S >= 6x.
  
  **Note**: On the Pi 4B, the optimal thread count may not be 4 due to memory bandwidth and L2 cache constraints. Experiment with different thread counts and report your findings. This is expected behavior, not a bug!

## 6. Report (15 pts)

Write a report (PDF) covering:

1. **Design description**: Briefly explain your approach for each task.  For Task 2, describe the online softmax algorithm in your own words.  For Task 4, describe how you partition work across threads.

2. **Performance results**: Include a table and plot showing:
   - Execution time (ms) and speedup for all four tasks on the `large` dataset
   - For Task 4: speedup vs. number of threads (1, 2, 3, 4)
   - (Optional) Effect of different `kv_block` values on Task 2/3 performance

3. **Analysis**: Discuss:
   - Why does Task 2 perform similarly to Task 1 (or better/worse)?
   - How much speedup does NEON provide and why?
   - Does the speedup from 1 to 4 threads scale linearly? Why or why not?
   - What is the theoretical peak speedup on 4 cores?  How close do you get?
   - (Optional) Run `make upper_bound` and compare your Task 4 against PyTorch's `scaled_dot_product_attention`.  Why does SDPA achieve only a small fraction of theoretical peak FLOPS? (Hint: think about memory bandwidth vs. compute.  What is the arithmetic intensity of attention?)

## 7. Upper-Bound Comparison (Optional)

Compare your implementation against PyTorch's optimized `scaled_dot_product_attention`:

```bash
make upper_bound
```

This will automatically install PyTorch from the Tsinghua mirror if it is not already installed, then benchmark against:
1. **PyTorch SDPA** -- `torch.nn.functional.scaled_dot_product_attention`, specifically optimized for this operator
2. **NumPy** (matmul + softmax) -- for baseline comparison
3. **Theoretical peak** of the Cortex-A72 (4 cores @ 1.5 GHz, 96 GFLOPS -- unachievable)

SDPA is **memory bandwidth bound** on the Pi 4B, not compute-bound, which is why even PyTorch achieves only a small fraction of theoretical peak.  Your online-softmax approach avoids materializing the full N\*N attention matrix, which is a significant advantage at larger sequence lengths.

## Grading Summary

| Component | Points |
|-----------|--------|
| Task 1: Correctness | 15 |
| Task 2: Correctness (10) + Performance (10) | 20 |
| Task 3: Correctness (10) + Performance (15) | 25 |
| Task 4: Correctness (10) + Performance (15) | 25 |
| Written Report | 15 |
| **Total** | **100** |

Performance speedups are measured relative to your Task 1 on the `large` dataset.  We may change the random seed in `data/gen_data.py` and run your program multiple times to get the average.

## Submission

You should use `git.tsinghua.edu.cn` to manage your project. You may refer to the discussion session or Lab 1 documentation for setup instructions. If you don't have `git.tsinghua.edu.cn` permissions, you can also use services like GitHub or Gitee; make sure the repo is **private**, and contact the TA **before** the deadline.

You need to create a **private** repository, and add your teammate and TA `zhang-tr22` to the **Members** (with a role more powerful than `Reporter`) of your repo.

Your repository should contain:
- All source files you edited (`src/task1.c`, `src/task2.c`, `src/task3.c`, `src/task4.c`, `src/simd.c`)
- Your written report (PDF)
- The Makefile and all framework files (unchanged)

You need to keep your final submission code and your report in your **default branch** of your repo, and then submit `student1_id`, `student2_id`, and the **repo URL** on `https://learn.tsinghua.edu.cn`.

## Appendix A: NEON Intrinsics Quick Reference

```
Type:        float32x4_t        -- 128-bit vector of 4 floats

Load/Store:
  vld1q_f32(ptr)                 -- load 4 floats from memory
  vst1q_f32(ptr, vec)            -- store 4 floats to memory

Arithmetic:
  vfmaq_f32(acc, a, b)           -- fused multiply-add: acc + a*b
  vmulq_f32(a, b)                -- element-wise multiply: a * b
  vaddq_f32(a, b)                -- element-wise add: a + b
  vsubq_f32(a, b)                -- element-wise subtract: a - b

Broadcast:
  vdupq_n_f32(scalar)            -- fill all 4 lanes with scalar

Reduction:
  vaddvq_f32(vec)                -- horizontal sum of 4 lanes (aarch64)

Comparison:
  vmaxq_f32(a, b)                -- element-wise max
  vminq_f32(a, b)                -- element-wise min
```

Include `<arm_neon.h>` and compile with `-march=armv8-a`.

## Appendix B: Debugging Tips

- **Check NEON assembly**: `gcc -S -O2 -march=armv8-a -Isrc src/simd.c -o simd.s` and look for `fmla`, `fmul`, `ld1` instructions.
- **Disassemble**: `objdump -d task3 | grep -A 20 dot_f32_neon`
- **Monitor CPU usage**: Run `htop` in another terminal.  With 4 worker threads, you should see ~400% CPU utilization.
- **Performance counters** (if available): `perf stat ./task4 --data data/large/meta.txt --threads 4 --pin-cores --quiet`
- **Correctness debugging**: Run on the `tiny` dataset first (B=1, H=1, M=4, N=4, D=16) -- small enough to print and trace manually.
