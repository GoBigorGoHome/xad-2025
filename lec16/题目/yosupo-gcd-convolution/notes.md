$g(x, i) := \set{y \le N : x \mid y,\ y只在前 i 个素数上跟 x 不同}$

$g(x, i) = g(x, i - 1) \sqcup \set{y \le N : x \mid y,\ y只在前 i 个素数上跟 x 不同,且y里 p_i 的次数大于 x 里 p_i 的次数}$

后者等于 $g(xp_i, i)$，于是有

$g(x, i) = g(x, i - 1) \sqcup g(xp_i, i)$

注意到当 $xp_i > N$ 时，$g(xp_i, i)$ 是空集，此时有 $g(x, i) = g(x, i - 1)$。
所以我们只需要对 $x \le N/p_i$ 计算 $g(x, i)$。并且需要按 $x$ 从大到小的顺序计算。

把 $(a_i)_{1 \le i \le N}$ 变成 $(\sum_{j: i \mid j} a_j)_{1 \le i \le N}$ 的变换叫作 Zeta 变换。



定义序列 $(F_i)_{1 \le i \le N}$ 

$F_i := (\sum_{j : i | j} a_j)(\sum_{k: i|k} b_k),$

和序列 $(f_i)_{1 \le i \le N}$

$f_i := \sum_{\gcd(j, k) = i} a_j b_k$.

已知 $(F_i)_i$，求 $(f_i)_i$。



把 $(F_i)_i$ 变成 $(f_i)_i$ 的变换叫作 Mobius 变换。 

