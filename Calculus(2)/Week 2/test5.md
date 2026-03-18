Prob 1. 给定单位向量 $v \in R^m$, $H_v=I-2vv^t$ 是 $R^m$ 关于 $\text{span}(v)^\perp$ 的镜面反射, 从而 $H_v$ 是 $m$ 阶正交矩阵. 求 $F:R^m \rarr M_{m \times m}$, $F(v)=H_v$ 的微分.

有 $F(v_0+v) - F(v_0) = 2(v_0v_0^t - (v_0+v)(v_0+v)^t) = -2(vv_0^t + v_0v^t + vv^t)$. 由于 $\lVert vv^t \rVert_\infty = \lVert v \rVert_\infty^2 = o(\lVert v \rVert)$, 故微分为 $\text{d}F(v_0)(v)=-2(vv_0^t + v_0v^t)$.
