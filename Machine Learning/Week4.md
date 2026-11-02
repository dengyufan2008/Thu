# Week4 Homework

By Deng Yufan.

## Prob 1

a. When $w=(\frac{3}{4}, -\frac{1}{2})$, the loss is 0.

b. We have $w=(\sum_{i=1}^N x_ix_i^T+\lambda NI)^{-1}\sum_{i=1}^N y_ix_i$. So $w=\frac{1}{31}(20, -3)^T$, minimal is $\frac{33}{124}$.

c. We have $w=(\sum_{i=1}^N x_ix_i^T)^{-1}(\sum_{i=1}^N y_ix_i-\frac{\lambda N}{2}e)$, where $e_i = -1+2[w_i > 0]$.

In this case, we have $w = \frac{1}{4}(3, -2)^T - \frac{1}{16}\left[\begin{matrix}1&-2\\-2&20\end{matrix}\right]e$.

Easy to see $w_1 \ge 0$, $w_2 \le 0$. If $w_1 > 0$, $w_2 < 0$, then the condition is not consist.

If $w_1=0$, then we need to minimize $\frac{1}{4}[(w_2-1)^2+9]+\frac{1}{2}w_2$, when $w_2=0$ we have the minimal $\frac{5}{2}$.

If $w_2=0$, then we need to minimize $\frac{1}{4}[(2w_1-1)^2+(4w_1-3)^2]+\frac{1}{2}w_1$, when $w_1=\frac{13}{20}$ we have the minimal $\frac{31}{80}$.

So $w=(\frac{13}{20}, 0)^T$, minimal is $\frac{31}{80}$.

## Prob 2

a. They all rely on a specific $H$, when $H$ is small the label for objects is strongly restricted.

b. Take LLM as example, the distribution of our language is not arbitary, so it is possible to learn our language.
