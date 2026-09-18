# Week1 Homework

By Deng Yufan.

## Prob 1

This algorithm generate all $n!$ permutations with **unequal** probability.

The algorithm will choose $j_1, j_2, \cdots, j_n$ independently in $\{1, 2, \cdots, n\}$, so there is $n^n$ possibilities. But $n^n$ is not a multiplication of $n!$ when $n \ge 3$ since $n-1 \mid n!$ but $n-1 \nmid n^n$.

## Prob 2

a. For token embeddings $x$ and $y$, let $x_1, x_2, \cdots, x_d$, $y_1, y_2, \cdots, y_d$ be the coor. of $x$ and $y$. Then each $x_i$ and $y_i$ are uniformly in $[-1, 1]$. We have

$$
\cos(x, y)=\frac{\sum_{i=1}^d x_iy_i}{\sqrt{\sum_{i=1}^d x_i^2\sum_{i=1}^d y_i^2}}.
$$

Obviously $\mathbb E(\cos(x, y))=0$, since $y$ and $-y$ can be a pair and has contribution 0.

And

$$
\text{Var}(\cos(x, y))=\mathbb E(\cos^2(x, y))=\sum_{i=1}^d\sum_{j=1}^d \mathbb E\left(\frac{x_iy_ix_jy_j}{\sum_{k=1}^d x_k^2\sum_{k=1}^d y_k^2}\right).
$$

When $i \ne j$, the expectation is 0 since $x_i$ and $-x_i$ can be a pair. So

$$
\begin{aligned}
\sum_{i=1}^d\sum_{j=1}^d \mathbb E\left(\frac{x_iy_ix_jy_j}{\sum_{k=1}^d x_k^2\sum_{k=1}^d y_k^2}\right) &= \sum_{i=1}^d \mathbb E\left(\frac{x_i^2y_i^2}{\sum_{k=1}^d x_k^2\sum_{k=1}^d y_k^2}\right)
\\
&= d \cdot \mathbb E\left(\frac{x_1^2}{\sum_{k=1}^d x_k^2}\right) \cdot \mathbb E\left(\frac{y_1^2}{\sum_{k=1}^d y_k^2}\right)
\\
&= \frac{1}{d} \cdot \mathbb E\left(\frac{\sum_{k=1}^d x_k^2}{\sum_{k=1}^d x_k^2}\right) \cdot \mathbb E\left(\frac{\sum_{k=1}^d y_k^2}{\sum_{k=1}^d y_k^2}\right)
\\
&= \frac{1}{d}.
\end{aligned}
$$

Thus $\mathbb E(\cos(x, y))=0$, $\text{Var}(\cos(x, y))=\frac{1}{d}$.

b. In $q_i=Qx_i$, we have $2d^2-d$ operations, so compute all $q_i$, $k_i$, $v_i$ take $6nd^2-3nd$ operations.

In $c_{ij}=q_i \cdot k_j$, we have $2d-1$ operations, so compute all $c_{ij}$ take $2n^2d-n^2$ operations.

In $y_i=\sum_{j=1}^n c_{ij}v_j$, we have $2nd-d$ operations, so compute all $y_i$ take $2n^2d-nd$ operations.

Totally, $4n^2d+6nd^2-n^2-4nd$ operations.

c. We have $L(4n^2d+6nd^2-n^2-4nd)=4\text{e}16+6\text{e}15-1\text{e}12-4\text{e}11$ operations for a query. Then total energy is $(4\text{e}16+6\text{e}15-1\text{e}12-4\text{e}11) * 7\text{e}9 * 2\text{e-}10=5.6\text{e}16+8.4\text{e}15-1.4\text{e}12-5.6\text{e}11 \approx 6.44 \times 10^{16} J$.

## Prob 3

a.1. Since only positions that Alice and Bob pick the same basis are retained, obviously their classical bits are the same.

a.2. Since we need their basis are the same, so obtain $\frac{N}{2}$ bits.

b. If Eve picks the right basis, the error rate is 0. If eve picks wrong basis, easy to see both states is with $\frac{1}{2}$ prob. to appear, so the error rate is $\frac{1}{2}$.

Totally, error rate is $\frac{1}{4}$.

c. Prob. of Eve is detected is $(\frac{3}{4})^m$, since Eve must be right at every position. As $m$ increases, the prob. will exponentially fast decrease to 0.

## Declaration of AI Use

I used AI to translate part of words.
