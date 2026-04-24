#!/usr/bin/env python3
"""
Compute reference SDPA outputs using NumPy.
Run: python3 data/reference_sdpa.py  (after gen_data.py)
"""
import numpy as np
import os
import sys

DATASETS = ["tiny", "small", "medium", "large"]


def load_meta(path):
    """Parse a key-value meta.txt file."""
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


def compute_reference(name):
    """Compute and save reference output for one dataset."""
    meta_path = os.path.join("data", name, "meta.txt")
    if not os.path.exists(meta_path):
        print(f"  {name}: meta.txt not found, skipping")
        return

    meta = load_meta(meta_path)
    B, H, M, N = meta["B"], meta["H"], meta["M"], meta["N"]
    D, DV = meta["D"], meta["DV"]
    scale = meta["scale"]

    Q = np.fromfile(meta["q_path"], dtype=np.float32).reshape(B, H, M, D)
    K = np.fromfile(meta["k_path"], dtype=np.float32).reshape(B, H, N, D)
    V = np.fromfile(meta["v_path"], dtype=np.float32).reshape(B, H, N, DV)

    # Attention: softmax(Q @ K^T * scale) @ V
    scores = np.matmul(Q, K.transpose(0, 1, 3, 2)) * scale  # [B,H,M,N]
    scores_max = scores.max(axis=-1, keepdims=True)
    exp_scores = np.exp(scores - scores_max)
    weights = exp_scores / exp_scores.sum(axis=-1, keepdims=True)
    out = np.matmul(weights, V).astype(np.float32)           # [B,H,M,DV]

    ref_path = meta["ref_path"]
    out.tofile(ref_path)
    print(f"  {name:8s}: checksum={out.sum():.6f}  "
          f"shape={out.shape}  -> {ref_path}")


def main():
    print("Computing reference SDPA outputs...")
    for name in DATASETS:
        compute_reference(name)
    print("Done.")


if __name__ == "__main__":
    main()
