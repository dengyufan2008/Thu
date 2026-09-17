Prob 1. 设 $n \in \Z$, 证明 $u(x) = \int_0^\pi \cos(n \varphi - x \sin \varphi) \text{d}\varphi$ 满足 $x^2u'' + xu' + (x^2-n^2)u = 0$.

$u'(x) = \int_0^\pi \sin \varphi \sin(n \varphi - x \sin \varphi) \text{d}\varphi$, $u''(x) = -\int_0^\pi \sin^2 \varphi \cos(n \varphi - x \sin \varphi) \text{d}\varphi$. 令 $\theta = n \varphi - x \sin \varphi$.

$$
\begin{aligned}
x^2u'' + xu' + (x^2-n^2)u &= x^2\int_0^\pi \cos^2 \varphi \cos \theta \text{d}\varphi + x\int_0^\pi \sin \varphi \sin \theta \text{d}\varphi - n^2\int_0^\pi \cos \theta \text{d}\varphi
\\
&= \int_0^\pi (x^2\cos^2 \varphi-n^2) \cos \theta + x\sin \varphi \sin \theta \text{d}\varphi
\\
&= -(n+x\cos \varphi) \sin \theta \Big|_{\varphi = 0}^\pi
\\
&= (x-n) \sin (n\pi)
\\
&= 0.
\end{aligned}
$$
