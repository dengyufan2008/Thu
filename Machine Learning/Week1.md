# Week1 Homework

By Deng Yufan.

## Prob 1

a. Self-supervised learning is for data that has no label, we find a way to generate the label for all data, and let model to learn. E.g. For LLM, we can delete the last word of a text, and let model to predict the last word.

Different to unsupervesed learning, self-supervised learning **do** has label for each data.

b. The research group use unsupervised learning to solve predicting image rotations, and gets a best result in all unsupervised learning, with similar accurary to supervised learning. The group use this method in other problems, getting a result as significant as the current problem.

c. Nowadays embodied AI can't fell tactile sensing very accurately and comprehensively, so they can't react the phisical world in time.

To solve this problem, we may make the hand of robot to be soft and be filled by liquid, thus we can measure the presure to deduce the force that every point is currently act.

## Prob 2

We have $n = 15$, $\mu = 6$, so $\text{Pr}(X \ge (1+\frac{2}{3})\mu = 10) \le e^{-\frac{8}{9}} \approx 0.41$.

## Prob 3

a. i. to ii.: We have

$$
\begin{aligned}
f(w')-f(w)-\langle \nabla f(w), w'-w \rangle &= \int_0^1 \langle \nabla f(w+u(w'-w)) - \nabla f(w), w'-w \rangle \text{d}u
\\
& \le \int_0^1 Lu \lVert w'-w \rVert \lVert w'-w \rVert \text{d}u
\\
& = \frac{L}{2} \lVert w'-w \rVert^2.
\end{aligned}
$$

ii. to i. (helped by chatgpt): We have

$$
\max(f(w')-f(w)+\langle \nabla f(w),w-w' \rangle, f(w)-f(w')+\langle \nabla f(w),w'-w \rangle) \le \frac{L}{2} \lVert w-w' \rVert^2,
$$

likely,

$$
\max(f(w)-f(w')+\langle \nabla f(w'),w'-w \rangle, f(w')-f(w)+\langle \nabla f(w'),w-w' \rangle) \le \frac{L}{2} \lVert w'-w \rVert^2,
$$

so

$$
|\langle \nabla f(w), w-w' \rangle + \langle \nabla f(w'), w'-w \rangle| \le L \lVert w-w' \rVert^2,
$$

that is

$$
|\langle \nabla f(w) - \nabla f(w'), w-w' \rangle| \le L \lVert w-w' \rVert^2.
$$

Let $w' = w + th$, we have

$$
|\langle \frac{\nabla f(w + th) - \nabla f(w)}{t}, h \rangle| \le L \lVert h \rVert^2.
$$

Let $t \rarr 0$, we have

$$
|\langle H(w)h, h \rangle| \le L \lVert h \rVert^2,
$$

that is

$$
|h^tH(w)h| \le L \lVert h \rVert^2,
$$

so

$$
\lVert H(w) \rVert \le L.
$$

Then we have

$$
\lVert \nabla f(w+h) - \nabla f(w) \rVert \sim \lVert H(w)h \rVert \le L\lVert h \rVert,
$$

integral, we have

$$
\lVert \nabla f(w)-\nabla f(w')\rVert \le L \lVert w - w' \rVert.
$$

b. i. -> ii.: Let $z=ax+(1-a)y$, we have

$$
\begin{aligned}
a(f(z)-f(x)) &\le (1-a)(f(y)-f(z))-a(1-a)\frac{\mu}{2}\lVert x-y \rVert^2,
\\
\frac{f(z)-f(x)}{(1-a)\lVert x-y \rVert} &\le \frac{f(y)-f(z)}{a\lVert x-y \rVert}-\frac{\mu}{2}\lVert x-y \rVert,
\\
\frac{f(z)-f(x)}{\lVert z-x \rVert} &\le \frac{f(y)-f(z)}{\lVert y-z \rVert} - \frac{\mu}{2}\lVert y-x \rVert.
\end{aligned}
$$

Let $a \rarr 1$, that is $z \rarr x$, we have

$$
\begin{aligned}
\langle \nabla f(x), \frac{y-x}{\lVert y-x \rVert} \rangle &\le \frac{f(y)-f(x)}{\lVert y-x \rVert} - \frac{\mu}{2}\lVert y-x \rVert,
\\
f(y) &\ge f(x) + \langle \nabla f(x), y-x \rangle + \frac{\mu}{2}\lVert x-y \rVert^2.
\end{aligned}
$$

ii. -> iii.: We have

$$
f(y) - f(x) \ge \langle \nabla f(x), y-x \rangle + \frac{\mu}{2}\lVert x-y \rVert^2
$$

and

$$
f(x) - f(y) \ge \langle \nabla f(y), x-y \rangle + \frac{\mu}{2}\lVert y-x \rVert^2,
$$

so we have

$$
0 \ge \langle \nabla f(x)- \nabla f(y), y-x \rangle + \mu\lVert x-y \rVert^2,
$$

that is

$$
\langle \nabla f(x)- \nabla f(y), x-y \rangle \ge \mu\lVert x-y \rVert^2.
$$

iii. -> iv.: Let $y=x+th$, we have

$$
\langle \frac{\nabla f(x+th)- \nabla f(x)}{t}, h \rangle \ge \mu\lVert h \rVert^2.
$$

Let $t \rarr 0$, we have

$$
\begin{aligned}
\langle H(x)h, h \rangle &\ge \mu \lVert h \rVert^2
\\
h^tH(x)h &\ge \mu \lVert h \rVert^2
\\
\lambda_{\min} H(x) &\ge \mu.
\end{aligned}
$$

iv. -> ii. (helped by chatgpt): Let $g(a) = f(ax+(1-a)y)$.

We have $g'(a) = \langle \nabla f(ax + (1-a)y), x-y \rangle$, $g''(a) = (x-y)^t H(ax+(1-a)y)(x-y) \ge \mu \lVert x-y \rVert^2$.

So $g'(a) \le g'(1) - (1-a)\mu \lVert x-y \rVert^2$, $g(1)-g(0) \le g'(1) - \frac{\mu}{2}\lVert x-y \rVert^2$.

That is $f(y) \ge f(x) + \langle \nabla f(x), y-x \rangle + \frac{\mu}{2}\lVert x-y \rVert^2$.

ii. -> i. Let $z = ax+(1-a)y$, we have

$$
\begin{aligned}
\frac{f(x)-f(z)}{(1-a)\lVert x-y \rVert} + \frac{f(y)-f(z)}{a\lVert x-y \rVert} &= \frac{f(x)-f(z)}{\lVert x-z \rVert} + \frac{f(y)-f(z)}{\lVert y-z \rVert}
\\
& \ge \frac{\langle \nabla f(z), x-z \rangle + \frac{\mu}{2}\lVert x-z \rVert^2}{\lVert x-z \rVert} + \frac{\langle \nabla f(z), y-z \rangle + \frac{\mu}{2}\lVert y-z \rVert^2}{\lVert y-z \rVert}
\\
&= \langle \nabla f(z), \frac{x-z}{\lVert x-z \rVert} \rangle + \frac{\mu}{2}\lVert x-z \rVert + \langle \nabla f(z), \frac{y-z}{\lVert y-z \rVert} \rangle + \frac{\mu}{2}\lVert y-z \rVert
\\
&= \frac{\mu}{2}\lVert x-y \rVert.
\end{aligned}
$$

That is

$$
a(f(x)-f(z))+(1-a)(f(y)-f(z)) \ge a(1-a)\frac{\mu}{2}\lVert x-y \rVert^2,
$$

so

$$
f(ax+(1-a)y) \le af(x) + (1-a)f(y) - a(1-a)\frac{\mu}{2}\lVert x-y \rVert^2.
$$

## Prob 4 (use chatgpt to understand the goal of problem)

a. Let $x_{n+1} = x_n - \eta \nabla f(x_n)$ where $\eta \le \frac{1}{L}$. Let $f^* = \inf f$. We have

$$
\begin{aligned}
f(x_{n+1}) &\le f(x_n) + \langle \nabla f(x_n), -\eta \nabla f(x_n) \rangle + \frac{L}{2} \lVert \eta \nabla f(x_n) \rVert^2
\\
&= f(x_n) - (\eta - \frac{L \eta^2}{2}) \lVert \nabla f(x_n) \rVert^2
\\
& \le f(x_n) - \frac{\eta}{2} \lVert \nabla f(x_n) \rVert^2.
\end{aligned}
$$

So

$$
\begin{aligned}
f(x_{n+1}) &\le f(x_n) - \frac{\eta}{2} \lVert \nabla f(x_n) \rVert^2
\\
&\le f(x_{n-1}) - \frac{\eta}{2}(\lVert \nabla f(x_n) \rVert^2 + \lVert \nabla f(x_{n-1}) \rVert^2)
\\
&\cdots
\\
&\le f(x_0) -\frac{\eta}{2}\sum_{i=0}^n \lVert \nabla f(x_i) \rVert^2.
\end{aligned}
$$

Thus

$$
\sum_{i=0}^n \lVert \nabla f(x_i) \rVert^2 \le \frac{2}{\eta}(f(x_0)-f(x_{n+1})) \le \frac{2}{\eta}(f(x_0)-f^*).
$$

$$
\min_{i \in [0, n]} \lVert \nabla f(x_i) \rVert^2 \le \frac{2(f(x_0)-f^*)}{\eta(n+1)}.
$$

So $\lVert \nabla f \rVert^2$ converges to 0 at speed of $O(\frac{1}{T})$.

b. Let $\eta \le \min(\frac{1}{L}, \frac{1}{2\mu})$, we have

$$
\begin{aligned}
f(x_{n+1}) &\le f(x_n) - \frac{\eta}{2} \lVert \nabla f(x_n) \rVert^2
\\
&\le f(x^*) + \langle \nabla f(x_n), x_n - x^* \rangle - \frac{\mu}{2}\lVert x_n - x^* \rVert^2 - \frac{\eta}{2}\lVert \nabla f(x_n) \rVert^2
\\
&= f(x^*) - \frac{1}{\eta}\langle x_{n+1}-x_n, x_n - x^* \rangle - \frac{1}{2\eta}\lVert x_{n+1}-x_n \rVert^2 - \frac{\mu}{2}\lVert x_n - x^* \rVert^2
\\
&= f(x^*) - \frac{1}{2\eta}\lVert x_{n+1}-x^* \rVert^2 + \frac{1}{2\eta} \lVert x_n-x^* \rVert^2 - \frac{\mu}{2}\lVert x_n - x^* \rVert^2
\\
&= f(x^*) + \frac{1-\mu \eta}{2\eta}\lVert x_n - x^* \rVert^2 - \frac{1}{2\eta}\lVert x_{n+1}-x^* \rVert^2
\end{aligned}
$$

That is

$$
\begin{aligned}
f(x_{n+1})-f(x^*) &\le \frac{1-\mu \eta}{2\eta}\lVert x_n - x^* \rVert^2 - \frac{1}{2\eta}\lVert x_{n+1}-x^* \rVert^2,
\\
\frac{f(x_{n+1})-f(x^*)}{(1-\mu \eta)^n} &\le \frac{1}{2\eta(1-\mu \eta)^{n-1}}\lVert x_n - x^* \rVert^2 - \frac{1}{2\eta(1-\mu \eta)^n}\lVert x_{n+1}-x^* \rVert^2,
\\
\sum_{i=0}^{n-1} \frac{f(x_{i+1})-f(x^*)}{(1-\mu \eta)^i} &\le \frac{1-\mu \eta}{2\eta}\lVert x_0 - x^* \rVert^2 - \frac{1}{2\eta(1-\mu \eta)^{n-1}}\lVert x_n-x^* \rVert^2,
\\
f(x_n)-f(x^*) &\le \frac{(1-\mu \eta)^n}{2\eta} \lVert x_0 - x^* \rVert^2.
\end{aligned}
$$

We have $1-\mu \eta \ge 1-\mu\frac{1}{2\mu}=\frac{1}{2}$, so $\frac{1}{2} \le 1-\mu\eta < 1$. Thus $f(x_n) \sim O((1-\epsilon)^n)$.
