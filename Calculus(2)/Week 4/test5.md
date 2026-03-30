设 $A$ 是 $n$ 阶实对称矩阵, $\lambda_1 \ge \lambda_2 \ge \cdots \ge \lambda_n$ 是 $A$ 的特征值, $v_1, v_2, \cdots, v_n$ 是 $R^n$ 的由特征向量组成的单位正交基.

Prob 1. 对充分靠近 $A$ 的 $n$ 阶实对称矩阵 $B$, $B$ 的从大到小排列后的特征值是否是关于 $B$ 的 $\mathscr C^\infty$ 函数? 是否有 $R^n$ 的由 $B$ 的特征向量组成的单位正交基充分靠近 $v_1, v_2, \cdots, v_n$?

考虑 $f(A, t) = \det(A-tI) \in \mathscr C^\infty$. 有 $f_t = -\sum_{i=1}^n \prod_{j \ne i} (\lambda_j - t)$. 显然 $f_t(A, \lambda_i) \ne 0$ iff $\lambda_j \ne \lambda_i \space (j \ne i)$. 故若 $\lambda_i$ 互不相同, 则运用隐函数定理, $B$ 的特征值是 $B$ 的 $\mathscr C^\infty$.

否则 $\lambda_i$ 存在一对相等. 考虑反例: $n=2$, $A=0$, $B = \left[\begin{matrix}t & 0 \\ 0 & -t\end{matrix}\right]$, $t \rarr 0$. 则 $B$ 的特征值为 $|t| \ge -|t|$. 但 $|t| \notin \mathscr C^1$. 对于一般情况的构造反例同理.

---

现在考虑特征向量的连续性. 依旧假设 $\lambda_i$ 两两不同, 否则考虑 $n=2$, $A=0$, $B=\left[\begin{matrix}0 & t \\ t & 0\end{matrix}\right]$, $t \rarr 0$. 当 $t > 0$ 时, 最大特征值对应的单位特征向量为 $\frac{1}{\sqrt 2}(1, 1)$, $t < 0$ 时为 $\frac{1}{\sqrt 2}(1, -1)$. 显然不连续.

则 $\lambda_i$ 两两不同, 那么只要对每个特征值任意选取一个单位特征向量, 就有这些向量彼此正交 (由于 $B$ 实对称).

显然对每个 $i$ 可以有 $\lambda_i(B) \in \mathscr C^\infty$. 设 $g:\mathcal S_n \times R^n \rarr R^{n-1} \times R$ 满足 $g(B, v) = [(B-\lambda_i(B) I)v, \frac{1}{2}(\lVert v \rVert^2 - 1)]$, 则 $g_v(A, v_i) = (A-\lambda_i I, v_i^t)$. 由于 $R(A-\lambda_i I) = N(A-\lambda_i I)^\perp = \text{span}(v_i)^\perp$, 则前者 $n-1$ 维, 后者 1 维, 恰好可逆.

则运用隐函数定理得到单位特征向量映射 $v_i(B) \in \mathscr C^\infty$, 从而 $\{v_i(B)\}$ 构成单位正交基.
