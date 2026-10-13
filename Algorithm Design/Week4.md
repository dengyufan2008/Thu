# Week4 Homework

By Deng Yufan without AI.

## Prob 5 (P200 T23)

Recall the problem of computing a minimum-cost arborescence in a
directed graph $G = (V, E)$, with a cost $c_e \ge 0$ on each edge. Here we will consider the case in which $G$ is a directed acyclic graph-that is, it contains no directed cycles.

As in general directed graphs, there can be many distinct minimumcost solutions. Suppose we are given a directed acyclic graph $G = (V, E)$, and an arborescence $A \subseteq E$ with the guarantee that for every $e \in A$, $e$ belongs to some minimum-cost arborescence in $G$. Can we conclude that $A$ itself must be a minimum-cost arborescence in $G$? Give a proof or a counterexample with explanation.

---

Since $G$ is a DAG, there exists ST iff $G$ is connected when regard every edge as undirected, and $\#\{in_i=0\}=1$ (if there are $in_x=in_y=0$, then $x$ and $y$ cannot reach each other; if only $x$ s.t. $in_x=0$, then repeatly do $i \larr pre_i$ will end on $x$, where $pre_i$ is a inter edge from any vertex to $i$, since there is no cycle, so every vertex can be reached by $x$). In this case, only the unique $x$ that $in_x=0$ can be root.

We let $c_e \larr c_e - \min_{(j, i, c) \in E} \{c\}$ where $i$ is the outer vertex of $e$, this preserves minimum ST. After changing the weight, we have $A$ is a minimum ST, iff $c_A=0$ iff $e \in A \rarr c_e=0$. This part is proven in how to compute minimum ST.

So for $A \subseteq E$ and every $e \in A$, $e$ belongs to some minimum ST, then $c_e=0$, and thus $c_A=0$, $A$ is minimum ST.

## Prob 6 (P205 T32)

Consider a directed graph $G = (V, E)$ with a root $r \in V$ and nonnegative costs on the edges. In this problem we consider variants of the minimum-cost arborescence algorithm.

a. The algorithm discussed in Section 4.9 works as follows. We modify the costs, consider the subgraph of zero-cost edges, look for a directed cycle in this subgraph, and contract it (if one exists). Argue briefly that instead of looking for cycles, we can instead identify and contract strong components of this subgraph.

b. In the course of the algorithm, we defined $y_v$ to be the minimum cost of an edge entering $v$, and we modified the costs of all edges $e$ entering node $v$ to be $c'_e = c_e − y_v$. Suppose we instead use the following modified cost: $c''_e = \max(0, c_e − 2y_v)$. This new change is likely to turn more edges to 0 cost. Suppose now we find an arborescence $T$ of 0 cost. Prove that this $T$ has cost at most twice the cost of the minimum-cost arborescence in the original graph.

c. Assume you do not find an arborescence of 0 cost. Contract all 0-cost strong components and recursively apply the same procedure on the resulting graph until an arborescence is found. Prove that this $T$ has cost at most twice the cost of the minimum-cost arborescence in the original graph.

---

a. After contract SCC, we get a minimal ST, then for all SCC, we find any 0 weighted ST, and restore edges in and out the SCC to specific vertex. Obviously this preserves the total cost of ST between before and after restoring all SCC. So this modified algo. can calc minimum ST.

b. Since the answer for original graph is $ans=\sum_{v \ne r} y_v$, and for $c''_e = 0$, we have $c_e \le 2y_v$, so $\sum_{e \in T} c_e \le \sum_{v \ne r} 2y_v = 2ans$.

c. We assume the recursive procedure can find a $\le 2$x answer, and we now restore all SCC. So the total cost is $\sum_{e \in C \cup R} c_e \le \sum_{v \ne r} 2y_v + 2rec \le 2ans$, where $C$ is edges used to restore SCC, $R$ is the set of edges calced in recursive procedure; $rec$ is actural answer in recursive procedure, $ans$ is actural answer overall. The second inequality is because we contruct more or equal to vertex contructed in precise version, and we minus a larger amount for each edge than precise version.

## Prob 7

In this problem, we introduce a very useful and important concept in combinatorics, matroid. Matroids have very close connections with greedy algorithms and submodular functions (another important concept we will explorein later homeworks). The theory of matroids is a deep branch of combinatorics.

A finite matroid $M$ is a pair $(E, \mathcal I)$, where $E$ is a finite set (called the "groundset") and $\mathcal I$ is a collection of subsets of $E$. Each element in $\mathcal I$ (which is a subset of $E$) is called an independent set (this notion has nothing to do with the notion of independent set in graph theory). Moreover, $(E, \mathcal I)$ has to satisfy the following properties: 1. $\varnothing \in \mathcal I$. 2. Every subset of an independent set is independent, i.e., if $A \subset B$, $B \in \mathcal I$, then $A \in \mathcal I$. 3. If $A$ and $B$ are two independent sets of $\mathcal I$ and $A$ has more elements than $B$,then there exists an element $e \in A-B$ such that $B \cup \{e\}$ is an independent set.

Try to answer the following questions.

a. Suppose $E$ is a set of real vector of the same length and $\mathcal I=\{S \subseteq E \mid \text{All vectors in } S \text{ are linearly independent}\}$. Prove that $(E, \mathcal I)$ is a matroid.

b. Suppose $E$ is the set of edges of a given graph $G$ and $I=\{S \subseteq E \mid \text{All edges in } S \text{ constitute a forest of }G\}$. (A forest is just a collection of trees. Note that a singleton node is also a tree) Prove that $(E, \mathcal I)$ is a matroid.

c. Suppose each element $e \in E$ is associated with a weight $c_e \ge 0$. Design a polynomial time algorithm to find a max-weight independent set. Inother words, the algorithm should output an independent set $A \in \mathcal I$ such that $\sum_{e \in A} c_e$ is maximized. You need to prove the correctness of your algorithm.

---

a. A empty set obviously is independent. A subset of a independent set is obviously independent. If $A$ and $B$ is independent, $|A|>|B|$, then we have $x \in A$ and $x \notin \text{span}(B)$, then $B \cup \{x\}$ is independent.

b. A empty set is a forest. A subset of a forest is a forest. If $A$ and $B$ is forest, $|A|>|B|$, then Let $S_A = \{A_1, A_2, \cdots, A_p\}$ be connected components in $A$, $S_B = \{B_1, B_2, \cdots, B_q\}$ be connected components in $B$. Since $n-p = |A| > |B| = n-q$, we have $p < q$. Let $f_A(x)$ be the identifier of connected component of $x$ in forest $A$. If for all $f_B(x) \ne f_B(y)$ we have $f_A(x) \ne f_A(y)$, then we have $p = \#\{f_A(x)\} \ge \#\{f_B(x)\}=q$. So we can pick $x$ and $y$ that $f_A(x)=f_A(y)$ and $f_B(x) \ne f_B(y)$.

Since $f_A(x)=f_A(y)$, there exists a path connecting $x$ and $y$. Let the path be $a_0=x, a_1, a_2, \cdots, a_k=y$. We find any $i \in [0, k)$ that $f_B(a_i) \ne f_B(a_{i+1})$. Since $f_B(x) \ne f_B(y)$, such $i$ is always exist. Let $e = (a_i, a_{i+1})$, we have $e \in A$ but $e \notin B$. Since $f_B(a_i) \ne f_B(a_{i+1})$, $B \cup \{e\}$ is still a forest.

c. A possible algorithm: First sort all $e$ by $c_e$ decreasing. Keep a set $S$ initially empty. Consider every $e$ in order, if $S \cup \{e\} \in \mathcal I$, then $S \larr S \cup \{e\}$. After considering all $e$, $S$ is the answer. If we consider decide whether $S \in \mathcal I$ is a $O(m)$ oracle, the time complicity is $O(n \log n + nm)$.

Now we show the correctness. Suppose every $c_e$ is distinct, otherwise we can add a multiple of $\epsilon$ to every same value. Let $e_1, \cdots, e_n$ be the sorted list, $S$ be the answer found by the algorithm and $T$ be the optimal answer. Consider the most front difference, called $e_i$. If $e_i \notin S$, $e_i \in T$, then $e_i$ will add to $S$ by the algorithm process. So $e_i \in S$, $e_i \notin T$. Since $c_T > c_S$, there must be at least 2 elements in $T$ that identifier is larger than $i$.

Let $O = S \cap \{e_1, e_2, \cdots, e_{i-1}\}$. Since $S \in \mathcal I$, we have $R = S \cap (O \cup \{e_i\}) \in \mathcal I$, and $|R| = |O| + 1 < |O| + 2 \le |T|$. So until $|R| = |T|$, we can keep to find $e \in T - R$ and $R \cup \{e\} \in \mathcal I$, then let $R \larr R \cup \{e\}$. So at the ending of the process, we have $R = T - \{e_j\} \cup \{e_i\}$, and $j>i$. So $c_R > c_T$, and $T$ is not the optimal answer.
