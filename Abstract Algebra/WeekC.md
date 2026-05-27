# WeekC Homework

By Deng Yufan.

## P529 T1

Let $F$ be a finite field of characteristic $p$. Prove that $|F|=p^n$ for some positive integer $n$.

---

If $q \mid |F|$, $q \ne p$, then we have a Sylow-$q$ additive subgroup $Q$. Since add is comm., $Q \unlhd F$, that is $n_q=1$.

We have $aQ$ is also Sylow-$q$, so $aQ=Q$, that is $Q$ is a ideal for $F$. But we know field has only $0$ and $F$ to be ideal, contradiction.

## P529 T3

Determine the minimal polynomial over $Q$ for the element $1 + i$.

---

We have $f(x)=x^2-2x+2 \in Q[x]$ has root $1+i$ and $1-i$. Obviously $f(x)$ is minimal.

## P530 T7

Prove that $Q(\sqrt 2 + \sqrt 3) = Q(\sqrt 2, \sqrt 3)$. Conclude that $[Q(\sqrt 2 + \sqrt 3) : Q] = 4$. Find an irreducible polynomial satisfied by $\sqrt 2 + \sqrt 3$.

---

Obviously $Q(\sqrt 2 + \sqrt 3) \subseteq Q(\sqrt 2, \sqrt 3)$. We have $(\sqrt 2 + \sqrt 3)^2 = 5 + 2 \sqrt 6$, so $2 + \sqrt 6 \in Q(\sqrt 2 + \sqrt 3)$, thus $\frac{2 + \sqrt 6}{\sqrt 2 + \sqrt 3} = \sqrt 2 \in Q(\sqrt 2 + \sqrt 3)$, and $\sqrt 3 \in Q(\sqrt 2 + \sqrt 3)$. So $Q(\sqrt 2 + \sqrt 3) = Q(\sqrt 2, \sqrt 3)$. So $[Q(\sqrt 2 + \sqrt 3) : Q] = 4$.

We have $x^2-2\sqrt 3x+1$ has root $\sqrt 3 + \sqrt 2$ and $\sqrt 3 - \sqrt 2$; $x^2+2\sqrt 3x+1$ has root $-\sqrt 3 + \sqrt 2$ and $-\sqrt 3 - \sqrt 2$. So $(x^2+1)^2-12x^2=x^4-10x^2+1$ is a poly satisfying the cons.

## P530 T11

a. Let $\sqrt{3+4i}$ denote the square root of the complex number $3 + 4i$ that lies in the first quadrant and let $\sqrt{3-4i}$ denote the square root of $3 - 4i$ that lies in the fourth quadrant. Prove that $[Q(\sqrt{3+4i} + \sqrt{3-4i}) : Q] = 1$.

b. Determine the degree of the extension $Q(\sqrt{1+\sqrt{-3}}+\sqrt{1-\sqrt{-3}})$ over $Q$.

---

a. We have $(\sqrt{3+4i} + \sqrt{3-4i})^2=16$, so $\sqrt{3+4i} + \sqrt{3-4i} = 4$. Obviously $[Q(4):Q]=1$.

b. We have $(\sqrt{1+\sqrt{-3}}+\sqrt{1-\sqrt{-3}})^2=6$, so $\sqrt{1+\sqrt{-3}}+\sqrt{1-\sqrt{-3}} = \sqrt 6$. Obviously $[Q(\sqrt 6):Q]=2$.

## P530 T14

Prove that if $[F(a) : F]$ is odd then $F(a) = F(a^2)$.

---

We have $[F(a) : F(a^2)] \mid [F(a) : F]$, so $[F(a) : F(a^2)]$ is odd. We also have $x^2-(a^2)=0$ has a root $a$, so $[F(a) : F(a^2)] \le 2$. That is $[F(a) : F(a^2)] = 1$, and $F(a)=F(a^2)$.

## P530 T17

Let $f(x)$ be an irreducible polynomial of degree $n$ over a field $F$. Let $g(x)$ be any polynomial in $F[x]$. Prove that every irreducible factor of the composite polynomial $f(g(x))$ has degree divisible by $n$.

---

Pick a poly $p(x)$ is a irreducible factor of $f(g(x))$. Let $a \in K$ be a root for $p(x)$. We have $F(a) \cong F[x]/(p(x))$, $[F(a):F]=\deg p(x)$.

Since $p(a) \mid f(g(a))$, $f(g(a))=0$. So we have $b = p(a) \in F(a)$ that $f(b)=0$. So $F(b) \cong F[x]/(f(x))$, $[F(b):F]=\deg f(x)=n$.

Since $b=p(a)$, we have $F(a, b)=F(a)$. So $[F(b):F] \mid [F(a):F]$, that is $n \mid \deg p(x)$.

## P530 T18

Let $k$ be a field and let $k(x)$ be the field of rational functions in $x$ with coefficients from $k$. Let $t \in k(x)$ be the rational function $\frac{P(x)}{Q(x)}$ with relatively prime polynomials $P(x), Q(x) \in k[x]$, with $Q(x) \ne 0$. Then $k(x)$ is an extension of $k(t)$ and to compute its degree it is necessary to compute the minimal polynomial with coefficients in $k(t)$ satisfied by $x$.

a. Show that the polynomial $P(X) - tQ(X)$ in the variable $X$ and coefficients in $k(t)$ is irreducible over $k(t)$ and has $x$ as a root.

b. Show that the degree of $P(X) - tQ(X)$ as a polynomial in $X$ with coefficients in $k(t)$ is the maximum of the degrees of $P(x)$ and $Q(x)$.

c. Show that $[k(x) : k(t)] = [k(x) : k(\frac{P(x)}{Q(x)})] = \max (\deg P(x), \deg Q(x))$.

---

a. Only need to prove $P(X)-tQ(X)$ is irreducible in $(k[t])[X]=(k[X])[t]$ by Gauss. Since $\deg P(X)-tQ(X) = 1$ in $(k[X])[t]$, and $P(X)$ and $Q(X)$ is relatively prime in $k[X]$, so obviously irreducible.

Obviously $X=x$ is a root for $P(X)-tQ(X)$.

b. Write $P(X)=\sum_{i=0}^n a_iX^i$, $Q(X)=\sum_{i=0}^m b_iX^i$, and $a_i = 0$ for $i > n$, $b_i = 0$ for $i > m$. Then $P(X)-tQ(X)=\sum_{i=0}^{\max(n, m)} (a_i-tb_i)X^i$. We have $a_{\max(n, m)}-tb_{\max(n, m)} \ne 0$ since $a_n \ne 0$, $b_m \ne 0$. So $\deg P(X)-tQ(X)=\max(\deg P(X), \deg Q(X))$.

c. We have $m_{x, k(t)}=P(X)-tQ(X)$ since $P(X)-tQ(X)$ is irreducible and has $x$ as root if we make $P(X)-tQ(X)$ into monic. So $[k(x) : k(t)] = [k(x) : k(\frac{P(x)}{Q(x)})] = \deg P(X)-tQ(X) = \max (\deg P(x), \deg Q(x))$.

## P545 T2

Determine the splitting field and its degree over $Q$ for $x^4 + 2$.

---

Let $t = \sqrt[4] 2$. We have $\frac{\plusmn 1 \plusmn i}{t}$ to be 4 roots of $x^4+2$. So the splitting field is $Q(t, i)$, and degree is 8.

## P545 T6

Let $K_1$ and $K_2$ be finite extensions of $F$ contained in the field $K$, and assume both are splitting fields over $F$.

a. Prove that their composite $K_1 K_2$ is a splitting field over $F$.

b. Prove that $K_1 \cap K_2$ is a splitting field over $F$.

---

a. Let $K_1=F[a_1, \cdots, a_n]$ be splitting field for $p_1(x) \in F[x]$, $K_2=F[b_1, \cdots, b_m]$ for $p_2(x)$. Obviously $a_i$ is root of $p_1(x)$, $b_i$ is root of $p_2(x)$. And $p_1(x)p_2(x)$ splits in $K_1K_2=F[a_1, \cdots, a_n, b_1, \cdots, b_m]$, all $a_i$ and $b_i$ is root of $p_1(x)p_2(x)$. So $K_1K_2$ is a splitting field for $p_1(x)p_2(x)$.

b (helped by chatgpt). We first intro a definition and a lemma.

> Def. Field $K$ is called *normal* on $F$ if for all irreducible $p(x) \in F[x]$ that exist $a \in K$ that $p(a)=0$, $p(x)$ splits in $K$. i.e. If irreducible $p(x) \in F[x]$ has a root in $K$, then $p(x)$ splits in $K$.

> Lemma. Let $K$ be a finite extensions of $F$. $K$ is a splitting field iff $K$ normal.
>
> If: Let $K=F[a_1, a_2, \cdots, a_n]$, $m_i(x)=m_{a_i, F}(x)$. Obviously $m_i(a_i)=0$ and $m_i$ irreducible, so $m_i$ splits in $K$. Consider $m = \prod_{i=1}^n m_i$, $m$ splits in $K$, and has $a_1, \cdots, a_n$ to be roots. So $K$ is splitting field for $m$.
> 
> Only If: Let $K$ be splitting field for monic $f(x) = \prod_{i=1}^n (x-a_i)$, then $K=F(a_1, a_2, \cdots, a_n)$. For all irreducible $p(x) \in F[x]$ that $p(a) = 0$ for some $a \in K$, pick arbitary $b$ that $p(b)=0$. We have iso. $\varphi:F(a) \rarr F(b)$ that $\varphi(a)=b$, $\varphi_F=I$. Extend $\varphi$ to $K=F(a, a_1, \cdots, a_n) \rarr F(b, a_1, \cdots, a_n)$, then $f(\varphi(a_i))=\varphi(f(a_i))=0$, that is $\varphi(a_i)=a_j$, thus $\varphi(K) \cong K$, so $b \in K$.

Now we only need to prove if $K_1, K_2$ normal, then $K_1 \cap K_2$ normal. Suppose $p(x) \in F[x]$ irreducible, and $p(a) = 0$ for some $a \in K_1 \cap K_2$. Let $p(b)=0$.

By the only if part of the proof of lemma, we have iso. $\varphi_1:K_1 \rarr K_1$ that $\varphi_1(a)=b$, and $\varphi_2:K_2 \rarr K_2$ that $\varphi_2(a)=b$. So $b \in K_1$ and $b \in K_2$, thus $b \in K_1 \cap K_2$. $K_1 \cap K_2$ is normal.
