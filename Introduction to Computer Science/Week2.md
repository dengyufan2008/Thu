# Week2 Homework

By Deng Yufan.

## 1. Graph Basics

a. Connected components: (a, d, f), (b, e), (c, g).

Cycle: a-d-f-a.

The minimum number of new edges required to make the graph with $k$ connected components connected: $k-1$. $k-1$ is valid: You can link component $1$ to component $[2, k]$. $<k-1$ is impossible: If we can connect with $k'<k-1$ edges, then we delete a vertex with $\text{deg}=1$ (if this kind of vertex is not exist, then there is $2k/2=k$ edges), then we can connect $k-1$ component with $k'-1$ edges. Keep doing this, we can connect $k-k'>1$ components with 0 edge.

One possible set for $G$ is: $(a, b)$, $(a, c)$.

b. $T$ is a spanning tree for $H$. $c$ to $f$: $c-b-d-e-f$. Cycle: $c-b-d-e-f-c$. Removable edge: $(c, b)$, $(b, d)$, $(d, e)$, $(e, f)$.

## 2. Algorithm and Time complexity

a.1. $[1,3,4,6,8,9,10]$, $6$.

a.2. $T_{median}(2^{30})=20 \cdot 2^{30}$, $T_{sort}(2^{30})=60 \cdot 2^{30}$, so median is fewer by factor $1/3$. We have $T_{median}(2^{10})=T_{sort}(2^{10})$.

b. Binary Heap: $O((n+m)\log n)$. Fibonacci Heap: $O(n \log n + m)$.

c. Prim: $O(n \log n+m)$. When $m=\Theta(n)$, Prim is $O(n \log n)$ and Yao is $O(n \log \log n)$, so Yao is faster. When $m=\Theta(n \log n)$, Prim is $O(n \log n)$ and Yao is $O(n \log n \log \log n)$, so Prim is faster.

## 3. Shortest Path

a. Finalize order: S, B, A, D, C, E, F, T. Shortest: S-A-C-E-T, 1300m.

b. Finalize order: S, A, C, E, T. Total: 5 vertices.

c. Let $h'(v)=0.36h(v)$ representing the remainning time if use speed $20km/h$ and go straightly. Since you can never go faster than $20km/h$, and go curvely is worse than go straightly, the $h'$ is admissible.

Finalize order: S, A, C, B, D, F, T. Fastest: S-B-D-F-T, 612s.

## Declaration of AI Use

I used AI to translate part of words and search for Yao's algorithm.
