# Week8 Homework

By Deng Yufan.

## P230 T3

Let $R$ be a ring with identity and let $S$ be a subring of $R$ containing the identity. Prove that if $u$ is a unit in $S$ then $u$ is a unit in $R$. Show by example that the converse is false.

---

We have $uv = 1$ for a $v \in S$. Since $u, v \in S \le R$, $u$ is a unit in $R$.

Conversely, consider $R=Q$, $S=Z$, then $S \le R$. Consider $u = 2 \in S \le R$, we have $\frac{1}{2}u = 1$ thus $u$ is unit in $R$, but obviously $u$ is not unit in $S$.

## P231 T7

The center of a ring $R$ is $\{z \in R \mid zr = rz \forall r \in R\}$ (i.e., is the set of all elements which commute with every element of $R$). Prove that the center of a ring is a subring that contains the identity. Prove that the center of a division ring is a field.

---

Since $1r=r=r1$ for all $r$, so $1 \in Z(R)$. If $x, y \in Z(R)$, then $r(x-y)=rx-ry=xr-yr=(x-y)r$, $x-y \in Z(R)$, so $Z(R)$ is a subgroup of $R$. Also $rxy=xry=xyr$, $xy \in Z(R)$, so $Z(R)$ is a subring of $R$.

Obviously $Z(R)$ is commutative. If $R$ is a division ring, then $Z(R)$ has $1 \ne 0$. If $0 \ne x \in Z(R)$, then $x^{-1}r = x^{-1}rxx^{-1} = x^{-1}xrx^{-1}=rx^{-1}$, so $x^{-1} \in Z(R)$. Thus $Z(R)$ is a field.

## P231 T13

An element $x$ in $R$ is called nilpotent if $x^m = 0$ for some $m \in Z^+$.

a. Show that if $n=a^kb$ for some integers $a$ and $b$ then $\overline{ab}$ is a nilpotent element of $Z/nZ$.

b. If $a \in Z$ is an integer, show that the element $\overline a \in Z/nZ$ is nilpotent if and only if every prime divisor of $n$ is also a divisor of $a$. In particular, determine the nilpotent elements of $Z/72Z$ explicitly.

c. Let $R$ be the ring of functions from a nonempty set $X$ to a field $F$. Prove that $R$ contains no nonzero nilpotent elements.

---

a. Obviously $(ab)^k = (a^kb)b^{k-1} = 0$.

b. Let $n=p_1^{c_1} \cdots p_k^{c_k}$.

If: Let $a=p_1^{d_1} \cdots p_k^{d_k}$, then $a^m = 0$ where $m = c_1c_2 \cdots c_k$.

Only if: If $a^m = 0$ and $a \equiv t \pmod {p_i}$ for $0 < t < p_i$, then $t^m \equiv a^m \equiv 0 \pmod {p_i}$, contradiction.

Since $72 = 2^3 \times 3^2$, then for all $6 \mid x$, $x$ is a nilpotent.

## P231 T15

A ring $R$ is called a Boolean ring if $a^2 = a$ for all $a \in R$. Prove that every Boolean ring is commutative.

---

For all $x, y \in R$, we have $x + y = (x+y)^2 = x(x+y)+y(x+y) = x^2 + xy + yx + y^2 = x + y + xy + yx$. So $xy + yx = 0$, thus $xy = -yx$.

For all $z \in R$, we have $2z = (2z)^2 = 4z^2 = 4z$. So $2z = 0$.

Thus we have $xy + 2(yx) = -yx + 2(yx)$, which is $xy = yx$.

## P232 T25

Let $I$ be the ring of integral Hamilton Quaternions and define $N : I \rarr Z$ by $N(a + bi + cj + dk) = a^2 + b^2 + c^2 + d^2$ (the map $N$ is called a norm).

a. Prove that $N(\alpha) = \alpha \overline \alpha$ for all $\alpha \in I$, where if $\alpha = a + bi + cj + dk$ then $\overline \alpha = a - bi - cj - dk$.

b. Prove that $N(\alpha \beta) = N(\alpha)N(\beta)$ for all $\alpha, \beta \in I$.

c. Prove that an element of $I$ is a unit if and only if it has norm $+1$. Show that $I^\times$ is isomorphic to the quaternion group of order 8.

---

a. $\alpha \overline \alpha = (a + bi + cj + dk)(a - bi - cj - dk) = a^2 + b^2 + c^2 + d^2 + a(-bi-cj-dk) + (bi+cj+dk)a - \sum_{x, y \in \{bi, cj, dk\}} xy = a^2 + b^2 + c^2 + d^2 = N(\alpha)$.

b. Since $\overline \alpha$ is a auto. that $\phi(1) = 1$, $\phi(i) = -i$, $\phi(j) = -j$, $\phi(k) = -k$, and we have $\phi(xy) = \phi(y) \phi(x)$ for all $x, y \in \{1, i, j, k\}$, thus $\overline{xy} = \overline y \times \overline x$.

We have $N(\alpha \beta) = (\alpha \beta) \overline{\alpha \beta} = (\alpha \beta)(\overline \beta \overline \alpha) = \alpha N(\beta) \overline \alpha = \alpha \overline \alpha N(\beta) = N(\alpha)N(\beta)$.

c. If: Consider $\beta = \overline \alpha$, then $\alpha \beta = N(\alpha) = 1$.

Only if: Consider $\alpha \beta = 1$, then $N(\alpha)N(\beta) = N(\alpha \beta) = N(1) = 1$. Since $N(x) \in N$, only can have $N(\alpha) = N(\beta) = 1$.

When $N(x) = 1$, only can have that $x \in Q_8$. Obviously identity $\phi : Q_8 \rarr Q_8$ is a iso.

## P237 T1

Let $R$ be a commutative ring with $1$.

Let $p(x) = 2x^3 - 3x^2 + 4x - 5$ and let $q(x) = 7x^3 + 33x - 4$. In each of parts (a), (b) and (c) compute $p(x) + q(x)$ and $p(x)q(x)$ under the assumption that the coefficients of the two given polynomials are taken from the specified ring (where the integer coefficients are taken mod $n$ in parts (b) and (c)):

a. $R=Z$, b. $R=Z/2Z$, (c) $R=Z/3Z$.

---

a. $p(x)+q(x) = 9x^3 - 3x^2 + 37x - 9$.

$p(x)q(x) = 14x^6 - 21x^5 + 94x^4 - 142x^3 + 144x^2 - 181x + 20$.

b. $p(x)+q(x) = x^3 + x^2 + x + 1$.

$p(x)q(x) = x^5 + x$.

c. $p(x)+q(x) = x$.

$p(x)q(x) = 2x^6 + x^4 + 2x^3 + 2x + 2$.

## P239 T10

Consider the following elements of the integral group ring $ZS_3$: $\alpha = 3(1, 2) - 5(2, 3) + 14(1, 2, 3)$ and $\beta = 6e + 2(2, 3) - 7(1, 3, 2)$ (where $e$ is the identity of $S_3$). Compute the following elements:

a. $\alpha + \beta$, b. $2\alpha - 3\beta$, c. $\alpha \beta$, d. $\beta \alpha$, e. $\alpha^2$.

---

a. $\alpha + \beta = 6e + 3(1, 2) - 3(2, 3) + 14(1, 2, 3) - 7(1, 3, 2)$.

b. $2\alpha - 3\beta = -18e + 6(1, 2) - 16(2, 3) + 28(1, 2, 3) + 21(1, 3, 2)$.

c. $\alpha \beta = -108e + 81(1, 2) - 21(1, 3) - 30(2, 3) + 90(1, 2, 3)$.

d. $\beta \alpha = -108e + 18(1, 2) + 63(1, 3) - 51(2, 3) + 84(1, 2, 3) + 6(1, 3, 2)$.

e. $\alpha^2 = 34e - 70(1, 2) - 28(1, 3) + 42(2, 3) - 15(1, 2, 3) + 181(1, 3, 2)$.

## P249 T22

Let $a$ be an element of the ring $R$.

a. Prove that $\{x \in R \mid ax = 0\}$ is a right ideal and $\{y \in R \mid ya = 0\}$ is a left ideal (called respectively the right and left annihilators of $a$ in $R$).

b. Prove that if $L$ is a left ideal of $R$ then $\{x \in R \mid xa = 0 \forall a \in L\}$ is a two-sided ideal (called the left annihilator of $L$ in $R$).

---

a. For all $ax=0$, we have $a(xr) = (ax)r = 0$. So $\{x \in R \mid ax = 0\} r \subseteq \{x \mid ax = 0\}$.

Likewise, $\{y \in R \mid ya = 0\}$ is a left ideal.

b. For all $xa = 0 \forall a \in L$, we have $(rxr')a = (rx)(r'a) = (rx)a' = r(xa') = 0$ since $L$ is left ideal. So $\{x \in R \mid xa = 0 \forall a \in L\}$ is a ideal.

## P250 T26

The characteristic of a ring $R$ is the smallest positive integer $n$ such that $1 + 1 + \cdots + 1 = 0$ ($n$ times) in $R$; if no such integer exists the characteristic of $R$ is said to be $0$. For example, $Z/nZ$ is a ring of characteristic $n$ for each positive integer $n$ and $Z$ is a ring of characteristic $0$.

a. Prove that the map $Z \rarr R$ defined by $$k \rarr \left\{ \begin{aligned} &1 + 1 + \cdots + 1 (k \text{ times}) & k > 0 \\ &0 & k = 0 \\ &-1 - 1 - \cdots - 1 (-k \text{ times}) & k < 0 \end{aligned} \right.$$ is a ring homomorphism whose kernel is $nZ$, where $n$ is the characteristic of $R$ (this explains the use of the terminology "characteristic 0" instead of the archaic phrase "characteristic $\infty$" for rings in which no sum of 1's is zero).

b. Determine the characteristics of the rings $Q$, $Z[x]$, $Z/nZ[x]$.

c. Prove that if $p$ is a prime and if $R$ is a commutative ring of characteristic $p$, then $(a + b)^p = a^p + b^p$ for all $a, b \in R$.

---

a. We have $\phi(x+y) = (x+y)\cdot 1 = x \cdot 1 + y \cdot 1 = \phi(x) + \phi(y)$, where $n \cdot 1$ means $n$ '1' plus together (-1 if $n<0$). And $\phi(xy) = (xy) \cdot 1 = (x \cdot 1)(y \cdot 1) = \phi(x) \phi(y)$. So $\phi$ is a homo. We have $\phi(x) = 0$ iff $x = 0$ or ($n \ne 0$ and $n \mid x$), so $\ker \phi = nZ$.

b. Since $n \cdot 1$ will never be $0$ in $Q$, $\text{char}(Q)=0$. Likewise, $\text{char}(Z[x])=0$. Since $n \cdot 1 = 0$ in $Z/nZ[x]$, we have $\text{char}(Z/nZ[x]) = n$.

c. We have $(a+b)^p = \sum_{i=0}^p {p \choose i} a^ib^{p-i} = a^p + b^p + \sum_{i=1}^{p-1} {p \choose i} a^ib^{p-i}$. Since ${p \choose i} = \frac{p!}{i!(p-i)!}$, when $i \ne 0$, $i \ne p$, we have $p \mid {p \choose i}$. So ${p \choose i} a^ib^{p-i} = 0$ for all $0 < i < p$, thus $(a + b)^p = a^p + b^p$.
