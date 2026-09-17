# WeekD Homework

By Deng Yufan.

## P551 T5

For any prime $p$ and any nonzero $a \in F_p$ prove that $x^p-x+a$ is irreducible and separable over $F_p$.

---

(helped by chatgpt) Let $b$ be a root, then $b^p-b+a=0$. We have $(b+1)^p-(b+1)+a=b^p+1-b-1+a=0$, so $b+1$ is also a root. If $x \in F_p$ is a root, then $0$ is a root, contradiction.

Let $x \notin F_p$ is a root, $x \in K$, $K/F_p$, then $x+F_p$ is all $p$ roots. We have $x^p=x-a$, then $x^{p^2}=(x-a)^p=x^p-a=x-2a$, so $x^{p^n}=x-na$, thus $x^{p^p}=x$, so $x \in F_{p^p}$. If exists $1 < q < p$ that $x \in F_{p^q}$, then $x^{p^q}=x-qa$, that is $qa=0$, $q=0$, contradiction. So we can take minimal $K$ as $F_{p^p}$. Thus $[F(x) : F]=p$, so $\deg m_{x, F_p} = p$, $m_{x, F_p}(x)=x^p-x+a$. So $x^p-x+a$ is irreducible.

Since $x+F_p$ is all $p$ roots, obviously separable.

## P566 T1

a. Show that if the field $K$ is generated over $F$ by the elements $a_1, \cdots, a_n$ then an automorphism $\sigma$ of $K$ fixing $F$ is uniquely determined by $\sigma(a_1), \cdots, \sigma(a_n)$. In particular show that an automorphism fixes $K$ if and only if it fixes a set of generators for $K$.

b. Let $G \le \text{Gal}(K/F)$ be a subgroup of the Galois group of the extension $K/F$ and suppose $\sigma_1, \cdots, \sigma_k$ are generators for $G$. Show that the subfield $E/F$ is fixed by $G$ if and only if it is fixed by the generators $\sigma_1, \cdots, \sigma_k$. 

---

a. For all $x \in K$, we have $x \in F(a_1, \cdots, a_n)$, so $x$ can write into poly for $a_1, \cdots, a_n$ with coef. $F$, $\sigma(x)$ is uniquely determined.

b. If: For all $\sigma \in G$, we have $\sigma \in \langle \sigma_1, \cdots, \sigma_k \rangle$, so $\sigma(x)=x$ for all $x \in E$.

Only If: Obvious.

## P567 T4

Prove that $Q(\sqrt 2)$ and $Q(\sqrt 3)$ are not isomorphic. 

---

We have $\text{Gal}(Q(\sqrt 2)/Q) \cong Z_2$, but $\text{Gal}(Q(\sqrt 3)/Q) \cong 1$, so they are not iso.

## P567 T5

Determine the automorphisms of the extension $Q(\sqrt[4]2)/Q(\sqrt 2)$ explicitly.

---

We have $|\text{Aut}(Q(\sqrt[4]2)/Q(\sqrt 2))| \le [Q(\sqrt[4]2):Q(\sqrt 2)]=2$. The auto.s are: $I$, $\sigma(a+b\sqrt[4]2+c\sqrt 2+d\sqrt[4]8)=a-b\sqrt[4]2+c\sqrt 2-d\sqrt[4]8$.

## P567 T7

This exercise detennines $\text{Aut}(R/Q)$.

a. Prove that any $\sigma \in \text{Aut}(R/Q)$ takes squares to squares and takes positive reals to positive reals. Conclude that $a < b$ implies $\sigma a < \sigma b$ for every $a, b \in R$.

b. Prove that $-\frac{1}{m}<a-b<\frac{1}{m}$ implies $-\frac{1}{m}<\sigma a-\sigma b < \frac{1}{m}$ for every positive integer $m$. Conclude that $\sigma$ is a continuous map on $R$.

c. Prove that any continuous map on $R$ which is the identity on $Q$ is the identity map, hence $\text{Aut}(R/Q) = 1$.

---

a. We have $\sigma(x^2)=\sigma(x)^2$, and for $x>0$ we have $\sigma(x)=\sigma(\sqrt x^2)=\sigma(\sqrt x)^2>0$ since $\sigma(x)=0 \rarr x=0$. So for $a<b$, we have $\sigma(b)-\sigma(a)=\sigma(b-a)>0$, that is $\sigma(a) < \sigma(b)$.

b. For $-\frac{1}{m}<a-b<\frac{1}{m}$, we have $\sigma(a)-\sigma(b)+\frac{1}{m}=\sigma(a-b+\frac{1}{m})>0$, $\sigma(b)-\sigma(a)+\frac{1}{m}=\sigma(b-a+\frac{1}{m})>0$, so $-\frac{1}{m}<\sigma (a)-\sigma (b) < \frac{1}{m}$. So $\sigma$ is continuous by definition.

c. We have $\sigma$ is continuous, and $\sigma$ fixed $Q$. For all $x \in R$, let $a_n \in (x, x+\frac{1}{n}) \cap Q$, then $\lim_{n \rarr +\infty} \sigma(a_n)=\lim_{n \rarr  +\infty} a_n=x$, so $\sigma(x)=x$. That is $\sigma=I$, so $\text{Aut}(R/Q) = 1$.

## P581 T2

Determine the minimal polynomial over $Q$ for the element $1 + \sqrt[3]2 + \sqrt[3]4$.

We have $4+2\sqrt[3]2 + \sqrt[3]4=(\sqrt[3]2 + \sqrt[3]4)^2 \in Q(1 + \sqrt[3]2 + \sqrt[3]4)$, so $\sqrt[3]2 \in Q(1 + \sqrt[3]2 + \sqrt[3]4)$. Thus $Q(1 + \sqrt[3]2 + \sqrt[3]4)=Q(\sqrt[3]2)$, so $\deg m_{1 + \sqrt[3]2 + \sqrt[3]4, Q}=3$.

Easy to verify $1 + \sqrt[3]2 + \sqrt[3]4$ is root of $(x-1)^3-6x$, so $m_{1 + \sqrt[3]2 + \sqrt[3]4, Q}=(x-1)^3-6x=x^3-3x^2-3x-1$.

## P581 T3

Determine the Galois group of $(x^2 - 2)(x^2 - 3)(x^2 - 5)$. Determine all the subfields of the splitting field of this polynomial.

---

Obviously $(x^2 - 2)(x^2 - 3)(x^2 - 5)$ separable, so Galois field exists, and exactly equals splitting field $Q(\sqrt 2, \sqrt 3, \sqrt 5)$. $|\text{Gal}(Q(\sqrt 2, \sqrt 3, \sqrt 5)/Q)|=[Q(\sqrt 2, \sqrt 3, \sqrt 5):Q]=8$.

Let $\sigma_1(\sqrt 2)=-\sqrt 2$, $\sigma_1(\sqrt 3)=\sqrt 3$, $\sigma_1(\sqrt 5)=\sqrt 5$; $\sigma_2(\sqrt 2)=\sqrt 2$, $\sigma_2(\sqrt 3)=-\sqrt 3$, $\sigma_2(\sqrt 5)=\sqrt 5$; $\sigma_3(\sqrt 2)=\sqrt 2$, $\sigma_3(\sqrt 3)=\sqrt 3$, $\sigma_3(\sqrt 5)=-\sqrt 5$. Then all auto. can represented as $\sigma_1^{b_1} \circ \sigma_2^{b_2} \circ \sigma_3^{b_3}$, where $b_i \in \{0, 1\}$. So $\text{Gal}(Q(\sqrt 2, \sqrt 3, \sqrt 5)/Q) \cong Z_2 \times Z_2 \times Z_2$.

Subfield: $Q(c_1, c_2, c_3)$, where $c_1 \in \{0, \sqrt 2\}$, $c_2 \in \{0, \sqrt 3\}$, $c_3 \in \{0, \sqrt 5\}$, total 8.

## P582 T6

Let $K = Q(\sqrt[8]2, i)$ and let $F_1 = Q(i)$, $F_2 = Q(\sqrt 2)$, $F_3 = Q(\sqrt{-2})$. Prove that $\text{Gal}(K/F_1) \cong Z_8$, $\text{Gal}(K/F_2) \cong D_8$, $\text{Gal}(K/F_3) \cong Q_8$.

---

For $K/F_1$, we have $\sigma(\sqrt[8]2)=\omega_8\sqrt[8]2$ is auto., where $\omega_8=\frac{1}{\sqrt 2}(1+i)$. All auto. is $\sigma^n$ where $n \in [0, 8)$, so $\text{Gal}(K/F_1) \cong Z_8$.

For $K/F_2$, we have $\sigma(\sqrt[8]2)=i\sqrt[8]2$, $\sigma(i)=i$; $\tau(\sqrt[8]2)=\sqrt[8]2$, $\tau(i)=-i$ is auto. All auto. is $\sigma^n\tau^m$ where $n \in [0, 4)$, $m \in [0, 2)$, so $\text{Gal}(K/F_2) \cong D_8$.

For $K/F_3$, we have $\sigma(\sqrt[8]2)=\omega_8\sqrt[8]2$, $\sigma(i)=i$; $\tau(\sqrt[8]2)=\sqrt[8]2$, $\tau(i)=-i$. We need $\sqrt[8]2^4i$ fixed, so $\sigma^{2n+m} \circ \tau^m$ is auto., where $n \in [0, 4)$, $m \in [0, 2)$. Let $1=1$, $\sigma^4=-1$, $\sigma^2=i$, $\sigma \circ \tau=j$, $\sigma^3 \circ \tau=k$, we can see $\text{Gal}(K/F_3) \cong Q_8$.

## P582 T12

Determine the Galois group of the splitting field over $Q$ of $x^4-14x^2+9$.

---

Obviously roots are $\plusmn \sqrt 2 \plusmn \sqrt 5$, so separable. Galois field is splitting field is $Q(\sqrt 2, \sqrt 5)$, so $|\text{Gal}(Q(\sqrt 2, \sqrt 5)/Q)|=[Q(\sqrt 2, \sqrt 5):Q]=4$.

We have $\sigma(\sqrt 2)=-\sqrt 2$, $\sigma(\sqrt 5)=\sqrt 5$; $\tau(\sqrt 2)=\sqrt 2$, $\tau(\sqrt 5)=-\sqrt 5$. All $\sigma^n \circ \tau^m$ is auto., where $n, m \in \{0, 1\}$. So $\text{Gal}(Q(\sqrt 2, \sqrt 5)/Q)=V_4$.

## P583 T23

Let $K$ be a Galois extension of $F$ with cyclic Galbis group of order $n$ generated by $\sigma$. Suppose $a \in K$ has $N_{K/F}(a) = 1$. Prove that $a$ is of the form $a=\frac{\beta}{\sigma \beta}$ for some nonzero $\beta \in K$.

Note that $N_{K/F}(a)$ means $\prod_{\tau \in \text{Gal}(K/F)} \tau(a)$ is a norm for $K/F$.

---

Since $1, \sigma, \cdots, \sigma^{n-1}$ is distinct elements in $\text{Gal}(K/F)$, we have $\sigma^i:K \rarr K$ is character, so they are independent.

Let $\tau=1+a\sigma+a\sigma(a)\sigma+\cdots+a\sigma(a)\sigma^2(a)\cdots \sigma^{n-2}(a)\sigma^{n-1}$, then $\tau \ne 0$. So exists $\theta \in K$ that $\tau(\theta) \ne 0$. Let $\beta = \tau(\theta)$.

We have $\frac{\beta}{\sigma \beta}=\frac{\theta+a\sigma(\theta)+a\sigma(a)\sigma(\theta)+\cdots+a\sigma(a)\sigma^2(a)\cdots\sigma^{n-2}(a)\sigma^{n-1}(\theta)}{\sigma(\theta)+\sigma(a)\sigma^2(\theta)+\sigma(a)\sigma^2(a)\sigma^3(\theta)+\cdots+\sigma(a)\sigma^2(a)\sigma^3(a)\cdots\sigma^{n-1}(a)\theta}$.

Since $N_{K/F}(a) = 1$, we have $\sigma(a)\sigma^2(a)\sigma^3(a)\cdots\sigma^{n-1}(a)=a^{-1}$, so $\frac{\beta}{\sigma \beta}=\frac{\theta+a\sigma(\theta)+a\sigma(a)\sigma(\theta)+\cdots+a\sigma(a)\sigma^2(a)\cdots\sigma^{n-2}(a)\sigma^{n-1}(\theta)}{a^{-1}\theta+\sigma(\theta)+\sigma(a)\sigma^2(\theta)+\cdots+\sigma(a)\sigma^2(a)\cdots\sigma^{n-2}(a)\sigma^{n-1}(\theta)}=a$.
