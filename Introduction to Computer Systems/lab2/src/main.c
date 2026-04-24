/*
 * main.c -- CLI driver for the SDPA lab.
 * DO NOT MODIFY THIS FILE.
 *
 * Usage:
 *   ./task1 --data data/small/meta.txt [--repeat 5] [--warmup 1]
 *   ./task4 --data data/large/meta.txt --threads 4 [--kv-block 64] [--pin-cores]
 *
 * The binary is compiled with -DTASK_ID=1..4, which selects the
 * student function to call (sdpa_naive / sdpa_online / sdpa_neon / sdpa_threaded).
 *
 * Output:
 *   - The output tensor is written to the 'out_path' specified in meta.txt.
 *   - Timing information is printed to stderr in machine-readable format:
 *       avg_time_ms: <value>
 */
#include "sdpa.h"
#include "sdpa_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TASK_ID
#error "TASK_ID must be defined (1, 2, 3, or 4)"
#endif

typedef int (*sdpa_fn)(const SDPAParams *);

static sdpa_fn get_task_fn(void)
{
#if   TASK_ID == 1
    return sdpa_naive;
#elif TASK_ID == 2
    return sdpa_online;
#elif TASK_ID == 3
    return sdpa_neon;
#elif TASK_ID == 4
    return sdpa_threaded;
#else
#error "TASK_ID must be 1, 2, 3, or 4"
#endif
}

static const char *get_task_name(void)
{
#if   TASK_ID == 1
    return "naive (scalar)";
#elif TASK_ID == 2
    return "online softmax (scalar)";
#elif TASK_ID == 3
    return "NEON SIMD";
#elif TASK_ID == 4
    return "multi-threaded + NEON";
#else
    return "unknown";
#endif
}

static void usage(const char *prog)
{
    fprintf(stderr,
        "Usage: %s --data <meta.txt> [options]\n"
        "\n"
        "Options:\n"
        "  --data <path>       Path to metadata file (required)\n"
        "  --threads <N>       Number of threads (Task 4, default: 4)\n"
        "  --kv-block <K>      KV block size (default: from meta.txt)\n"
        "  --pin-cores         Pin threads to CPU cores\n"
        "  --warmup <W>        Warmup iterations (default: 1)\n"
        "  --repeat <R>        Timed iterations (default: 3)\n"
        "  --quiet             Suppress info output\n"
        , prog);
}

int main(int argc, char **argv)
{
    const char *meta_path = NULL;
    int num_threads = 4;
    int kv_block_override = 0;
    int pin_cores = 0;
    int warmup = 1;
    int repeat = 3;
    int quiet = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--data") == 0 && i + 1 < argc) {
            meta_path = argv[++i];
        } else if (strcmp(argv[i], "--threads") == 0 && i + 1 < argc) {
            num_threads = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--kv-block") == 0 && i + 1 < argc) {
            kv_block_override = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--pin-cores") == 0) {
            pin_cores = 1;
        } else if (strcmp(argv[i], "--warmup") == 0 && i + 1 < argc) {
            warmup = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--repeat") == 0 && i + 1 < argc) {
            repeat = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--quiet") == 0) {
            quiet = 1;
        } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            usage(argv[0]);
            return 0;
        } else {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
            usage(argv[0]);
            return 1;
        }
    }

    if (!meta_path) {
        fprintf(stderr, "error: --data is required\n");
        usage(argv[0]);
        return 1;
    }

    /* Load data */
    SDPAParams params;
    char out_path[512], ref_path[512];
    if (sdpa_load_params(meta_path, &params,
                         out_path, sizeof(out_path),
                         ref_path, sizeof(ref_path)) != 0) {
        return 1;
    }

    /* Apply CLI overrides */
    params.num_threads = num_threads;
    params.pin_threads_to_cores = pin_cores;
    if (kv_block_override > 0)
        params.kv_block = kv_block_override;

    if (!quiet) {
        fprintf(stderr, "Task %d: %s\n", TASK_ID, get_task_name());
        sdpa_print_info(&params, stderr);
    }

    sdpa_fn fn = get_task_fn();
    if (warmup < 0) warmup = 0;
    if (repeat < 1) repeat = 1;

    /* Warmup */
    for (int w = 0; w < warmup; w++) {
        int rc = fn(&params);
        if (rc != 0) {
            fprintf(stderr, "error: task function returned %d during warmup\n", rc);
            sdpa_free_params(&params);
            return 1;
        }
    }

    /* Timed runs */
    uint64_t total_ns = 0;
    for (int r = 0; r < repeat; r++) {
        /* Clear output before each run */
        memset(params.out, 0, (size_t)params.B * params.H * params.M * params.DV * sizeof(float));

        uint64_t t0 = timer_ns();
        int rc = fn(&params);
        uint64_t t1 = timer_ns();

        if (rc != 0) {
            fprintf(stderr, "error: task function returned %d on run %d\n", rc, r);
            sdpa_free_params(&params);
            return 1;
        }
        total_ns += (t1 - t0);

        if (!quiet) {
            fprintf(stderr, "  run %d/%d: %.3f ms\n",
                    r + 1, repeat, (double)(t1 - t0) / 1e6);
        }
    }

    double avg_ms = (double)total_ns / (double)repeat / 1e6;
    fprintf(stderr, "avg_time_ms: %.3f\n", avg_ms);

    /* Write output */
    if (out_path[0] != '\0') {
        if (sdpa_write_output(out_path, &params) != 0) {
            sdpa_free_params(&params);
            return 1;
        }
        if (!quiet)
            fprintf(stderr, "Output written to %s\n", out_path);
    }

    sdpa_free_params(&params);
    return 0;
}
