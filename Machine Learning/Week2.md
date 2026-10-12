# Week2 Homework

By Deng Yufan.

## Prob 1

I searched SAG and SAGA by AI.

SAG: Keep $n$ gradient for all samples, each is latest. Use average of $n$ gradients to approximate real gradient.

SVRG: As we learnt in lecture.

SAGA: Similar to SAG, but add a fix term.

Formula: SAG: $v_k = \frac{1}{n} (\nabla f_i(x_k) - y_i + \sum_{j=1}^n y_j)$. SVRG: $v_k = \nabla f_i(x_k) - \nabla f_i(\tilde x) + \nabla f(\tilde x)$. SAGA: $v_k = \nabla f_i(x_k) - y_i + \frac{1}{n} \sum_{j=1}^n y_j$.

Convergence speed: For strongly convex, all of them are linear.

Biased or not: SAG biased, SVRG and SAGA not biased.

Space: SAG and SAGA is $O(nd)$, SVRG is $O(d)$.

## Prob 2

Let $x_{t+1} = \argmin_y \{V_{x_t}(y) + \langle a \cdot \nabla f(x_t), y - x_t \rangle\} = \argmin_y W(a, x_t, y)$, then we have $\nabla^2 W(a, x_t, y) = \nabla^2 R(y)$ is strongly convex. So $x_{t+1}$ is uniquely determined by $\nabla W(a, x_t, x_{t+1}) = 0$, that is $\nabla R(x_{t+1}) - \nabla R(x_t) + a\nabla f(x_t) = 0$.

Let $x'_{t+1} = \argmin_y \{a \sum_{i=1}^t \langle y, \nabla f(x'_i) \rangle + R(y)\} = \argmin_y W'(a, x'_t, y)$, then $\nabla^2 W'(a, x'_t, y) = \nabla^2 R(y)$ is strongly convex. $x'_{t+1}$ uniquely determined by $a \sum_{i=1}^t \nabla f(x'_i) + \nabla R(x'_{t+1}) = 0$.

We prove $x_t = x'_t$ for all $t$. Induct on $t$, we have $t=1$ is true, and we assume $t$ to prove $t+1$. We have $x'_{t+1}$ is determined by

$$
\begin{aligned}
0 &= a \sum_{i=1}^t \nabla f(x'_i) + \nabla R(x'_{t+1})
\\
&= (a \sum_{i=1}^{t-1} \nabla f(x'_i) + \nabla R(x'_t)) + \nabla R(x_{t+1}) - \nabla R(x_t) + a\nabla f(x_t)
\\
&= \nabla R(x_{t+1}) - \nabla R(x_t) + a\nabla f(x_t).
\end{aligned}
$$

So $\nabla W(a, x_t, x_{t+1}) = 0$ iff $\nabla W'(a, x'_t, x'_{t+1}) = 0$, that is $x_{t+1}=x'_{t+1}$.

## Prob 3

a. We have

$$
\begin{aligned}
& \frac{1}{2}E \lVert \nabla f_i(x) - \nabla f_i(\tilde x) + \nabla f(\tilde x) - \nabla f(x) \rVert^2
\\
\le & E \lVert \nabla f_i(x) - \nabla f_i(x^*) - \nabla f(x) + \nabla f(x^*) \rVert^2 + E \lVert \nabla f_i(\tilde x) - \nabla f_i(x^*) - \nabla f(\tilde x) + \nabla f(x^*) \rVert^2
\\
\le & E \lVert \nabla f_i(x) - \nabla f_i(x^*) - E(\nabla f_i(x) - \nabla f_i(x^*)) \rVert^2 + E \lVert \nabla f_i(\tilde x) - \nabla f_i(x^*) - E(\nabla f_i(\tilde x) - \nabla f_i(x^*)) \rVert^2
\\
\le & E \lVert \nabla f_i(x) - \nabla f_i(x^*) \rVert^2 + E \lVert \nabla f_i(\tilde x) - \nabla f_i(x^*) \rVert^2.
\end{aligned}
$$

b. We first prove $f(y) \ge f(x) + \langle \nabla f(x), y - x \rangle + \frac{1}{2L} \lVert \nabla f(x) - \nabla f(y) \rVert^2$ for convex and $L$-smooth $f$.

Let $g(y) = f(y) - f(x) - \langle \nabla f(x), y-x \rangle - \frac{1}{2L} \lVert \nabla f(x) - \nabla f(y) \rVert^2$, then $\nabla g(y) = \frac{1}{2L}(2LI-\nabla^2 f(y))(\nabla f(y) - \nabla f(x))$. Since $f$ is convex and $L$-smooth, $\nabla^2 f(y)$ is semi-positive and $\lVert \nabla^2 f(y) \rVert \le L$. Let $\nabla^2 f(y) = PDP^{-1}$ is orthoric diagonalize, we have $0 \le D_i \le L$ and $2LI - \nabla^2 f(y) = P(2LI-D)P^{-1}$. So $\nabla g(y)$ is convex. Since $g(x) = 0$, $\nabla g(x) = 0$, we have $g(y) \ge 0$.

Then since $0 \in \partial(\Psi + f)(x^*)$, we have $-\nabla f(x^*) \in \partial \Psi(x^*)$. That is $\Psi(x) - \Psi(x^*) \ge -\langle \nabla f(x^*), x-x^* \rangle$. So we have

$$
\begin{aligned}
& \frac{1}{2L}(E \lVert \nabla f_i(x^*) - \nabla f_i(x) \rVert^2 + E \lVert \nabla f_i(x^*) - \nabla f_i(\tilde x) \rVert^2)
\\
\le & E(f_i(x)-f_i(x^*)-\langle \nabla f_i(x^*), x-x^* \rangle) + E(f_i(\tilde x)-f_i(x^*)-\langle \nabla f_i(x^*), \tilde x-x^* \rangle)
\\
\le & f(x) - f(x^*) - \langle \nabla f(x^*), x - x^* \rangle + f(\tilde x) - f(x^*) - \langle \nabla f(x^*), \tilde x - x^* \rangle
\\
\le & F(x)-F(x^*)+F(\tilde x)-F(x^*).
\end{aligned}
$$

## Prob 4

a. Since we need $\lVert x \rVert_1 = 1$, to make $x$ move along with $\ell$, if $\ell$ is not tangent to the surface, you cant move a tiny step, so the method will not work.

b. In MD, we have $x_{t+1} = \argmin_{y \in \Delta_n} \{\frac{1}{2}\lVert y-x_t \rVert^2_2 + \eta \langle \ell_t, y-x_t \rangle\}$.

In PGD, we have $x_{t+1} = \argmin_{y \in \Delta_n} \lVert x_t - \eta \ell_t - y \rVert^2_2 = \argmin_{y \in \Delta_n} \{\lVert x_t - y \rVert^2_2 - 2\eta\langle x_t - y, \ell_t \rangle + \eta^2 \lVert \ell_t \rVert^2_2\}$.

So they calc same $x_{t+1}$.

We have

$$
\begin{aligned}
\eta(x_t^T \ell_t - u^T \ell_t) &= \eta \langle \ell_t, x_t-u \rangle
\\
&= \langle \eta \ell_t, x_t - x_{t+1} \rangle + \langle \eta \ell_t, x_{t+1}-u \rangle
\\
&= \langle \eta \ell_t, x_t - x_{t+1} \rangle + \langle x_t - x_{t+1}, x_{t+1}-u \rangle
\\
&= \langle \eta \ell_t, x_t - x_{t+1} \rangle + \frac{1}{2}(\lVert u-x_t \rVert_2^2 - \lVert u - x_{t+1} \rVert_2^2 - \lVert x_t - x_{t+1} \rVert_2^2)
\\
&= (\langle \eta \ell_t, x_t - x_{t+1} \rangle - \frac{1}{2}\lVert x_t - x_{t+1} \rVert_2^2) + \frac{1}{2}(\lVert u-x_t \rVert_2^2 - \lVert u - x_{t+1} \rVert_2^2)
\\
&\le \frac{\eta^2}{2} \lVert \ell_t \rVert_2^2 + \frac{1}{2}(\lVert u-x_t \rVert_2^2 - \lVert u - x_{t+1} \rVert_2^2).
\end{aligned}
$$

So

$$
\begin{aligned}
\frac{1}{T}(\sum_{t=1}^T x_t^T \ell_t - \sum_{t=1}^T {x^*}^T \ell_t) &\le \frac{\eta}{2T} \sum_{t=1}^T \lVert \ell_t \rVert_2^2 + \frac{1}{2\eta T}\lVert x^* - x_1 \rVert_2^2
\\
&\le \frac{\eta n \rho^2}{2} + \frac{\lVert x^* - x_1 \rVert_2^2}{2\eta T}.
\end{aligned}
$$

Let $\eta = \frac{\lVert x^* - x_1 \rVert_2}{\rho \sqrt{nT}}$, so $\frac{1}{T}(\sum_{t=1}^T x_t^T \ell_t - \sum_{t=1}^T {x^*}^T \ell_t) \le \frac{\rho \sqrt n\lVert x^* - x_1 \rVert_2}{\sqrt T}$. When $\epsilon = \frac{1}{T}(\sum_{t=1}^T x_t^T \ell_t - \sum_{t=1}^T {x^*}^T \ell_t)$, we have $T \le \frac{\rho^2 n \lVert x^* - x_1 \rVert_2^2}{\epsilon^2} = O(\frac{\rho^2n}{\epsilon^2})$.

c. When $w(x) = \sum x^i \log x^i$, we have $\nabla w(x) = 1 + \log x$, so $V_x(y) = \sum y^i \log y^i - \sum (y-x)^i(1+\log x^i) - \sum x^i \log x^i = \sum y^i \log \frac{y^i}{x^i}$.

In MWU, we have $x_{t+1} = R(x_te^{-\eta\ell_t})$, where $R(x) = \frac{x}{\lVert x \rVert_1}$.

In MD, we have $x_{t+1} = \argmin_{y \in \Delta_n} \{\sum y^i \log \frac{y^i}{x^i} + \eta \langle \ell_t, y-x_t \rangle\}$. Let $g(y, \lambda) = \sum y^i \log \frac{y^i}{x^i} + \eta \langle \ell_t, y-x_t \rangle + \lambda(\lVert y \rVert_1 - 1)$, we have $\nabla_{y^i} g(y, \lambda) = 1 + \log y^i - \log x^i + \eta \ell_t^i + \lambda R(y)^i$, so $\lambda = 0$, $x_{t+1} = R(x_te^{-\eta \ell_t - 1})$.

So they calc same $x_{t+1}$.

d. We first prove $V_x(y) \ge \frac{1}{2} \lVert x-y \rVert_1^2$. We have $\nabla^2 w(x) = diag(\{\frac{1}{x^i}\})$, so $\lVert y \rVert_1^2 = (\sum \frac{y^i}{\sqrt x^i} \cdot \sqrt x^i)^2 \le \sum \frac{{y^i}^2}{x^i} \sum x^i = y^T \nabla^2 w(x)y$. We have $V_x(y) = \int_0^1 (1-t)(y-x)^T \nabla^2 w(x+t(y-x)) (y-x) \text{d}t \ge \frac{1}{2} \lVert y-x \rVert_1^2$.

Then we prove $\lVert x \rVert_\infty^2 - 2\langle x, y \rangle + \lVert y \rVert_1^2 \ge 0$. We have $\langle x, y \rangle = \sum x^iy^i \le \max x^i \sum y^i = \lVert x \rVert_\infty^2 \lVert y \rVert_1^2$, so $\lVert x \rVert_\infty^2 - 2\langle x, y \rangle + \lVert y \rVert_1^2 \ge (\lVert x \rVert_\infty - \lVert y \rVert_1)^2 \ge 0$.

And when $x=(\frac{1}{n}, \cdots, \frac{1}{n})$, $V_x(y) = \log n + \sum y^i \log y^i \le \log n$.

We have

$$
\begin{aligned}
\eta(x_t^T \ell_t - u^T \ell_t) &= \eta \langle \ell_t, x_t - u \rangle
\\
&= \langle \eta\ell_t, x_t - x_{t+1} \rangle + \langle \eta\ell_t, x_{t+1} - u \rangle
\\
&= \langle \eta\ell_t, x_t - x_{t+1} \rangle + \langle x_t - x_{t+1}, x_{t+1} - u \rangle
\\
&= \langle \eta\ell_t, x_t - x_{t+1} \rangle + V_{x_t}(u)-V_{x_{t+1}}(u)-V_{x_t}(x_{t+1})
\\
&\le (\langle \eta\ell_t, x_t - x_{t+1} \rangle - \frac{1}{2} \lVert x_t - x_{t+1} \rVert_1^2) + V_{x_t}(u)-V_{x_{t+1}}(u)
\\
&\le \frac{\eta^2}{2} \lVert \ell_t \rVert_\infty^2 + V_{x_t}(u) - V_{x_{t+1}}(u).
\end{aligned}
$$

So

$$
\begin{aligned}
\frac{1}{T}(\sum_{t=1}^T x_t^T \ell_t - \sum_{t=1}^T {x^*}^T \ell_t) &\le \frac{\eta}{2T} \sum_{t=1}^T \lVert \ell_t \rVert_\infty^2 + \frac{V_{x_1}(x^*)}{\eta T}
\\
&\le \frac{\eta \rho^2}{2} + \frac{\log n}{\eta T}.
\end{aligned}
$$

When $\eta = \frac{\sqrt{2 \log n}}{\rho \sqrt T}$, let $\epsilon = \frac{1}{T}(\sum_{t=1}^T x_t^T \ell_t - \sum_{t=1}^T {x^*}^T \ell_t)$, we have $T \le \frac{2\rho^2 \log n}{\epsilon^2} = O(\frac{\rho^2 \log n}{\epsilon^2})$.
