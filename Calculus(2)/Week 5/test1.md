Prob 1. 证明 Laplace 变换把卷积变成点积: $\mathscr{L}[f * g] = \mathscr{L}[f] \cdot \mathscr{L}[g]$.

$\mathscr{L}[f * g](t) = \int_0^\infty e^{-tx}\int_0^x f(y)g(x-y) \text{d}y\text{d}x = \int_0^\infty f(y) \int_y^\infty e^{-tx}g(x-y) \text{d}x\text{d}y = \int_0^\infty f(y) \int_0^\infty e^{-t(x+y)}g(x) \text{d}x\text{d}y = \int_0^\infty e^{-ty}f(y) \text{d}y \int_0^\infty e^{-tx}g(x) \text{d}x = \mathscr{L}[f](t) \cdot \mathscr{L}[g](t)$.

---

Prob 2. 解方程 $y(x)=h(x)+\int_0^x y(x-t)f(t)\text{d}t$.

有 $\mathscr{L}[y] = \mathscr{L}[h] + \mathscr{L}[y] \mathscr{L}[f]$, $\mathscr{L}[y] = \frac{\mathscr{L}[h]}{1-\mathscr{L}[f]} = \mathscr{L}[h](1+\mathscr{L}[f]+\mathscr{L}[f]^2+\cdots)$.

故 $y=h + h*f + h*f^2 + \cdots$.
