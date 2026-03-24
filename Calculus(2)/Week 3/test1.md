设 $f:C \rarr C$, $z=x+iy$, $f(z)=u(x, y)+iv(x, y)$. 称 $f$ 可微 iff 差商极限存在.

Prob 1. 若 $f$ 在 $z_0$ 可微, 证明 $u$, $v$ 在 $(x_0, y_0)$ 可微, 且 $u_x=v_y$, $u_y=-v_x$.

将 $C$ 看作 $R^2$, 则 $f$ 是二维映射. 显然各分量均可微.

$f$ 在 $z_0$ 可微 $\rarr$ $\lim_{z \rarr z_0} \frac{(u(x, y)-u(x_0, y_0))+i(v(x, y) - v(x_0, y_0))}{(x-x_0) + i(y-y_0)}$ 存在 $\rarr$ $\lim_{z \rarr z_0} \frac{[(u(x, y)-u(x_0, y_0))+i(v(x, y) - v(x_0, y_0))][(x-x_0) - i(y-y_0)]}{(x-x_0)^2 + (y-y_0)^2}$ 存在 $\rarr$ $\lim_{z \rarr z_0} \frac{(u(x, y)-u(x_0, y_0))(x-x_0) + (v(x, y) - v(x_0, y_0))(y-y_0)}{(x-x_0)^2 + (y-y_0)^2}$ 和 $\lim_{z \rarr z_0} \frac{-(u(x, y)-u(x_0, y_0))(y-y_0) + (v(x, y) - v(x_0, y_0))(x-x_0)}{(x-x_0)^2 + (y-y_0)^2}$ 存在 $\rarr$ $\lim_{x \rarr x_0, y=y_0} \frac{(u(x, y)-u(x_0, y_0))(x-x_0) + (v(x, y) - v(x_0, y_0))(y-y_0)}{(x-x_0)^2 + (y-y_0)^2} = \lim_{x=x_0, y \rarr y_0} \frac{(u(x, y)-u(x_0, y_0))(x-x_0) + (v(x, y) - v(x_0, y_0))(y-y_0)}{(x-x_0)^2 + (y-y_0)^2}$ 和 $\lim_{x \rarr x_0, y = y_0} \frac{-(u(x, y)-u(x_0, y_0))(y-y_0) + (v(x, y) - v(x_0, y_0))(x-x_0)}{(x-x_0)^2 + (y-y_0)^2} = \lim_{x=x_0, y \rarr y_0} \frac{-(u(x, y)-u(x_0, y_0))(y-y_0) + (v(x, y) - v(x_0, y_0))(x-x_0)}{(x-x_0)^2 + (y-y_0)^2}$ $\rarr$ $u_x = v_y$, $-v_x = u_y$.

---

Prob 2. 若 $f \in \mathscr C^2$, 则 $\Delta u = \Delta v = 0$.

$\Delta u = u_{xx} + u_{yy} = v_{yx} + (-v_{xy}) = 0$. 同理 $\Delta v = 0$.
