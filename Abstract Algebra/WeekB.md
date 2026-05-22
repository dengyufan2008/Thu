# WeekB Homework

By Deng Yufan.

## P311 T2

Prove that the following polynomials are irreducible in $Z[x]$:

b. $x^6+30x^5-15x^3+6x-120$.

d. $\frac{(x+2)^p-2^p}{x}$, where $p$ is an odd prime.

---

b. We have $f(x)=x^6+30x^5-15x^3+6x-120$, then $f'(x) = f(x) \bmod 9=
x^6+3x^5+3x^3-3x-3$. Since $Z_9/(3)=Z_3$ is a field, so $(3)$ is prime in $Z_9$. Since $f'_6=1$, $f'_i \in (3)$, $f'_0 \notin (3)^2 = (0)$, $f'(x)$ thus $f(x)$ is irreducible.

d. We have $g(x)=\frac{(x+2)^p-2^p}{x} = \sum_{i=0}^{p-1}{p \choose i+1}x^i$, so $g_{p-1}=1$, $p \mid g_i$, $p^2 \nmid g_0$, thus $g(x)$ is irreducible.

## P311 T7

Prove that $R[x]/(x^2 + 1)$ is a field which is isomorphic to the complex numbers.

---

Easy to verify $(x-a)(x-b) \ne x^2+1$ when $a, b \in R$. So $x^2+1$ is irreducible and belongs to $R[x]$. So $K=R[x]/(x^2+1)$ is a extend of $R$, $\{1, \theta\}$ is a basis for $K$. So $K = \{a+b\theta \mid a, b \in R\}$, and we have $\theta^2+1=0$, that is $\theta^2=-1$. So $K=C$.

## P312 T18

Show that $6x^5 + 14x^3 - 21x + 35$ and $18x^5 - 30x^2 + 120x +360$ are irreducible in $Q[x]$.

---

$6x^5 + 14x^3 - 21x + 35$: We have $7 \nmid 6$, $49 \nmid 35$, but $7 \mid 14, 21, 35$. Then irreducible in $Z[x]$, thus in $Q[x]$ bu Gauss.

$18x^5 - 30x^2 + 120x +360$: Likewise, use $p=5$.

## P312 T20

Show that the polynomial $f(x) = x$ in $Z/6Z[x]$ factors as $(3x + 4)(4x + 3)$, hence is not an irreducible polynomial.

a. Show that the reduction of $f(x)$ modulo both of the nontrivial ideals $(2)$ and $(3)$ of $Z/6Z$ is an irreducible polynomial, showing that the condition that $R$ be an integral domain in Proposition 12 is necessary.

b. Show that in any factorization $f(x) = g(x)h(x)$ in $Z/6Z[x]$ the reduction of $g(x)$ modulo $(2)$ is either $1$ or $x$ and the reduction of $h(x)$ modulo $(2)$ is then either $x$ or $1$, and similarly for the reductions modulo $(3)$. Determine all the factorizations of $f(x)$ in $Z/6Z[x]$.

c. Show that the ideal $(3, x)$ is a principal ideal in $Z/6Z[x]$.

d. Show that over the ring $Z/30Z[x]$ the polynomial $f(x) = x$ has the factorization $f(x) = (10x + 21)(15x + 16)(6x + 25)$. Prove that the product of any of these factors is again of the same degree.
Prove that the reduction of $f(x)$ modulo any prime in $Z/30Z$ is an irreducible polynomial. Determine all the factorizations of $f(x)$ in $Z/30Z[x]$.

e. Generalize part d. to $Z/nZ[x]$ where $n$ is the product of $k$ distinct primes.

---

a. We need to prove $f(x)=x$ is irreducible in $Z/2Z[x]$ and $Z/3Z[x]$. Since $Z/2Z$ and $Z/3Z$ is field, we prove $f(x)=x$ is irreducible in $F[x]$. If $f=ab$, we have $a_0b_0=0$, thus suppose $a_0=0$. Thus $f$ irreducible iff $g(x)=1$ irreducible. And we know $1$ is prime in $F[x]$, and $F[x]$ is ED.

b. Suppose $a_0=0$, we have $a_1b_0=1$. Thus $a_1=b_0=1$. Take max $n$, $m$ that $a_n=b_m=1$, so $f_{n+m}=1$. Thus $n+m=1$, so only $a(x)=x$, $b(x)=1$. Likewise, $a(x)=1$, $b(x)=x$.

If mod 3, then the coefficient of $a$, $b$ can both be 2.

If mod 6, that is $x * 1$, $(3x+4)(4x+3)$, $5x*5$, $(3x+2)(2x+3)$, and diverse by comm.

c. We have $(3, x)=(4x+3)$. Since $4x+3 \in (3, x)$, $(3x+4)(4x+3)=x$, $3(4x+3)=3$.

d. Mod 2: $1$, $x$, $1$. Mod 3: $x$, $1$, $1$. Mod 5: $1$, $1$, $x$. So the mul is $x$ mod 30.

Any two: Equal to $x$ mod 2 primes, and equal to $1$ mod the other. So the mul of two term is a 1-deg poly.

We already prove $f(x)$ mod any prime is irreducible in a.

All factorization is showed in e. as a special case.

e. Let $n=p_1 \cdots p_k$. Pick $n_1, n_2, \cdots, n_k$ that $n_i \equiv [i=j] \pmod {p_j}$ by CRT. For all $i \in [1, k]$, pick $a_{i1}, a_{i2}, \cdots, a_{ik}$ that $\prod_j a_{ij} \equiv 1 \pmod {p_i}$. All factorization is in form of $f=g_1g_2 \cdots g_k$, where $g_j=n_ja_{jj}x + \sum_{i \ne j} n_ia_{ij}$. Since $g_j \equiv 1 \pmod {p_i}$ for $i \ne j$, $g_j \bmod p_j$ is irreducible, then $g_j$ is irreducible.

## P315 T3

Let $p$ be an odd prime in $Z$ and let $n$ be a positive integer. Prove that $x^n - p$ is irreducible over $Z[i]$.

---

Since $Z[i]$ is ED, we have $p$ is prime when $p \equiv 3 \pmod 4$ and otherwise $p=a^2+b^2$ unique, $a+bi$ and $a-bi$ is prime.

If $p$ is prime, then $x^n-p$ is irreducible since $p \notin (p)^2$.

Otherwise, we have $N((a+bi)^2)=N(a+bi)^2=N(p)$. Since $p \ne (a+bi)^2$, and all 1-norm element is unit, we have $p \notin (a+bi)^2$, thus $x^n-p$ is irreducible.

## P315 T7

Prove that the additive and multiplicative groups of a field are never isomorphic.

---

If $-1 \ne 1$ in $F$, We have $\lvert -1 \rvert=2$ in $F^\times$. If $x+x=0$ in $F^+$, then $x=-x$, $1=-1$.

If $-1 = 1$ in $F$, We have $\lvert x \rvert = 2$ for $x \ne 0$ in $F^+$. So we have $x^2=1$ for all $x \in F^\times$. But $x^2=1$ has atmost 2 solution, thus $F^\times$ is finite. $|F^+|=|F|$ but $|F^\times|=|F|-1$.

## P519 T1

Show that $p(x) = x^3 + 9x + 6$ is irreducible in $Q[x]$. Let $\theta$ be a root of $p(x)$. Find the inverse of $1 + \theta$ in $Q(\theta)$.

---

Since $6 \notin (3)^2$, $9, 6 \in (3)$, $p(x)$ is irreducible in $Z[x]$, thus is irreducible in $Q[x]$ by Gauss.

We have $\theta^3+9\theta+6=0$, so easy to verify $(1+\theta)^{-1} = \frac{1}{4}(10-\theta+\theta^2)$.

## P519 T2

Show that $x^3-2x-2$ is irreducible over $Q$ and let $\theta$ be a root. Compute $(1+\theta)(1+\theta+\theta^2)$ and $\frac{1+\theta}{1+\theta+\theta^2}$ in $Q[\theta]$.

---

Since $2 \notin (2)^2$, $2 \in (2)$, the poly is irreducible.

We have $\theta^3-2\theta-2=0$. So $(1+\theta)(1+\theta+\theta^2)=3+4\theta+2\theta^2$. $\frac{1+\theta}{1+\theta+\theta^2} = \frac{1}{3}(1+2\theta-\theta^2)$.

## P519 T5

Suppose $a$ is a rational root of a monic polynomial in $Z[x]$. Prove that $a$ is an integer.

---

Let $a=\frac{r}{s}$, $p(x)$ is the poly mentioned, we have $s \mid p_n=1$, so $s=1$.

## P519 T6

Show that if $\alpha$ is a root of $a_nx^n+\cdots+a_0$ then $a_n \alpha$ is a root of the monic polynomial $x^n+a_{n-1}x^{n-1}+a_na_{n-2}x^{n-2}+\cdots+a_n^{n-1}a_0$.

---

We have $a_n^n\alpha^n+a_n^{n-1}a_{n-1}\alpha^{n-1}+\cdots+a_n^{n-1}a_0=0$. So $(a_n\alpha)^n+a_{n-1}(a_n\alpha)^{n-1}+\cdots+a_n^{n-1}a_0=0$.
