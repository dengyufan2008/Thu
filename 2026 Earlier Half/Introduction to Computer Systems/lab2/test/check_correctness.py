#!/usr/bin/env python3
"""
Check student SDPA output against the NumPy reference.

Usage: python3 test/check_correctness.py <meta.txt> <student_out.bin>

Exits 0 on success, 1 on failure.
"""
import numpy as np
import sys
import os

ATOL = 1e-4
RTOL = 1e-4


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


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <meta.txt> <student_out.bin>")
        sys.exit(1)

    meta_path = sys.argv[1]
    out_path  = sys.argv[2]

    meta = load_meta(meta_path)
    B, H, M, DV = meta["B"], meta["H"], meta["M"], meta["DV"]
    expected_count = B * H * M * DV

    # Load student output
    if not os.path.exists(out_path):
        print(f"\033[0;31mFAILED\033[0m: output file '{out_path}' not found")
        sys.exit(1)

    student = np.fromfile(out_path, dtype=np.float32)
    if student.size != expected_count:
        print(f"\033[0;31mFAILED\033[0m: wrong output size: "
              f"{student.size} vs expected {expected_count}")
        sys.exit(1)

    # Load reference
    ref_path = meta["ref_path"]
    if not os.path.exists(ref_path):
        print(f"\033[0;31mFAILED\033[0m: reference file '{ref_path}' not found. "
              f"Run: python3 data/reference_sdpa.py")
        sys.exit(1)

    ref = np.fromfile(ref_path, dtype=np.float32)
    if ref.size != expected_count:
        print(f"\033[0;31mFAILED\033[0m: reference size mismatch")
        sys.exit(1)

    # Compare
    diff = np.abs(student - ref)
    max_abs_err  = float(np.max(diff))
    mean_abs_err = float(np.mean(diff))
    ok = np.allclose(student, ref, atol=ATOL, rtol=RTOL)

    print(f"  max_abs_error:  {max_abs_err:.2e}")
    print(f"  mean_abs_error: {mean_abs_err:.2e}")

    if ok:
        print(f"  \033[0;32mCORRECT\033[0m (atol={ATOL}, rtol={RTOL})")
    else:
        # Show first few mismatches for debugging
        mismatch = np.where(np.abs(student - ref) > ATOL + RTOL * np.abs(ref))[0]
        n_show = min(5, len(mismatch))
        print(f"  \033[0;31mFAILED\033[0m ({len(mismatch)} mismatches, "
              f"atol={ATOL}, rtol={RTOL})")
        for i in range(n_show):
            idx = mismatch[i]
            print(f"    [{idx}]: student={student[idx]:.8f} "
                  f"ref={ref[idx]:.8f} diff={diff[idx]:.2e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
