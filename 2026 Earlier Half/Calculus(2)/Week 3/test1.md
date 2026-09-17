设 $f:C \to C$, $z=x+iy$, $f(z)=u(x, y)+iv(x, y)$. 称 $f$ 可微 iff 差商极限存在.

Prob 1. 若 $f$ 在 $z_0$ 可微, 证明 $u$, $v$ 在 $(x_0, y_0)$ 可微, 且 $u_x=v_y$, $u_y=-v_x$.

将 $C$ 看作 $R^2$, 则 $f$ 是二维映射. 显然各分量均可微.

$f$ 在 $z_0$ 可微 $\to$ $\lim_{z \to z_0} \frac{(u(x, y)-u(x_0, y_0))+i(v(x, y) - v(x_0, y_0))}{(x-x_0) + i(y-y_0)}$ 存在 $\to$ $\lim_{z \to z_0} \frac{[(u(x, y)-u(x_0, y_0))+i(v(x, y) - v(x_0, y_0))][(x-x_0) - i(y-y_0)]}{(x-x_0)^2 + (y-y_0)^2}$ 存在 $\to$ $\lim_{z \to z_0} \frac{(u(x, y)-u(x_0, y_0))(x-x_0) + (v(x, y) - v(x_0, y_0))(y-y_0)}{(x-x_0)^2 + (y-y_0)^2}$ 和 $\lim_{z \to z_0} \frac{-(u(x, y)-u(x_0, y_0))(y-y_0) + (v(x, y) - v(x_0, y_0))(x-x_0)}{(x-x_0)^2 + (y-y_0)^2}$ 存在 $\to$ $\lim_{x \to x_0, y=y_0} \frac{(u(x, y)-u(x_0, y_0))(x-x_0) + (v(x, y) - v(x_0, y_0))(y-y_0)}{(x-x_0)^2 + (y-y_0)^2} = \lim_{x=x_0, y \to y_0} \frac{(u(x, y)-u(x_0, y_0))(x-x_0) + (v(x, y) - v(x_0, y_0))(y-y_0)}{(x-x_0)^2 + (y-y_0)^2}$ 和 $\lim_{x \to x_0, y = y_0} \frac{-(u(x, y)-u(x_0, y_0))(y-y_0) + (v(x, y) - v(x_0, y_0))(x-x_0)}{(x-x_0)^2 + (y-y_0)^2} = \lim_{x=x_0, y \to y_0} \frac{-(u(x, y)-u(x_0, y_0))(y-y_0) + (v(x, y) - v(x_0, y_0))(x-x_0)}{(x-x_0)^2 + (y-y_0)^2}$ $\to$ $u_x = v_y$, $-v_x = u_y$.

---

Prob 2. 若 $f \in \mathscr C^2$, 则 $\Delta u = \Delta v = 0$.

$\Delta u = u_{xx} + u_{yy} = v_{yx} + (-v_{xy}) = 0$. 同理 $\Delta v = 0$.
