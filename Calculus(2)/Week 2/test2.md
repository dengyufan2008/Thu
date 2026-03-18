设 $z(x, y)$ 可微.

Prob 1. 若 $a \frac{\partial z}{\partial x} + b \frac{\partial z}{\partial y} = 0$, 证明直线 $\frac{x-x_0}{a}=\frac{y-y_0}{b}$ 是 $z$ 的等高线.

不妨设 $a, b \ne 0$, 否则退化为一元问题. 令 $r=\sqrt{a^2+b^2}$, $u=\frac{1}{r}(a, b)$.

则 $z_u=\frac{a}{r}\frac{\partial z}{\partial x} + \frac{b}{r}\frac{\partial z}{\partial y} = 0$, 故任意点沿 $\vec u$ 引出的直线都是等高线. 也即斜率为 $\frac{b}{a}$ 的所有直线.

---

Prob 2. 若 $x \frac{\partial z}{\partial x} + y \frac{\partial z}{\partial y} = 0$, 证明 $z$ 是零次齐次函数.

由 Prob 3 得, $x \frac{\partial z}{\partial x} + y \frac{\partial z}{\partial y}=kz \Lrarr z$ 是 $k$ 次齐次函数. 取 $k=0$ 即可.

---

Prob 3. 若 $k \in \N$, 证明 $z$ 是 $k$ 次齐次函数 $\Lrarr x \frac{\partial z}{\partial x} + y \frac{\partial z}{\partial y}=kz$.

$\Rarr$: 任取 $t > 0$, $k$ 次齐次即 $z(tx, ty)=t^kz(x, y)$.

令 $u=tx$, $v=ty$, 两边对 $t$ 求偏导, 得 $x\frac{\partial z(u, v)}{\partial u} + y\frac{\partial z(u, v)}{\partial v} = \frac{\partial z(u, v)}{\partial t} = kt^{k-1}z(x, y)$.

令 $t=1$, 即得 $u=x$, $v=y$, $x \frac{\partial z}{\partial x} + y \frac{\partial z}{\partial y}=kz$.

$\Larr$: 令 $\phi(t)=t^{-k}z(tx, ty)$, $t > 0$. 有 $\frac{\partial \phi(t)}{\partial t} = -kt^{-k-1}z(u, v) + t^{-k} x\frac{\partial z(u, v)}{\partial u} + t^{-k} y\frac{\partial z(u, v)}{\partial v} = t^{-k-1}(-kz(u, v)+x\frac{\partial z(u, v)}{\partial u}+y\frac{\partial z(u, v)}{\partial v})=0$.

故 $\phi(t)=\phi(1)=z(x, y)$. 也即 $z$ 是 $k$ 次齐次.
