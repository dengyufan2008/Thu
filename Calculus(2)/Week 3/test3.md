Prob 1. 求 $\det A$ 在 $A=I$ 处带 Peano 余项的二阶 Taylor 公式.

分类讨论用到的 $A_{ij}$ 数量和位置, 有

$$
\begin{aligned}
\det(I+A) &= 1 + \text{tr}(A) + \sum_{1 \le i < j \le n} (A_{ii}A_{jj} - A_{ij}A_{ji}) + o(\lVert A \rVert^2)
\\
&= 1 + \text{tr}(A) + \sum_{1 \le i \le j \le n} (A_{ii}A_{jj} - A_{ij}A_{ji}) + o(\lVert A \rVert^2)
\\
&= 1 + \text{tr}(A) + \frac{1}{2} \sum_{1 \le i, j \le n} (A_{ii}A_{jj} - A_{ij}A_{ji}) + o(\lVert A \rVert^2)
\\
&= 1 + \text{tr}(A) + \frac{1}{2} (\text{tr}(A)^2 - \text{tr}(A^2)) + o(\lVert A \rVert^2).
\end{aligned}
$$
