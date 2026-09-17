Prob 1. 设 $z(x, y) \in \mathscr C^2$, $z_{xx} + z_{xy} + z_x = z$. 求 $w(u, v) = ze^y$ 其中 $u=\frac{x+y}{2}$, $v=\frac{x-y}{2}$ 满足的偏微分方程.

$w(u, v) = z(u+v, u-v)e^{u-v}$.

$w_u = (z_x+z_y+z)e^{u-v}$.

$w_v = (z_x-z_y-z)e^{u-v}$.

$w_{uu} = (z_{xx} + 2z_{xy} + z_{yy} + 2z_x + 2z_y + z)e^{u-v}$.

$w_{vv} = (z_{xx} - 2z_{xy} + z_{yy} - 2z_x + 2z_y + z)e^{u-v}$.

$w_{uv} = (z_{xx} - z_{yy} - 2z_y - z)e^{u-v}$.

故 $\frac{1}{2} (w_{uu} + w_{uv}) = w$, 即 $w_{uu} + w_{uv} = 2w$.
