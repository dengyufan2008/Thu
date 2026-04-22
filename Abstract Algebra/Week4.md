# Week4 Homework

By Deng Yufan.

## P101 T2

Prove all parts of the Lattice Isomorphism Theorem.

---

Consider $\phi(A)=A/N$. For all $N \le A \le G$, since $N \unlhd G$, then $N \unlhd A$, thus $A/N$ is well defined. Consider $\phi^{-1}(A) = \bigcup_{x \in A} x$. Obviously $\phi^{-1}(\phi(A)) = \bigcup_{x \in A} xN = AN = A$, $\phi(\phi^{-1}(A/N)) = A/N$, so $\phi$ is bijection. Let $\overline A = \phi(A)$.

We have $\overline A \le \overline B$ iff $xy^{-1} \in \overline A$ iff $xN(yN)^{-1} \in A/N$ iff $(xy^{-1})N \in A/N$ iff $xy^{-1} \in A$ iff $A \le B$, since $\overline A \le \overline B \to N \le A \to A \ne \varnothing$, $A \le B \to A \ne \varnothing \to \overline A \ne \varnothing$.

If $A \le B$, $|\overline B:\overline A| = \frac{|\overline B|}{|\overline A|} = \frac{|B| / |N|}{|A| / |N|} = \frac{|B|}{|A|} = |B:A|$.

$\overline{\langle A, B \rangle} = \bigcup (A^{a_1}B^{b_1}A^{a_2} \cdots A^{a_n}B^{b_n})/N = \bigcup (A/N)^{a_1}(B/N)^{b_1}\cdots (B/N)^{b_n} = \langle \overline A, \overline B \rangle$.

$\overline{A \cap B} = \{xN \mid x \in A, x \in B\} = \{xN \mid x \in A\} \cap \{xN \mid x \in B\} = \overline A \cap \overline B$.

$\overline A \unlhd \overline G$ iff $(gN)(A/N)(g^{-1}N) \subseteq A/N$ iff $\{(gag^{-1})N \mid a \in A\} \subseteq \{aN \mid a \in A\}$ iff $\{gag^{-1} \mid a \in A\} \subseteq \{a \mid a \in A\}$ iff $gAg^{-1} \subseteq A$ iff $A \unlhd G$.

## P101 T4

Let $C$ be a normal subgroup of the group $A$ and let $D$ be a normal subgroup of the group $B$. Prove that $(C \times D) \unlhd (A \times B)$ and $(A \times B)/(C \times D) \cong (A/C) \times (B/D)$.

---

For all $(a, b) \in A \times B$, we have $(a, b)(C \times D)(a^{-1}, b^{-1}) = (aCa^{-1}) \times (bDb^{-1}) = C \times D$.

Let $\phi:(A \times B)/(C \times D) \to (A/C) \times (B/D)$ that $\phi[(a, b)(C \times D)] = (aC, bD)$. $\phi^{-1}(aC, bD) = (a, b)(C \times D)$.

Easy to show $\phi$ and $\phi^{-1}$ is well defined, and $\phi \phi^{-1} = I$, $\phi^{-1} \phi = I$, and $\phi[(a_1, b_1)(C \times D)] \phi[(a_2, b_2)(C \times D)] = \phi[(a_1a_2, b_1b_2)(C \times D)]$.

## P101 T7

Let $M$ and $N$ be normal subgroups of $G$ such that $G = M N$. Prove that $G/(M \cap N) \cong (G/M) \times (G/N)$.

---

Consider $\phi:MN \to (MN / M) \times (MN / N)$ that $\phi(x) \to (xM, xN)$. Then $\ker \phi = M \cap N$.

To show $\phi$ is onto, for all $(mnM, m'n'N) = (n''m''M, m'n'N) = (n''M, m'N)$, we have $\phi(n''m') = (n''m'M, n''m'N) = (n''M, (m'n'''m'^{-1})m'N) = (n''M, m'N)$.

Thus $MN / \ker \phi \cong (MN / M) \times (MN / N)$, that is $G / (M \cap N) \cong (G / M) \times (G / N)$.

## P106 T5

Prove that subgroups and quotient groups of a solvable group are solvable.

---

If $1=G_0 \unlhd \cdots \unlhd G_s = G$, $G_{i+1}/G_i$ is Abelian.

For $H \le G$, consider $H_i = G_i \cap H$, then $H_0=1$, $H_s = H$.

To prove $H_i \unlhd H_{i+1}$, consider $x \in H_i$, $y \in H_{i+1}$. We have $yxy^{-1} \in G_i$ since $G_i \unlhd G_{i+1}$; and $yxy^{-1} \in H$ since $H$ is group. So $yxy^{-1} \in H_i$.

To prove $H_{i+1} / H_i$ is Abelian, consider $\phi : H_{i+1} \to G_{i+1} / G_i$ that $\phi(x) = xG_i$. So $\ker \phi = H_{i+1} \cap G_i = H_i$. Thus $H_{i+1} / H_i = \phi(H_{i+1}) \le G_{i+1} / G_i$ is Abelian.

For $N \unlhd G$, $\overline G = G / N$, consider $\overline{G_i} = G_iN / N$, then $\overline{G_0}=1$, $\overline{G_s}=\overline G$.

To prove $\overline{G_i} \unlhd \overline{G_{i+1}}$, consider $xn \in G_iN$, $ym \in G_{i+1}N$. We have $(ym)(xn)(m^{-1}y^{-1}) = ymxnm^{-1}y^{-1} = y(y^{-1}m'y)x(y^{-1}n'y)y^{-1} = m'yxy^{-1}n' = m'x'n' = (x'm''x'^{-1})x'n' = x'(m''n') \in G_iN$. So $G_iN \unlhd G_{i+1}N$, thus $\overline{G_i} \unlhd \overline{G_{i+1}}$ by lattice.

To prove $\overline{G_{i+1}} / \overline{G_i}$ is Abelian, we have $\overline{G_{i+1}} / \overline{G_i} = G_{i+1}N / G_iN$. For all $x = an$, $y=bm$, $a, b \in G_{i+1}$, we only need to prove $xy(yx)^{-1} \in G_iN$. That is, $(an)(bm)(n^{-1}a^{-1})(m^{-1}b^{-1}) \in G_iN$, that is $(aba^{-1}b^{-1})n' \in G_iN$ since $n, m \in N \unlhd G$. Since $G_{i+1}/G_i$ is Abelian, we have $aba^{-1}b^{-1} \in G_i$. That completes the proof.

## P106 T8

Let $G$ be a finite group. Prove that the following are equivalent:

i. $G$ is solvable.

ii. $G$ has a chain of subgroups: $1 = H_0 \unlhd H_1 \unlhd \cdots \unlhd H_s = G$ such that $H_{i+1} / H_i$ is cyclic.

iii. All composition factors of $G$ are of prime order.

iv. $G$ has a chain of subgroups: $1 = N_0 \unlhd N_1 \unlhd \cdots \unlhd N_t = G$ such that each $N_i$ is a normal subgroup of $G$ and $N_{i+1} / N_i$ is abelian.

---

ii -> i, iv -> i: Obvious.

i -> ii, i -> iii: Since $G$ is solvable, then $1 = G_0 \unlhd G_1 \unlhd \cdots \unlhd G_n = G$, $G_{i+1} / G_i$ is Abelian.

We prove every Abelian group $A$ can have a chain $1 = A_0 \unlhd \cdots \unlhd A_m = A$, where $A_{i+1} / A_i \cong Z_p$. Then we can insert groups between $G_i$ and $G_{i+1}$ so that $G'_{i+1} / G'_i \cong Z_p$, which satisfy ii and iii.

For group $A$, we pick a prime $p \mid |A|$, so we can have $x \in A$ that $|x| = p$. Let $A_1 = \langle x \rangle$, then $A_1 \unlhd A$ since $A$ Abelian. And obviously $A / A_1$ is also Abelian. So we can do the process until $A=1$.

iii -> iv: Induction $|G|$. If $G=1$, obvious. Otherwise we pick $1 \ne M \unlhd G$ that for all $N \unlhd G$, we have $N \le M \to N = 1 \lor N = M$. Since $G$ finite, we can simple pick $|M|$ smallest. We show $M$ is Abelian, then apply iv to $G/M$, we complete the proof.

Since $M$ is finite, then $M$ has a composition series. If $M=M_k$, we take $N=M_{k-1}$. Since composition factor of $M$ is compositon factor of $G$, then $|M:N| = p$.

Easy to verify $gNg^{-1} \unlhd gMg^{-1} = M$ for all $g \in G$. Then $|M:gNg^{-1}|=p$. So $M/gNg^{-1}$ is cyclic and thus Abelian. So $aba^{-1}b^{-1} \in gNg^{-1}$ for all $a, b \in M$. Thus $aba^{-1}b^{-1} \in \bigcap_{g \in G} gNg^{-1} = S$.

Obviously $S \unlhd G$, and $S \le N < M$, so $S=1$. Thus $aba^{-1}b^{-1} = 1$, $M$ is Abelian.

## P106 T11

Prove that if $H$ is a nontrivial normal subgroup of the solvable group $G$ then there is a nontrivial subgroup $A$ of $H$ with $A \unlhd G$ and $A$ abelian.

---

We proved $G$ solvable iff $G$ has a chain of subgroups: $1 = N_0 \unlhd N_1 \unlhd \cdots \unlhd N_t = G$ such that each $N_i$ is a normal subgroup of $G$ and $N_{i+1} / N_i$ is abelian in T8.

Let $H_i = H \cap G_i$, we proved $1 = H_0 \unlhd \cdots \unlhd H_t = H$, $H_{i+1}/H_i$ Abelian in T5. Take $A=H_k$ where $H_k \ne 1$ and $H_{k-1} = 1$. So $A$ Abelian, $A \le H$.

We have $A = H \cap G_k$, and $H \unlhd G$, $G_k \unlhd G$, so $A \unlhd G$.

## P106 T12

Prove that the following are equivalent:

i. Every group of odd order is solvable.

ii. The only simple groups of odd order are those of prime order.

---

i -> ii: For finite simple group $G$ that $2 \nmid |G|$, we have $G$ solvable, then the only chain is $1 \unlhd G$, so $G$ Abelian. Let $p \mid |G|$, we have $|x|=p$. Let $H = \langle x \rangle$, then $H \unlhd G$ since $G$ Abelian. Since $H \ne 1$, then $H=G$, so $|G|=p$.

ii -> i: For finite group $G$ that $2 \nmid |G|$, we can keep take biggest $|H|$ that $H \unlhd G$, and do the same process to $H$. So we can have $1=G_0 \unlhd G_1 \unlhd \cdots \unlhd G_s = G$, and $H \unlhd G_{i+1} \to |H| \le |G_i|$.

If $G_{i+1}/G_i$ is not simple, then we have $\overline H \lhd G_{i+1}/G_i$, $\overline H \ne 1$. So we have $G_i \lhd H \lhd G_{i+1}$, contradiction. So $G_{i+1}/G_i$ is simple.

Since $|G_{i+1}/G_i| \mid |G_{i+1}| \mid |G|$ is odd, then $|G_{i+1}/G_i|$ is odd. So $|G_{i+1}/G_i| = p$, thus $G_{i+1}/G_i = \langle x \rangle$ and thus is Abelian.
