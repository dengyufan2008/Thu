Prob 1. 证明对 $-1 < r < 1$ 有 $\int_0^\pi \ln(1-2r\cos x + r^2)\text{d}x = 0$.

设 $f(r) = \int_0^\pi \ln(1-2r\cos x + r^2)\text{d}x = \int_0^\pi \ln ((1-r\cos x)^2 + r^2\sin^2 x) \text{d}x = \int_0^\pi \ln(|1-re^{ix}|^2) \text{d}x = \int_0^{2\pi} \ln|1-re^{ix}| \text{d}x$, 由于 $\ln(|1-re^{ix}|^2)$ 是偶函数且以 $2\pi$ 为周期.

根据 ds 的描述, $\ln |1-rz|$ 是调和的, 故 $\int_0^{2\pi} \ln|1-re^{ix}| \text{d}x = \frac{1}{2\pi} \ln|1| = 0$.
