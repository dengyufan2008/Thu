# Week5 Homework

By Deng Yufan.

If I write $G/H$ without $H \unlhd G$, it means $\{gH \mid g \in G\}$ which is not a group.

## P116 T1

Let $G$ act on the set $A$. Prove that if $a, b \in A$ and $b = g \cdot a$ for some $g \in G$, then $G_b = gG_ag^{-1}$. Deduce that if $G$ acts transitively on $A$ then the kernel of the action is $\bigcap_{g \in G} gG_ag^{-1}$.

---

We first prove $gG_ag^{-1} \subseteq G_b$. For all $x \in G_a$, we have $(gxg^{-1}) \cdot b = (gx) \cdot a = g \cdot a = b$, so $gxg^{-1} \in G_b$.

Apply $(a, b) = (b, a)$ to the proved part, we have $g^{-1}G_bg \subseteq G_a$, thus $G_b \subseteq gG_ag^{-1}$. So $G_b = gG_ag^{-1}$.

Obviously kernel is $\bigcap_{g \in G} gG_ag^{-1}$ by the proven part.

## P117 T7

Let $G$ be a transitive permutation group on the finite set $A$. A block is a nonempty subset $B$ of $A$ such that for all $\sigma \in G$ either $\sigma(B) = B$ or $\sigma(B) \cap B = \varnothing$ (here $\sigma(B)$ is the set $\{\sigma(b) \mid b \in B\}$).

a. Prove that if $B$ is a block containing the element $a$ of $A$, then the set $G_B$ defined by $G_B = \{\sigma \in G \mid \sigma(B) = B\}$ is a subgroup of $G$ containing $G_a$.

b. Show that if $B$ is a block and $\sigma_1(B), \sigma_2(B), \cdots, \sigma_n(B)$ are all the distinct images of $B$ under the elements of $G$, then these form a partition of $A$.

c. A (transitive) group $G$ on a set $A$ is said to be primitive if the only blocks in $A$ are the trivial ones: the sets of size 1 and $A$ itself. Show that $S_4$ is primitive on $A = \{1, 2, 3, 4\}$. Show that $D_8$ is not primitive as a permutation group on the four vertices of a square.

d. Prove that the transitive group $G$ is primitive on $A$ if and only if for each $a \in A$, the only subgroups of $G$ containing $G_a$ are $G_a$ and $G$ (i.e., $G_a$ is a maximal subgroup of $G$).

---

a. For all $\sigma \in G_a$, we have $B \ni a = \sigma(a) \in \sigma(B)$, so $\sigma(B) \cap B \ne \varnothing$, thus $\sigma(B) = B$, $\sigma \in G_B$. So $1 \in G_a \subseteq G_B$, $G_B \ne \varnothing$.

For all $x, y \in G_B$, we have $xy^{-1}(B) = B$, so $xy^{-1} \in G_B$.

b. If $a \in \sigma_i(B) \cap \sigma_j(B)$, then $\exist b \in B$, $\sigma_i(b) = a$, thus $(\sigma_j^{-1} \circ \sigma_i)(b) \in B$, so $(\sigma_j^{-1} \circ \sigma_i)(B) = B$, that is $\sigma_i(B) = \sigma_j(B)$. So $\sigma_i(B)$ dont overlap.

Since $(G, A)$ is transitive, so $\bigcup_{i=1}^n \sigma_i(B) = A$, thus forms a partition.

c. $S_4$ is primitive: For all $1 < |B| < |A|$, relabel that $B = \{1, 2, \cdots, m\}$. Consider $\sigma = (1, 2, \cdots, m+1)$.

$D_8$ is not primitive: Consider the 2 diagonal vertices in a square, easy to check.

d. If: For all $1 < |B| < |A|$, if $B$ is a block, then $\bigcup_{x \in B} G_x \subseteq G_B$. Since $\exist x \notin B, y \in B, \sigma \in G$, $x = \sigma(y)$, so $\sigma \notin G_B$, thus $G_B \subset G$. If $G_x$ are not the same, then $G_B$ must be $G$; so all $G_x$ be the same, and $G_x = G_B$ for all $x \in B$.

But $\exist x, y \in B, x \ne y, \sigma \in G$, $x = \sigma(y)$, then $x \in \sigma(B) \cap B$ thus $\sigma(B) = B$. So $\sigma \in G_B = G_y$, but $\sigma(y) = x \ne y$, contradiction.

Only If: If $G_a < H < G$, let $B=\{\sigma(a) \mid \sigma \in H\}$, we prove $B$ is a block.

For all $\sigma \in G$, if $\sigma(B) \cap B \ne \varnothing$, then $\exist \sigma_1, \sigma_2 \in H$, $\sigma_1(a)=(\sigma \circ \sigma_2)(a)$, thus $(\sigma_1^{-1} \circ \sigma \circ \sigma_2)(a) = a$, $\sigma_1^{-1} \circ \sigma \circ \sigma_2 \in G_a < H$, then $\sigma \in \sigma_1 H \sigma_2^{-1} \subseteq H$. So for all $\sigma' \in H$, $(\sigma \circ \sigma')(a) \in B$, thus $\sigma(B) = B$, so $B$ is a block.

Since $G_a < H$, $|B| > 1$. Suppose $B = A$, then $G \cdot a = A = B = H \cdot a$, so $G/G_a = H/G_a$. For all $gG_a$, we have $x \in H$ that $gG_a = xG_a$, thus $g \in xG_a \subseteq H$, thus $G = H$, contradiction. So $B$ is a nontrivial block, contradiction.

## P121 T4

Use the left regular representation of $Q_8$ to produce two elements of $S_8$ which generate a subgroup of $S_8$ isomorphic to the quaternion group $Q_8$.

---

We have $Q_8 = \langle i, j \rangle$. Consider group action $(Q_8, Q_8)$, we have $\sigma_i = (1, i, -1, -i) (j, k, -j, -k)$; $\sigma_j = (1, j, -1, -j) (k, i, -k, -i)$. So $\langle (1, 3, 2, 4) (5, 7, 6, 8), (1, 5, 2, 6) (7, 3, 8, 4) \rangle \cong Q_8$.

## P122 T8

Prove that if $H$ has finite index $n$ then there is a normal subgroup $K$ of $G$ with $K \le H$ and $|G : K| \le n!$.

---

Let $K = \bigcap_{x \in G} xHx^{-1}$. Obviously $K \le H$ and $K \unlhd G$. We prove group action $(G/K, G/H)$ is faithful, which iff kernel is trivial, while $g_1K \cdot g_2H = (g_1g_2)H$. Thus $G/K \rarr S_{G/H}$ is one-to-one, so $|G : K| \le n!$.

We first prove the action is well-defined. For $g_1K = g_1'K$, $g_2H = g_2'H$, we have $g_1^{-1}g_1' \in K$, $g_2^{-1}g_2' \in H$, so $(g_1g_2)^{-1}(g_1'g_2') = g_2^{-1}(g_1^{-1}g_1')g_2' = g_2^{-1}kg_2' = g_2^{-1}(g_2k'g_2^{-1})g_2' = k'(g_2^{-1}g_2') = k'h \in H$.

Then we prove kernel is trivial. If $(gx)H = xH$ for all $x \in G$, thus $x^{-1}gx \in H$, $g \in xHx^{-1}$ for all $x$. Thus $g \in \bigcap_{x \in G} xHx^{-1} = K$, so $gK = 1K$ is the identity of $G/K$.

## P122 T11

Let $G$ be a finite group and let $\pi : G \rarr S_G$ be the left regular representation. Prove that if $x$ is an element of $G$ of order $n$ and $|G|=mn$, then $\pi(x)$ is a product of $m$ $n$-cycles.

Deduce that $\pi(x)$ is an odd permutation if and only if $|x|$ is even and $\frac{|G|}{|x|}$ is odd. 

---

Since $\pi(x)$ is a perm. Then it forms some rings. Consider a ring $(x_0, x_1, \cdots, x_{k-1})$. We have $x^kx_0 = \sigma^k(x_0) = x_0$, so $x^k = 1$ and $x^{k'} \ne 1$ for $1 \le k' < k$. Since $|x| = n$, then $n = k$. So all rings are in size of $n$, thus there is $m$ $n$-ring.

## P122 T14

Let $G$ be a finite group of composite order $n$ with the property that $G$ has a subgroup of order $k$ for each positive integer $k$ dividing $n$. Prove that $G$ is not simple.

---

Let $p$ be the smallest prime divide $n$. We have $H \le G$ that $|G : H| = p$ must satisfy $H \unlhd G$. This complete the proof.

Let $A = G/H$, then $|A|=p$. Consider $\pi : G \rarr S_A$ that $\pi(g) = \sigma_g$ action on $A$. Obviously $\pi$ is a iso. and $\ker \pi = \bigcap_{x \in G} xAx^{-1}$, thus $G/\ker \pi \cong \pi(G) \le S_A$.

Let $|H:\ker \pi| = k$, then $pk = |G : \ker \pi| \mid |S_A| = p!$. So $k \mid (p-1)!$. Since $k \mid |H| \mid |G|$, so $k \mid \gcd((p-1)!, |G|) = 1$, thus $k=1$, $H = \ker \pi$. So $H = \ker \pi \unlhd G$.

## P130 T2

Find all conjugacy classes and their sizes in the following groups: (a) $D_8$ (b) $Q_8$ (c) $A_4$.

---

a. Orbit for $1$: $\{1\}$, 1-size.

Orbit for $r$: $\{r, r^3\}$, 2-size.

Orbit for $r^2$: $\{r^2\}$, 1-size.

Orbit for $s$: $\{s, r^2s\}$, 2-size.

Orbit for $rs$: $\{rs, r^3s\}$, 2-size.

b. Orbit for $1$: $\{1\}$, 1-size.

Orbit for $-1$: $\{-1\}$, 1-size.

Orbit for $i$: $\{i, -i\}$, 2-size.

Orbit for $j$: $\{j, -j\}$, 2-size.

Orbit for $k$: $\{k, -k\}$, 2-size.

c. Orbit for $1$: $\{1\}$, 1-size.

Orbit for $(1, 2)(3, 4)$: $\{(1, 2)(3, 4), (1, 3)(2, 4), (1, 4)(2, 3)\}$, 3-size.

Orbit for $(1, 2, 3)$: $\{(1, 2, 3), (1, 3, 2), (1, 4, 3), (1, 3, 4)\}$, 4-size.

Orbit for $(1, 2, 4)$: $\{(1, 2, 4), (1, 4, 2), (2, 3, 4), (2, 4, 3)\}$, 4-size.

## P132 T32

For $n = 2k + 1$ an odd integer show that the conjugacy classes in $D_{2n}$ are $\{1\}, \{r^{\plusmn 1}\}, \cdots, \{r^{\plusmn k}\}, \{sr^b \mid b = 0, 1, \cdots, n-1\}$. Give the class equation for $D_{2n}$.

---

Obviously orbit of $1$ is $\{1\}$.

To calc orbit for $r^i$ where $1 \le i \le k$, we have $(r^j)(r^i)(r^j)^{-1} = r^i$, $(sr^j)(r^i)(sr^j)^{-1} = r^{-i}$. So orbit is $\{r^{\plusmn i}\}$.

To calc orbit for $s$, we have $(r^j)s(r^j)^{-1} = sr^{-2j}$, $(sr^j)s(sr^j)^{-1} = sr^{2j}$. Since $-2j$ consist all odd number, $2j$ consist all even number, orbit is $\{sr^b\}$.

We have $|D_{2n}| = |\{1\}| + \sum_{i=1}^k |D_{2n} : C_{D_{2n}}(r^i)| + |D_{2n} : C_{D_{2n}}(s)|$.

## P132 T36

Let $\pi : G \rarr S_G$ be the left regular representation afforded by the action of $G$ on itself by left multiplication. For each $g \in G$ denote the permutation $\pi(g)$ by $\sigma_g$, so that $\sigma_g(x) = gx$ for all $x \in G$. Let $\lambda : G \rarr S_G$ be the permutation representation afforded by the corresponding right action of $G$ on itself, and for each $h \in G$ denote the permutation $\lambda(h)$ by $\tau_h$. Thus $\tau_h(x) = xh^{-1}$ for all $x \in G$ ($\lambda$ is called the right regular representation of $G$).

a. Prove that $\sigma_g$ and $\tau_h$ commute for all $g, h \in G$. (Thus the centralizer in $S_G$ of $\pi(G)$ contains the subgroup $\lambda(G)$, which is isomorphic to $G$).

b. Prove that $\sigma_g = \tau_g$ if and only if $g$ is an element of order 1 or 2 in the center of $G$.

c. Prove that $\sigma_g = \tau_h$ if and only if $g$ and $h$ lie in the center of $G$ and $g=h^{-1}$. Deduce that $\pi(G) \cap \lambda(G) = \pi(Z(G)) = \lambda(Z(G))$.

---

a. We have $(\sigma_g \circ \tau_h)(x) = \sigma_g(xh^{-1}) = gxh^{-1} = \tau_h(gx) = (\tau_h \circ \sigma_g)(x)$.

b. If: When $|g| = 1$ or $|g| = 2$, we have $g^2 = 1$. We have $\sigma_g(x) = gx = (xgx^{-1})x = xg = xg^{-1} = \tau_g(x)$.

Only If: We have $gx = xg^{-1}$ for all $x$. So $g1 = 1g^{-1}$, that is $g^2 = 1$. So $|g| = 1$ or $|g| = 2$. So $gx = xg$ for all $x$, that is $g$ in $Z(G)$.

c. If: We have $\sigma_g(x) = gx = (xgx^{-1})x = xg = xh^{-1} = \tau_h(x)$.

Only If: We have $gx = xh^{-1}$ for all $x$. So $g=h^{-1}$, and $gx=xg$, $h^{-1}x=xh^{-1}$ for all $x$. That is $g, h \in Z(G)$.
