# 讲义：从微分学到变分法与曲面几何

## 序章：$\mathbb{R}^n$ 中的拓扑基础

**前言**


关于讲义之后的一些内容,我们为了方便的讨论微分几何相关的一些理论而不涉及过于高深的定理以及过于复杂的分析方面的讨论,以下讨论的函数与映射都认为是光滑的.并且为避免涉及流形和拓扑的相关概念,只讨论特定的一些曲面.

**定义 1（开邻域基）**  
设 $x\in\mathbb{R}^n$，称集族 $\{B(x,r)\mid r>0\}$ 为 $x$ 的**开邻域基**，其中 $B(x,r)=\{y\in\mathbb{R}^n\mid |y-x|<r\}$。

**定义 2（开集）**  
设 $A\subset\mathbb{R}^n$。若对任意 $x\in A$，存在 $r>0$ 使得 $B(x,r)\subset A$，则称 $A$ 为 $\mathbb{R}^n$ 中的**开集**。

**定义 3（开邻域）**  
设 $x\in\mathbb{R}^n$，若 $A$ 是开集且 $x\in A$，则称 $A$ 为 $x$ 的**开邻域**。

---

## 第1章：微分学基本定理

### 1.1 光滑映射的极值必要条件
设 $M\subset\mathbb{R}^n$ 是开集，$f:M\to\mathbb{R}$ 为光滑映射。若 $f$ 在 $x_0\in M$ 取得局部极大值（或极小值），则梯度 $\nabla f(x_0)=0$。

**证明**：\
设在 $x_0$ 某邻域内 $f(x)\le f(x_0)$。若 $\nabla f(x_0)\neq0$，令 $v=\nabla f(x_0)$。
\
$f(x_0+tv)=f(x_0)+t\|v\|^2+o(|t|),\qquad (t\to0) .$
\
因 $\|v\|^2>0$，可取充分小的 $t>0$ 使得 $x_0+tv\in M$ 且 $f(x_0+tv)>f(x_0)$，矛盾。极大情形类似。$\square$

#### 注记1 
内含核心思想, $x_0$作为开集中的局部最值点, 其在各个方向上的扰动之后不会更优 ,开集保证所有方向上以足够小的距离移动不会离开定义域

### 1.2 逆映射定理
设 $M\subset\mathbb{R}^n$ 为开集，$f:M\to\mathbb{R}^n$ 光滑。\
若在 $x_0\in M$ 处微分 $Df(x_0)$ ( Jacobi 矩阵) 可逆，则存在 $x_0$ 的开邻域 $U\subset M$ 和 $f(x_0)$ 的开邻域 $V$，使得 $f|_U:U\to V$ 可逆映射，存在光滑逆 $f^{-1}$ \
且对 $x\in U$ 有 $D(f^{-1})(f(x))=[Df(x)]^{-1}$。

#### 注记2 
本定理不加证明给出是因为其作为处理映射局部逆的手段不可或缺,同时证明手段过于有技巧性且与本文主要传达证明思想的主旨相差较远

### 1.3 隐函数定理
设 $U\subset\mathbb{R}^n\times\mathbb{R}^k$ 为开集，$f:U\to\mathbb{R}^k$ 光滑 ,我们将$\mathbb{R}^n\ $对应成$\mathbb{R}^{n-k} × \mathbb{R}^k\ $ 并将$f(v)$ 表示为$f(x,y)$\
若在 $(x_0,y_0)\in U$ 处 $f(x_0,y_0)=0$ 且偏导矩阵 $\frac{\partial f}{\partial y}(x_0,y_0)$ 可逆，则存在 $x_0$ 的开邻域 $A$，$y_0$ 的开邻域 $B$，以及唯一光滑映射 $g:A\to B$，使得 $g(x_0)=y_0$ 且对任意 $x\in A$ 有 $f(x,g(x))=0$。

**证明**：\
作为 ($1.2$) 的直接推论, 我们构造 $F(x,y)=(x,f(x,y))$ ,
则 $F$ 在 $(x_0,y_0)$ 处 Jacobi 矩阵可逆 ( 分块矩阵中对角块为单位矩阵和偏导矩阵$\frac{\partial f}{\partial y}(x_0,y_0)$ ) 。\
由逆映射定理，$F$ 有局部光滑逆 $F^{-1}$，取 $g(x)$ 为 $F^{-1}(x,0)$ 的 $y$ 分量即得。

### 1.4 拉格朗日乘数存在性定理
设 $U\subset\mathbb{R}^n$ 为开集，$f:U\to\mathbb{R}$，$\phi:U\to\mathbb{R}^k$ 光滑（$k<n$）。若 $x_0\in\phi^{-1}(0)$ 是 $f$ 在约束集 $\phi^{-1}(0)$ 上的局部极值点，且 $D\phi(x_0)$ 满秩 (行满秩) ，则存在唯一 $\lambda=(\lambda_1,\dots,\lambda_k)\in\mathbb{R}^k$，使得 $\nabla f(x_0)=\lambda\cdot D\phi(x_0)$，即 $\nabla f(x_0)=\sum_{i=1}^k\lambda_i\nabla\phi_i(x_0)$。

**证明**：
因 $D\phi(x_0)$ 行满秩，故存在 $k$ 列线性无关。经适当重排坐标，将变量写为 $x = (y,z)$，其中 $y\in\mathbb{R}^{n-k}$，$z\in\mathbb{R}^k$，并使得分块
$$
D\phi(x_0) = 
\begin{pmatrix}
\displaystyle\frac{\partial\phi}{\partial y}(x_0) & \displaystyle\frac{\partial\phi}{\partial z}(x_0)
\end{pmatrix}
$$
中右块 $\displaystyle B = \frac{\partial\phi}{\partial z}(x_0)\in\mathbb{R}^{k\times k}$ 可逆。记
$$
A = \frac{\partial\phi}{\partial y}(x_0)\in\mathbb{R}^{k\times(n-k)},\qquad
D\phi(x_0) = 
\begin{pmatrix} A & B \end{pmatrix}.
$$

设 $x_0 = (y_0,z_0)$，则 $\phi(y_0,z_0)=0$。由**隐函数定理**，存在 $y_0$ 的开邻域 $U_y\subset\mathbb{R}^{n-k}$，$z_0$ 的开邻域 $U_z\subset\mathbb{R}^k$，以及唯一的光滑映射 $g:U_y\to U_z$，使得
$$
g(y_0)=z_0,\qquad \phi(y,g(y))\equiv 0,\;\forall y\in U_y,
$$
且导数矩阵满足
$$
Dg(y_0) = -B^{-1}A \in\mathbb{R}^{k\times(n-k)}. \tag{1}
$$

定义辅助函数 $h:U_y\to\mathbb{R}$ 为 $h(y) = f(y,g(y))$。由假设，$y_0$ 是 $h$ 在开集 $U_y$ 上的局部极值点。根据极值必要条件 ($1.1$) ，
$$
Dh(y_0) = 0 \in\mathbb{R}^{1\times(n-k)}. \tag{2}
$$

将梯度 $\nabla f$ 按 $y,z$ 分块为行向量：
$$
\nabla f(x_0) = 
\begin{pmatrix} \nabla_y f(x_0) & \nabla_z f(x_0) \end{pmatrix},
$$
其中 $\nabla_y f(x_0)\in\mathbb{R}^{1\times(n-k)}$，$\nabla_z f(x_0)\in\mathbb{R}^{1\times k}$。由链式法则，
$$
Dh(y_0) = \nabla_y f(x_0) + \nabla_z f(x_0)\, Dg(y_0). \tag{3}
$$

将 (1) 代入 (3)，并利用 (2) 得
$$
\nabla_y f(x_0) - \nabla_z f(x_0) B^{-1}A = 0. \tag{4}
$$

令
$$
\lambda^T = \nabla_z f(x_0) B^{-1} \in\mathbb{R}^{1\times k},
$$
即列向量 $\lambda = (\lambda^T)^T\in\mathbb{R}^k$。则 (4) 式可改写为
$$
\nabla_y f(x_0) = \lambda^T A. \tag{5}
$$
由 $\lambda^T$ 的定义亦直接得出
$$
\nabla_z f(x_0) = \lambda^T B. \tag{6}
$$

将 (5) 与 (6) 合并为矩阵形式：
$$
\begin{aligned}
\nabla f(x_0) &= 
\begin{pmatrix} \nabla_y f(x_0) & \nabla_z f(x_0) \end{pmatrix} \\
&= \begin{pmatrix} \lambda^T A & \lambda^T B \end{pmatrix} \\
&= \lambda^T \begin{pmatrix} A & B \end{pmatrix} \\
&= \lambda^T D\phi(x_0).
\end{aligned}
$$
两边取转置，即得
$$
\nabla f(x_0)^T = D\phi(x_0)^T \lambda,
$$
或等价地
$$
\nabla f(x_0) = D\phi(x_0)^T \lambda = \sum_{i=1}^k \lambda_i \nabla\phi_i(x_0).
$$

**唯一性**：若另有 $\tilde\lambda$ 满足同一等式，则 $(\lambda - \tilde\lambda)^T D\phi(x_0) = 0$，即 $D\phi(x_0)^T (\lambda - \tilde\lambda) = 0$。因 $D\phi(x_0)$ 行满秩，其转置列满秩，故 $\lambda - \tilde\lambda = 0$，即 $\lambda = \tilde\lambda$。$\square$

#### 注记3
根据隐函数定理我们找到了条件 Φ(x)=0 限制下对最值点的影响, 也就是直接构造 $U$ 限制后的点集,再转化为 ($1.1$) 的情形

---

## 第2章：一维变分法入门

### 2.1 泛函与欧拉–拉格朗日方程
设 $a<b$，考虑光滑函数类 $\{y:[a,b]\to\mathbb{R}\}$。给定光滑函数 $L:\mathbb{R}\times\mathbb{R}\times\mathbb{R}\to\mathbb{R}$（记自变量为 $(x,z,q)$），定义作用量泛函
$$
F[y]=\int_a^b L(x,y(x),y'(x))\,dx .
$$
记 $S^*$ 为满足固定端点条件 $y(a)=p$，$y(b)=q$ 的光滑函数全体。若 $y_0\in S^*$ 使 $F$ 在 $S^*$ 中取得局部极值，则取任意满足 $\mu(a)=\mu(b)=0$ 的光滑函数 $\mu$，考虑单参数族 $y_\varepsilon=y_0+\varepsilon\mu$（如果$S^*$限制了像集,则可考虑对充分小 $\varepsilon$ 仍在 $S^*$ 中）。定义 $\Phi(\varepsilon)=F[y_\varepsilon]$，因 $y_0$ 极值，$\Phi'(0)=0$。由积分号下求导（被积光滑且区间紧，可交换）及分部积分，
$$
\begin{aligned}
0=\Phi'(0)&=\int_a^b\left[\frac{\partial L}{\partial y}\mu+\frac{\partial L}{\partial y'}\mu'\right]dx \\
&=\int_a^b\left[\frac{\partial L}{\partial y}-\frac{d}{dx}\!\left(\frac{\partial L}{\partial y'}\right)\right]\mu\,dx .
\end{aligned}
$$
由 $\mu$ 的任意性，得：(这一步是基本的积分学结论)
$$
\frac{\partial L}{\partial y}-\frac{d}{dx}\!\left(\frac{\partial L}{\partial y'}\right)=0 .
$$

此处的方程称之为**欧拉–拉格朗日方程** ,并记关于扰动 $\mu$ 的变分 $\partial F=\Phi '(0)$

#### 注记4
这里的推导我们效仿 ($1.1$), 通过对$y$施加所有 **方向** 上可行的扰动, 刻画了取极值的 $y$ 应该满足的性质
### 2.2 例：最速降线
在竖直平面内取 $y$ 轴向下为正 ( 重力方向 ) ，质点从原点 $(0,0)$ 沿光滑曲线滑至 $(a,b)$（$a>0,b>0$），不计摩擦。欲使滑落时间最短。

以 $y$ 为自变量，设曲线为 $x=x(y)$，则 $x(0)=0$，$x(b)=a$，弧长微元 $ds=\sqrt{1+x'(y)^2}\,dy$，速度 $v=\sqrt{2gy}$。根据物理意义求得时间泛函为
$$
T[x]=\int_0^b\sqrt{\frac{1+(x')^2}{2gy}}\,dy .
$$
忽略常数因子，取拉格朗日量 $L(y,x,x')=\sqrt{\dfrac{1+(x')^2}{y}}$。
并将摆线方程
$$
x = R\arccos\!\Big(1-\frac{y}{R}\Big) - \sqrt{2Ry-y^2},
$$
其中常数 $R$ 由终点 $(a,b)$ 确定 .\
带入 ($2.1$) 得到的欧拉-拉格朗日方程,可以验证是其的解


---

## 第3章：曲线的微分几何

### 定义 3.1 光滑参数曲线
称映射 $r:[a,b]\to\mathbb{R}^3$ 为**光滑参数曲线**，若
- $r$ 光滑（在端点单侧光滑），
- 正则：$r'(t)\neq0$ 对所有 $t$ 成立，
- 单射：$t_1\neq t_2\Rightarrow r(t_1)\neq r(t_2)$。

### 定义 3.2 弧长与弧长参数化
曲线 $r$ 的弧长定义为
$$
L[r]=\int_a^b \|r'(t)\|\,dt .
$$
令弧长函数 $s(t)=\int_a^t \|r'(u)\|\,du$。因正则性 $s'>0$，存在光滑逆映射 $t(s)$。定义**弧长参数化** $\tilde{r}(s)=r(t(s))$，则可以验证 $\|\tilde{r}'(s)\|\equiv1$。

### 3.3 例：连接两点的最短曲线是线段
给定 $P,Q\in\mathbb{R}^3$，在所有以 $P,Q$ 为端点的光滑正则简单曲线中，求弧长泛函的极值曲线。

设极值曲线为 $r:[a,b]\to\mathbb{R}^3$（不妨取弧长参数）。取变分 $\eta(a)=\eta(b)=0$，令 $r_\varepsilon=r+\varepsilon\eta$，则 $\Phi(\varepsilon)=L[r_\varepsilon]$ 在 $\varepsilon=0$ 处临界。计算得
$$
0=\Phi'(0)=\int_a^b \frac{r'\cdot\eta'}{\|r'\|}\,dt = \int_a^b r'\cdot\eta'\,dt = -\int_a^b r''\cdot\eta\,dt .
$$
由 $\eta$ 任意得 $r''=0$，故 $r(t)=tv+c$ 为直线段。由端点确定即连接 $P,Q$ 的线段。

#### 注记5
此处"变分"虽然输入函数与在 ($2.1$)中定义的不同, 但是本质是一样的,完全类似的推导可以导出这里$\Phi'(0)=0$的必要性, 主要要点是把握变分法的核心思想

---

## 第4章：曲面的微分几何

### 4.1 隐曲面
设 $F:\mathbb{R}^3\to\mathbb{R}$ 光滑，$0$ 为正则值（即对任意 $p\in F^{-1}(0)$ 有 $\nabla F(p)\neq0$）。称零点集
$$
S = \{p\in\mathbb{R}^3\mid F(p)=0\}
$$
为一张**隐曲面**。

### 4.2 切空间与法向量
对 $p\in S$，定义**切空间**为
$$
T_p S = \{v\in\mathbb{R}^3\mid \exists\text{ 光滑曲线 }\gamma:(-\varepsilon,\varepsilon)\to S,\ \gamma(0)=p,\ \gamma'(0)=v\}.
$$
对任一 $v\in T_p S$，由 $F(\gamma(t))\equiv0$ 求导得 $\nabla F(p)\cdot v=0$，故
$$
T_p S \subseteq \{ v\in\mathbb{R}^3\mid \nabla F(p)\cdot v = 0 \}.
$$
定义曲面在 $p$ 点的**单位法向量**为
$$
N(p) = \frac{\nabla F(p)}{\|\nabla F(p)\|}.
$$

### 4.3 切空间视角下的拉格朗日乘数法
设 $f:\mathbb{R}^3\to\mathbb{R}$ 光滑，$p\in S$ 是限制 $f|_S$ 的局部极值点。对任意 $v\in T_p S$，取相应曲线 $\gamma$，因 $f\circ\gamma$ 在 $0$ 取极值，有
$$
0 = \frac{d}{dt}\Big|_{t=0}f(\gamma(t)) = \nabla f(p)\cdot v .
$$
故 $\nabla f(p)\perp T_p S$。若$T_p S$中向量张成非退化的二维平面 ，其正交补由则由 $\nabla F(p)$ 张成，因此存在 $\lambda\in\mathbb{R}$ 使
$$
\nabla f(p) = \lambda \nabla F(p).
$$
此为第1章拉格朗日乘数法的几何本质。

#### 注记6
此时我们知道了在条件约束下(1.1)还能生效的原因,也就是几何直观下(1.4)的解释:
为保证扰动之后点仍然落于曲面S内,我们只考虑**落在切空间内的扰动**\
事实上,如果把$\mathbb R^{2}$也当作一张隐曲面,则在每一点处的切空间同构于$\mathbb R^{2}$本身

---

*讲义终*