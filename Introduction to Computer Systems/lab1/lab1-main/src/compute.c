#define _POSIX_C_SOURCE 199309L
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#ifdef SIMD
#include <arm_neon.h>
#endif

#include "common.h"
#include "compute.h"

void zero_z() {
  for (int i = 0; i != m; ++i) {
    for (int j = 0; j != n; ++j) {
      Z[i][j] = 0;
    }
  }
}

void zero_zp() {
  for (int j = 0; j != n; ++j) {
    for (int i = 0; i != m; ++i) {
      ZP[j][i] = 0;
    }
  }
}

void compute_row_major_mnk() {
  zero_z();
  for (int i = 0; i != m; ++i) {
    for (int j = 0; j != n; ++j) {
      for (int l = 0; l != k; ++l) {
        Z[i][j] += X[i][l] * Y[l][j];
      }
    }
  }
}

void compute_row_major_mkn() {
  zero_z();
  for (int i = 0; i != m; i++) {
    for (int l = 0; l != k; l++) {
      for (int j = 0; j != n; j++) {
        Z[i][j] += X[i][l] * Y[l][j];
      }
    }
  }
}

void compute_row_major_kmn() {
  zero_z();
  for (int l = 0; l != k; l++) {
    for (int i = 0; i != m; i++) {
      for (int j = 0; j != n; j++) {
        Z[i][j] += X[i][l] * Y[l][j];
      }
    }
  }
}

void compute_row_major_nmk() {
  zero_z();
  for (int j = 0; j != n; j++) {
    for (int i = 0; i != m; i++) {
      for (int l = 0; l != k; l++) {
        Z[i][j] += X[i][l] * Y[l][j];
      }
    }
  }
}

void compute_row_major_nkm() {
  zero_z();
  for (int j = 0; j != n; j++) {
    for (int l = 0; l != k; l++) {
      for (int i = 0; i != m; i++) {
        Z[i][j] += X[i][l] * Y[l][j];
      }
    }
  }
}

void compute_row_major_knm() {
  zero_z();
  for (int l = 0; l != k; l++) {
    for (int j = 0; j != n; j++) {
      for (int i = 0; i != m; i++) {
        Z[i][j] += X[i][l] * Y[l][j];
      }
    }
  }
}

void compute_y_transpose_mnk() {
  zero_z();
  for (int i = 0; i != m; i++) {
    for (int j = 0; j != n; j++) {
      for (int l = 0; l != k; l++) {
        Z[i][j] += X[i][l] * YP[j][l];
      }
    }
  }
}

void compute_row_major_mnkkmn_b32() {
  static const int kB = 32;
  zero_z();
  for (int oi = 0; oi < m; oi += kB) {
    for (int oj = 0; oj < n; oj += kB) {
      for (int ol = 0; ol < k; ol += kB) {
        for (int ul = 0; ul < kB && ol + ul < k; ul++) {
          for (int ui = 0; ui < kB && oi + ui < m; ui++) {
            for (int uj = 0; uj < kB && oj + uj < n; uj++) {
              Z[oi + ui][oj + uj] += X[oi + ui][ol + ul] * Y[ol + ul][oj + uj];
            }
          }
        }
      }
    }
  }
}

void compute_row_major_mnk_lu2() {
  zero_z();
  for (int i = 0; i < m; i += 2) {
    for (int j = 0; j < n; j += 2) {
      for (int l = 0; l < k; l += 2) {
        Z[i][j] += X[i][l] * Y[l][j];
        Z[i][j] += X[i][l | 1] * Y[l | 1][j];
        Z[i][j | 1] += X[i][l] * Y[l][j | 1];
        Z[i][j | 1] += X[i][l | 1] * Y[l | 1][j | 1];
        Z[i | 1][j] += X[i | 1][l] * Y[l][j];
        Z[i | 1][j] += X[i | 1][l | 1] * Y[l | 1][j];
        Z[i | 1][j | 1] += X[i | 1][l] * Y[l][j | 1];
        Z[i | 1][j | 1] += X[i | 1][l | 1] * Y[l | 1][j | 1];
      }
    }
  }
}

void compute_handmade_task2() {
  static const int kB = 32;
  if (m > n) {
    zero_z();
    for (int oi = 0; oi < m; oi += kB) {
      int _m = oi + kB < m ? oi + kB : m;
      for (int oj = 0; oj < n; oj += kB) {
        int _n = oj + kB < n ? oj + kB : n;
        for (int ol = 0; ol < k; ol += kB) {
          int _k = ol + kB < k ? ol + kB : k;
          for (int i = oi; i < _m; i += 2) {
            for (int j = oj; j < _n; j += 2) {
              for (int l = ol; l < _k; l += 2) {
                Z[i][j] += X[i][l] * YP[j][l];
                Z[i][j] += X[i][l | 1] * YP[j][l | 1];
                Z[i][j | 1] += X[i][l] * YP[j | 1][l];
                Z[i][j | 1] += X[i][l | 1] * YP[j | 1][l | 1];
                Z[i | 1][j] += X[i | 1][l] * YP[j][l];
                Z[i | 1][j] += X[i | 1][l | 1] * YP[j][l | 1];
                Z[i | 1][j | 1] += X[i | 1][l] * YP[j | 1][l];
                Z[i | 1][j | 1] += X[i | 1][l | 1] * YP[j | 1][l | 1];
              }
            }
          }
        }
      }
    }
  } else {
    zero_zp();
    for (int oj = 0; oj < n; oj += kB) {
      int _n = oj + kB < n ? oj + kB : n;
      for (int oi = 0; oi < m; oi += kB) {
        int _m = oi + kB < m ? oi + kB : m;
        for (int ol = 0; ol < k; ol += kB) {
          int _k = ol + kB < k ? ol + kB : k;
          for (int j = oj; j < _n; j += 2) {
            for (int i = oi; i < _m; i += 2) {
              for (int l = ol; l < _k; l += 2) {
                ZP[j][i] += X[i][l] * YP[j][l];
                ZP[j][i] += X[i][l | 1] * YP[j][l | 1];
                ZP[j | 1][i] += X[i][l] * YP[j | 1][l];
                ZP[j | 1][i] += X[i][l | 1] * YP[j | 1][l | 1];
                ZP[j][i | 1] += X[i | 1][l] * YP[j][l];
                ZP[j][i | 1] += X[i | 1][l | 1] * YP[j][l | 1];
                ZP[j | 1][i | 1] += X[i | 1][l] * YP[j | 1][l];
                ZP[j | 1][i | 1] += X[i | 1][l | 1] * YP[j | 1][l | 1];
              }
            }
          }
        }
      }
    }
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        Z[i][j] = ZP[j][i];
      }
    }
  }
}

void compute_simd() {
#ifdef SIMD
  if (m < n) {
    zero_z();
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        for (int l = 0; l < k; l += 64) {
          Z[i][j] += vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l]), vld1_u16(&YP16[j][l]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 4]), vld1_u16(&YP16[j][l | 4]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 8]), vld1_u16(&YP16[j][l | 8]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 12]), vld1_u16(&YP16[j][l | 12]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 16]), vld1_u16(&YP16[j][l | 16]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 20]), vld1_u16(&YP16[j][l | 20]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 24]), vld1_u16(&YP16[j][l | 24]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 28]), vld1_u16(&YP16[j][l | 28]))) + 
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 32]), vld1_u16(&YP16[j][l | 32]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 36]), vld1_u16(&YP16[j][l | 36]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 40]), vld1_u16(&YP16[j][l | 40]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 44]), vld1_u16(&YP16[j][l | 44]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 48]), vld1_u16(&YP16[j][l | 48]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 52]), vld1_u16(&YP16[j][l | 52]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 56]), vld1_u16(&YP16[j][l | 56]))) +
                     vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 60]), vld1_u16(&YP16[j][l | 60])));
        }
      }
    }
  } else {
    zero_zp();
    for (int j = 0; j < n; j++) {
      for (int i = 0; i < m; i++) {
        for (int l = 0; l < k; l += 64) {
          ZP[j][i] += vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l]), vld1_u16(&YP16[j][l]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 4]), vld1_u16(&YP16[j][l | 4]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 8]), vld1_u16(&YP16[j][l | 8]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 12]), vld1_u16(&YP16[j][l | 12]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 16]), vld1_u16(&YP16[j][l | 16]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 20]), vld1_u16(&YP16[j][l | 20]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 24]), vld1_u16(&YP16[j][l | 24]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 28]), vld1_u16(&YP16[j][l | 28]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 32]), vld1_u16(&YP16[j][l | 32]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 36]), vld1_u16(&YP16[j][l | 36]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 40]), vld1_u16(&YP16[j][l | 40]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 44]), vld1_u16(&YP16[j][l | 44]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 48]), vld1_u16(&YP16[j][l | 48]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 52]), vld1_u16(&YP16[j][l | 52]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 56]), vld1_u16(&YP16[j][l | 56]))) +
                      vaddlvq_u32(vmull_u16(vld1_u16(&X16[i][l | 60]), vld1_u16(&YP16[j][l | 60])));
        }
      }
    }
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        Z[i][j] = ZP[j][i];
      }
    }
  }
#endif
}

uint64_t elapsed(const struct timespec start, const struct timespec end) {
  struct timespec result;
  result.tv_sec = end.tv_sec - start.tv_sec;
  result.tv_nsec = end.tv_nsec - start.tv_nsec;
  if (result.tv_nsec < 0) {
    --result.tv_sec;
    result.tv_nsec += SEC;
  }
  uint64_t res = result.tv_sec * SEC + result.tv_nsec;
  return res;
}

uint64_t compute() {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  switch (COMPUTE_SELECT) {
    case COMPUTE_ROW_MAJOR_MNK:
      // printf("COMPUTE_ROW_MAJOR_MNK\n");
      compute_row_major_mnk();
      break;
    case COMPUTE_ROW_MAJOR_MKN:
      // printf("COMPUTE_ROW_MAJOR_MKN\n");
      compute_row_major_mkn();
      break;
    case COMPUTE_ROW_MAJOR_KMN:
      // printf("COMPUTE_ROW_MAJOR_KMN\n");
      compute_row_major_kmn();
      break;
    case COMPUTE_ROW_MAJOR_NMK:
      // printf("COMPUTE_ROW_MAJOR_NMK\n");
      compute_row_major_nmk();
      break;
    case COMPUTE_ROW_MAJOR_NKM:
      // printf("COMPUTE_ROW_MAJOR_NKM\n");
      compute_row_major_nkm();
      break;
    case COMPUTE_ROW_MAJOR_KNM:
      // printf("COMPUTE_ROW_MAJOR_KNM\n");
      compute_row_major_knm();
      break;
    case COMPUTE_Y_TRANSPOSE_MNK:
      // printf("COMPUTE_Y_TRANSPOSE_MNK\n");
      compute_y_transpose_mnk();
      break;
    case COMPUTE_ROW_MAJOR_MNKKMN_B32:
      // printf("COMPUTE_ROW_MAJOR_MNKKMN_B32\n");
      compute_row_major_mnkkmn_b32();
      break;
    case COMPUTE_ROW_MAJOR_MNK_LU2:
      // printf("COMPUTE_ROW_MAJOR_MNK_LU2\n");
      compute_row_major_mnk_lu2();
      break;
    case COMPUTE_HANDMADE_TASK2:
      // printf("COMPUTE_HANDMADE_TASK2\n");
      compute_handmade_task2();
      break;
    case COMPUTE_SIMD:
      // printf("COMPUTE_SIMD\n");
      compute_simd();
      break;
    default:
      printf("Unreachable!");
      return 0;
  }

  clock_gettime(CLOCK_MONOTONIC, &end);
  return elapsed(start, end);
}
