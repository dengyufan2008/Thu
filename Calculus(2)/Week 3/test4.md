Prob 1. 设 $f:R^2 \to R$, $f \in \mathscr C^2$, $\Delta f(u, v) = 0$. 若 $g(x, y) = f(\frac{x}{x^2+y^2}, \frac{y}{x^2+y^2})$, 证明 $\Delta g = 0$.

用极坐标系有 $g(r, \theta) = f(\frac{\cos \theta}{r}, \frac{\sin \theta}{r})$. 有 $\Delta g = g_{rr} + \frac{1}{r^2}g_{\theta \theta} + \frac{1}{r} g_{r}$.

$g_r = -\frac{1}{r^2}(\cos \theta f_x + \sin \theta f_y)$.

$g_{rr} = \frac{2}{r^3}(\cos \theta f_x + \sin \theta f_y) + \frac{1}{r^4}(\cos \theta (\cos \theta f_{xx} + \sin \theta f_{xy}) + \sin \theta(\cos \theta f_{xy} + \sin \theta f_{yy}))$.

$g_{\theta} = -\frac{1}{r} \sin \theta f_x + \frac{1}{r} \cos \theta f_y$.

$g_{\theta \theta} = -\frac{1}{r}(\cos \theta f_x - \frac{1}{r} \sin^2 \theta f_{xx} + \frac{1}{r} \sin \theta \cos \theta f_{xy}) + \frac{1}{r}(-\sin \theta f_y - \frac{1}{r} \sin \theta \cos \theta f_{xy} + \frac{1}{r} \cos^2 \theta f_{yy})$.

故 $\Delta g = [\frac{2}{r^3}(\cos \theta f_x + \sin \theta f_y) + \frac{1}{r^4}(\cos \theta (\cos \theta f_{xx} + \sin \theta f_{xy}) + \sin \theta(\cos \theta f_{xy} + \sin \theta f_{yy}))] + \frac{1}{r^2}[-\frac{1}{r}(\cos \theta f_x - \frac{1}{r} \sin^2 \theta f_{xx} + \frac{1}{r} \sin \theta \cos \theta f_{xy}) + \frac{1}{r}(-\sin \theta f_y - \frac{1}{r} \sin \theta \cos \theta f_{xy} + \frac{1}{r} \cos^2 \theta f_{yy})] + \frac{1}{r}[-\frac{1}{r^2}(\cos \theta f_x + \sin \theta f_y)] =\frac{1}{r^4} f_{xx} + \frac{1}{r^4} f_{yy} = \frac{1}{r^4} \Delta f = 0$.
