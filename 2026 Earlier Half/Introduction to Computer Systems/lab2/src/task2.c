/*
 * task2.c -- Task 2: Online (blocked) softmax SDPA (single-threaded).
 *
 * Instead of materializing all N scores and doing a two-pass softmax,
 * this version processes K/V in blocks of kv_block rows and maintains
 * running softmax statistics (m_prev, l_prev, acc).  This is the
 * key insight behind FlashAttention.
 *
 * Build & test:
 *   make task2
 *   make check_task2
 */
#include <math.h>
#include <string.h>

#include "sdpa.h"
#include "sdpa_utils.h"

/*
 * Process one query row (b, h, m) using the online softmax algorithm.
 *
 * Parameters:
 *   p      -- SDPA parameters (tensors, dimensions, scale, kv_block)
 *   b,h,m  -- which query row to process
 *   scores -- pre-allocated workspace of size [kv_block]
 *   acc    -- pre-allocated workspace of size [DV]
 */
static void attention_row_online(const SDPAParams* p,
                                 int b, int h, int m,
                                 float* scores, float* acc) {
  const float* q_row = p->q + qkv_offset(b, h, m, p->H, p->M, p->D);
  const float* k_base = p->k + qkv_offset(b, h, 0, p->H, p->N, p->D);
  const float* v_base = p->v + qkv_offset(b, h, 0, p->H, p->N, p->DV);
  float* o_row = p->out + qkv_offset(b, h, m, p->H, p->M, p->DV);

  const int N = p->N, D = p->D, DV = p->DV;
  const int BK = p->kv_block;
  const float scale = p->scale;

  /* Initialize running softmax state. */
  memset(acc, 0, (size_t)DV * sizeof(float));
  float m_prev = -INFINITY; /* running max of scores   */
  float l_prev = 0.0f;      /* running sum of exp(...) */

  for (int o = 0; o < N; o += BK) {
    int cur = (o + BK <= N) ? BK : (N - o); /* rows in this block */

    /* --- Phase A: Compute scores for this block --- */
    for (int i = 0; i < cur; i++) {
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
    for (int dv = 0; dv < DV; dv++) {
      acc[dv] *= alpha;
    }
    float l_new = l_prev * alpha;

    /* Accumulate this block's contribution. */
    for (int i = 0; i < cur; i++) {
      float w = expf(scores[i] - m_new);
      l_new += w;
      for (int dv = 0; dv < DV; dv++) {
        acc[dv] += w * v_base[(o + i) * DV + dv];
      }
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

int sdpa_online(const SDPAParams* params) {
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
        attention_row_online(params, b, h, m, scores, acc);

  aligned_free_f32(scores);
  aligned_free_f32(acc);
  return 0;
}

/* Stubs for other tasks. */
int sdpa_naive(const SDPAParams* p) {
  (void)p;
  return -1;
}
int sdpa_neon(const SDPAParams* p) {
  (void)p;
  return -1;
}
int sdpa_threaded(const SDPAParams* p) {
  (void)p;
  return -1;
}
