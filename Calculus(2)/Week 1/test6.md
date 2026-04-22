Prob 1. 设 $f(x, y) = \log_x(x+y)$, 讨论 $\lim_{x \to 1, y \to 0} f(x, y)$ 和 $\lim_{x \to 1} \lim_{y \to 0} f(x, y)$, $\lim_{y \to 0} \lim_{x \to 1} f(x, y)$.

$$
\begin{aligned}
\lim_{x \to 1} \lim_{y \to 0} f(x, y) &= \lim_{x \to 1} \lim_{y \to 0} \frac{\ln(x+y)}{\ln x}
\\
&= \lim_{x \to 1} 1
\\
&= 1.
\end{aligned}
$$

$$
\begin{aligned}
\lim_{y \to 0} \lim_{x \to 1} f(x, y) &= \lim_{y \to 0} \lim_{x \to 1} \frac{\ln(x+y)}{\ln x}
\\
&= \lim_{y \to 0} \frac{\ln(1+y)}{0}
\\
&= \lim_{y \to 0} +\infty
\\
&= +\infty.
\end{aligned}
$$

故 $\lim_{x \to 1, y \to 0} f(x, y)$ 不存在.
