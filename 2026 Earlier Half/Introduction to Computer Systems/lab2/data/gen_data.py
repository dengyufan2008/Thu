#!/usr/bin/env python3
"""
Generate Q, K, V test tensors as binary float32 files for the SDPA lab.
Run: python3 data/gen_data.py
"""
import numpy as np
import os

DATASETS = {
    "tiny":   {"B": 1, "H": 1,  "M": 4,   "N": 4,   "D": 16, "DV": 16},
    "small":  {"B": 1, "H": 4,  "M": 64,  "N": 64,  "D": 64, "DV": 64},
    "medium": {"B": 1, "H": 8,  "M": 256, "N": 256, "D": 64, "DV": 64},
    "large":  {"B": 2, "H": 8,  "M": 512, "N": 512, "D": 64, "DV": 64},
}

SEED = 42


def gen_dataset(name, params):
    """Generate one dataset: Q.bin, K.bin, V.bin, and meta.txt."""
    rng = np.random.default_rng(SEED + abs(hash(name)) % (2**31))
    B, H, M, N, D, DV = (params["B"], params["H"], params["M"],
                          params["N"], params["D"], params["DV"])

    Q = (rng.standard_normal((B, H, M, D))  * 0.5).astype(np.float32)
    K = (rng.standard_normal((B, H, N, D))  * 0.5).astype(np.float32)
    V = (rng.standard_normal((B, H, N, DV)) * 0.5).astype(np.float32)

    out_dir = os.path.join("data", name)
    os.makedirs(out_dir, exist_ok=True)

    Q.tofile(os.path.join(out_dir, "Q.bin"))
    K.tofile(os.path.join(out_dir, "K.bin"))
    V.tofile(os.path.join(out_dir, "V.bin"))

    scale = 1.0 / np.sqrt(float(D))
    meta = {
        "B": B, "H": H, "M": M, "N": N, "D": D, "DV": DV,
        "scale": round(scale, 8),
        "kv_block": 64,
        "q_path":   os.path.join(out_dir, "Q.bin"),
        "k_path":   os.path.join(out_dir, "K.bin"),
        "v_path":   os.path.join(out_dir, "V.bin"),
        "out_path": os.path.join(out_dir, "out.bin"),
        "ref_path": os.path.join(out_dir, "ref.bin"),
    }

    with open(os.path.join(out_dir, "meta.txt"), "w") as f:
        for k, v in meta.items():
            f.write(f"{k} {v}\n")

    total_bytes = Q.nbytes + K.nbytes + V.nbytes
    print(f"  {name:8s}: Q{Q.shape} K{K.shape} V{V.shape}  "
          f"({total_bytes / 1024:.1f} KB)")


def main():
    print("Generating SDPA test datasets...")
    for name, params in DATASETS.items():
        gen_dataset(name, params)
    print("Done. Now run: python3 data/reference_sdpa.py")


if __name__ == "__main__":
    main()
