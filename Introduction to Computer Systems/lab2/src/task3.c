/*
 * task3.c -- Task 3: NEON SIMD-accelerated SDPA (single-threaded).
 *
 * Same online softmax algorithm as Task 2, but using the NEON helper
 * functions you implemented in simd.c for the inner loops.
 *
 * Key optimizations over Task 2:
 *   - dot4_f32_neon: compute 4 Q.K scores at once
 *   - vec_fma4_f32_neon: accumulate 4 weighted V rows at once
 *   - vec_scale_f32_neon / vec_copy_scaled_f32_neon for rescaling
 *
 * Build & test:
 *   make task3
 *   make check_task3
 */
#include <math.h>
#include <string.h>

#include "sdpa.h"
#include "sdpa_utils.h"
#include "simd.h"

static void attention_row_neon(const SDPAParams* p,
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

  for (int o = 0; o < N; o += BK) {
    int cur = (o + BK <= N) ? BK : (N - o); /* rows in this block */

    /* --- Phase A: Compute scores for this block --- */
    for (int i = 0; i < cur; i += 4) {
      dot4_f32_neon(q_row,
                    k_base + (o + i + 0) * D,
                    k_base + (o + i + 1) * D,
                    k_base + (o + i + 2) * D,
                    k_base + (o + i + 3) * D,
                    D, &scores[i], &scores[i + 1],
                    &scores[i + 2], &scores[i + 3]);
      scores[i + 0] *= scale;
      scores[i + 1] *= scale;
      scores[i + 2] *= scale;
      scores[i + 3] *= scale;
    }
    for (int i = (cur / 4) * 4; i < cur; i++) {
      scores[i] = 0.0f;
      for (int j = 0; j < D; j++) {
        scores[i] += q_row[j] * k_base[(o + i) * D + j];
      }
      scores[i] *= scale;
    }

    /* --- Phase B: Update online softmax --- */
    float block_max = -INFINITY;
    for (int i = 0; i < cur; i++) {
      if (scores[i] > block_max) {
        block_max = scores[i];
      }
    }

    float m_new = fmaxf(m_prev, block_max);

    /* Rescale previous accumulation to account for new max. */
    float alpha = isfinite(m_prev) ? expf(m_prev - m_new) : 0.0f;
    if (alpha != 1) {
      vec_scale_f32_neon(acc, alpha, DV);
    }
    float l_new = l_prev * alpha;

    /* Accumulate this block's contribution. */
    for (int i = 0; i < cur; i += 4) {
      float w0 = expf(scores[i + 0] - m_new);
      float w1 = expf(scores[i + 1] - m_new);
      float w2 = expf(scores[i + 2] - m_new);
      float w3 = expf(scores[i + 3] - m_new);
      l_new += w0 + w1 + w2 + w3;
      vec_fma4_f32_neon(acc,
                        v_base + (o + i + 0) * DV, w0,
                        v_base + (o + i + 1) * DV, w1,
                        v_base + (o + i + 2) * DV, w2,
                        v_base + (o + i + 3) * DV, w3, DV);
    }
    /* Handle remainder with vec_fma_f32_neon. */
    for (int i = (cur / 4) * 4; i < cur; i++) {
      float w = expf(scores[i] - m_new);
      l_new += w;
      vec_fma_f32_neon(acc, v_base + (o + i) * DV, w, DV);
    }

    m_prev = m_new;
    l_prev = l_new;
  }

  if (l_prev > 0.0f) {
    for (int dv = 0; dv < DV; dv++) {
      o_row[dv] = acc[dv] / l_prev;
    }
  } else {
    memset(o_row, 0, (size_t)DV * sizeof(float));
  }
}

int sdpa_neon(const SDPAParams* params) {
  if (!params || !params->q || !params->k || !params->v || !params->out)
    return -1;

  float* scores = aligned_alloc_f32((size_t)params->kv_block);
  float* acc = aligned_alloc_f32((size_t)params->DV);
  if (!scores || !acc) {
    aligned_free_f32(scores);
    aligned_free_f32(acc);
    return -1;
  }

  for (int b = 0; b < params->B; b++)
    for (int h = 0; h < params->H; h++)
      for (int m = 0; m < params->M; m++)
        attention_row_neon(params, b, h, m, scores, acc);

  aligned_free_f32(scores);
  aligned_free_f32(acc);
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
int sdpa_threaded(const SDPAParams* p) {
  (void)p;
  return -1;
}
