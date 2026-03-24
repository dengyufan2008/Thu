Prob 1. 若 $f, g \in \mathscr C^2$, 证明 $\Delta(fg) = f \Delta g + g \Delta f + 2 \langle \nabla f, \nabla g \rangle$.

$$
\begin{aligned}
\Delta(fg) &= \sum_{i=1}^m (fg)_{x_ix_i}
\\
&= \sum_{i=1}^m (f_{x_i}g + fg_{x_i})_{x_i}
\\
&= \sum_{i=1}^m f_{x_ix_i}g + 2f_{x_i}g_{x_i} + fg_{x_ix_i}
\\
&= g \Delta f + 2 \sum_{i=1}^m f_{x_i}g_{x_i} + f \Delta g
\\
&= f \Delta g + g \Delta f + 2 \text{d}f(\cdot)(g_{x_1}, g_{x_2}, \cdots, g_{x_m})
\\
&= f \Delta g + g \Delta f + 2 \langle \nabla f, \nabla g \rangle.
\end{aligned}
$$
