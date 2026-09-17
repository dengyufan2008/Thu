设 $u=u(x, y)$ 二阶可微.

Prob 1. 求 $\frac{\partial u}{\partial r}$ 和 $\frac{\partial u}{\partial \theta}$, 并判断是否为 $u$ 的方向导数.

有 $\frac{\partial u}{\partial r} = u_x \cos \theta + u_y \sin \theta$, $\frac{\partial u}{\partial \theta} = -u_x r \sin \theta + u_y r \cos \theta$.

前者是在 $(\cos \theta, \sin \theta)$ 方向上的方向导数, 但后者是在 $(-\sin \theta, \cos \theta)$ 方向上的非方向导数, 是方向向量的 $r$ 倍.

Prob 2. 求 $u$ 在极坐标系下的梯度.

显然梯度为 $(u_x, u_y)$. 有 $u_x=\cos \theta u_r - \frac{1}{r} \sin \theta u_\theta$, $u_y = \sin \theta u_r + \frac{1}{r}\cos \theta u_\theta$.

假设梯度的极坐标表示为 $Ae_r+Be_\theta$, 则平面直角坐标系表示为 $(A \cos \theta - B \sin \theta, A \sin \theta + B \cos \theta)$.

对比系数得 $A=u_r$, $B=\frac{1}{r}u_\theta$, 故梯度为 $u_re_r+\frac{1}{r}u_\theta e_\theta$.

Prob 3. 证明 $(u_x)^2+(u_y)^2=(u_r)^2+(\frac{1}{r}u_\theta)^2$, 即梯度的模长与坐标系选取无关.

显然梯度为 $\nabla = u_xe_x+u_ye_y = u_re_r + \frac{1}{r}u_\theta e_\theta$. 左右同时取模长, 得到上式.

Prob 4. 用极坐标表示 $u_{xx}+u_{yy}$.

由于 $u_x=\cos \theta u_r - \frac{1}{r} \sin \theta u_\theta$.

$u_{xx}=(\cos^2 \theta u_{rr} + \frac{1}{r} \sin^2 \theta u_r - \frac{1}{r} \sin \theta \cos \theta u_{r\theta}) - \frac{1}{r}(\sin \theta \cos \theta (u_{\theta r} - \frac{1}{r} u_\theta) - \frac{1}{r} \sin \theta \cos \theta u_{\theta} - \frac{1}{r} \sin^2 \theta u_{\theta \theta}) = \cos^2 \theta u_{rr} + \frac{1}{r^2}\sin^2 \theta u_{\theta \theta} - \frac{2}{r} \sin \theta \cos \theta u_{r \theta} + \frac{1}{r} \sin^2 \theta u_r + \frac{2}{r^2} \sin \theta \cos \theta u_\theta$.

由于对称性, 只需旋转 $\pi / 2$ 弧度即可从 $u_{xx}$ 得到 $u_{yy}$. 故 $u_{yy} = \sin^2 \theta u_{rr} + \frac{1}{r^2}\cos^2 \theta u_{\theta \theta} + \frac{2}{r} \sin \theta \cos \theta u_{r \theta} + \frac{1}{r} \cos^2 \theta u_r - \frac{2}{r^2} \sin \theta \cos \theta u_\theta$.

故 $u_{xx}+u_{yy}=u_{rr}+\frac{1}{r^2}u_{\theta \theta} + \frac{1}{r} u_r$.
