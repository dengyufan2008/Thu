/*
 * sdpa.h -- Scaled Dot-Product Attention (SDPA) for Raspberry Pi 4B
 *
 * Core data structures and function declarations for all lab tasks.
 * DO NOT MODIFY THIS FILE.
 */
#ifndef SDPA_H
#define SDPA_H

#include <stdint.h>
#include <stddef.h>

/* ------------------------------------------------------------------ */
/*  Compiler helpers                                                   */
/* ------------------------------------------------------------------ */

#ifndef RESTRICT
#  if defined(__GNUC__) || defined(__clang__)
#    define RESTRICT __restrict__
#  else
#    define RESTRICT
#  endif
#endif

#ifndef SDPA_INLINE
#  define SDPA_INLINE static inline
#endif

/* ------------------------------------------------------------------ */
/*  SDPAParams -- describes one SDPA computation                       */
/* ------------------------------------------------------------------ */

/*
 * Tensor layouts (row-major, contiguous float32):
 *
 *   Q   : [B, H, M, D]   -- queries
 *   K   : [B, H, N, D]   -- keys
 *   V   : [B, H, N, DV]  -- values
 *   out : [B, H, M, DV]  -- output
 *
 * Attention(Q, K, V) = softmax(Q @ K^T * scale) @ V
 *
 * 'scale' is typically 1 / sqrt(D).
 */
typedef struct {
    const float *RESTRICT q;     /* [B, H, M, D]  */
    const float *RESTRICT k;     /* [B, H, N, D]  */
    const float *RESTRICT v;     /* [B, H, N, DV] */
    float       *RESTRICT out;   /* [B, H, M, DV] */

    int B;       /* batch size                     */
    int H;       /* number of attention heads       */
    int M;       /* query sequence length           */
    int N;       /* key / value sequence length     */
    int D;       /* dimension of Q and K per head   */
    int DV;      /* dimension of V per head         */

    float scale; /* scaling factor (1/sqrt(D))      */

    /* Task 2+: block size for online softmax (default 64) */
    int kv_block;

    /* Task 4: threading parameters */
    int num_threads;
    int pin_threads_to_cores;
} SDPAParams;

/* ------------------------------------------------------------------ */
/*  Task function declarations                                         */
/* ------------------------------------------------------------------ */

/*
 * All functions return 0 on success, non-zero on error.
 * params->out is pre-allocated by the framework.
 */

/* Task 1: Naive scalar SDPA (single-threaded, two-pass softmax).
 *
 * For each query row (b, h, m):
 *   1. scores[j] = dot(Q[b,h,m,:], K[b,h,j,:]) * scale   for j in [0..N)
 *   2. Softmax:  max -> exp -> sum -> normalize
 *   3. out[b,h,m,:] = sum_j weights[j] * V[b,h,j,:]
 */
int sdpa_naive(const SDPAParams *params);

/* Task 2: Online (blocked) softmax SDPA (single-threaded, scalar).
 *
 * Process K/V in blocks of kv_block rows.  Maintain running state
 * (m_prev, l_prev, acc[DV]) to avoid materializing the full N-length
 * score vector.
 */
int sdpa_online(const SDPAParams *params);

/* Task 3: NEON SIMD-accelerated SDPA (single-threaded).
 *
 * Same online softmax algorithm, but inner loops use ARM NEON
 * intrinsics for dot products, scaling, and accumulation.
 */
int sdpa_neon(const SDPAParams *params);

/* Task 4: Multi-threaded SDPA with NEON.
 *
 * Distribute the B*H*M query rows across num_threads pthreads.
 * Each thread processes a disjoint range with its own workspace.
 */
int sdpa_threaded(const SDPAParams *params);

#endif /* SDPA_H */
