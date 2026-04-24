#!/usr/bin/env python3
"""
Benchmark SDPA tasks and compute speedups / grades.

Usage:
  python3 test/bench.py               # benchmark all tasks
  python3 test/bench.py --task 3      # benchmark a single task
  python3 test/bench.py --check-only  # correctness check only (no timing)
"""
import subprocess
import sys
import re
import os

# -- Configuration --
SMALL_DATA  = "data/small/meta.txt"
LARGE_DATA  = "data/large/meta.txt"
CHECK_SCRIPT = "test/check_correctness.py"
REPEAT  = 5
WARMUP  = 1
THREADS = 4

# Grading parameters (speedup relative to Task 1)
GRADE = {
    1: {"corr": 15, "perf": 0,  "perf_max_s": 1.0},
    2: {"corr": 10, "perf": 10, "perf_max_s": 1.0},   # full perf if S >= 0.9
    3: {"corr": 10, "perf": 15, "perf_max_s": 3.0},   # full perf if S >= 3.0
    4: {"corr": 10, "perf": 15, "perf_max_s": 6.0},   # full perf if S >= 6.0
}


def run_task(task_id, data_path, repeat=REPEAT, warmup=WARMUP,
             threads=THREADS, quiet=True):
    """Run a task binary and return average time in ms, or None on failure."""
    binary = f"./task{task_id}"
    if not os.path.exists(binary):
        print(f"  Binary '{binary}' not found. Run 'make task{task_id}' first.")
        return None

    cmd = [binary, "--data", data_path,
           "--repeat", str(repeat), "--warmup", str(warmup)]
    if task_id == 4:
        cmd += ["--threads", str(threads), "--pin-cores"]
    if quiet:
        cmd += ["--quiet"]

    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"  Task {task_id} execution failed:")
        print(f"    {result.stderr.strip()}")
        return None

    match = re.search(r'avg_time_ms:\s*([\d.]+)', result.stderr)
    if not match:
        print(f"  Task {task_id}: could not parse timing from stderr")
        return None
    return float(match.group(1))


def check_correctness(task_id, data_path):
    """Run correctness check. Returns True if passed."""
    binary = f"./task{task_id}"
    if not os.path.exists(binary):
        print(f"  Binary '{binary}' not found.")
        return False

    # Run the task to produce output
    cmd = [binary, "--data", data_path, "--repeat", "1", "--warmup", "0",
           "--quiet"]
    if task_id == 4:
        cmd += ["--threads", str(THREADS), "--pin-cores"]

    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"  Task {task_id} execution failed: {result.stderr.strip()}")
        return False

    # Parse out_path from meta.txt
    out_path = None
    with open(data_path) as f:
        for line in f:
            parts = line.strip().split(None, 1)
            if len(parts) == 2 and parts[0] == "out_path":
                out_path = parts[1]
    if not out_path:
        print(f"  No out_path in {data_path}")
        return False

    # Check correctness
    result = subprocess.run(
        [sys.executable, CHECK_SCRIPT, data_path, out_path],
        capture_output=True, text=True)
    print(result.stdout, end="")
    return result.returncode == 0


def compute_perf_points(task_id, speedup):
    """Compute performance points for a task given speedup over Task 1."""
    g = GRADE[task_id]
    if g["perf"] == 0:
        return 0

    if task_id == 2:
        # Task 2: full points if S >= 0.9
        if speedup >= 0.9:
            return g["perf"]
        else:
            return max(0, int(speedup / 0.9 * g["perf"]))
    else:
        # Tasks 3, 4: linear scale up to perf_max_s
        s_clamped = min(speedup, g["perf_max_s"])
        return max(0, round((s_clamped - 1.0) / (g["perf_max_s"] - 1.0) * g["perf"]))


def main():
    tasks = [1, 2, 3, 4]
    check_only = False

    for arg in sys.argv[1:]:
        if arg == "--check-only":
            check_only = True
        elif arg == "--task":
            idx = sys.argv.index(arg)
            tasks = [int(sys.argv[idx + 1])]

    # Verify data exists
    for data_path in [SMALL_DATA, LARGE_DATA]:
        if not os.path.exists(data_path):
            print(f"Data not found: {data_path}")
            print("Run: make gen_data")
            sys.exit(1)

    print("=" * 60)
    print("SDPA Lab -- Correctness & Performance Evaluation")
    print("=" * 60)

    # -- Phase 1: Correctness on small dataset --
    print(f"\n--- Correctness Check (using {SMALL_DATA}) ---")
    correct = {}
    for tid in tasks:
        print(f"\nTask {tid}:")
        correct[tid] = check_correctness(tid, SMALL_DATA)

    if check_only:
        print("\n--- Summary ---")
        for tid in tasks:
            status = "\033[0;32mPASS\033[0m" if correct[tid] else "\033[0;31mFAIL\033[0m"
            print(f"  Task {tid}: {status}")
        sys.exit(0 if all(correct.get(t, False) for t in tasks) else 1)

    # -- Phase 2: Benchmark on large dataset --
    print(f"\n--- Performance Benchmark (using {LARGE_DATA}) ---")
    print(f"    repeat={REPEAT}, warmup={WARMUP}, threads={THREADS}")

    times = {}
    for tid in tasks:
        if not correct.get(tid, False):
            print(f"\nTask {tid}: SKIPPED (correctness failed)")
            continue
        print(f"\nTask {tid}:")
        if tid == 4:
            # Try multiple thread counts, keep the best
            best_t = None
            best_nt = 0
            for nt in [1, 2, 3, 4]:
                t = run_task(tid, LARGE_DATA, repeat=REPEAT, warmup=WARMUP,
                             threads=nt)
                if t is not None:
                    print(f"  threads={nt}: {t:.3f} ms")
                    if best_t is None or t < best_t:
                        best_t = t
                        best_nt = nt
            if best_t is not None:
                times[tid] = best_t
                print(f"  best: threads={best_nt} -> {best_t:.3f} ms")
        else:
            t = run_task(tid, LARGE_DATA, repeat=REPEAT, warmup=WARMUP)
            if t is not None:
                times[tid] = t
                print(f"  avg_time: {t:.3f} ms")

    # -- Phase 3: Grading --
    baseline = times.get(1)
    print("\n" + "=" * 60)
    print(f"{'Task':<8} {'Correct':<10} {'Time(ms)':<12} {'Speedup':<10} "
          f"{'Corr pts':<10} {'Perf pts':<10} {'Total':<8}")
    print("-" * 60)

    grand_total = 0
    for tid in tasks:
        corr_ok = correct.get(tid, False)
        t = times.get(tid)
        speedup = baseline / t if (baseline and t) else 0.0

        corr_pts = GRADE[tid]["corr"] if corr_ok else 0
        perf_pts = compute_perf_points(tid, speedup) if (corr_ok and t) else 0
        total = corr_pts + perf_pts
        grand_total += total

        corr_str = "\033[0;32mPASS\033[0m" if corr_ok else "\033[0;31mFAIL\033[0m"
        t_str = f"{t:.1f}" if t else "N/A"
        s_str = f"{speedup:.2f}x" if (baseline and t) else "N/A"

        print(f"  {tid:<6} {corr_str:<19} {t_str:<12} {s_str:<10} "
              f"{corr_pts:<10} {perf_pts:<10} {total:<8}")

    print("-" * 60)
    print(f"  Code total: {grand_total}/85  (+ 15 pts report)")
    print("=" * 60)


if __name__ == "__main__":
    main()
