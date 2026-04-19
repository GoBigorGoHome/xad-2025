---
marp: true
math: mathjax
paginate: true
theme: lecture
title: 矩阵及其运算
---

# 矩阵及其运算

$\newcommand{\bs}[1]{\boldsymbol{#1}}$


---

# 矩阵

所谓矩阵，就是一个矩形数表，就是我们熟知的二维数组。
<div class=definition>

设 $m, n$ 是正整数。一个 $m \times n$ **矩阵**是指如下的资料
$$
\begin{aligned}
\bs{A} &= (a_{ij})_{\substack{1 \le i \le m \\1 \le j \le n}} \\
&= \pmatrix{
a_{11} & a_{12} & \dots & a_{1n} \\
a_{21} & a_{22} & \dots & a_{2n} \\
\vdots &        &       & \vdots \\
a_{m1} & a_{m2} & \dots & a_{mn}
} = \pmatrix{
      & \vdots & \\
\dots &  a_{i,j} & \dots \\
    & \vdots & 
}
\end{aligned}
$$
其中 $a_{ij}$ 是一个数，称为矩阵 $\bs{A}$ 的第 $(i,j)$ 个矩阵元或 $(i,j)$-项，而 $n\times n$ 的矩阵也称为 $n$ 阶**方阵**。
</div>


---



我们经常将矩阵 $\bs{A} = (a_{ij})_{\substack{1 \le i \le m \\ 1 \le j \le n}}$ 简记为 $(a_{ij})_{i,j}$。

- 括号内的式子表示矩阵元
- 括号外的 $i, j$ 分别表示括号内的矩阵元所在的行和列的编号

---

# 矩阵加法

对于任意两个 $m \times n$ 矩阵 $A=(a_{ij})_{i,j}$ 和 $B=(b_{ij})_{i,j}$，定义
$$
A + B := (a_{ij} + b_{ij})_{\substack{1\le i \le m \\ 1 \le j \le n}}.
$$


---

# 矩阵的数乘

对于任意数 $t$ 和 $m\times n$ 矩阵 $\bs{A} = (a_{ij})_{i,j}$，定义
$$
t \cdot \bs{A} = t\bs{A} := (ta_{ij})_{\substack{1 \le i \le m \\ 1 \le j \le n}}.
$$

---

一个 $1\times n$ 矩阵
$$\pmatrix{a_1 & a_2 & \dots & a_n}$$
称为 $n$ 维**行向量**。有时也写成 $(a_1, a_2, \dots, a_n)$。

一个 $n \times 1$ 矩阵
$$\pmatrix{a_1 \\ a_2 \\ \vdots \\ a_n}$$
称为 $n$ 维**列向量**。

---



# 矩阵乘法

<div class=definition>

若 $\bs{A} = (a_{ij})_{\substack{1 \le i \le m \\ 1 \le j \le n}}$，$\bs{B} = (b_{jk})_{\substack{1 \le j \le n \\ 1 \le k \le r}}$，则 $\bs{AB} = (c_{ik})_{\substack{1 \le i \le m \\ 1 \le j \le r}}$，其中
$$
c_{ik} := \sum_{j = 1}^{n} a_{ij} b_{jk} = \underset{\scriptsize\text{第 $i$ 行}}{\pmatrix{a_{i1} & \dots & a_{in}}}
\underset{\scriptsize\text{第 $k$ 列}}{\pmatrix{b_{1k} \\ \vdots \\ b_{nk}}}.
$$


</div>


- 注意：只有行数和列数合乎规格的矩阵才能相乘，$\bs{AB}$ 暗含着 $\bs{A}$ 的列数等于 $\bs{B}$ 的行数。
- $\bs{AB}$ 有时也写成 $\bs{A} \cdot \bs{B}$。

---

定义 $n$ 阶**单位矩阵**为如下的 $n$ 阶方阵
$$
\bs{I}_n := \pmatrix{1 & & \\ & \ddots & \\ & & 1}
$$
其中对角线矩阵元全为 $1$，其余留白部分全为 $0$。

容易验证，对于所有 $m \times n$ 矩阵 $\bs{A}$ 都有
$$
\bs{I}_m \cdot \bs{A} = \bs{A} = \bs{A} \cdot \bs{I}_n.
$$

---

<div class=proposition>

矩阵乘法满足以下性质：
- **结合律**   $\quad$ $(\bs{AB})\bs{C} = \bs{A}(\bs{BC})$；
- **分配律** $\quad$ $\bs{A}(\bs{B} + \bs{C}) = \bs{AB} + \bs{AC}$，$(\bs{B}+\bs{C})\bs{A} = \bs{BA} + \bs{CA}$；
- **线性** $\quad$ $\bs{A}(t\bs{B}) = t(\bs{AB}) = (t\bs{A})\bs{B}$

其中数 $t$ 和矩阵 $\bs{A}, \bs{B}, \bs{C}$ 是任意的，前提是矩阵的行数和列数使运算有意义。
</div>

---

<div class=proof>

对 $(\bs{AB})\bs{C}$ 和 $\bs{A}(\bs{BC})$ 的每个矩阵元进行考察，可见结合律相当于说
$$
\sum_{k}(\sum_{j} a_{ij}b_{jk}) c_{kl} = \sum_{j}a_{ij}(\sum_{k} b_{jk} c_{kl}),
$$
下标 $i, j, l, l$ 的取值范围取决于矩阵尺寸。根据求和符号的基本操作，交换 $\sum_{k}$ 和 $\sum_{j}$ 以后，问题归结为证
$$
(a_{ij}b_{jk})c_{kl} = a_{ij}(b_{jk}c_{kl}).
$$
然而这无非是数的乘法结合律。同理，分配律归结为数的乘法分配律
$$
a_{ij}(b_{jk} + c_{jk}) = a_{ij} b_{jk} + c_{ij} c_{jk}.
$$
最后一则性质归结为等式 $a_{ij}(tb_{jk}) = t(a_{ij}b_{jk}) = (ta_{ij})b_{jk}$，而这又归结为数的乘法交换律和结合律。
</div>

---

矩阵乘法**不满足交换律**。

设 $\bs{A}$ 是 $m\times n$ 矩阵，$\bs{B}$ 是 $n \times m$ 矩阵，那么 $\bs{AB}$ 和 $\bs{BA}$ 都有意义，$\bs{AB}$ 是 $m$ 阶方阵，$\bs{BA}$ 是 $n$ 阶方阵。

$\bs{AB}$ 和 $\bs{BA}$ 一般不相等。
- 如果 $m \ne n$，这是显然的。
- 即便 $m = n$，即 $\bs{A}$ 和 $\bs{B}$ 都是 $n$ 阶方阵，一般来说 $\bs{AB}$ 和 $\bs{BA}$ 也不相等。
例如
$$
\begin{aligned}
\pmatrix{0 & 1 \\ 1 & 0} \pmatrix{1 & 1 \\ 0 & 1} &= \pmatrix{0 & 1 \\ 1 & 1}, \\
\pmatrix{1 & 1 \\ 0 & 1} \pmatrix{0 & 1 \\ 1 & 0} &= \pmatrix{1 & 1 \\ 1 & 0}.
\end{aligned}
$$

---

# 用矩阵乘法表述线性方程组

$$
\begin{cases}
a_{11}X_1 + \dots + a_{1n} X_n &= b_1 \\
a_{21}X_1 + \dots + a_{2n} X_n &= b_2 \\
\vdots                     &\phantom{=\ }\vdots \\
a_{m1}X_1 + \dots + a_{mn} X_n &= b_m
\end{cases} \iff \pmatrix{a_{11} & \dots & a_{1n} \\ \vdots & \ddots & \vdots \\ a_{m1} & \dots & a_{mn}} \pmatrix{X_1 \\ \vdots \\ X_n} = \pmatrix{b_1 \\ \vdots \\ b_m}.
$$

取方程组的系数矩阵 $\bs{A} := (a_{ij})_{i,j}$，并且定义列向量
$$
\bs{x} := \pmatrix{X_1 \\ \vdots \\ X_n}, \quad \bs{b} := \pmatrix{b_1 \\ \vdots \\ b_m},
$$
则原方程组等价于以 $\bs{x}$ 为变量的矩阵方程
$$
\bs{Ax} = \bs{b}.
$$
矩阵写法胜在简洁，而这也为矩阵乘法的定义提供了一部分的解释。

---

# 方阵的幂

对于任意正整数 $n, k$ 和 $n$ 阶方阵 $\bs{A}$，定义
$$
\bs{A}^{k} := \underbracket{\bs{A\dots A}}_{k个\bs{A}},
$$
约定 $\bs{A}^{0} := \bs{I}_n$.

由于矩阵乘法满足结合律，我们可以用快速幂算法来计算方阵的幂。

---

# 习题 矩阵乘法

[洛谷B2105 矩阵乘法](https://www.luogu.com.cn/problem/B2105)
[洛谷P3390 矩阵快速幂](https://www.luogu.com.cn/problem/P3390)

---

# 利用矩阵乘法计算递推数列的某一项

---

## Fibonacci 数列

$f_0 = 0, f_1 = 1$，对于 $n \ge 2$ 有
$$f_n = f_{n-1} + f_{n-2}.$$

这个递推式可以用矩阵乘法来表述
$$
\pmatrix{f_n \\ f_{n-1}} = \pmatrix{1 & 1 \\ 1 & 0} \pmatrix{f_{n-1} \\ f_{n-2}} 
$$
或写成
$$
\pmatrix{f_n & f_{n-1}} = \pmatrix{f_{n-1} & f_{n-2}} \pmatrix{1 & 1 \\ 1 & 0}.
$$

于是有
$$
\pmatrix{f_n \\ f_{n-1}} =  \pmatrix{1 & 1 \\ 1 & 0}^{n-1} \pmatrix{f_1 \\ f_0}.
$$

---

## 等比数列的和

对于任意实数 $x$，定义数列 $(s_n)_{n\ge 0}$，$s_n := \sum_{i=0}^{n-1} x^i$。有递推式
$$
s_{n+1} = s_n + x^{n}
$$
可以用矩阵乘法表述为
$$
\pmatrix{s_{n+1} \\ x^{n+1}} = \pmatrix{1 & 1 \\ 0 & x} \pmatrix{s_n \\ x^n}
$$
于是有
$$
\pmatrix{s_n \\ x^n} = \pmatrix{1 & 1 \\ 0 & x}^n \pmatrix{s_0 \\ x^0}.
$$

---

递推式
$$s_{n+1} = s_n + x^{n}$$
用矩阵乘法也可以表述为
$$
\pmatrix{s_{n+1} & x^{n+1}} = \pmatrix{s_n & x^n} \pmatrix{1 & 0 \\ 1 & x}
$$
于是有
$$
\pmatrix{s_n & x^n} = \pmatrix{s_0 & x^0} \pmatrix{1 & 0 \\ 1 & x}^n.
$$

---

另一个递推式
$$
s_{n+1} = 1 + xs_n
$$
可以用矩阵乘法表述为
$$
\pmatrix {s_{n+1} \\ 1} = \pmatrix{x & 1 \\ 0& 1} \pmatrix{s_n \\ 1}
$$
于是有
$$
\pmatrix{s_n \\ 1} = \pmatrix{x & 1 \\ 0& 1}^{n} \pmatrix{s_0 \\ 1}.
$$

---


## Sum of Powers


对于任意实数 $x$ 和非负整数 $k$，令
$$
S_k(n) := \sum_{i=0}^{n-1} x^k.
$$
有递推式
$$
S_k(n + 1) = S_k(n) + n^k.
$$
定义行向量
$$
\bs{v}_n := \pmatrix{S_k(n),n^0,n^1, \dots, n^k} 
$$
对于每个 $i = 0, 1, \dots, k$，有
$$
(n+1)^i = \sum_{j = 0}^i {i \choose j} n^j.
$$

---

我们可以写
$$
\bs{v}_{n+1} = \bs{v}_n \bs{A}
$$
其中 $\bs{A}$ 是一个 $(k+2)$ 阶方阵，其矩阵元可由上面的递推式得出。

例如，当 $k = 2$ 时，有
$$
\bs{v}_{n+1} = \bs{v}_n \pmatrix{} 
$$

