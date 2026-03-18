设 $z(x, y) \in \mathscr C^2$. 设 $w=x+y+z$, $u=x$, $v=x+y$.

Prob 1. 把微分方程 $z_{xx}-2z_{xy}+z_{yy}+z_x-z_y=0$ 改写为关于 $w=w(u, v)$ 的方程.

$z_x=w_x-v_x=w_u+w_v-1$, $z_y=w_y-v_y=w_v-1$.

$z_{xx}=(w_{uu}+w_{uv}) + (w_{vu}+w_{vv}) = w_{uu}+2w_{uv}+w_{vv}$.

$z_{xy}=w_{vu}+w_{vv}=w_{uv}+w_{vv}$.

$z_{yy}=w_{vv}$.

故 $w_{uu}+w_u=0$.

---

Prob 2. 求微分方程的解.

令 $f=w_u$, 则 $f_u = -f$. 令 $g=e^uf$, 则 $g_u=0$, $g(u, v)=h(v)$, $f(u, v)=e^{-u}h(v)$.

故有 $w_u=e^{-u}h(v)$, $w(u, v)=-e^{-u}h(v)$.

故 $z(x, y)=-e^{-x}h(y-x)+x-y$.
