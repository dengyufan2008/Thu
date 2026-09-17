Prob 1. 设 $u(x, y) \in \mathscr C^2$. 证明 $u(x, y) = f(x)g(y)$ iff $u_xu_y = u u_{xy}$.

Only If: 容易验证.

If: 令 $v=u_y$, 变形得 $\frac{u_x}{u} = \frac{v_x}{v}$, 即 $(\ln u)_x = (\ln v)_x$, $(\ln \frac{v}{u})_x = 0$.

故 $\ln \frac{v}{u} = a(y)$, $\frac{v}{u} = e^{a(y)} = b(y) > 0$. 即 $(\ln u)_y = b(y)$.

故 $\ln u(x, y) = \ln u(x, 0) + \int_0^y b(t) \text{d}t$. 即 $u(x, y) = u(x, 0) e^{\int_0^y b(t) \text{d}t} = c(x) d(y)$. 其中 $d(y) > 0$.
