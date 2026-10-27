# Week3 Homework

By Deng Yufan.

## Prob 1

For any continous $D$ and $\epsilon, \delta \in (0, 1)$, let $r^* \in \R^+$ that $L_{D, f}(h_{r^*})=0$. Let $p<r^*$ s.t. $\underset{x \sim D}{\text{Pr}}(\lVert x \rVert \in (p, r^*)) = \epsilon$. For any trainning set $S$, let $l = \max_{(x, 1) \in S} \lVert x \rVert$. For the algo that always take $h_l$ as optimal, if $l \ge p$, then so $L_{D, f}(h_l) \le \epsilon$. So $\text{Pr}(L_{D, f}(h_l) > \epsilon) \le \text{Pr}(l<p) = (1-\epsilon)^m = e^{m\ln (1-\epsilon)} \le e^{-m\epsilon}$, so when $m \ge \frac{\ln(1/\delta)}{\epsilon}$ we have $\text{Pr}(L_{D, f}(h_l) > \epsilon) \le \delta$. Thus $m_{\mathcal H}(\epsilon, \delta) \le \lceil \frac{\ln(1/\delta)}{\epsilon} \rceil$.

## Prob 2

a. VCdim = 1, since for $x$ we can have $h_{x+1}(x)=0$ and $h_{x-1}(x)=1$, but for $x<y$ we always have $h_a(x) \le h_a(y)$.

b. VCdim = 2, since for $x<y$ we can have ranges containing none, left, right, both. But for $x<y<z$, we cannot have $h_a(x)=1$, $h_a(y)=0$, $h_a(z)=1$.

c. VCdim = 1, since for $x \ne k \pi$ we have $h_1(x) \ne h_{-1}(x)$, but we have $|\mathcal H| = 2$ so VCdim cannot be larger than 1.

d. VCdim = 2, since for $x = \pi/4$, $y = 3\pi/4$, we have $h_0(x)=h_0(y)=1$, $h_{\pi}(x)=h_{\pi}(y)=0$, $h_{\pi/2}(x)=1, h_{\pi/2}(y)=0$, $h_{3\pi/2}(x)=0, h_{3\pi/2}(y)=1$. But if we let $U=[0, 2\pi)$, then $\{\mathcal 1\{\sin(x+a)>0\}\} \subseteq \{1\{a \le x \le b\}\}$, so VCdim cannot larger than 2.

e. VCdim can be any large. We can pick a list of odd prime: $p_0, p_2, \cdots, p_{2^n-1}$, and consider $\{h_{2\pi/p_s}\}$. We have $h_{2\pi/p_s}(x)=1$ if $x \bmod p = 1$ and $h_{2\pi/p_s}(x)=0$ if $x \bmod p = p-1$. So for $x_0, \cdots, x_{n-1}$, we can arrange some proper value to fit $h_{2\pi/p_s}(x_i) = [i \in s]$ where $s$ is bit mask for $[0, n)$.

## Prob 3

Let $\eta(x)=\text{Pr}(Y=1 \mid X=x)$, then $f_{\mathcal D}(x)=[\eta(x) \ge \frac{1}{2}]$. For all $g(x)$, we have $\text{Pr}(Y \ne g(x) \mid X=x) = \eta(x)$ or $\text{Pr}(Y \ne g(x) \mid X=x) = 1-\eta(x)$, so $\text{Pr}(Y \ne g(x) \mid X=x) \ge \min(\eta(x), 1-\eta(x))=\text{Pr}(Y \ne f_{\mathcal D}(x) \mid X=x)$.

So $\text{Pr}(Y \ne g(x)) \ge \text{Pr}(Y \ne f_{\mathcal D}(x))$, that is $L_{\mathcal D}(f_{\mathcal D}) \le L_{\mathcal D}(g)$.

## Prob 4

If $C$ is a shattering set of $\mathcal H'$, we have $|\mathcal H_C| \ge |\mathcal H'_C|=2^{|C|}$, so $C$ is a shattering set of $\mathcal H$. So VCdim of $\mathcal H$ is larger than VCdim of $\mathcal H'$.

## Prob 5

We need to calc $\max(\frac{n}{r}\max_i \lVert e_i^T U \rVert_2^2, \frac{m}{r}\max_j \lVert e_j^T V \rVert_2^2)$. Easy to see all of the matrix s.t. $n=m=4$, $r=2$, so we need to calc $2\max(\max_i \lVert e_i^T U \rVert_2^2, \max_j \lVert e_j^T V \rVert_2^2)$. We also have $\lVert e_i^T U \rVert_2^2 = e_i^T U U^T e_i = (UU^T)_{i, i}$, $\lVert e_j^TV \rVert_2^2 = (VV^T)_{i, i}$.

For $A_1$, the column space is $U: \{\frac{1}{\sqrt 2}(1, 1, 0, 0)^T, \frac{1}{\sqrt 2}(0, 0, 1, 1)^T\}$, so every $(UU^T)_{i, i} = \frac{1}{2}$. The row space is $V: \{\frac{1}{\sqrt 2}(1, 0, 1, 0)^T, \frac{1}{\sqrt 2}(0, 1, 0, 1)^T\}$, so $(VV^T)_{i, i}=\frac{1}{2}$. Thus $u=1$.

For $A_2$, the column space is the same as $A_1$. And easy to calc $\max (VV^T)_{i, i} = \frac{113}{114}$. Thus $u = \frac{113}{57}$.

For $A_3$, the column space is the same as $A_1$. And easy to calc $\max (VV^T)_{i, i} = \frac{87}{89}$. Thus $u = \frac{174}{89}$.
