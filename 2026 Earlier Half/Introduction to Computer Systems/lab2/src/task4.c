/*
 * task4.c -- Task 4: Multi-threaded SDPA with NEON.
 *
 * Distribute the B*H*M query rows across multiple pthreads.
 * Each thread computes its assigned rows using the NEON-accelerated
 * online softmax from Task 3.  Since each thread writes to disjoint
 * output rows, no synchronization is needed on the output tensor.
 *
 * Build & test:
 *   make task4
 *   make check_task4
 *
 * Run with different thread counts:
 *   ./task4 --data data/large/meta.txt --threads 1
 *   ./task4 --data data/large/meta.txt --threads 2
 *   ./task4 --data data/large/meta.txt --threads 4 --pin-cores
 */
#define _GNU_SOURCE
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sdpa.h"
#include "sdpa_utils.h"
#include "simd.h"

#if defined(__linux__)
#include <sched.h>
#endif
#if defined(__aarch64__)
#include <arm_neon.h>
#endif

/* Per-worker arguments and workspace */
typedef struct {
  const SDPAParams* p;
  int tid;
  int nthreads;
  float* scores; /* size kv_block */
  float* acc;    /* size DV */
  pthread_barrier_t* barrier;
} WorkerArgs;

/* NEON-accelerated attention row (same logic as Task 3) */
static void attention_row_threaded(const SDPAParams* p,
                                   int b, int h, int m,
                                   float* scores, float* acc) {
  const float* q_row = p->q + qkv_offset(b, h, m, p->H, p->M, p->D);
  const float* k_base = p->k + qkv_offset(b, h, 0, p->H, p->N, p->D);
  const float* v_base = p->v + qkv_offset(b, h, 0, p->H, p->N, p->DV);
  float* o_row = p->out + qkv_offset(b, h, m, p->H, p->M, p->DV);

  const int N = p->N, D = p->D, DV = p->DV;
  const int BK = p->kv_block;
  const float scale = p->scale;

  memset(acc, 0, (size_t)DV * sizeof(float));
  float m_prev = -INFINITY;
  float l_prev = 0.0f;

  for (int kb = 0; kb < N; kb += BK) {
    int cur = (kb + BK <= N) ? BK : (N - kb);

    float block_max = -INFINITY;
    int t = 0;
    for (; t + 3 < cur; t += 4) {
      float s0, s1, s2, s3;
      dot4_f32_neon(q_row,
                    k_base + (kb + t + 0) * D,
                    k_base + (kb + t + 1) * D,
                    k_base + (kb + t + 2) * D,
                    k_base + (kb + t + 3) * D,
                    D, &s0, &s1, &s2, &s3);
      s0 *= scale;
      s1 *= scale;
      s2 *= scale;
      s3 *= scale;
      scores[t + 0] = s0;
      scores[t + 1] = s1;
      scores[t + 2] = s2;
      scores[t + 3] = s3;

      block_max = fmaxf(block_max, fmaxf(fmaxf(s0, s1), fmaxf(s2, s3)));
    }
    for (; t < cur; t++) {
      float s = dot_f32_neon(q_row, k_base + (kb + t) * D, D) * scale;
      scores[t] = s;
      block_max = fmaxf(block_max, s);
    }

    float m_new = fmaxf(m_prev, block_max);
    float alpha = isfinite(m_prev) ? expf(m_prev - m_new) : 0.0f;
    if (alpha != 1.0f)
      vec_scale_f32_neon(acc, alpha, DV);
    float l_new = l_prev * alpha;

    int u = 0;
    for (; u + 3 < cur; u += 4) {
      float w0 = expf(scores[u + 0] - m_new);
      float w1 = expf(scores[u + 1] - m_new);
      float w2 = expf(scores[u + 2] - m_new);
      float w3 = expf(scores[u + 3] - m_new);
      l_new += w0 + w1 + w2 + w3;
      vec_fma4_f32_neon(acc,
                        v_base + (kb + u + 0) * DV, w0,
                        v_base + (kb + u + 1) * DV, w1,
                        v_base + (kb + u + 2) * DV, w2,
                        v_base + (kb + u + 3) * DV, w3, DV);
    }
    for (; u < cur; u++) {
      float w = expf(scores[u] - m_new);
      l_new += w;
      vec_fma_f32_neon(acc, v_base + (kb + u) * DV, w, DV);
    }
    m_prev = m_new;
    l_prev = l_new;
  }

  if (l_prev > 0)
    vec_copy_scaled_f32_neon(o_row, acc, 1.0f / l_prev, DV);
  else
    memset(o_row, 0, (size_t)DV * sizeof(float));
}

/* Worker entry: each thread processes a slice of M for every (b,h) head
 * and synchronizes between heads using a barrier. */
static void* worker_entry(void* arg) {
  WorkerArgs* wa = (WorkerArgs*)arg;
  const SDPAParams* p = wa->p;
  int tid = wa->tid;
  int nthreads = wa->nthreads;

#if defined(__linux__)
  if (p->pin_threads_to_cores) {
    int num_cores = sdpa_num_cpus();
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(tid % num_cores, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
  }
#endif

  int B = p->B, H = p->H, M = p->M;
  int rows_per = (M + nthreads - 1) / nthreads;
  int m_begin = tid * rows_per;
  int m_end = m_begin + rows_per;
  if (m_end > M) m_end = M;

  for (int b = 0; b < B; b++) {
    for (int h = 0; h < H; h++) {
      for (int m = m_begin; m < m_end; m++) {
        attention_row_threaded(p, b, h, m, wa->scores, wa->acc);
      }
      if (wa->barrier)
        pthread_barrier_wait(wa->barrier);
    }
  }

  return NULL;
}

int sdpa_threaded(const SDPAParams* params) {
  if (!params || !params->q || !params->k || !params->v || !params->out)
    return -1;

  int ncpus = sdpa_num_cpus();
  int nthreads = params->num_threads > 0 ? params->num_threads : ncpus;
  if (nthreads > ncpus) nthreads = ncpus;
  if (nthreads > params->M) nthreads = params->M > 0 ? params->M : 1;
  if (nthreads < 1) nthreads = 1;

  int BK = params->kv_block;
  int DV = params->DV;

  pthread_t* threads = NULL;
  WorkerArgs* wargs = NULL;
  pthread_barrier_t barrier;

  threads = malloc((size_t)nthreads * sizeof(pthread_t));
  if (!threads) return -1;
  wargs = malloc((size_t)nthreads * sizeof(WorkerArgs));
  if (!wargs) {
    free(threads);
    return -1;
  }

  if (pthread_barrier_init(&barrier, NULL, (unsigned)nthreads) != 0) {
    free(threads);
    free(wargs);
    return -1;
  }

  /* Single-thread fast path */
  if (nthreads == 1) {
    float* scores = aligned_alloc_f32((size_t)BK);
    float* acc = aligned_alloc_f32((size_t)DV);
    if (!scores || !acc) {
      aligned_free_f32(scores);
      aligned_free_f32(acc);
      pthread_barrier_destroy(&barrier);
      free(threads);
      free(wargs);
      return -1;
    }
    for (int b = 0; b < params->B; b++)
      for (int h = 0; h < params->H; h++)
        for (int m = 0; m < params->M; m++)
          attention_row_threaded(params, b, h, m, scores, acc);

    aligned_free_f32(scores);
    aligned_free_f32(acc);
    pthread_barrier_destroy(&barrier);
    free(threads);
    free(wargs);
    return 0;
  }

  /* Create workers */
  for (int t = 0; t < nthreads; t++) {
    wargs[t].p = params;
    wargs[t].tid = t;
    wargs[t].nthreads = nthreads;
    wargs[t].scores = aligned_alloc_f32((size_t)BK);
    wargs[t].acc = aligned_alloc_f32((size_t)DV);
    wargs[t].barrier = &barrier;
    if (!wargs[t].scores || !wargs[t].acc) {
      for (int j = 0; j <= t; j++) {
        aligned_free_f32(wargs[j].scores);
        aligned_free_f32(wargs[j].acc);
      }
      pthread_barrier_destroy(&barrier);
      free(threads);
      free(wargs);
      return -1;
    }
    if (pthread_create(&threads[t], NULL, worker_entry, &wargs[t]) != 0) {
      for (int j = 0; j <= t; j++) {
        aligned_free_f32(wargs[j].scores);
        aligned_free_f32(wargs[j].acc);
      }
      pthread_barrier_destroy(&barrier);
      free(threads);
      free(wargs);
      return -1;
    }
  }

  /* Join workers */
  for (int t = 0; t < nthreads; t++) {
    pthread_join(threads[t], NULL);
    aligned_free_f32(wargs[t].scores);
    aligned_free_f32(wargs[t].acc);
  }

  pthread_barrier_destroy(&barrier);
  free(threads);
  free(wargs);
  return 0;
}

/* Stubs */
int sdpa_naive(const SDPAParams* p) {
  (void)p;
  return -1;
}
int sdpa_online(const SDPAParams* p) {
  (void)p;
  return -1;
}
int sdpa_neon(const SDPAParams* p) {
  (void)p;
  return -1;
}
