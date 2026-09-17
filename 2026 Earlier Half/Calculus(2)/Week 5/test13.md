Prob 1. 设 $I(y) = \int_0^{+\infty} e^{-x^2} \sin(2xy) \text{d}x$, 证明 $I(y) = e^{-y^2} \int_0^y e^{t^2} \text{d}t$.

有 $I'(y) = \int_0^{+\infty} 2xe^{-x^2} \cos(2xy) \text{d}x$, 则 $2yI + I' = \int_0^{+\infty} e^{-x^2} [2x\cos(2xy)+2y\sin(2xy)] \text{d}x = -e^{-x^2}\cos(2xy) \Big|_{x=0}^{+\infty} = 1$.

发现 $I(y) = e^{-y^2} \int_0^y e^{t^2} \text{d}t$ 是微分方程 $2yI+I'=1$, $I(0) = 0$ 的解.
