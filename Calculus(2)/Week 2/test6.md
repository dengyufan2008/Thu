设 $v$ 是欧氏空间上的一个向量, $\lVert v \rVert \ne 1$.

Prob 1. 求 $\det(I-vv^t)$, 证明是可逆矩阵.

显然存在单位正交矩阵 $Q$ 使得 $\frac{v}{\lVert v \rVert}=Q e_1$, 则 $\det(I-vv^t)=\det(QQ^t - \lVert v \rVert^2 Qe_1e_1^tQ^t) = \det(Q(I-\lVert v \rVert^2e_1e_1^t)Q^t) = \det(I - \lVert v \rVert^2 e_1e_1^t) = 1 - \lVert v \rVert^2 \ne 0$. 故可逆.

---

Prob 2. 求 $f(v)=\det(I-vv^t)$ 的梯度.

显然有 $f(v)=1-\lVert v \rVert^2 = 1 - \sum x_i^2$.

$\frac{\partial f}{\partial x_i} = -2x_i$, 故梯度为 $-2v$.

---

Prob 3. 求 $F:R^m \to M_{m \times m}$, $F(v)=(I-vv^t)^{-1}$ 的微分.

对于任意可逆矩阵映射 $H(x)$, 有 $H(x)H^{-1}(x)=I$. 两边对 $x_i$ 微分, 有 $H_{x_i}(x)H^{-1}(x)+H(x)H^{-1}_{x_i}(x)=0$, 即 $H^{-1}_{x_i}(x)=-H^{-1}(x)H_{x_i}(x)H^{-1}(x)$. 故 $\text{d}H^{-1}(x)=-H^{-1}(x) \text{d}H(x) H^{-1}(x)$.

代入 $F(v)=I-vv^t$, 则 $\text{d}F(v)(h)=-(hv^t+vh^t)$, 故 $\text{d}F^{-1}(v)(h)=(I-vv^t)^{-1}(hv^t+vh^t)(I-vv^t)^{-1}$.
