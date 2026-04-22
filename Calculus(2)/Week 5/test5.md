Prob 1. 设 $\phi, f_1, f_2, \cdots, f_n, \cdots \in \mathscr C[a, b]$, 且 $\forall x \in [a, b]$, $f_1(x) \le f_2(x) \le \cdots \le f_n(x) \le \cdots$, $\phi(x) = \lim_{n \rarr +\infty} f_n(x)$. 证明 $f_n$ 在 $[a, b]$ 上一致收敛到 $\phi$.

设 $g(x, y)$ 满足 $g(x, n) = f_n(x)$, $g(x, y) = g(x, \lfloor y \rfloor) (\lceil y \rceil - y) + g(x, \lceil y \rceil) (y - \lfloor y \rfloor)$. 显然 $g(x, y)$ 关于两个参数各自连续.

对于任意 $(x, y) \in [a, b] \times [1, +\infty)$ 和 $0 < \epsilon < 1$, 不妨假设 $y \notin \Z^+$, $g(x, y) = 0$, 其余情况是类似的. 设 $M = \max(|g(x, \lfloor y \rfloor)|, |g(x, \lceil y \rceil)|, 1)$. 取 $\delta > 0$ 使得 $\delta < \min(y - \lfloor y \rfloor, \lceil y \rceil - y)$, $g(x, \lfloor y \rfloor)$ 和 $g(x, \lceil y \rceil)$ 在 $\delta$ 邻域内函数值变化不超过 $\frac{\epsilon}{4}$, $\delta < \frac{\epsilon}{8M}$.

则对于任意 $g(x', y')$ 有 $|g(x', y')| \le |(g(x, \lfloor y \rfloor)+\frac{\epsilon}{4})(\lceil y \rceil - y + \frac{\epsilon}{8M}) + (g(x, \lceil y \rceil)+\frac{\epsilon}{4})(y - \lfloor y \rfloor + \frac{\epsilon}{8M})| \le 0+\frac{2M\epsilon}{8M}+\frac{\epsilon}{4}+\frac{\epsilon^2}{4M} \le \frac{3}{4}\epsilon$.

故 $g(x, y)$ 二元连续, 且由于 $g(x, y)$ 关于 $y$ 单调, 收敛到 $\phi(x)$, 故 $g(x, y)$ 一致收敛于 $\phi(x)$.
