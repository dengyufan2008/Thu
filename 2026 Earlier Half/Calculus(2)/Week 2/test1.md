Prob 1. 设 $f(x, y)$ 在 $(0, 0)$ 存在偏导数 $\frac{\partial f}{\partial x}(0, 0)$, 在 $(0, 0)$ 的邻域内存在偏导数 $\frac{\partial f}{\partial y}(x, y)$. 证明: 若 $\frac{\partial f}{\partial y}(x, y)$ 有界, 则 $f$ 在 $(0, 0)$ 连续; 若 $\frac{\partial f}{\partial y}(x, y)$ 连续, 则 $f$ 在 $(0, 0)$ 可微.

若 $\lVert (x, y) \rVert_1 < \delta$ 时 $|\frac{\partial f}{\partial y}(x, y)| < M$, 则

$$
\begin{aligned}
|f(x, y)-f(0, 0)| &\le |f(x, 0)-f(0, 0)|+|f(x, y)-f(x, 0)|
\\
&= |x\frac{\partial f}{\partial x}(0, 0)| + |y\frac{\partial f}{\partial y}(x, y)| + o(x) + o(y)
\\
&< 2|\frac{\partial f}{\partial x}(0, 0)||x| + 2M|y|.
\end{aligned}
$$

若 $\lVert (x, y) \rVert_1 < \delta$ 时 $\frac{\partial f}{\partial y}(x, y)$ 连续, 则

$$
\begin{aligned}
& |f(x, y)-f(0, 0)-x\frac{\partial f}{\partial x}(0, 0)-y\frac{\partial f}{\partial y}(0, 0)|
\\
=& |x\frac{\partial f}{\partial x}(0, 0)+y\frac{\partial f}{\partial y}(x, y)+o(x)+o(y)-x\frac{\partial f}{\partial x}(0, 0)-y\frac{\partial f}{\partial y}(0, 0)|
\\
=& |y\frac{\partial f}{\partial y}(x, y)-y\frac{\partial f}{\partial y}(0, 0)+o(x)+o(y)|.
\end{aligned}
$$

对于任意 $\epsilon > 0$, 都能找到 $\delta' \le \delta$ 使得 $|\frac{\partial f}{\partial y}(x, y)-\frac{\partial f}{\partial y}(0, 0)| < \epsilon$, 故

$$
\begin{aligned}
& |y\frac{\partial f}{\partial y}(x, y)-y\frac{\partial f}{\partial y}(0, 0)+o(x)+o(y)|
\\
<& \epsilon |y| + o(x)+o(y)
\\
=& o(x)+o(y).
\end{aligned}
$$

故 $x\frac{\partial f}{\partial x}(0, 0)+y\frac{\partial f}{\partial y}(0, 0)$ 是 $f$ 在 $(0, 0)$ 的微分.
