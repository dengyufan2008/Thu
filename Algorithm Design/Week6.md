# Week6 Homework

By Deng Yufan without AI.

## Prob 1

Obviously the problem is NP. If we can decide whether a graph has a k-size dominating set, then we can do 3-SAT, which is NPC and easy to prove by direct definition.

Consider a graph with vertex $x_i$, $\lnot x_i$ and $l_{i, 1}$, $l_{i, 2}$, $l_{i, 3}$, we connect $x_i$ and $\lnot x_i$ as $K_2$ and $l_{i, 1}$, $l_{i, 2}$, $l_{i, 3}$ as $K_3$. If $l_{i, j}=x_k$, we connect $l_{i, j}$ and $x_k$; if $l_{i, j}=\lnot x_k$, we connect $l_{i, j}$ and $\lnot x_k$.

Note that to form a dominating set, we must choose at least one of $x_i$ and $\lnot x_i$; and at least two of $l_{i, 1}$, $l_{i, 2}$ and $l_{i, 3}$. So dominating set size is no less than $n+2m$. If there is a $n+2m$ dominating set, then easy to see the chosen $x_i$ and $\lnot x_i$ is a solution of the 3-SAT.

## Prob 2

Obviously Hamitonian path is NP.

If we can do Hamitonian path, then for a graph we enumerate all edges $(x, y)$, and calc Hamitonian path from $x$ to $y$. If we find a Hamitonian path, then we find a Hamitonian ring by adding $(x, y)$. So we can do Hamitonian ring which is NPC.

## Prob 3

If we can do NPC in $O(n^{\log n})$, then for a NP problem we can reduce to the NPC problem in $O(n^c)$ and do $O(n^{\log n})$. So NP can do in $O(n^{\log n} + n^c) = O(n^{\log n})$.

## Prob 4

a. Obviously max-clique is NP.

If we can do max-clique, then for a graph we calc its complement and ask if has $k$-size max-clique, we know if the original graph has $k$-size dominating set, but minimal dominating set is NPC, so max-clique is NPC.

b. Obviously densest $k$ subgraph is NP.

If we can do densest $k$ subgraph, then for a graph we ask whether it has $k$ vertex and $k \choose 2$ edges, then we can do max-clique, but max-clique is NPC, so densest $k$ subgraph is NPC.

## Prob 6 (where is 5?)

a. For a language $L$, if $L \in P$, we have $\bar L \in P$, since we can swap the accept node and reject node. Since $P \subseteq NP$, we have $L \in P \subseteq NP$ and $\bar L \in P \subseteq NP$, so $L \in NP \cap coNP$.

b. To show FACTOR is NP and coNP, for input $(x, r)$, we take $p_1, p_2, \cdots, p_k$, and $[p_1], \cdots, [p_k]$ as evidence, where $p_i$ is prime, $\prod p_i = x$, and $[p_i]$ is evidence of $p_i$ is prime.

We have $k \le \log_2 x = O(n)$, $|p_i| \le |x| = O(n)$, $|[p_i]|$ is P. So evidence is P.
