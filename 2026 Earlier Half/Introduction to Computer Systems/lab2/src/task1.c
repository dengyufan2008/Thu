/*
 * task1.c -- Task 1: Naive scalar SDPA (single-threaded).
 *
 * Implement sdpa_naive() below.  This is a straightforward two-pass
 * softmax: first compute ALL scores, then softmax, then weighted sum.
 *
 * Build & test:
 *   make task1
 *   make check_task1
 */
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "sdpa.h"
#include "sdpa_utils.h"

int sdpa_naive(const SDPAParams* params) {
  if (!params || !params->q || !params->k || !params->v || !params->out)
    return -1;

  const int B = params->B, H = params->H;
  const int M = params->M, N = params->N;
  const int D = params->D, DV = params->DV;
  const float scale = params->scale;

  /* Allocate workspace for one query row. */
  float* scores = (float*)malloc((size_t)N * sizeof(float));
  float* weights = (float*)malloc((size_t)N * sizeof(float));
  if (!scores || !weights) {
    free(scores);
    free(weights);
    return -1;
  }

  for (int b = 0; b < B; b++) {
    for (int h = 0; h < H; h++) {
      for (int m = 0; m < M; m++) {
        const float* q_row = params->q + qkv_offset(b, h, m, H, M, D);
        const float* k_base = params->k + qkv_offset(b, h, 0, H, N, D);
        const float* v_base = params->v + qkv_offset(b, h, 0, H, N, DV);
        float* o_row = params->out + qkv_offset(b, h, m, H, M, DV);

        float max_score = -INFINITY;
        float sum_w = 0.0f;

        for (int i = 0; i < N; i++) {
          scores[i] = 0.0f;
          for (int j = 0; j < D; j++) {
            scores[i] += q_row[j] * k_base[i * D + j];
          }
          scores[i] *= scale;

          if (scores[i] > max_score) {
            max_score = scores[i];
          }
        }

        for (int i = 0; i < N; i++) {
          weights[i] = expf(scores[i] - max_score);

          sum_w += weights[i];
        }

        for (int i = 0; i < N; i++) {
          weights[i] /= sum_w;
        }

        for (int i = 0; i < DV; i++) {
          o_row[i] = 0.0f;
          for (int j = 0; j < N; j++) {
            o_row[i] += weights[j] * v_base[j * DV + i];
          }
        }
      }
    }
  }

  free(scores);
  free(weights);
  return 0;
}

/* Provide stub implementations for other tasks so linking succeeds.  */
/* You do NOT need to modify these.                                   */
int sdpa_online(const SDPAParams* p) {
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
