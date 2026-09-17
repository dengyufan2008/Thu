Prob 1. 设 $\alpha > 0$, 讨论积分的收敛性: $\int_0^{+\infty} \frac{\sin x}{x + \alpha}e^{-\alpha x} \text{d}x$, $\int_0^{+\infty} \frac{x\sin \alpha x}{\alpha(1+x^2)} \text{d}x$, $\int_0^1 \frac{1}{x^\alpha}\sin \frac{1}{x} \text{d}x$.

$\int_0^{+\infty} |\frac{\sin x}{x + \alpha}e^{-\alpha x}| \text{d}x \le \int_0^{+\infty} \frac{e^{-\alpha x}}{\alpha} \text{d}x = \frac{1}{\alpha^2}$. 故绝对收敛.

$\int_0^{+\infty} |\frac{x\sin \alpha x}{\alpha(1+x^2)}| \text{d}x$ 与 $\int_0^{+\infty} \frac{1}{x} \text{d}x$ 收敛性相同, 故不绝对收敛. 但是 $\int_0^{+\infty} \frac{x\sin \alpha x}{\alpha(1+x^2)} \text{d}x = \int_0^{+\infty} \frac{x\sin x}{\alpha(\alpha^2+x^2)} \text{d}x$ 与 $\int_1^{+\infty} \frac{\sin x}{x} \text{d}x$ 收敛性相同, 故条件收敛.

$\int_0^1 \frac{1}{x^\alpha}\sin \frac{1}{x} \text{d}x = \int_1^{+\infty} x^{\alpha-2} \sin x \text{d}x$. 故当 $\alpha < 1$ 时绝对收敛, $\alpha = 1$ 时条件收敛, $\alpha > 1$ 时发散.
