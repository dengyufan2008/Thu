# Week4 Homework

By Deng Yufan.

## 1. Local Functions and the Sheaf Property

a. Not compatible. Since $f_2(d)=0$ but $f_3(d)=1$, $d \in U_2 \cap U_3$, so $f_2 |_{U_2 \cap U_3} \ne f_3 |_{U_2 \cap U_3}$.

b. $f:(a, b, c, d, e) \mapsto (1, 0, 1, 0, 0)$.

c. When $U_1=\{a\}$, $U_2=\{b\}$, $\{U_1, U_2\}$ is a cover. Let $g_1 : (a) \mapsto (0)$, $g_2 : (b) \mapsto (1)$, then they cannot glue into a global constant function since $g : (a, b) \mapsto (0, 1)$.

d. Overlap graph for $\mathcal U_A$: 1-2, 2-3. So there is 1 connected component, and #compatible families of local constant func = 2 since $g_1(b)=g_2(b)$, $g_2(c)=g_3(c)$, then all local func needs to be same value.

Overlap graph for $\mathcal U_B$: no edge. So there is 3 connected component, and #compatible families of local constant func = 8 since all possible family of local constant func is compatible.

e. Existence: For every element $x$ in $X$, let $i_x$ s.t. $x \in U_{i_x}$. Since $\bigcup_{i=1}^k U_i = X$, such $i_x$ is always exist. Let $f:U \to S$ such that $f(x)=f_{i_x}(x)$.

Since for every $i \in [1, k]$ and $x \in U_i$, we have $x \in U_{i_x}$ and $f_i|_{U_i \cap U_{i_x}}=f_{i_x}|_{U_i \cap U_{i_x}}$, then $f_i(x) = f_{i_x}(x)$. So $f_i(x)=f(x)$ for every $i$ and $x \in U_i$. That is $f|_{U_i}=f_i$, $f$ is global gluing.

Uniqueness: Suppose there is $f \ne f'$ that both of them are global gluing, then we have $x \in X$ that $f(x) \ne f'(x)$. Then we have $f_{i_x} = f|_{U_{i_x}} \ne f'|_{U_{i_x}} = f_{i_x}$, contradiction.

## 2. Recovering an Object from Its Relations

a. We have $f \circ h:X \to A \to B$. And $\eta_Y(h \circ u) = f \circ (h \circ u) = (f \circ h) \circ u = \eta_X(h) \circ u$.

b. i. Let $f = \eta_A(id_A)$, since $id_A:A \to A$, so $\eta_A(id_A):A \to B$.

ii. We have $\eta_X(h) = \eta_X(id_A \circ h) = \eta_A(id_A) \circ h = f \circ h$. If there is $f' \ne f$ that $\eta_X(h) = f' \circ h$, we have $f=\eta_A(id_A)=f' \circ id_A=f'$, contradiction.

c. i. We have $\theta_X(\eta_X(h))=g \circ (f \circ h) = (g \circ f) \circ h = h$ and $\eta_X(\theta_X(k))=f \circ (g \circ k) = (f \circ g) \circ k = k$.

ii. We have $\eta_B:Hom(B, A) \to Hom(B, B)$ is surjective, so there exists $g:B \to A$ that $\eta_B(g) = id_B$. Thus $f \circ g = \eta_B(g) = id_B$.

iii. We have $\eta_A(g \circ f) = f \circ (g \circ f) = (f \circ g) \circ f = f$, and $\eta_A(id_A) = f \circ id_A = f$. Since $\eta_A$ is bijective and $\eta_A(g \circ f) = \eta_A(id_A)$, we have $g \circ f = id_A$. Since $f \circ g = id_B$ and $g \circ f = id_A$, $f$ is isomorphism.

## Declaration of AI Use

I used AI to translate part of words.
