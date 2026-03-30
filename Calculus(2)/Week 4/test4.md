Prob 1. 设 $n$ 阶方阵 $A$ 有单位特征向量 $v_0$, 相应的实特征值为 $\lambda_0$. 若 $\lambda_0$ 是 $\det(A-\lambda I)$ 的单根, 证明存在 $A$ 的邻域 $U$ 和 $\mathscr C^\infty$ 函数 $\lambda : U \rarr R$ 和 $\mathscr C^\infty$ 映射 $v : U \rarr R^n$, 使得 $\forall B \in U$, $\lambda(B)$ 和 $v(B)$ 是 $B$ 的实特征值和相应的单位特征向量, 且 $\lambda(A)=\lambda_0$, $v(A)=v_0$.

设 $f(B, \lambda, v) = (Bv-\lambda v, \frac{1}{2}(\lVert v \rVert^2 - 1))$. 则 $f \in \mathscr C^\infty$, $f(A, \lambda_0, v_0)=0$.

则 $f_y = \left[\begin{matrix}-v & B-\lambda I \\ 0 & v^t\end{matrix}\right]$.

则 $f_y(A, \lambda_0, v_0) = \left[\begin{matrix}-v_0 & A-\lambda_0 I \\ 0 & v_0^t\end{matrix}\right]$.

假设 $\left[\begin{matrix}-v_0 & A-\lambda_0 I \\ 0 & v_0^t\end{matrix}\right]\left[\begin{matrix}\lambda \\ v\end{matrix}\right] = 0$, 则有 $(A - \lambda_0 I)v = \lambda v_0$, $v_0^tv = 0$.

有 $(A - \lambda_0 I)^2v = \lambda (A - \lambda_0 I) v_0 = 0$, 则 $v \in K_{\lambda_0}$. 由于 $\lambda_0$ 是单根, 有 $K_{\lambda_0} = E_{\lambda_0}$, 则 $\lambda v_0 = (A-\lambda_0 I)v = 0$. 显然 $v_0 \ne 0$, 则 $\lambda = 0$.

又有 $v \in N(A-\lambda_0 I) = \text{span}(v_0)$, 又由 $v_0^tv = 0$ 得 $v \in \text{span}(v_0)^\perp$. 故 $v = 0$.

综上, $\lambda = 0$ 且 $v = 0$, 则 $f_y(A, \lambda_0, v_0)$ 是单射. 又有 $f_y(A, \lambda_0, v_0)$ 将 $R^{n+1}$ 映射到自身, 则 $f_y(A, \lambda_0, v_0)$ 是双射.

使用隐函数定理, 得到要求的两个映射.
