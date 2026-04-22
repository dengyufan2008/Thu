Prob 1. 证明对 $x \ge 0$, $\int_0^{+\infty} \frac{\ln(1+x^2t^2)}{1+t^2} \text{d}t = \pi \ln(1+x)$.

设 $f(x) = \int_0^{+\infty} \frac{\ln(1+x^2t^2)}{1+t^2} \text{d}t$. $f(0) = 0$, 当 $x > 0$ 时有 $f'(x) = 2x\int_0^{+\infty} \frac{t^2}{(1+t^2)(1+x^2t^2)} \text{d}t = \frac{2x}{1-x^2}\int_0^{+\infty} \frac{1}{1+x^2t^2} - \frac{1}{1+t^2} \text{d}t = \frac{2x}{1-x^2}(\frac{\pi}{2x} - \frac{\pi}{2}) = \frac{\pi}{1+x}$. 故 $f(x) = \pi\ln(1+x)$.
