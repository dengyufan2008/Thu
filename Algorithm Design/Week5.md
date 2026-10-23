# Week5 Homework

By Deng Yufan without AI.

## Prob 1

Suppose that $s$ has at least one path to every node. Otherwise we can do a DFS or so to ignore nodes not reachable.

We first do Bellman-Ford $n-1$ cycles, then we have $d_1, d_2, \cdots, d_n$ represent the minimal path length from $s$ to every node by at most $n-1$ edges. Then we check for every edge $(x, y, w)$, if $d_y > d_x + w$, then we cliam $y$ is in a neg ring. After we find all nodes satisfy the condition, we run Tarjan and get all SCC and consatruct DAG on SCCs. If a SCC has a neg point we found before, then the SCC is neg; if a neg SCC can reach another SCC, then that SCC is also neg. We do DP on the DAG, then we can find all neg SCC. All nodes in neg SCC is actually nodes that the distance from $s$ cannot be defined, and distance of other nodes is actually $d_i$.

We simply explain the correctness. If $d_y > d_x + w$, then minimal path for $y$ has strictly more than $n-1$ edges, which means there is a ring on the minimal path, so the ring is neg and $y$ has no distance. For any neg ring, there must exist a node in the ring that be detected, otherwise we sum $d_y - d_x \le w$ along the ring, we have $\sum w \ge 0$ so the ring is not neg. So we can for every neg ring detect a node in the ring, then all node reachable by the detected nodes is actually all nodes that has no distance.

Obviously this algo takes $O(nm)$ time.

## Prob 2

Since the problem cannot premise that there exists a player has winning strategy (consider $n=1$ and $\forall s \in S, s > 1$), I consider the problem as the player cannot remove sticks lose the game.

Let $f_i$ represent when $n=i$ who has winning strategy. Obviously for all $0 \le i < \min_{s \in S} \{s\}$, $f_i = B$. For all $\min_{s \in S} \{s\} \le i \le n$, we do such DP:

$$
f_i = A \text{ if } \exist s \in S, f_{i-s}=B \text{ else } B.
$$

And the answer is $f_n$. This DP takes $O(n|S|)$ time. The correctness is obvious by game theory.

## Prob 3

Let $C(x) = \sum_{i=1}^n [x \in S_i]$, we first claim the answer is $t = \max_{x \in \R} C(x)$, where $\{S_i\}$ is list of intevals. First obviously the number is a lower bound of ans, and we prove the number is reallizable. We can find a $x \in \R$ that is the maximizer, and arrange all inteval containing $x$ a distince color. Then the uncolored invevals are in two cases: $R_i < x$ or $L_i > x$. We only consider the first case, the second is just a mirror flip.

Sort all intevals by $R_i$ decreasing. For every $S_i$, consider all overlapped and colored intevals, we claim such intevals is no more than $t - 1$ so we can find a unused color. Suppose there is already $t$ colored intevals, then these intevals s.t. $R_j \ge R_i$ (for intevals containing $x$, we have $R_j \ge x > R_i$; otherwise we just sorted all intevals), and thus $L_j \le R_i$ (otherwise $S_i$ and $S_j$ is not overlapped), so $C(R_i) \ge t+1$, contradiction.

Then we prove the algo mentioned in problem is fake. Consider $\{S_i\} = \{[1, 7], [2, 8], [3, 4], [5, 11], [6, 12], [9, 10]\}$, obviously $\max C(x) = 4$ and $6$ is such a position. And max independent size is 2 since there is 2 2-length inteval and 4 7-length inteval, and when we pick 2 2-length inteval we cannot pick other inteval, and 1 2-length and 2 7-length is 16-length which larger than 12. The $O(n \log n)$ algo first pick $[3, 4]$ and $[9, 10]$, then the rest of the intevals need 4 colors because they all contain $6$, so the algo will give that we need 5 colors.

## Prob 4

We first claim that in a optimal path, any two of segments will not intersect. Suppose there is a path like $w - y \cdots x - z$, where in clockwise is $w, x, y, z$, then we replace $w-y$ and $x-z$ by $w-x$ and $y-z$; and reverse the path in $\cdots$ is better. This is to prove $d_{wx}+d_{yz} \le d_{wy} + d_{xz}$. Let $u$ be the point that the two segment intersect, we need prove $d_{wx}+d_{yz} \le d_{wu}+d_{uy}+d_{xu}+d_{uz}$, and we have $d_{wx} \le d_{wu} + d_{xu}$, $d_{yz} \le d_{uy} + d_{uz}$.

Thus every prefix of the optimal path will form a range of vertex on the convex (otherwise to reach the insider vertex we need to make a intersect). So let $f_{i, j, 0/1}$ represent the minimal distance from $1$ and passing by all vertex in $[i, j]$, and end up with $i$ if the last argument is 0 otherwise $j$. Notice $[i, j]$ take the meaning on the ring. And we have $f_{1, 1, 0} = f_{1, 1, 1} = 0$, DP formula as:

$$
f_{i, j, 0} = \min(f_{i+1, j, 0} + d_{i, i+1}, f_{i+1, j, 1} + d_{i, j}),
\\
f_{i, j, 1} = \min(f_{i, j-1, 1} + d_{j-1, j}, f_{i, j-1, 0} + d_{i, j}).
$$

This algo takes $O(n^2)$ time.

## Prob 5

a. For every edge $(x, y)$ in tree $T$, we regard the edge as a bag. For every node in $T$, we connect all adjacent edges to form a chain. Obviously every node and edge are contained in some bag.

Obviously two edges are connected on the TD (tree decomposition) only when they has a same endpoint. If there is a ring $\{(x_i, y_i)\}$ that $y_i = x_{i+1}$, then there is a ring $\{x_i\}$ on $T$ that $x_i$ and $x_{i+1}$ has a edge, so we truely construct a tree. Since for every vertex $x$ on $T$, all edge that $x$ is a endpoint is connected as a chain, so the TD we construct is valid.

Since every bag is 2-size, then TW = 1.

b. Suppose we add edge $(x, y)$ on $T$. Let the path from $x$ to $y$ on $T$ be $a_0=x, a_1, \cdots, a_k=y$. We first construct $T$'s TD by a.'s method, but we need to make $(x, a_1)$ be the endpoint of the chain of $x$ and $(a_{k-1}, y)$ be the endpoint of the chain of $y$. Then we add a bag of edge $(x, y)$ and connect $(x, y)$ to $(x, a_1)$, and for all $i \in [0, k-2]$, add vertex $y$ into bag $(a_i, a_{i+1})$. The new TD is still a tree because we add a bag and add a edge from the new bag to some bag, so $m=n-1$ and still connected. And obviously all vertex and all edges is contained in new TD.

For node $z \ne x$ and $z \ne y$, we didnt modify the occurence of every bag, so $z$ still occur in a chain. For $x$, we link $(x, y)$ to $(x, a_1)$ and since $(x, a_1)$ is the endpoint of the chain, $x$ still occur in a chain. For $y$, we link $(x, y)$ to $(x, a_1)$ and add $y$ to path between $(x, a_1)$ and $(a_{k-2}, a_{k-1})$, and $(a_{k-1}, y)$ is a endpoint of the chain, so $y$ also occur in a chain.

Since the max bag is 3-size, then TW=2.

## Prob 6

We claim that TW $\le 3$. And when $n \ge 4$, we can pick $1-2-3-4$ and $2-4-1-3$ to form a $K_4$, which TW=3. Now we prove TW $\le 3$.

We first introduce a method to construct a TD. We first pick a perm. of vertex of $G$ called $p_1, \cdots, p_n$. For $G$ we repeatly delete $p_i$, and for $x, y \in N(p_i)$ where $N$ means neighbor, we connect $x$ and $y$. Then add a bag $S_i = N(p_i) \cup \{p_i\}$. After we get $n$ bags, for bag $|S_i|>1$, we find the neighbor that deleted earliest, called $p_j$ and $j>i$, then we condider $S_j$ as father of $S_i$. Since $S_n=\{p_n\}$ we will link at most $n-1$ edges, and every father of $S_i$ we have $j>i$, then there is no ring. So we form a forest and connect arbitary edges to form a tree. We claim this is a TD.

First we prove every edge in $G$ is used. For a edge $(p_i, p_j)$ and $i<j$, when we delete $p_i$, we have $p_j \in N(p_i)$ so $p_i, p_j \in S_i$. Then we prove every vertex is occured as a connected component. Since $p_i \notin S_j$ when $i<j$ because $p_i$ will be deleted after considering $p_i$, so $S_i$ is the bag containing $p_i$ with lowest depth. For every $S_j$ that $p_i \in S_j$, we have $j<i$. Since we connect all $N(p_j)$ as a complete graph, $S_{f_j}$ or say father of $S_j$ s.t. $S_j \setminus \{p_j\} \subseteq S_{f_j}$ (recall $p_{f_j}$ is a neighbor of $p_j$). So we have $p_i \in S_{f_j}$ since $p_i \ne p_j$. This deduces $p_j$ forms a connected component. Easy to see if when we delete $p_i$, we have $|N(p_i)| \le C$, then TW of $G \le C$. Since size of every bag is no more than $C+1$.

Since $G$ is union of 2 trees, we have $|E| \le 2n-2 < 2n$. Then we can find a vertex $p_1$ that $deg(p_i) \le 3$ (otherwise every vertex has deg larger than 4, #edge=4n/2=2n, contradiction). Then we will delete $p_i$ and add edge to connect all pairs of neighbor, the change of #edge = ${deg \choose 2}-deg \le 0$ when $deg \le 3$. So we still have $|E| < 2n$ after deleting $p_1$. Then we can repeatly choose $p_2, p_3, \cdots, p_n$. Use the method mentioned, we conclude that TW $\le 3$.

## Prob 7

For a ring $C \subseteq G$ and $|C|>3$, we want to prove there is a chord in $G'$. If in a TD there is a bag contains 3 or more vertex in $C$, then to link them as a clique, we can get a chord. So suppose exist a TD that every bag only contains at most 2 vertex in $C$. Then we deduce TW of a ring is no more than 1. But we know TW of $C_3$ is 2 since $C_3=K_3$ is a clique. So $G'$ is chordal.

## Prob 8

We first prove for all $x \in V \setminus (b \cap b')$, we have $x \in s \to s \notin T_1$ or $x \in s \to s \notin T_2$. Suppose $x \in s \in T_1$ and $x \in s' \in T_2$, then we have $x \in b$ and $x \in b'$ since $b$ and $b'$ is on path between $s$ and $s'$.

Suppose there is a path between $v$ and $u$ not using vertex in $b \cap b'$, called $a_0=v, a_1, \cdots, a_k=u$. Let edge $(a_0, a_1)$ in bag $s$, then $s \in T_1$, so $a_1 \in s' \to s' \in T_1$. Repeatly use the lemma before, we finally deduce $a_k \in s' \to s' \in T_1$, that is $u \in T_1$, contradiction.

## Prob 9

We first do binary search on #colors. So we need to check if it is possible to use atmost $c$ colors. We do DP on TD. Let $f_{i, mask}$ represent if we can color the subtree of $b_i$ with color of vertex in $b_i$ is actually as $mask$.

To merge two subtrees, represented as $f_{i, mask}$ and $f_{j, \cdot}$, where $i$ is father of $j$, we only need to check if we have $f_{j, mask'}$ is succussful and that for vertex in $b_i \cap b_j$, $mask$ and $mask'$ gives same color. This can be done in $O(1)$ time if we pre-calc information for $f_{j, \cdot}$. Since there is no edge out of considering by thm of Prob 8, the algo is correct.

The mask is $O(c^w) \in O(n^w)$, so this algo takes $O(n^{w+1} \log n)$ time, when $w=O(1)$ this algo is poly time.

## Prob 10

Suppose there is a ring $|C|>3$ and it has no chord. Let $C=(T_1, T_2, \cdots, T_k)$, then let $a_i \in T_{i-1} \cap T_i$, there exists path $a_i-a_{i+1}$ in $T_i$ (notice we take $i-1$ and $i+1$ as modulo $k$). If $a_i-a_{i+1} \cap a_j-a_{j+1} \ne \varnothing$ for $i \ne j$, then we have $|i-j|=1$, otherwise $T_i$ is connected with $T_j$ and is a chord. Suppose $j=i-1$, consider $S = a_{i-1}-a_i \cap a_i-a_{i+1}$. We have $a_i \in S$. If $S$ is not a sub chain of $a_{i-1}-a_i$, then we pick $x$ and $y$ that there is no vertex in $S$ between them, so $x-y-x$ forms a ring by use a path in $a_{i-1}-a_i$ and a path in $a_i-a_{i+1}$. Likewise, we have $S$ is a sub chain of both path. So we let $a_i \leftarrow a_i'$ where $a_i'$ is another endpoint of $S$, then $a_{i-1}-a_i \cap a_i'-a_{i+1}=\varnothing$. So $a_1'-a_2'-\cdots-a_k'-a_1'$ forms a simple ring, contradiction to $T$ is a tree.
