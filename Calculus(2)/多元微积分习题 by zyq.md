
## 习题

### 习题 1（第2章补充：Beltrami恒等式与最速降线）
(1) 设泛函 $F[y]=\int_a^b L(y,y')\,dx$ 中 $L$ 不显含 $x$。试从欧拉–拉格朗日方程出发，证明沿极值曲线有首次积分
$$
L - y'\frac{\partial L}{\partial y'} = C\quad(\text{常数}).
$$
(2) 利用上述恒等式，对最速降线拉格朗日量 $L(y,x') = \sqrt{\dfrac{1+(x')^2}{y}}$（$y$ 为自变量），导出极值曲线满足的一阶方程，并积分得到 $x=x(y)$ 的表达式。

### 习题 2（第4章补充：切空间的结构）
设 $S=F^{-1}(0)$ 为隐曲面，$p\in S$。证明：
$$
T_p S = \{ v\in\mathbb{R}^3\mid \nabla F(p)\cdot v = 0 \}.
$$
并由此推出 $T_p S$ 是二维线性子空间（以 $\nabla F(p)$ 为法向量的平面）。  
*（提示：利用隐函数定理得局部参数化，反向构造曲线。）*

### 习题 3（参数曲面与曲率线网）
*预备知识：设 $U\subset\mathbb{R}^2$ 为开集，$r:U\to\mathbb{R}^3$ 光滑，正则（$r_u\times r_v\neq0$），且为单射。记 $n = \dfrac{r_u\times r_v}{\|r_u\times r_v\|}$ 为单位法向量。定义第一基本形式系数 $E=r_u\cdot r_u$，$F=r_u\cdot r_v$，$G=r_v\cdot r_v$；第二基本形式系数 $L = r_{uu}\cdot n$，$M = r_{uv}\cdot n$，$N = r_{vv}\cdot n$。Weingarten 映射 $S:T_pS\to T_pS$ 由 $S(r_u)=-n_u$，$S(r_v)=-n_v$ 线性延拓定义。*

(1) 验证 $n_u,n_v\perp n$，故确属切空间；证明 $S$ 是切空间上良定义的线性映射。  
(2) 证明 $S$ 在基 $\{r_u,r_v\}$ 下的矩阵为 $\mathrm{I}^{-1}\mathrm{II}$，其中 $\mathrm{I}=\begin{pmatrix}E&F\\F&G\end{pmatrix}$，$\mathrm{II}=\begin{pmatrix}L&M\\M&N\end{pmatrix}$；并验证该矩阵关于内积 $\mathrm{I}$ 是自伴的。  
(3) 设 $p$ 为非脐点（$S$ 的两个特征值不同）。  
 (a) 利用特征投影构造 $p$ 的某邻域内两个光滑的单位正交向量场 $e_1,e_2$，使得 $S(e_i)=\kappa_i e_i$；  
 (b) 由此说明存在局部重新参数化 $s = r\circ h$（$h$ 为参数平面上的坐标变换），使坐标曲线恰为曲率线，即满足 $n_\xi\parallel s_\xi$，$n_\eta\parallel s_\eta$ 且 $s_\xi\perp s_\eta$。  
*（注：第(3)问中可积性部分可参考 Codazzi 方程所得主方向场无旋的结论，或直接承认该事实后完成构造。）*

### 习题 4（变分法与等周问题）
(1) 设 $F[y]=\int_a^b L(x,y,y')\,dx$，$J[y]=\int_a^b M(x,y,y')\,dx$，其中 $y$ 满足固定端点条件。若 $y_0$ 在约束 $J[y]=C$ 下使 $F$ 取极值，证明：对任意两个满足 $\eta_i(a)=\eta_i(b)=0$ 的变分，一阶变分 $\delta F_i = \frac{d}{d\varepsilon}F[y_0+\varepsilon\eta_i]\big|_{\varepsilon=0}$ 与 $\delta J_i$ 满足
$$
\delta J_1\cdot\delta F_2 = \delta J_2\cdot\delta F_1,
$$
或 $\delta J_1=\delta J_2=0$。由此推出存在常数 $\lambda$，使对一切容许变分有 $\delta F + \lambda\, \delta J = 0$，从而极值曲线满足辅助泛函 $H[y]=F[y]+\lambda J[y]$ 的欧拉–拉格朗日方程。  
*（提示：回顾第4.3节切空间与梯度正交化归为线性关系的思想。）*

(2) 悬链线问题：给定两端点及曲线总长 $L$，求使得势能最小的曲线形状。设曲线 $y=y(x)$，$y(x_0)=y_0$，$y(x_1)=y_1$，长度 $\int_{x_0}^{x_1}\sqrt{1+(y')^2}\,dx = L$，势能泛函 $U[y]=\int_{x_0}^{x_1} y\sqrt{1+(y')^2}\,dx$。利用 (1) 的结论，写出辅助泛函及相应的欧拉–拉格朗日方程，并借 Beltrami 恒等式求出一阶积分，导出悬链线方程 $y = c\cosh(\frac{x-a}{c}) + b$。

---
