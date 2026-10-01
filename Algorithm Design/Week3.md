# Week3 Homework

By Deng Yufan with ChatGPT on Prob 8.

## Prob 5 (P193 T11)

Suppose you are given a connected graph $G = (V, E)$, with a cost $c_e$ on each edge $e$. In an earlier problem, we saw that when all edge costs are distinct, $G$ has a unique minimum spanning tree. However, $G$ may have many minimum spanning trees when the edge costs are not all distinct. Here we formulate the question: Can Kruskal's Algorithm be made to find all the minimum spanning trees of $G$?

Recall that Kruskal's Algorithm sorted the edges in order of increasing cost, then greedily processed edges one by one, adding an edge $e$ as long as it did not form a cycle. When some edges have the same cost, the phrase "in order of increasing cost" has to be specified a little more carefully: we'll say that an ordering of the edges is valid if the corresponding sequence of edge costs is nondecreasing. We'll say that a valid execution of Kruskal's Algorithm is one that begins with a valid ordering of the edges of $G$.

For any graph $G$, and any minimum spanning tree $T$ of $G$, is there a valid execution of Kruskal's Algorithm on $G$ that produces $T$ as output? Give a proof or a counterexample.

---

Yes. For a minimum spanning tree $T$, collect all edges as $\{(x_e, y_e, w_e)\}$. Then let $w'_e=w_e-[e \in T]\epsilon$, where $0<\epsilon < \frac{1}{2}\min_{w_i \ne w_j} |w_i-w_j|$. Sort all edges by increasing $w'$, and do Kruskal. Then this order is valid since we didn't alternate edges that has different values.

Suppose Kruskal dont give $T$ when we use this order, insteadly give $T'$, then on some edge $e_0$, the algorithm **firstly** behave differently by add a edge $e_0 \in T'$ but $e_0 \notin T$ (it cant be $e_0 \notin T'$ but $e_0 \in T$, since therefore Kruskal will add $e_0$ into the final answer).

Let $e_0=(x_0, y_0, w_0)$, and consider $x_0-y_0$ path in $T$, all edges on the path need that $w_e \le w_0$ to be minimum. And there must exist a edge $e_1$ that coming later than $e_0$, otherwise $e_0$ will not add to $T'$. So we have $w_{e_1} \le w_{e_0}$ and $w'_{e_1} \ge w'_{w_0}$, that implies $w'_{e_1}=w_{e_1}=w_{e_0}$ and $w'_{e_0}=w_{e_0}-\epsilon$. But this implies $e_0 \in T$, contradiction.

So Kruskal gives $T$ in this order.

## Prob 6 (P192 T9)

One of the basic motivations behind the Minimum Spanning Tree Problem is the goal of designing a spanning network for a set of nodes with minimum total cost. Here we explore another type of objective: designing a spanning network for which the most expensive edge is as cheap as possible.

Specifically, let $G = (V, E)$ be a connected graph with $n$ vertices, $m$ edges, and positive edge costs that you may assume are all distinct. Let $T = (V, E)$ be a spanning tree of $G$; we define the bottleneck edge of $T$ to be the edge of $T$ with the greatest cost.

A spanning tree $T$ of $G$ is a minimum-bottleneck spanning tree if there is no spanning tree $T$ of $G$ with a cheaper bottleneck edge.

a. Is every minimum-bottleneck tree of $G$ a minimum spanning tree of $G$? Prove or give a counterexample.

b. Is every minimum spanning tree of $G$ a minimum-bottleneck tree of $G$? Prove or give a counterexample.

---

a. No. Consider the graph: $(a, b, 0)$, $(a, c, 1)$, $(b, c, 1)$ and minimum-bottleneck spanning tree: $(a, c, 1)$, $(b, c, 1)$. It is not a minimum spanning tree.

b. Yes. Consider a algorithm to calculate the minimum-bottleneck as follow. We sort all edges by $w_e$ in increasing order and add every edge to graph $G'$ in order. Whenever $G'$ become connected, then we found the minimum-bottleneck, and at this time, all spanning tree of $G'$ is a minimum-bottleneck spanning tree.

Now we consider Kruskal. We surprisingly (maybe not) found that Kruskal is doing the thing we described before, so the statement is hold.

## Prob 7 (P197 T17)

Consider the following variation on the Interval Scheduling Problem. You have a processor that can operate 24 hours a day, every day. People submit requests to run daily jobs on the processor. Each such job comes with a start time and an end time; if the job is accepted to run on the processor, it must run continuously, every day, for the period between its start and end times. (Note that certain jobs can begin before midnight and end after midnight; this makes for a type of situation different from what we saw in the Interval Scheduling Problem.)

Given a list of $n$ such jobs, your goal is to accept as many jobs as possible (regardless of their length), subject to the constraint that the processor can run at most one job at any given point in time. Provide an algorithm to do this with a running time that is polynomial in $n$. You may assume for simplicity that no two jobs have the same start or end times.

---

Obviously this problem is only change the axis to a ring, compared to traditional interval scheduling. We have a algorithm with $O(n^2)$ as below. Obviously we need to choose more than or equal to 1 interval, so we first enumerate every interval $[l, r)$ as fixed chosen. Then the ring $0-24-0$ removes $[l, r)$ and become a interval $[r, l)$. Then we do traditional interval scheduling on $[r, l)$ with $O(n)$. And we take the best solution among $n$ possible versions.

We introduce another algorithm with time $O(n \log n)$, leave the proof of correcness to TA. We first sort all intervals with increasing right endpoint (here right means slightly less is in the range, but slightly greater is out of the range; since we are on a ring, the increasing order is set to 0-24-0). Note that the sorted array is considered as a ring (a.k.a. $1-n-1$). We define right distence $r_i(j)=(j-i) \bmod n$, for every interval $I_i$, we calc $nxt_i=\argmin_{I_i \cap I_j = \varnothing} r_i(j)$ represent the closest interval that dont overlap with current interval. This can be done in $O(n \log n)$ by binary search. Define $nxt^{(k)}_i=nxt^{(k-1)}_{nxt_i}$, and $nxt^{(0)}_i=i$. For every interval $I_i$, we calc $ans_i=1+\max_{I_{nxt^{(k)}_i} \cap I_i = \varnothing \forall k \in [1, j]} j$ by binary search in $O(n \log n)$, and $\max ans_i$ is the final answer.

## Prob 8 (P203 T29)

Given a list of $n$ natural numbers $d_1, d_2, \cdots, d_n$, show how to decide in polynomial time whether there exists an undirected graph $G = (V, E)$ whose node degrees are precisely the numbers $d_1, d_2, \cdots, d_n$. (That is, if $V = \{v_1, v_2, \cdots, v_n\}$, then the degree of $v_i$ should be exactly $d_i$.) $G$ should not contain multiple edges between the same pair of nodes, or "loop" edges with both endpoints equal to the same node.

---

We first sort $d_i$ by decreasing order, and relabel the vertices by the order of $d_i$. Let $m=\frac{1}{2}\sum_{i=1}^n d_i$ represent edges we need to add in total. We only need to verify: $m$ is interger and $d_i \ge 0$ and $k(k-1)+\sum_{i=k+1}^n \min(d_i, k)-\sum_{i=1}^k d_i \ge 0$ for all $k \in [1, n]$. The algorithm can be done in $O(n)$.

Since The proof is very long, the proof I have written in Chinese in [Luogu](https://www.luogu.com/paste/41eigjic), and translated to English by ChatGPT in [Luogu](https://www.luogu.com/paste/7wpe6vk2).

Thanks to Zeng Yunqin, CUHK, he inspired me about the proof and I formalized and completed it. I used ChatGPT only in checking my proof and translation.

## Prob 9

In the algorithm for finding strongly connected component, what happens if we modify the algorithm in the following way: We do not compute the transpose of $G$; instead, we perform another round of DFS, but the outer loop uses the increasing order of the finishing times of all nodes. Is this algorithm correct? Prove its correctness or provide a counter example.

---

The algorithm is not correct. Consider the graph: $V=\{a, b, c, d\}$, $E=\{(a, b), (b, c), (c, a), (a, d)\}$. Then SCC is $(a, b, c)$ and $(d)$.

If we run the algorithm as: start at $a$, then go to $b$, go to $c$, back to $b$, back to $a$, go to $d$, back to $a$, end. The finishing time order is $c, b, d, a$. So we DFS from $c$ first in the second round, and find $a, b, c, d$ reachable, so consider $(a, b, c, d)$ be a SCC. This is obviously wrong.
