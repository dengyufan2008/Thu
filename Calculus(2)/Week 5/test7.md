Prob 1. 计算 $\int_0^{+\infty} \frac{\cos ax - \cos bx}{x^2} \text{d}x$, $a, b > 0$.

设 $f(a) = \int_0^{+\infty} \frac{\cos ax - \cos bx}{x^2} \text{d}x$, 则 $f'(a) = -\int_0^{+\infty} \frac{\sin ax}{x} \text{d}x = -\int_0^{+\infty} \frac{\sin x}{x} \text{d}x = -\frac{\pi}{2}$. 根据对称性得 $f(a) = \frac{\pi}{2}(b-a)$.

Prob 2. 计算 $\int_0^{+\infty} \frac{1-\cos bx}{x}e^{-x}\text{d}x$.

设 $f(b) = \int_0^{+\infty} \frac{1-\cos bx}{x}e^{-x}\text{d}x$, $f(0) = 0$, $f'(b) = \int_0^{+\infty} e^{-x}\sin bx\text{d}x = \text{Image}\int_0^{+\infty} e^{-(1-bi)x}\text{d}x = \text{Image}\frac{1}{1-bi} = \frac{b}{1+b^2}$.

故 $f(b) = \int_0^b \frac{x}{1+x^2} \text{d}x = \frac{1}{2}\ln(1+b^2)$.

Prob 3. 计算 $\int_0^{+\infty} \frac{\cos x}{1+x^2} \text{d}x$.

设 $f(a) = \int_0^{+\infty} \frac{\cos ax}{1+x^2} \text{d}x$. 有 $\mathcal L[f](s) = \int_0^{+\infty} e^{-sa} \int_0^{+\infty} \frac{\cos ax}{1+x^2} \text{d}x \text{d}a = \int_0^{+\infty} \frac{1}{1+x^2} \int_0^{+\infty} e^{-sa}\cos xa \text{d}a \text{d}x$.

当 $s>0$ 时有 $\int_0^{+\infty} e^{-sa}\cos xa \text{d}a = \text{Real} \int_0^{+\infty} e^{-(s-xi)a} \text{d}a = \text{Real} \frac{1}{s-xi} = \frac{s}{s^2+x^2}$.

当 $s \ne 1$ 时有 $\mathcal L[f](s) = \int_0^{+\infty} \frac{1}{1+x^2} \frac{s}{s^2+x^2} \text{d}x = \frac{s}{s^2-1} \int_0^{+\infty} (\frac{1}{1+x^2} - \frac{1}{s^2+x^2}) \text{d}x = \frac{s}{s^2-1} (\frac{\pi}{2} - \frac{\pi}{2s}) = \frac{\pi}{2} \frac{1}{s+1}$.

故 $f(a) = \frac{\pi}{2}e^{-a}$, $f(1) = \frac{\pi}{2e}$.
