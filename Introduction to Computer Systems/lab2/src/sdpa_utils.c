/*
 * sdpa_utils.c -- Utility functions for the SDPA lab.
 * DO NOT MODIFY THIS FILE.
 */
#define _POSIX_C_SOURCE 200112L
#include "sdpa_utils.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

/* ------------------------------------------------------------------ */
/*  Aligned memory                                                     */
/* ------------------------------------------------------------------ */

float *aligned_alloc_f32(size_t count)
{
    if (count == 0) return NULL;
    void *p = NULL;
    if (posix_memalign(&p, 64, count * sizeof(float)) != 0)
        return NULL;
    return (float *)p;
}

void aligned_free_f32(void *p)
{
    free(p);
}

/* ------------------------------------------------------------------ */
/*  Meta-file parser                                                   */
/* ------------------------------------------------------------------ */

/* Read a binary float32 file into a pre-allocated buffer. */
static int read_bin_f32(const char *path, float *buf, size_t count)
{
    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "error: cannot open '%s': %s\n", path, strerror(errno));
        return -1;
    }
    size_t got = fread(buf, sizeof(float), count, f);
    fclose(f);
    if (got != count) {
        fprintf(stderr, "error: '%s': expected %zu floats, got %zu\n",
                path, count, got);
        return -1;
    }
    return 0;
}

int sdpa_load_params(const char *meta_path, SDPAParams *p,
                     char *out_path_buf, size_t out_path_buf_len,
                     char *ref_path_buf, size_t ref_path_buf_len)
{
    memset(p, 0, sizeof(*p));
    if (out_path_buf && out_path_buf_len > 0) out_path_buf[0] = '\0';
    if (ref_path_buf && ref_path_buf_len > 0) ref_path_buf[0] = '\0';

    char q_path[512] = {0};
    char k_path[512] = {0};
    char v_path[512] = {0};

    FILE *f = fopen(meta_path, "r");
    if (!f) {
        fprintf(stderr, "error: cannot open meta file '%s': %s\n",
                meta_path, strerror(errno));
        return -1;
    }

    /* Resolve the directory part of meta_path for relative bin paths. */
    char dir[512] = {0};
    {
        const char *last_slash = strrchr(meta_path, '/');
        if (last_slash) {
            size_t dlen = (size_t)(last_slash - meta_path + 1);
            if (dlen >= sizeof(dir)) dlen = sizeof(dir) - 1;
            memcpy(dir, meta_path, dlen);
            dir[dlen] = '\0';
        }
    }

    char line[1024];
    while (fgets(line, (int)sizeof(line), f)) {
        char key[64], val[512];
        if (sscanf(line, "%63s %511s", key, val) != 2) continue;

        if      (strcmp(key, "B")  == 0) p->B  = atoi(val);
        else if (strcmp(key, "H")  == 0) p->H  = atoi(val);
        else if (strcmp(key, "M")  == 0) p->M  = atoi(val);
        else if (strcmp(key, "N")  == 0) p->N  = atoi(val);
        else if (strcmp(key, "D")  == 0) p->D  = atoi(val);
        else if (strcmp(key, "DV") == 0) p->DV = atoi(val);
        else if (strcmp(key, "scale")    == 0) p->scale    = (float)atof(val);
        else if (strcmp(key, "kv_block") == 0) p->kv_block = atoi(val);
        else if (strcmp(key, "q_path")   == 0) snprintf(q_path, sizeof(q_path), "%s", val);
        else if (strcmp(key, "k_path")   == 0) snprintf(k_path, sizeof(k_path), "%s", val);
        else if (strcmp(key, "v_path")   == 0) snprintf(v_path, sizeof(v_path), "%s", val);
        else if (strcmp(key, "out_path") == 0 && out_path_buf)
            snprintf(out_path_buf, out_path_buf_len, "%s", val);
        else if (strcmp(key, "ref_path") == 0 && ref_path_buf)
            snprintf(ref_path_buf, ref_path_buf_len, "%s", val);
    }
    fclose(f);

    /* Validate */
    if (p->B <= 0 || p->H <= 0 || p->M <= 0 || p->N <= 0 ||
        p->D <= 0 || p->DV <= 0) {
        fprintf(stderr, "error: invalid dimensions in '%s'\n", meta_path);
        return -1;
    }
    if (p->scale == 0.0f) p->scale = 1.0f / sqrtf((float)p->D);
    if (p->kv_block <= 0)  p->kv_block = 64;

    /* Allocate tensors */
    size_t q_count  = (size_t)p->B * p->H * p->M * p->D;
    size_t k_count  = (size_t)p->B * p->H * p->N * p->D;
    size_t v_count  = (size_t)p->B * p->H * p->N * p->DV;
    size_t o_count  = (size_t)p->B * p->H * p->M * p->DV;

    float *qbuf = aligned_alloc_f32(q_count);
    float *kbuf = aligned_alloc_f32(k_count);
    float *vbuf = aligned_alloc_f32(v_count);
    float *obuf = aligned_alloc_f32(o_count);

    if (!qbuf || !kbuf || !vbuf || !obuf) {
        fprintf(stderr, "error: memory allocation failed\n");
        aligned_free_f32(qbuf);
        aligned_free_f32(kbuf);
        aligned_free_f32(vbuf);
        aligned_free_f32(obuf);
        return -1;
    }
    memset(obuf, 0, o_count * sizeof(float));

    /* Load binary data */
    if (read_bin_f32(q_path, qbuf, q_count) != 0 ||
        read_bin_f32(k_path, kbuf, k_count) != 0 ||
        read_bin_f32(v_path, vbuf, v_count) != 0) {
        aligned_free_f32(qbuf);
        aligned_free_f32(kbuf);
        aligned_free_f32(vbuf);
        aligned_free_f32(obuf);
        return -1;
    }

    p->q   = qbuf;
    p->k   = kbuf;
    p->v   = vbuf;
    p->out = obuf;
    return 0;
}

void sdpa_free_params(SDPAParams *p)
{
    if (!p) return;
    /* Cast away const -- we own these buffers from sdpa_load_params. */
    aligned_free_f32((void *)(uintptr_t)p->q);
    aligned_free_f32((void *)(uintptr_t)p->k);
    aligned_free_f32((void *)(uintptr_t)p->v);
    aligned_free_f32(p->out);
    memset(p, 0, sizeof(*p));
}

/* ------------------------------------------------------------------ */
/*  Binary output                                                      */
/* ------------------------------------------------------------------ */

int sdpa_write_output(const char *bin_path, const SDPAParams *p)
{
    size_t count = (size_t)p->B * p->H * p->M * p->DV;
    FILE *f = fopen(bin_path, "wb");
    if (!f) {
        fprintf(stderr, "error: cannot create '%s': %s\n",
                bin_path, strerror(errno));
        return -1;
    }
    size_t wrote = fwrite(p->out, sizeof(float), count, f);
    fclose(f);
    if (wrote != count) {
        fprintf(stderr, "error: short write to '%s'\n", bin_path);
        return -1;
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/*  Timer                                                              */
/* ------------------------------------------------------------------ */

uint64_t timer_ns(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

/* ------------------------------------------------------------------ */
/*  CPU query                                                          */
/* ------------------------------------------------------------------ */

int sdpa_num_cpus(void)
{
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    return (n > 0) ? (int)n : 1;
}

/* ------------------------------------------------------------------ */
/*  Debug info                                                         */
/* ------------------------------------------------------------------ */

void sdpa_print_info(const SDPAParams *p, FILE *out)
{
    fprintf(out, "SDPA params: B=%d H=%d M=%d N=%d D=%d DV=%d "
            "scale=%.6f kv_block=%d threads=%d pin=%d\n",
            p->B, p->H, p->M, p->N, p->D, p->DV,
            p->scale, p->kv_block, p->num_threads,
            p->pin_threads_to_cores);
}
