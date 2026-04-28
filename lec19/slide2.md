---
marp: true
math: mathjax
paginate: true
theme: lecture
title: "树论（一）：子树求和"
---

<div class=hidden>

$\DeclareMathOperator{\lca}{lca}$
$\DeclareMathOperator{\parent}{parent}$
</div>

---

# 例题 Milk Visits

[洛谷P5838](https://www.luogu.com.cn/problem/P5838)

给你一个有 $N$ 个点的树。每个点有一个颜色，点 $i$ 的颜色是 $T_i$。

回答 $M$ 个询问。第 $j$ 个询问是
- 从点 $A_j$ 到点 $B_j$ 的路径上有没有颜色是 $C_j$ 的点？

输出一个长为 $M$ 的 01 串作为答案。

- $1 \le N, M \le 10^5$
- $1 \le T_i, C_j \le N$

---

我们来尝试把树上差分用在这题上。

---
