# Week9 Homework

By Deng Yufan.

## P250 T35

Let $I$, $J$, $K$ be ideals of $R$.

a. Prove that $I (J + K) =I J +I K$ and $(I + J)K = I K + J K$.

b. Prove that if $J \subseteq I$ then $I \cap (J + K) = J + (I \cap K)$.

---

a. Obviously $J+K$ is ideal. We have $I(J+K) \subseteq R(J+K) = (J+K)$. Since $J+K \subseteq IJ+IK$, $IJ+IK$ is ideal, so $(J+K) \subseteq IJ+IK$.

Conversely, we have $IJ \subseteq I(J+K)$, $IK \subseteq I(J+K)$, so $IJ+IK \subseteq I(J+K)$.

Prove $(I+J)K=IK+JK$ is likewise.

b. Since $J \subseteq I$, we have $I \cap (J+K) = I \cap (J+I \cap K) = J + I \cap K$.

## P256 T5

Prove that if $M$ is an ideal such that $R/M$ is a field then $M$ is a maximal ideal.

---

If $M \subset M' \subset R$, $M'$ is ideal. Then we have $(R/M)/(M'/M) \cong R/M'$ is a field. So $M'/M$ is a ideal of $R/M$, but $R/M$ only have $0$ and $R/M$ to be ideal, so $M'=M$ or $M'=R$, contradiction.

## P258 T25

Assume $R$ is commutative and for each $a \in R$ there is an integer $n > 1$ (depending on $a$) such that $a^n = a$. Prove that every prime ideal of $R$ is a maximal ideal.

---

Let $P$ be a prime ideal, then $R/P$ is integral. For all $a+P \in R/P$, we have $0 = (a^n+P)-(a+P) = (a+P) \cdot (a^{n-1}-1+P)$. Since $R/P$ is integral, we have $a+P = 0+P$ or $a^{n-1}-1+P = 0+P$. So $a+P=0+P$ or $a^{n-1}+P=1+P$.

If $a+P \ne 0+P$, then $a^{n-2}+P$ is a inverse of $a+P$. So $R/P$ is a field thus $P$ is maximal.

## P260 T41

A proper ideal $Q$ of the commutative ring $R$ is called primary if whenever $ab \in Q$ and $a \notin Q$ then $b^n \in Q$ for some positive integer $n$. (Note that the symmetry between $a$ and $b$ in this definition implies that if $Q$ is a primary ideal and $ab \in Q$ with neither $a$ nor $b$ in $Q$, then a positive power of $a$ and a positive power of $b$ both lie in $Q$.) Establish the following facts about primary ideals.

a. The primary ideals of $Z$ are $0$ and $(p^n)$, where $p$ is a prime and $n$ is a positive integer.

b. Every prime ideal of $R$ is a primary ideal.

c. An ideal $Q$ of $R$ is primary if and only if every zero divisor in $R/Q$ is a nilpotent element of $R/Q$ (P231 T13).

d. If $Q$ is a primary ideal then $\text{rad}(Q)$ is a prime ideal ($\text{rad}(Q) = \{r \in R \mid r^n \in Q\}$).

---

a. If $(x)$ is primary, and $x = p_1^{c_1}p_2^{c_2}\cdots$ (more than 2 primes), then let $a = p_1^{c_1}$, $b = p_2^{c_2}\cdots$. We have $1 < a, b < x$, $ab = x$. Then $a^n \in (x)$, that is $a^n = kx$. But $\gcd(a^n, p_2) = 1$, $\gcd(kx, p_2) > 1$.

Easy to verify $0$ and $(p^n)$ is primary.

b. If $Q$ is prime, then $ab \in Q, a \notin Q \Rarr b \in Q$.

c. $Q$ is primary iff $ab \in Q, a \notin Q \Rarr b^n \in Q$ iff $(a+Q)(b+Q) = 0, a+Q \ne 0 \Rarr b^n+Q = 0$ iff zero divisor in $R/Q$ is nilpotent.

d. Let $I = \text{rad}(Q)$, we have $rI = \{rx \mid x^n \in Q\}$. Since $x^n \in Q \rarr r^nx^n \in Q$, we have $rI \subseteq \{rx \mid (rx)^n \in Q\} \subseteq I$. So $I$ is ideal.

If $ab \in I$, $a \notin I$, we have $a^nb^n = (ab)^n \in Q$, $a^n \notin Q$, so $b^{nm} = (b^n)^m \in Q$, $b \in I$.

## P264 T4

Prove that any subfield of $R$ must contain $Q$.

---

Let $F$ be a subfield of $R$, then $1 \in F$. So we have $n = n1 \in F$, thus $Z \subseteq F$. So $Q \subseteq F$.

## P267 T5

Let $n_1, n_2, \cdots, n_k$ be integers which are relatively prime inpairs: $(n_i, n_j) = 1$ for all $i \ne j$.

a. Show that the Chinese Remainder Theorem implies that for any $a_1, a_2, \cdots, a_k \in Z$ there is a solution $x \in Z$ to the simultaneous congruences $x \equiv a_1 \bmod {n_1}, x \equiv a_2 \bmod {n_2}, \cdots, x \equiv a_k \bmod {n_k}$ and that the solution $x$ is unique $\bmod n = n_1n_2 \cdots n_k$.

b. Let $n_i' = n/n_i$ be the quotient of $n$ by $n_i$, which is relatively prime to $n_i$ by assumption. Let $t_i$ be the inverse of $n_i' \bmod n_i$. Prove that the solution $x$ in a. is given by $x = a_1t_1n_1' + a_2t_2n_2' + \cdots + a_kt_kn_k' \bmod n$.

c. Solve the simultaneous system of congruences $x \equiv 1 \bmod 8, x \equiv 2 \bmod 25, x \equiv 3 \bmod 81$, and the simultaneous system $y \equiv 5 \bmod 8, y \equiv 12 \bmod 25, y \equiv 47 \bmod 81$.

---

a. Let $\phi : Z \rarr Z/n_1Z \times Z/n_2Z \times \cdots \times Z/n_kZ$, then we have $\phi$ is onto and $\ker \phi = \bigcap n_iZ = (n_1n_2 \cdots n_k)Z$. So $Z/(n_1n_2 \cdots n_k)Z \cong Z/n_1Z \times Z/n_2Z \times \cdots \times Z/n_kZ$, thus we can find a unique $x \in Z/(n_1n_2 \cdots n_k)Z$ that $\phi(g) = (a_1, a_2, \cdots, a_k)$ for all $g \in x$.

b. We have $t_in_i' \bmod n_j = 0$ if $i \ne j$, and $t_in_i' \bmod n_i = 1$. So the solution is obviously right.

c. We have $n = 16200$, $n_1' = 2025$, $n_2' = 648$, $n_3' = 200$, $t_1 = 1$, $t_2 = 12$, $t_3 = 32$.

So $x \equiv 4377 \bmod 16200$, $y \equiv 15437 \bmod 16200$.

## P269 T11

Let $p$ be a prime, let $I=Z^+$, let $A_i=Z/p^iZ$ and let $\mu_{ji}$ be the natural projection maps $\mu_{ji}:a \pmod {p_j} \rarr a \pmod {p_i}$. The inverse limit $\underset{\xleftarrow{\hphantom \lim}}\lim Z/p^iZ$ is called the ring of $p$-adic integers, and is denoted by $Z_p$. (a element in $Z_p$ is a infinite sequence $\{a_i\}$ that $a_i \in A_i$, $\mu_{ji}(a_j)=a_i$.)

a. Show that every element of $Z_p$ may be written uniquely as an infinite formal sum $b_0+b_1p+\cdots$ with each $b_i \in \{0, 1, \cdots, p-1\}$. Describe the rules for adding and multiplying such formal sums corresponding to addition and multiplication in the ring $Z_p$.

b. Prove that $Z_p$ is an integral domain that contains a copy of the integers.

c. Prove that $b_0+b_1p+\cdots$ as in a. is a unit in $Z_p$ if and only if $b_0 \ne 0$.

d. Prove that $pZ_p$ is the unique maximal ideal of $Z_p$ and $Z_p/pZ_p \cong Z/pZ$. Prove that every nonzero ideal of $Z_p$ is of the form $p^n Z_p$ for some integer $n \ge 0$.

e. Show that if $a_1 \not \equiv 0 \pmod p$ then there is an element $a = (a_i)$ in the direct limit $Z_p$ satisfying $a_j^{p-1} \equiv 1 \pmod {p^j}$ and $\mu_{j1}(a_j)=a_1$ for all $j$. Deduce that $Z_p$ contains $p - 1$ distinct $(p-1)^{\text{st}}$ roots of $1$.

---

a. For $(a_1, a_2, \cdots)$ ($0 \le a_n < p^n$) to $b_0+b_1p+\cdots$, we can have $b_0 = a_1$, $b_1 = \frac{a_2-a_1}{p}$, $b_n = \frac{a_{n+1}-a_n}{p^n}$. We have $0 \le b_i < p$ and $b_i \in \N$ since $0 \le a_n < p^n$ and $a_{n+1} \equiv a_n \pmod {p^n}$. Thus we have $b_0+b_1p+\cdots \equiv a_i \pmod {p^i}$.

Conversely, we can have $a_n = b_0+b_1p+\cdots+b_{n-1}p^{n-1}$.

Add and mul two formal sum is just like what we do to normal integers in base $p$.

b. If $b_n \ne 0$, $c_m \ne 0$, then we have $(bc)_{n+m} \ne 0$, thus $Z_p$ is integral.

For a integer, we get its $p$-base representation, write into a form of sum, then we have the integer in $Z_p$.

c. If: We can have $c_0 \equiv b_0^{-1} \pmod p$, $c_1 \equiv -b_0^{-1}(b_1c_0) \pmod {p^2}$, $c_n \equiv -b_0^{-1}\sum_{i=0}^{n-1} b_{n-i}c_i \pmod {p^n}$. Easy to verify $bc=1$.

Only if: When $bc=1$, we have $1=(bc)_0=b_0c_0$, so $b_0 \ne 0$.

d. We have $(pb)_{n+1}=b_n$, so $pZ_p$ is that the set $b$ that $b_0=0$. Obviously if $b_0=0$ then $(bc)_0=0$, so $pZ_p$ is ideal.

We have $b+pZ_p=c+pZ_p$ iff $b-c \in pZ_p$ iff $(b-c)_0=0$ iff $b_0=c_0$. So $Z_p/pZ_p \cong Z/pZ$ by take $b_0$. Since $Z/pZ$ is a field, $pZ_p$ is maximal ideal.

If $I$ is a ideal of $Z_p$ and $b \in I$, $b_0 \ne 0$, we have $1=cb \in I$, thus $I=Z_p$. So $pZ_p$ is unique maximal ideal.

If $I$ is a ideal, let $\text{low}(b)$ be the lowest digit that is non-zero, and we find $b$ has minimal $\text{low}(b)$, let $\text{low}(b)=t$. Let $c_n=b_{n+t}$, then $c_0 \ne 0$, we have $cd=1$. Thus $bd=p^t$, and obviously $p^t$ can generate $p^tZ_p$.

e. Let $a_n \equiv a_1^{p^{n-1}} \pmod {p^n}$, then we have $a_n \equiv a_1^{p^{n-1}} \equiv a_1^{p^{n-1} \bmod p^{i-1}(p-1)} \equiv a_1^{p^{i-1}(p^{n-i} \bmod p-1)} \equiv a_1^{p^{i-1}} \equiv a_i \pmod {p^i}$. So $(a_i) \in Z_p$. We have $a_n^{p-1} \equiv a_1^{(p-1)p^{n-1}} \equiv a_1 \pmod {p^n}$.

So for all $a_1 \in (0, p) \cap \N$, we can have $b$ that $b^{p-1}=1$, thus $\sqrt[p-1]1$ has $p-1$ solutions in $Z_p$.

## P278 T4

Let $R$ be a Euclidean Domain.

a. Prove that if $(a, b) = 1$ and $a$ divides $bc$, then $a$ divides $c$. More generally, show that if $a$ divides $bc$ with nonzero $a$, $b$ then $\frac{a}{(a, b)}$ divides $c$.

b. Consider the Diophantine Equation $ax + by = N$ where $a$, $b$ and $N$ are integers and $a$, $b$ are nonzero. Suppose $x_0$, $y_0$ is a solution: $ax_0 + by_0 = N$. Prove that the full set of solutions to this equation is given by $x=x_0+m\frac{b}{(a, b)}$, $y=y_0-m\frac{a}{(a, b)}$ as $m$ ranges over the integers.

---

a. Let $(a, b) = d$, $a=dx$, $b=dy$. We have $(x, y)=1$, $dxz=dyc$, $xz=yc$.

Let $px+qy=1$, then we have $qxz=qyc=(1-px)c$, thus $c=(pc+qz)x$, $x \mid c$. And we have $x = \frac{a}{d} = \frac{a}{(a, b)}$.

b. Let $x$, $y$ satisfy $ax+by=N$. We have $ax+by=ax_0+by_0$, $a(x-x_0)=b(y_0-y)$. So $a \mid b(y_0-y)$, thus $\frac{a}{(a, b)} \mid y_0-y$. Likewise, $\frac{b}{(a, b)} \mid x-x_0$.

Let $x=x_0+m\frac{b}{(a, b)}$, $y=y_0-n\frac{a}{(a, b)}$, we have $N=ax+by=ax_0+by_0+(m-n)\frac{ab}{(a, b)} = N+(m-n)\frac{ab}{(a, b)}$, so $(m-n)\frac{ab}{(a, b)} = 0$, thus $m=n$.

## P278 T7

Find a generator for the ideal $(85, 1 + 13i)$ in $Z[i]$, i.e., a greatest common divisor for $85$ and $1 + 13i$, by the Euclidean Algorithm. Do the same for the ideal $(47 - 13i, 53 + 56i)$.

---

Let $N(a+bi)=a^2+b^2$. We have

$$
\begin{aligned}
85&=(1+13i)(-7i)+(-6+7i)
\\
1+13i&=(-6+7i)(1-i)+0,
\end{aligned}
$$

$$
\begin{aligned}
53+56i&=(47-13i)(1+i)+(-7+22i)
\\
47-13i&=(-7+22i)(-1-2i)+(-4-5i)
\\
-7+22i&=(-4-5i)(-2-3i)+0.
\end{aligned}
$$

So $(85, 1+13i)=(-6+7i)$, $(53+56i, 47-13i)=(-4-5i)$.

## P279 T12

Let $N$ be a positive integer. Let $M$ be an integer relatively prime to $N$ and let $d$ be an integer relatively prime to $\varphi(N)$, where $\varphi$ denotes Euler's $\varphi$-function. Prove that if $M_1 \equiv M^d \pmod N$ then $M \equiv M^{d'}_1 \pmod N$ where $d'$ is the inverse of $d \bmod \varphi(N)$: $dd' \equiv 1 \pmod {\varphi(N)}$.

---

We have $M_1^{d'} \equiv (M^d)^{d'} \equiv M^{dd'} \equiv M \pmod N$ since $M^{\varphi(N)} \equiv 1 \pmod N$ since $(M, N) = 1$.
