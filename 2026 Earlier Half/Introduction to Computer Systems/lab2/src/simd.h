/*
 * simd.h -- NEON SIMD helper function declarations and scalar fallbacks.
 * DO NOT MODIFY THIS FILE.
 *
 * Task 3 requires you to implement the NEON versions of these functions
 * in simd.c.  The scalar fallbacks below are provided so that you can
 * test your code before writing any NEON.
 */
#ifndef SIMD_H
#define SIMD_H

#include "sdpa.h"
#include <math.h>

/* ------------------------------------------------------------------ */
/*  NEON helper function declarations (implemented in simd.c)          */
/* ------------------------------------------------------------------ */

/* Dot product of vectors a and b, each of length n. */
float dot_f32_neon(const float *RESTRICT a,
                   const float *RESTRICT b, int n);

/*
 * Four dot products at once: q.k0, q.k1, q.k2, q.k3.
 * All vectors have length d.  Results written to *s0 .. *s3.
 */
void dot4_f32_neon(const float *RESTRICT q,
                   const float *RESTRICT k0,
                   const float *RESTRICT k1,
                   const float *RESTRICT k2,
                   const float *RESTRICT k3,
                   int d,
                   float *s0, float *s1, float *s2, float *s3);

/* x[i] *= a  for i in [0, n) */
void vec_scale_f32_neon(float *RESTRICT x, float a, int n);

/* dst[i] += a * src[i]  for i in [0, n) */
void vec_fma_f32_neon(float *RESTRICT dst,
                      const float *RESTRICT src, float a, int n);

/* dst[i] += a0*x0[i] + a1*x1[i] + a2*x2[i] + a3*x3[i] */
void vec_fma4_f32_neon(float *RESTRICT dst,
                       const float *RESTRICT x0, float a0,
                       const float *RESTRICT x1, float a1,
                       const float *RESTRICT x2, float a2,
                       const float *RESTRICT x3, float a3,
                       int n);

/* dst[i] = a * src[i]  for i in [0, n) */
void vec_copy_scaled_f32_neon(float *RESTRICT dst,
                              const float *RESTRICT src,
                              float a, int n);

/* ------------------------------------------------------------------ */
/*  Scalar fallback implementations (for reference / initial testing)   */
/* ------------------------------------------------------------------ */

SDPA_INLINE float dot_f32_scalar(const float *RESTRICT a,
                                  const float *RESTRICT b, int n)
{
    float sum = 0.0f;
    for (int i = 0; i < n; ++i) sum += a[i] * b[i];
    return sum;
}

SDPA_INLINE void vec_scale_f32_scalar(float *RESTRICT x, float a, int n)
{
    for (int i = 0; i < n; ++i) x[i] *= a;
}

SDPA_INLINE void vec_fma_f32_scalar(float *RESTRICT dst,
                                     const float *RESTRICT src,
                                     float a, int n)
{
    for (int i = 0; i < n; ++i) dst[i] += a * src[i];
}

SDPA_INLINE void vec_fma4_f32_scalar(float *RESTRICT dst,
                                      const float *RESTRICT x0, float a0,
                                      const float *RESTRICT x1, float a1,
                                      const float *RESTRICT x2, float a2,
                                      const float *RESTRICT x3, float a3,
                                      int n)
{
    for (int i = 0; i < n; ++i)
        dst[i] += a0 * x0[i] + a1 * x1[i] + a2 * x2[i] + a3 * x3[i];
}

SDPA_INLINE void vec_copy_scaled_f32_scalar(float *RESTRICT dst,
                                             const float *RESTRICT src,
                                             float a, int n)
{
    for (int i = 0; i < n; ++i) dst[i] = src[i] * a;
}

#endif /* SIMD_H */
