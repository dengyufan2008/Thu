/*
 * simd.c -- Task 3: ARM NEON SIMD helper functions.
 *
 * Implement the NEON-optimized versions of each function below.
 * The scalar fallbacks (from simd.h) are used as placeholders so that
 * your code compiles and produces correct results before you add NEON.
 *
 * Key NEON intrinsics you will need:
 *
 *   float32x4_t vld1q_f32(const float *ptr)     -- load 4 floats
 *   void        vst1q_f32(float *ptr, float32x4_t v)  -- store 4 floats
 *   float32x4_t vdupq_n_f32(float val)           -- broadcast scalar
 *   float32x4_t vfmaq_f32(acc, a, b)             -- acc + a*b (FMA)
 *   float32x4_t vmulq_f32(a, b)                  -- a * b
 *   float32x4_t vaddq_f32(a, b)                  -- a + b
 *   float       vaddvq_f32(float32x4_t v)        -- horizontal sum (aarch64)
 *
 * Optimization strategy:
 *   - Process 16 elements per loop iteration (4 NEON loads of 4 floats).
 *   - Use 4 independent accumulators to hide the FMA pipeline latency
 *     on Cortex-A72 (~4 cycles).
 *   - Handle remainder elements (n % 16) with a scalar tail loop.
 *
 * Build & test:
 *   make task3
 *   make check_task3
 */
#include "simd.h"

#include "sdpa.h"

#if defined(__aarch64__)
#include <arm_neon.h>
#endif

/* ------------------------------------------------------------------ */
/* dot_f32_neon: dot product of a[0..n-1] and b[0..n-1]               */
/* ------------------------------------------------------------------ */
float dot_f32_neon(const float* RESTRICT a,
                   const float* RESTRICT b, int n) {
#if defined(__aarch64__)
  int i = 0;
  float32x4_t acc0 = vdupq_n_f32(0.0f);
  float32x4_t acc1 = vdupq_n_f32(0.0f);
  float32x4_t acc2 = vdupq_n_f32(0.0f);
  float32x4_t acc3 = vdupq_n_f32(0.0f);

  for (; i + 15 < n; i += 16) {
    acc0 = vfmaq_f32(acc0, vld1q_f32(a + i + 0), vld1q_f32(b + i + 0));
    acc1 = vfmaq_f32(acc1, vld1q_f32(a + i + 4), vld1q_f32(b + i + 4));
    acc2 = vfmaq_f32(acc2, vld1q_f32(a + i + 8), vld1q_f32(b + i + 8));
    acc3 = vfmaq_f32(acc3, vld1q_f32(a + i + 12), vld1q_f32(b + i + 12));
  }
  float32x4_t acc = vaddq_f32(vaddq_f32(acc0, acc1), vaddq_f32(acc2, acc3));
  float sum = vaddvq_f32(acc);
  for (; i < n; ++i) sum += a[i] * b[i];
  return sum;
#else
  return dot_f32_scalar(a, b, n);
#endif
}

/* ------------------------------------------------------------------ */
/* dot4_f32_neon: 4 simultaneous dot products q.k0, q.k1, q.k2, q.k3 */
/* ------------------------------------------------------------------ */
void dot4_f32_neon(const float* RESTRICT q,
                   const float* RESTRICT k0,
                   const float* RESTRICT k1,
                   const float* RESTRICT k2,
                   const float* RESTRICT k3,
                   int d,
                   float* s0, float* s1, float* s2, float* s3) {
#if defined(__aarch64__)
  int i = 0;
  float32x4_t acc0 = vdupq_n_f32(0.0f);
  float32x4_t acc1 = vdupq_n_f32(0.0f);
  float32x4_t acc2 = vdupq_n_f32(0.0f);
  float32x4_t acc3 = vdupq_n_f32(0.0f);

  for (; i + 3 < d; i += 4) {
    float32x4_t vq = vld1q_f32(q + i);
    acc0 = vfmaq_f32(acc0, vq, vld1q_f32(k0 + i));
    acc1 = vfmaq_f32(acc1, vq, vld1q_f32(k1 + i));
    acc2 = vfmaq_f32(acc2, vq, vld1q_f32(k2 + i));
    acc3 = vfmaq_f32(acc3, vq, vld1q_f32(k3 + i));
  }
  float sum0 = vaddvq_f32(acc0);
  float sum1 = vaddvq_f32(acc1);
  float sum2 = vaddvq_f32(acc2);
  float sum3 = vaddvq_f32(acc3);
  for (; i < d; ++i) {
    float qv = q[i];
    sum0 += qv * k0[i];
    sum1 += qv * k1[i];
    sum2 += qv * k2[i];
    sum3 += qv * k3[i];
  }
  *s0 = sum0;
  *s1 = sum1;
  *s2 = sum2;
  *s3 = sum3;
#else
  *s0 = dot_f32_scalar(q, k0, d);
  *s1 = dot_f32_scalar(q, k1, d);
  *s2 = dot_f32_scalar(q, k2, d);
  *s3 = dot_f32_scalar(q, k3, d);
#endif
}

/* ------------------------------------------------------------------ */
/* vec_scale_f32_neon: x[i] *= a                                      */
/* ------------------------------------------------------------------ */
void vec_scale_f32_neon(float* RESTRICT x, float a, int n) {
#if defined(__aarch64__)
  int i = 0;
  float32x4_t av = vdupq_n_f32(a);
  for (; i + 3 < n; i += 4) {
    float32x4_t vx = vld1q_f32(x + i);
    vst1q_f32(x + i, vmulq_f32(vx, av));
  }
  for (; i < n; ++i) x[i] *= a;
#else
  vec_scale_f32_scalar(x, a, n);
#endif
}

/* ------------------------------------------------------------------ */
/* vec_fma_f32_neon: dst[i] += a * src[i]                             */
/* ------------------------------------------------------------------ */
void vec_fma_f32_neon(float* RESTRICT dst,
                      const float* RESTRICT src, float a, int n) {
#if defined(__aarch64__)
  int i = 0;
  float32x4_t av = vdupq_n_f32(a);
  for (; i + 3 < n; i += 4) {
    float32x4_t vdst = vld1q_f32(dst + i);
    float32x4_t vsrc = vld1q_f32(src + i);
    vdst = vfmaq_f32(vdst, vsrc, av);
    vst1q_f32(dst + i, vdst);
  }
  for (; i < n; ++i) dst[i] += a * src[i];
#else
  vec_fma_f32_scalar(dst, src, a, n);
#endif
}

/* ------------------------------------------------------------------ */
/* vec_fma4_f32_neon: dst[i] += a0*x0[i]+a1*x1[i]+a2*x2[i]+a3*x3[i] */
/* ------------------------------------------------------------------ */
void vec_fma4_f32_neon(float* RESTRICT dst,
                       const float* RESTRICT x0, float a0,
                       const float* RESTRICT x1, float a1,
                       const float* RESTRICT x2, float a2,
                       const float* RESTRICT x3, float a3,
                       int n) {
  /*
   * TODO: Replace with NEON.
   * Process 16 elements per iteration.  For each group of 4:
   *   load dst[i..i+3]
   *   vfmaq_f32(d, x0_chunk, av0)
   *   vfmaq_f32(d, x1_chunk, av1)
   *   vfmaq_f32(d, x2_chunk, av2)
   *   vfmaq_f32(d, x3_chunk, av3)
   *   store dst[i..i+3]
   */
#if defined(__aarch64__)
  int i = 0;
  float32x4_t av0 = vdupq_n_f32(a0);
  float32x4_t av1 = vdupq_n_f32(a1);
  float32x4_t av2 = vdupq_n_f32(a2);
  float32x4_t av3 = vdupq_n_f32(a3);
  for (; i + 3 < n; i += 4) {
    float32x4_t vdst = vld1q_f32(dst + i);
    vdst = vfmaq_f32(vdst, vld1q_f32(x0 + i), av0);
    vdst = vfmaq_f32(vdst, vld1q_f32(x1 + i), av1);
    vdst = vfmaq_f32(vdst, vld1q_f32(x2 + i), av2);
    vdst = vfmaq_f32(vdst, vld1q_f32(x3 + i), av3);
    vst1q_f32(dst + i, vdst);
  }
  for (; i < n; ++i)
    dst[i] += a0 * x0[i] + a1 * x1[i] + a2 * x2[i] + a3 * x3[i];
#else
  vec_fma4_f32_scalar(dst, x0, a0, x1, a1, x2, a2, x3, a3, n);
#endif
}

/* ------------------------------------------------------------------ */
/* vec_copy_scaled_f32_neon: dst[i] = a * src[i]                      */
/* ------------------------------------------------------------------ */
void vec_copy_scaled_f32_neon(float* RESTRICT dst,
                              const float* RESTRICT src,
                              float a, int n) {
#if defined(__aarch64__)
  int i = 0;
  float32x4_t av = vdupq_n_f32(a);
  for (; i + 3 < n; i += 4) {
    float32x4_t vsrc = vld1q_f32(src + i);
    vst1q_f32(dst + i, vmulq_f32(vsrc, av));
  }
  for (; i < n; ++i) dst[i] = src[i] * a;
#else
  vec_copy_scaled_f32_scalar(dst, src, a, n);
#endif
}
