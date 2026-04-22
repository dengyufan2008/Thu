Prob 1. 设 $\mathcal N^t(x) = \mathcal N(x, t) = \frac{1}{2\sqrt {\pi t}}e^{-\frac{x^2}{4t}}$. 证明 $\int_{-\infty}^{+\infty} \mathcal N(x, t) \text{d}x = 1$, 且对于有界连续函数 $f:R \to R$, $u(x, t) = (\mathcal N^t * f)(x)$ 是热传导方程初值问题 $u_t-u_{xx}=0$, $u(x, 0)=f(x)$ 的解.

我们有 $(\int_{-\infty}^{+\infty} e^{-x^2} \text{d}x)^2 = \int_{-\infty}^{+\infty}\int_{-\infty}^{+\infty} e^{-(x^2+y^2)} \text{d}x \text{d}y = \int_0^{2\pi}\int_0^{+\infty} e^{-r^2}r \text{d}r\text{d}\theta = 2\pi \int_0^{+\infty} e^{-r^2}r \text{d}r = \pi \int_0^{+\infty} e^{-t} \text{d}t = \pi$. 故 $\int_{-\infty}^{+\infty} e^{-x^2} \text{d}x = \sqrt \pi$.

有 $\int_{-\infty}^{+\infty} \mathcal N(x, t) \text{d}x = \int_{-\infty}^{+\infty} \frac{1}{2\sqrt {\pi t}}e^{-\frac{x^2}{4t}} \text{d}x = \int_{-\infty}^{+\infty} \frac{1}{\sqrt {\pi}}e^{-x^2} \text{d}x = 1$.

当 $t \to 0$ 时, $\int_{-\delta}^{\delta} \mathcal N_t(x) \text{d}x \to 1 \forall \delta > 0$. 则 $(\mathcal N^t * f)(x) = f(x) \int_{-\delta}^\delta N^t(h) \text{d}h \to f(x)$.

$u_t(x, t) = \frac{\partial}{\partial t} \int_{-\infty}^{+\infty} \mathcal N(x-h, t) f(h) \text{d}h = \int_{-\infty}^{+\infty} \mathcal N_t(x-h, t) f(h) \text{d}h$.

$u_{xx}(x, t) = \frac{\partial^2}{\partial x^2} \int_{-\infty}^{+\infty} \mathcal N(x-h, t) f(h) \text{d}h = \int_{-\infty}^{+\infty} \mathcal N_{xx}(x-h, t) f(h) \text{d}h$.

只需证明 $\mathcal N_{xx} = \mathcal N_t$. 不难计算有 $N_{xx} = \frac{x^2-2t}{8t^2\sqrt {\pi t}} e^{-\frac{x^2}{4t}}$, $N_t = \frac{x^2-2t}{8t^2\sqrt {\pi t}}e^{-\frac{x^2}{4t}}$.
