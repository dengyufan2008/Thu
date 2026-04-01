# Week6 Homework

By Deng Yufan.

Too many dull problems!

## P137 T6

Prove that characteristic subgroups are normal. Give an example of a normal subgroup that is not characteristic.

---

If $H \text{ char } G$, then consider $G$ act conjugate on $G$ itself, every $\phi(x) = gxg^{-1}$ is a auto. Then $gHg^{-1} = H$, thus $H \unlhd G$.

Consider $(Z, +)$ be a Abelian group, and $\{0\}$ is a normal subgroup. But under auto. $\phi(n) = n+1$, $\{0\}$ dont invariant.

## P137 T8

Let G be a group with subgroups $H$ and $K$ with $H \le K$.

a. Prove that if $H$ is characteristic in $K$ and $K$ is normal in G then $H$ is normal in $G$.

b. Prove that if $H$ is characteristic in $K$ and $K$ is characteristic in $G$ then $H$ is characteristic in $G$. Use this to prove that the Klein 4-group $V_4$ is characteristic in $S_4$.

c. Give an example to show that if $H$ is normal in $K$ and $K$ is characteristic in $G$ then H need not be normal in G. 

---

a. For all $g \in G$, $gKg^{-1}=K$, so $\phi(x)=gxg^{-1}$ is a auto. on $K$. Thus $\phi(H)=H$, $H \unlhd G$.

b. For all one-to-one $\phi(G)=G$, we have one-to-one $\phi(K)=K$, thus $\phi(H)=H$ is one-to-one. So $H \text{ char } G$.

Consider $V_4 = \langle a, b, c \rangle \cong \langle (1, 2)(3, 4), (1, 3)(2, 4), (1, 4)(2, 3) \rangle \le A_4$, and $V_4$ is Sylow 2-subgroup of $A_4$. Since for all perm., the length of a ring under conjugate is invariant, so $gV_4g^{-1} \subseteq V_4$ for all $g \in S_4$, thus $V_4 \unlhd A_4$, and thus $V_4 \text{ char } A_4$. Obviously $A_4 \text{ char } S_4$ (Proved below). So $V_4 \text{ char } S_4$.

We prove $A_n \text{ char } S_n$ for all $n \in \Z^+$ by showing subgroup in index 2 is unique. For all $|S_n : H| = 2$, we have $H \unlhd S_n$. Thus there exists onto $\phi : S_n \rarr Z_2$ that $\ker \phi = H$ by $S_n \rarr S_n / H \rarr Z_2$. If there is a transposition $p$ that $\phi(p) = 1$, then all transposition need to be in kernel, thus $\ker \phi = S_n \ne H$. So all transposition not in kernel, thus we can see $\phi(\sigma) = \text{sgn}(\sigma)$. So $H = A_n$.

c. We have $\{a\}$ is normal in $V_4$, and $V_4$ is char in $S_4$, but $\{a\} = \{(1, 2)(3, 4)\}$ is not normal in $S_4$.

## P146 T1

Prove that if $P \in Syl_p(G)$ and $H$ is a subgroup of $G$ containing $P$ then $P \in Syl_p (H)$.

Give an example to show that, in general, a Sylow $p$-subgroup of a subgroup of $G$ need not be a Sylow $p$-subgroup of $G$.

---

If $|G|=p^am$, $p \nmid m$, then $|P|=p^a$, $|H|=p^ak$ thus $k \mid m$, so $p \nmid k$. Since $P \le H$, thus $P \in Syl_p(H)$.

We have $V_4$ is a Sylow 2-subgroup of $A_4$, and $A_4 \le S_4$, but $V_4$ is not a Sylow 2-subgroup of $S_4$.

## P146 T4

Exhibit all Sylow 2-subgroups and Sylow 3-subgroups of $D_{12}$ and $S_3 \times S_3$.

---

$D_{12}$: Sylow 2: $\{1, r^3, s, sr^3\}$, $\{1, r^3, sr, sr^4\}$, $\{1, r^3, sr^2, sr^5\}$.

Sylow 3: $\{1, r^2, r^4\}$.

$S_3 \times S_3$: Sylow 2: $P \times Q$, where $P, Q \in \{\{1, (1, 2)\}, \{1, (1, 3)\}, \{1, (2, 3)\}\}$, total 9 cases.

Sylow 3: $P \times Q$, where $P, Q \in \{\{1, (1, 2, 3)\}, \{1, (1, 3, 2)\}\}$, total 4 cases.

## P147 T19

Prove that if $|G|=6545$ then $G$ is not simple.

---

We have $6545 = 5 \times 7 \times 11 \times 17$. So $G$ has a Sylow 11-subgroup. Consider $n_{11} \mid 5 \times 7 \times 17$, and $n_{11} \equiv 1 \pmod {11}$, can verify that the only possibility is $n_{11} = 1$. So that the Sylow 11-subgroup is normal, and $G$ is not simple.

## P151 T2

Find all normal subgroups of $S_n$ for all $n \ge 5$.

---

For all $H \unlhd S_n$, let $K = H \cap A_n$. Since $A_n \unlhd S_n$, so $K = H \cap A_n \unlhd S_n$, then $K \unlhd A_n$. Since $A_n$ is simple, $K = 1$ or $K = A_n$.

If $K = A_n$, then $A_n \le H \le S_n$. Since $|S_n : A_n| = 2$, $H = A_n$ or $H = S_n$.

If $K = 1$, then $H = 1$ or $\exist \sigma, \text{sgn}(\sigma) = -1, \sigma \in H$. If $H \ne 1$, then $\sigma^2 \in H$, and $\text{sgn}(\sigma^2) = 1$, so $\sigma^2 = 1$. Suppose $\exist \tau, \text{sgn}(\tau) = -1, \tau \in H$, then $\sigma \tau \in H$, and $\text{sgn}(\sigma \tau) = 1$, thus $\sigma \tau = 1 = \sigma^2$. So $\sigma = \tau$. Thus $H = \{1, \sigma\}$. Use classification discussion likewise in $A_n$ is simple, we can deduce that $\sigma$ will become another odd perm. under conjugate. So $H$ is not normal, thus the only case is $H=1$.

As conclusion, $H=1$, $H=A_n$, or $H=S_n$. Easy to verify all cases is normal.

## P156 T2

Let $G_1, G_2, \cdots, G_n$ be groups and let $G = G_1 \times G_2 \times \cdots \times G_n$. Let $I$ be a proper, nonempty subset of $\{1, \cdots, n\}$ and let $J = \{1, \cdots, n\} - I$. Define $G_I$ to be the set of elements of $G$ that have the identity of $G_j$ in position $j$ for all $j \in J$.

a. Prove that $G_I$ is isomorphic to the direct product of the groups $G_i, i \in I$.

b. Prove that $G_I$ is a normal subgroup of $G$ and $G/G_I \cong G_J$.

c. Prove that $G \cong G_I \times G_J$.

---

a. Consider $\phi : G_I \rarr G_{I_1} \times G_{I_2} \times \cdots \times G_{I_m}$ that $\phi(a_1, a_2, \cdots, a_n) = (a_{I_1}, a_{I_2}, \cdots, a_{I_m})$. Easy to see $\phi^{-1}(a_{I_1}, a_{I_2}, \cdots, a_{I_m}) = (a_1, a_2, \cdots, a_n)$, where $a_i = 1$ if $i \notin I$. And easy to verify that $\phi$ is iso.

b. For all $g = (g_1, \cdots, g_n) \in G$, $a = (a_1, \cdots, a_n) \in G_I$, we have $gag^{-1} = (a'_1, \cdots, a'_n)$ where $a'_i = 1$ for $i \notin I$, so $gag^{-1} \in G_I$.

Since there is $\phi_j : G \rarr G_J$ that $\phi_j(a_1, \cdots, a_n) = (a'_1, \cdots, a'_n)$ that $a'_i = a_i$ if $i \in J$, $a'_i = 1$ if $i \notin J$, and obviously $a \in \phi_j^{-1}(a)$, $\ker \phi_j = G_I$, then $G/G_I \cong G_J$.

c. Consider $\phi' : G \rarr G_I \times G_J$ that $\phi'(a) = (\phi_i(a), \phi_j(a))$. Obviously $\phi'^{-1}(a, b) = (c_1, \cdots, c_n)$ that $c_i = a_i$ if $i \in I$, $c_i = b_i$ if $i \notin I$., and easy to verify $\phi'$ is iso.

## P156 T7

Let $G_1, G_2, \cdots, G_n$ be groups and let $\pi$ be a fixed element of $S_n$. Prove that the map $\phi_\pi : G_1 \times \cdots \times G_n \rarr G_{\pi^{-1}(1)} \times \cdots \times G_{\pi^{-1}(n)}$ defined by $\phi_\pi(g_1, \cdots, g_n) = (g_{\pi^{-1}(1)}, \cdots, g_{\pi^{-1}(n)})$ is an isomorphism (so that changing the order of the factors in a direct product does not change the isomorphism type).

---

Obviously $\phi_\pi^{-1}(g_1, \cdots, g_n) = (g_{\pi(1)}, \cdots, g_{\pi(n)})$. And easy to verify $\phi_\pi(1) = 1$, $\phi_\pi(g_1) \phi_\pi(g_2) = \phi_\pi(g_1g_2)$.

## P157 T12

Let $A$ and $B$ be groups. Assume $Z(A)$ contains a subgroup $Z_1$ and $Z(B)$ contains a subgroup $Z_2$ with $Z_1 \cong Z_2$. Let this isomorphism be given by the map $x_i \rarr y_i$ for all $x_i \in Z_1$. A central product of $A$ and $B$ is a quotient $(A \times B)/Z$ where $Z = \{(x_i, y_i^{-1}) \mid x_i \in Z_1\}$ and is denoted by $A * B$ - it is not unique since it depends on $Z_1$, $Z_2$ and the isomorphism between them. (Think of $A * B$ as the direct product of $A$ and $B$ "collapsed" by identifying each element $x_i \in Z_1$ with its corresponding element $y_i \in Z_2$.)

a. Prove that the images of $A$ and $B$ in the quotient group $A * B$ are isomorphic to $A$ and $B$, respectively, and that these images intersect in a central subgroup isomorphic to $Z_1$. Find $|A*B|$.

b. Let $Z_4 = \langle x \rangle$. Let $D_8 = \langle r, s \rangle$ and $Q_8 = \langle i, j \rangle$ be given by their usual generators and relations. Let $Z_4 * D_8$ be the central product of $Z_4$ and $D_8$ which identifies $x^2$ and $r^2$ (i.e., $Z_1 = \langle x^2 \rangle$, $Z_2 = \langle r^2 \rangle$ and the isomorphism is $x^2 \rarr r^2$) and let $Z_4 * Q_8$ be the central product of $Z_4$ and $Q_8$ which identifies $x^2$ and $-1$. Prove that $Z_4 * D_8 \cong Z_4 * Q_8$.

---

a. We first prove $A \rarr A':=\{(a, 1)Z \mid a \in A\}$ is iso. We have $(a, 1)Z = (a', 1)Z$ iff $(a^{-1}a', 1) \in Z$ iff $a^{-1}a' = 1$ iff $a=a'$. So easy to see $\phi(a) = (a, 1)Z$ is a iso.

Likewise, $B \rarr B':=\{(1, b)Z \mid b \in B\}$ is iso.

We have $(a, 1)Z = (1, b)Z$ iff $(a, b^{-1}) \in Z$ iff $a \in Z_1, a \rarr b$. So $A' \cap B' = Z':=\{(a, b^{-1})Z \mid a \in Z_1, a \rarr b\}$. Easy to see $\phi(a) = (a, b^{-1})Z$ where $a \rarr b$ is a iso. from $Z_1$ to $Z'$.

For all $(g, h)Z \in A*B$, $a \in Z_1$, $a \rarr b$, we have $[(g, h)Z][(a, b^{-1})Z][(g, h)Z]^{-1} = (gag^{-1}, hb^{-1}h^{-1})Z = (a, b^{-1})Z$ since $a \in Z_1$, $b \in Z_2$. So $Z' \le Z(A*B)$.

Obviously $|A*B|=\frac{|A \times B|}{|Z|} = \frac{|A| \cdot |B|}{|Z_1|}$.

b. Let $Z_1 = \langle (x^2, r^2) \rangle$, $Z_2 = \langle (x^2, i^2) \rangle$. Consider $\phi : Z_4 * D_8 \rarr Z_4 * Q_8$ that $\phi((x^a, r^bs^c)Z_1) = (x^{a-c}, i^bj^c)Z_2$.

We first prove this is well defined. We have $(x^{a_1}, r^{b_1}s^{c_1})Z_1 = (x^{a_2}, r^{b_2}s^{c_2})Z_1$ iff $(x^{a_1-a_2}, r^{b_1-b_2}) \in Z_1$ when $c_1=c_2$; $(x^{a_1-a_2}, r^{b_1+b_2}s) \in Z_1$ when $c_1 \ne c_2$. Easy to see the second case is impossible, so $c:=c_1=c_2$ and $(x^{a_1-a_2}, r^{b_1-b_2}) \in Z_1$. Which iff $2 \mid a_1-a_2=b_1-b_2$.

And we have $(x^{a_2}, i^{b_2}j^{c})^{-1} * (x^{a_1}, i^{b_1}j^{c}) = (x^{a_1-a_2}, j^{-c}i^{-b_2}i^{b_1}j^{c}) = (x^{b_1-b_2}, j^{-c}i^{b_1-b_2}j^c) = (x^{b_1-b_2}, (-1)^{c(b_1-b_2)}i^{b_1-b_2}) = (x^{b_1-b_2}, i^{2c(b_1-b_2)}i^{b_1-b_2}) = (x^{b_1-b_2}, i^{(2c+1)(b_1-b_2)}) = (x^{b_1-b_2}, i^{b_1-b_2}) \in Z_2$. Thus $\phi$ is well defined.

If $c_1 = 0$, we have $\phi((x^{a_1}, r^{b_1})Z_1)\phi((x^{a_2}, r^{b_2}s^{c_2})Z_1) = (x^{a_1+a_2-c_2}, i^{b_1+b_2}j^{c_2})Z_2 = \phi((x^{a_1}, r^{b_1})Z_1 * (x^{a_2}, r^{b_2}s^{c_2})Z_1)$.

If $c_1 = 1$, we have $\phi((x^{a_1}, r^{b_1}s)Z_1)\phi((x^{a_2}, r^{b_2}s^{c_2})Z_1) = (x^{a_1+a_2-1-c_2}, i^{b_1}ji^{b_2}j^{c_2})Z_2 = (x^{a_1+a_2-1-c_2}, (-1)^{b_2}i^{b_1+b_2}j^{1+c_2})Z_2 = (x^{a_1+a_2-1-c_2}, i^{-2b_2}i^{b_1+b_2}j^{1+c_2})Z_2 = (x^{a_1+a_2-1-c_2}, i^{b_1-b_2}j^{1+c_2})Z_2 = \phi((x^{a_1}, r^{b_1}s)Z_1 * (x^{a_2}, r^{b_2}s^{c_2})Z_1)$.

So $\phi$ is a homo. Obviously $\phi^{-1}((x^a, i^bj^c)Z_2) = (x^{a+c}, r^bs^c)Z_1$ is well defined since we prove $\phi$ is well defined use only iff. So $\phi$ is a iso.

## P157 T14

Let $G = A_1 \times \cdots \times A_n$ and for each $i$ let $B_i$ be a normal subgroup of $A_i$. Prove that $B_1 \times \cdots B_n \unlhd G$ and that $(A_1 \times \cdots \times A_n) / (B_1 \times \cdots \times B_n) \cong (A_1/B_1) \times \cdots \times (A_n/B_n)$.

---

Consider onto $\phi_i:A_i \rarr A_i/B_i$ that $\phi_i(a) = aB_i$. Consider $\phi:G \rarr (A_1/B_1) \times \cdots \times (A_n/B_n)$ that $\phi(a_1, \cdots, a_n) = (\phi_1(a_1), \cdots, \phi_n(a_n))$. Obviously $\phi$ is onto, and $\ker \phi = \ker \phi_1 \times \cdots \times \ker \phi_n = B_1 \times \cdots \times B_n$. This complete the proof.

## Mid-term Problem

Let $G$ be a finite group, and $p$ is the smallest prime that divides $|G|$. Prove if there is a subgroup $H \unlhd G$ that $|H| = p$, then $H \le Z(G)$.

---

Proof 1.

By P96 T9, we know that there is $x \in H$ and $|x| = p$. So $H = \langle x \rangle$.

Pick a fixed $g \in G$. We have $gxg^{-1} \in \langle x \rangle$, so $gxg^{-1} = x^a$. Let $\phi_g : H \rarr H$ that $\phi_g(y) = gyg^{-1}$, if $y = x^b$, then $\phi_g(y) = \phi_g(x^b) = \phi_g(x)^b = (x^a)^b = x^{ab} = (x^b)^a = y^a$. So $\phi_g(y) = y^a$. Then $\phi_{g^{p-1}}(y) = \phi_g^{p-1}(y) = y^{a^{p-1}} = y$ by Fermat's Little Theorem.

Consider $\sigma : G \rarr G^{p-1} := \{g^{p-1} \mid g \in G\}$ that $\sigma(g) = g^{p-1}$. Obviously $\sigma$ is onto. Suppose that $g^{p-1} = h^{p-1}$, we also have $g^{|G|} = 1 = h^{|G|}$. Since $\gcd(p - 1, |G|) = 1$, we have $s(p-1) + t|G| = 1$, so $g = (g^{p-1})^s(g^{|G|})^t = (h^{p-1})^s(h^{|G|})^t = h$. So $\sigma$ is one-to-one, thus $\sigma$ is bijection. Obviously $G^{p-1} \subseteq G$, then $G^{p-1} = G$.

For all $g \in G$, we can have $h = \sigma^{-1}(g)$, then we have $\phi_g(x) = \phi_{h^{p-1}}(x) = x$, that is $gxg^{-1} = x$. So $H \le Z(G)$.

---

Proof 2.

By P96 T9, we know that there is $x \in H$ and $|x| = p$. So $H = \langle x \rangle$.

Since $H \unlhd G$, consider $G$ act on $H$ conjugately. Let $\sigma_g : H \rarr H$ that $\sigma_g(y) = g \cdot y$. Consider $\phi : G \rarr \text{Aut}(H)$ that $\phi(g) = \sigma_g$ is a homo. and $\ker \phi = \{g \in G \mid \sigma_g = I\} = \{g \in G \mid gyg^{-1} = y \space \forall y \in H\} = C_G(H)$.

So $G/C_G(H) \cong K$, where $K \le \text{Aut}(H)$. Since $|\text{Aut}(\langle x \mid x^p = 1 \rangle)| = p-1$, we have $|G/C_G(H)|$ divides $p-1$. But also $|G/C_G(H)|$ divides $|G|$, so $|G/C_G(H)|$ divides $\gcd(p-1, |G|) = 1$, thus $G/C_G(H) = 1$.

So we have $C_G(H) = G$, which is $H \le Z(G)$.
