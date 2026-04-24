/*
 * sdpa_utils.h -- Utility functions for the SDPA lab.
 * DO NOT MODIFY THIS FILE.
 */
#ifndef SDPA_UTILS_H
#define SDPA_UTILS_H

#include "sdpa.h"
#include <stdio.h>

/* ------------------------------------------------------------------ */
/*  Aligned memory allocation (64-byte alignment for NEON / cache)     */
/* ------------------------------------------------------------------ */

float *aligned_alloc_f32(size_t count);
void   aligned_free_f32(void *p);

/* ------------------------------------------------------------------ */
/*  Data I/O                                                           */
/* ------------------------------------------------------------------ */

/*
 * Load tensors described by a plain-text metadata file.
 *
 *   Format (one key-value pair per line):
 *     B 1
 *     H 8
 *     M 256
 *     N 256
 *     D 64
 *     DV 64
 *     scale 0.125
 *     kv_block 64
 *     q_path data/medium/Q.bin
 *     k_path data/medium/K.bin
 *     v_path data/medium/V.bin
 *     out_path data/medium/out.bin
 *     ref_path data/medium/ref.bin
 *
 * Allocates Q, K, V, and out using aligned_alloc_f32.
 * Returns 0 on success, non-zero on error.
 */
int  sdpa_load_params(const char *meta_path, SDPAParams *p,
                      char *out_path_buf, size_t out_path_buf_len,
                      char *ref_path_buf, size_t ref_path_buf_len);

void sdpa_free_params(SDPAParams *p);

/* Write the output tensor (params->out) as raw float32. */
int  sdpa_write_output(const char *bin_path, const SDPAParams *p);

/* ------------------------------------------------------------------ */
/*  Timing                                                             */
/* ------------------------------------------------------------------ */

/* Wall-clock time in nanoseconds (CLOCK_MONOTONIC). */
uint64_t timer_ns(void);

/* ------------------------------------------------------------------ */
/*  Debug printing                                                     */
/* ------------------------------------------------------------------ */

void sdpa_print_info(const SDPAParams *p, FILE *out);

/* ------------------------------------------------------------------ */
/*  CPU query                                                          */
/* ------------------------------------------------------------------ */

/* Number of online (usable) CPU cores. */
int sdpa_num_cpus(void);

/* ------------------------------------------------------------------ */
/*  Tensor offset helpers                                              */
/* ------------------------------------------------------------------ */

/*
 * Compute the linear offset for element [b, h, pos, 0] in a
 * row-major tensor of shape [B, H, dim3, dim4].
 *
 *   offset = ((b * H + h) * dim3 + pos) * dim4
 *
 * Use this to find the start of a Q/K/V/out row:
 *   const float *q_row = params->q + qkv_offset(b, h, m, params->H, params->M, params->D);
 */
SDPA_INLINE size_t qkv_offset(int b, int h, int pos,
                               int H, int dim3, int dim4)
{
    return (((size_t)b * H + (size_t)h) * dim3 + (size_t)pos) * dim4;
}

#endif /* SDPA_UTILS_H */
