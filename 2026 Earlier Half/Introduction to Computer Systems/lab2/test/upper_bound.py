#!/usr/bin/env python3
"""
Upper-bound benchmark: compare student implementations against optimized
library implementations.

Upper bounds:
  1. PyTorch scaled_dot_product_attention (operator-level optimized)
  2. NumPy (matmul + softmax, OpenBLAS)
  3. Theoretical peak FLOPS for Cortex-A72

Usage: python3 test/upper_bound.py
"""
import numpy as np
import time
import subprocess
import sys
import os
import re
import torch


def load_meta(path):
    meta = {}
    with open(path) as f:
        for line in f:
            parts = line.strip().split(None, 1)
            if len(parts) != 2:
                continue
            key, val = parts
            try:
                val = int(val)
            except ValueError:
                try:
                    val = float(val)
                except ValueError:
                    pass
            meta[key] = val
    return meta


def benchmark_numpy(meta, repeats=5, warmup=1):
    """Benchmark NumPy SDPA (matmul + softmax)."""
    B, H, M, N = meta["B"], meta["H"], meta["M"], meta["N"]
    D, DV = meta["D"], meta["DV"]
    scale = meta["scale"]

    Q = np.fromfile(meta["q_path"], dtype=np.float32).reshape(B, H, M, D)
    K = np.fromfile(meta["k_path"], dtype=np.float32).reshape(B, H, N, D)
    V = np.fromfile(meta["v_path"], dtype=np.float32).reshape(B, H, N, DV)

    def sdpa_numpy():
        scores = np.matmul(Q, K.transpose(0, 1, 3, 2)) * scale
        scores -= scores.max(axis=-1, keepdims=True)
        exp_s = np.exp(scores)
        weights = exp_s / exp_s.sum(axis=-1, keepdims=True)
        return np.matmul(weights, V)

    for _ in range(warmup):
        sdpa_numpy()

    times = []
    for _ in range(repeats):
        t0 = time.perf_counter()
        sdpa_numpy()
        t1 = time.perf_counter()
        times.append((t1 - t0) * 1000.0)

    return min(times)


def benchmark_pytorch(meta, repeats=5, warmup=2):
    """Benchmark PyTorch scaled_dot_product_attention."""
    B, H, M, N = meta["B"], meta["H"], meta["M"], meta["N"]
    D, DV = meta["D"], meta["DV"]
    scale = meta["scale"]

    Q_np = np.fromfile(meta["q_path"], dtype=np.float32).reshape(B, H, M, D)
    K_np = np.fromfile(meta["k_path"], dtype=np.float32).reshape(B, H, N, D)
    V_np = np.fromfile(meta["v_path"], dtype=np.float32).reshape(B, H, N, DV)

    Q = torch.from_numpy(Q_np)
    K = torch.from_numpy(K_np)
    V = torch.from_numpy(V_np)

    fn = lambda: torch.nn.functional.scaled_dot_product_attention(
        Q, K, V, scale=scale)

    for _ in range(warmup):
        fn()

    times = []
    for _ in range(repeats):
        t0 = time.perf_counter()
        fn()
        t1 = time.perf_counter()
        times.append((t1 - t0) * 1000.0)

    return min(times)


def benchmark_student_task(task_id, meta_path, repeats=5):
    """Run a student task binary and return best time."""
    binary = f"./task{task_id}"
    if not os.path.exists(binary):
        return None

    if task_id == 4:
        best = None
        for nt in [1, 2, 3, 4]:
            cmd = [binary, "--data", meta_path, "--repeat", str(repeats),
                   "--warmup", "1", "--quiet", "--threads", str(nt), "--pin-cores"]
            result = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
            if result.returncode != 0:
                continue
            match = re.search(r'avg_time_ms:\s*([\d.]+)', result.stderr)
            if match:
                t = float(match.group(1))
                if best is None or t < best:
                    best = t
        return best
    else:
        cmd = [binary, "--data", meta_path, "--repeat", str(repeats),
               "--warmup", "1", "--quiet"]
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
        if result.returncode != 0:
            return None
        match = re.search(r'avg_time_ms:\s*([\d.]+)', result.stderr)
        return float(match.group(1)) if match else None


def compute_theoretical_peak(meta):
    """Compute theoretical peak and total FLOPS."""
    B, H, M, N = meta["B"], meta["H"], meta["M"], meta["N"]
    D, DV = meta["D"], meta["DV"]

    flops_per_row = N * (2 * D + 5 + 2 * DV)
    total_flops = B * H * M * flops_per_row

    freq_ghz = 1.5
    flops_per_cycle = 16  # 2 FMA pipes * 4-wide * 2 (FMA=2ops)
    cores = 4
    peak_gflops = freq_ghz * flops_per_cycle * cores

    return total_flops, peak_gflops


def main():
    data_path = "data/large/meta.txt"
    if not os.path.exists(data_path):
        print("Data not found. Run: make gen_data")
        sys.exit(1)

    meta = load_meta(data_path)
    total_flops, peak_gflops = compute_theoretical_peak(meta)

    print("=" * 70)
    print("SDPA Performance Comparison -- Upper Bounds")
    print(f"Dataset: large (B={meta['B']} H={meta['H']} M={meta['M']} "
          f"N={meta['N']} D={meta['D']} DV={meta['DV']})")
    print(f"Platform: Raspberry Pi 4B (4x Cortex-A72 @ 1.5 GHz)")
    print(f"Total FLOPS: {total_flops/1e9:.3f} GFLOP, "
          f"Peak: {peak_gflops:.0f} GFLOPS")
    print("=" * 70)

    results = []  # (name, time_ms, note)

    # Theoretical peak
    min_ms = total_flops / (peak_gflops * 1e9) * 1e3
    results.append(("Theoretical peak (4 cores)", min_ms,
                     "unachievable -- memory-bound"))

    # PyTorch
    print("\nBenchmarking PyTorch SDPA...")
    pt_ms = benchmark_pytorch(meta)
    results.append(("PyTorch SDPA", pt_ms, ""))
    print(f"  PyTorch: {pt_ms:.1f} ms")

    # NumPy
    print("Benchmarking NumPy...")
    np_ms = benchmark_numpy(meta)
    results.append(("NumPy (matmul + softmax)", np_ms, ""))
    print(f"  NumPy: {np_ms:.1f} ms")

    # Student tasks
    print("Benchmarking student implementations...")
    task_names = {1: "Task 1 (naive scalar)",
                  2: "Task 2 (online softmax)",
                  3: "Task 3 (NEON SIMD)",
                  4: "Task 4 (multi-threaded + NEON)"}
    for tid in [1, 2, 3, 4]:
        t = benchmark_student_task(tid, data_path)
        if t:
            results.append((task_names[tid], t, ""))
            print(f"  Task {tid}: {t:.1f} ms")

    # Summary table
    print(f"\n{'=' * 70}")
    print(f"{'Implementation':<42} {'Time(ms)':>9} {'GFLOPS':>8} {'% Peak':>8}")
    print(f"{'-' * 70}")
    for name, ms, note in results:
        gflops = total_flops / (ms / 1e3) / 1e9
        pct = gflops / peak_gflops * 100
        suffix = f"  ({note})" if note else ""
        print(f"{name:<42} {ms:>9.1f} {gflops:>8.2f} {pct:>7.1f}%{suffix}")
    print(f"{'=' * 70}")


if __name__ == "__main__":
    main()
