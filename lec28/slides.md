---
marp: true
math: mathjax
paginate: true
theme: lecture
title: 数论
---

# 数论

<div class=hidden>

$\newcommand{\Z}{\mathbb{Z}}$
$\newcommand{\R}{\mathbb{R}}$
$\DeclareMathOperator{\lcm}{lcm}$
$\DeclareMathOperator{\extgcd}{extgcd}$
$\newcommand{\Div}{\mathrel{\Vert}}$
$\DeclarePairedDelimiter\ceil{\lceil}{\rceil}$
$\DeclarePairedDelimiter\floor{\lfloor}{\rfloor}$
$\renewcommand{\%}{\mathbin{\text{\%}}}$

</div>

---

# 整除


对任意 $x \in \Z$ 定义 $x\Z := \set{xd : d\in\Z}$，它由 $x$ 的所有倍数构成。对于 $x, y\in \Z$，如果 $y \in x\Z$ 则称 $x$ **整除** $y$ 记为 $x \mid y$，否则记为 $x\not\mid y$。当 $x\mid y$ 时，我们称 $x$ 为 $y$ 的**因数**或**因子**。


---

# 最小公倍数、最大公因数、互素

以下选定 $n \in \Z_{\ge 1}$，并考虑一族整数 $x_1, \dots, x_n \in\Z$。

- 记这族整数的<ruby>**最小公倍数**<rt>least common multiple</rt></ruby>为
    $$\lcm(x_1, \dots, x_n) := \begin{aligned}
        \begin{cases}
        \min\set{m \in\Z_{\ge 1} : \forall 1\le i \le n,\ x_i\mid m}, & \forall i,\  x_i \ne 0, \\
        0, & \exists i,\ x_i = 0.
        \end{cases}
    \end{aligned}
    $$

- 记这族整数的<ruby>**最大公因数**<rt>greatest common divisor</rt></ruby>为
    $$\gcd(x_1, \dots, x_n) := \begin{aligned}
        \begin{cases}
        \max\set{d \in\Z_{\ge 1} : \forall 1\le i \le n,\ d \mid x_i}, & \exists i,\  x_i \ne 0, \\
        0, & \forall i,\ x_i = 0.
        \end{cases}
    \end{aligned}
    $$

- 若 $\gcd(x_1, \dots, x_n) = 1$，则称 $x_1, \dots, x_n$ **互素**，这也相当于说 $x_1, \dots, x_n$ 没有 $\pm 1$ 以外的公因子。

---



# 整数的带余除法

对于任意整数 $a, d \in \Z$，若 $d\ne 0$，则存在唯一的 $q, r\in\Z$ 使得 $0\le r < |d|$ 而 $a = dq + r$。

**证明** $\quad$ 不妨假定 $d > 0$。考虑集合
$$
R := \set{a - dq : q\in\Z} \cap \Z_{\ge 0}.
$$
这是 $\Z_{\ge 0}$ 的非空子集，故有极小元，记为 $r$；相应地 $a = dq + r$。必然有 $r < d$，否则 $a = d(q+1) + (r - d)$ 将给出 $r - d \in R$ 使得 $0 \le r - d < r$，与 $r$ 的极小性质矛盾。这就说明 $q, r$ 的存在性。

至于唯一性，设 $dq + r = dq' + r'$，其中 $q, q' \in \Z$ 而 $0 \le r \le r' < d$。因为 $r' - r = d(q - q')$ 既被 $d$ 整除，又有 $0 \le r'-r \le r' < d$，易证唯一的可能是 $r'=r$，从而由 $d \ne 0$ 推得 $q = q'$。

根据上述命题中的唯一性，带余除法中的余数 $r = 0$ 当且仅当 $d\mid a$。


---

<div class=lemma>

设 $I$ 为 $\Z$ 的非空子集，满足以下性质
$$
\begin{aligned}
x,y\in I &\implies  x+y\in I, \\
a\in \Z, x\in I &\implies ax\in I.
\end{aligned}
$$ 
<!-- 这样对齐会导致 \implies 左边的空格较小，不是正确的对齐方式。 -->
此时存在唯一的 $g\in\Z_{\ge 0}$ 使得 $I = g\Z$。

</div>

上述两个性质是说 $I$ 中任意两整数相加仍然在 $I$ 中，$I$ 中任意整数的倍数仍然在 $I$ 中。

**证明** $\quad$ 先讨论 $g$ 的存在性。不妨设 $I \ne \set{0}$，否则唯一的取法是 $g = 0$。注意到 $g\in I \iff -g\in I$。取 $g$ 为 $I$ 中的最小正整数。包含关系 $I \supseteq g\Z$ 自明。至于 $I\subseteq g\Z$，设 $m\in I$，用带余除法表为 $m= gq + r$，其中 $0 \le r < g$。不难验证 $m - gq$ 属于 $I$，于是 $r = m - gq$ 必为 $0$，否则将给出 $I$ 中比 $g$ 更小的正整数，矛盾。

至于 $g$ 的唯一性，若正整数 $g, g'$ 满足 $g\Z = g'\Z$，则它们相互整除，故唯一的可能是 $g = g'$。

---

<div class=definition>

对给定的 $x_1, \dots, x_n \in \Z$，定义 $\Z$ 的子集
$$
\begin{aligned}
\sum_{i=1}^{n} \Z x_i &= \Z x_1 + \dots + \Z x_n\\
&:= \left\{\sum_{i=1}^{n} a_i x_i \in \Z : a_1,  \dots, a_n \in\Z\right\};
\end{aligned}
$$
按照惯例，极端情形 $n = 0$（即“空和”）按 $\sum_{i=1}^{0}\Z x_i := \set{0}$ 来解释。

</div>

---

# Bézout's identity（裴蜀恒等式   ）

<div class=proposition>

设 $x_1, \dots, x_n$ 为整数，则
$$
\Z x_1 + \dots + \Z x_n = \gcd(x_1, \dots, x_n) \Z.
$$
作为推论，$x_1, \dots, x_n$ 互素的充要条件是存在 $a_1, \dots, a_n\in\Z$ 使得 $a_1 x_1 + \dots + a_n x_n = 1$。

</div>

**证明** 不妨设 $x_1, \dots, x_n$ 不全为 $0$，否则等式两边按定义同等于 $\set{0}$。据上述引理取 $g\in \Z_{\ge 1}$，使得 $\Z x_1 + \dots + \Z x_n = g\Z$。不难验证对于任意正整数 $d$，我们有
$$
(\forall 1\le i \le n,\ d\mid x_i) \iff (\forall x \in \Z x_1 + \dots + \Z x_n,\ d\mid x) \iff d \mid g.
$$
这就足以表明 $g = \gcd(x_1, \dots, x_n)$。

基于上述结果，$\gcd(x_1, \dots, x_n) = 1$ 蕴含 $1$ 可以表为 $a_1 x_1 + \dots + a_n x_n$ 的形式；反之，若存在 $a_1, \dots, a_n$ 使得 $1 = a_1 x_1 + \dots + a_n x_n$，则 $x_1, \dots, x_n$ 当然互素。

---

# Euclid's lemma

<div class=proposition>

若 $a, b, c\in \Z$ 使得 $a \mid bc$ 且 $\gcd(a, b) = 1$，则 $a \mid c$。

</div>

**证明** 由于 $\gcd(a, b) = 1$，裴蜀定理蕴含存在 $x,y\in\Z$ 使得 $1 = ax + by$。于是 $a \mid bc \implies a \mid (axc+ bcy)$，而 $axc + bcy = (ax+ by)c = c$，所以有 $a \mid c$。

---

# 计算 gcd(a, b)

<div class=question>

求正整数 $a, b$ 的最大公因数。

</div>

不妨设 $a \ge b$。设 $a$ 用带余除法表作 $a = bq + r$，其中 $0 \le r < b$。若 $d$ 是 $a, b$ 的公因数，则 $d$ 整除 $a - qb=r$；反之，若 $d$ 是 $b,r$ 的公因数则 $d$ 整除 $bq + r = a$。即 $a, b$ 和 $b, r$ 有同一群公因数，自然有
$$
\gcd(a, b) = \gcd(b, r).
$$
这引出如下递归算法：
$$
\gcd(a, b) = \gcd(b, r) \quad \begin{cases}
= b, \quad &若 r = 0, \\
继续作带余除法, \quad &若 r \ne 0.
\end{cases}
$$
一言以蔽之，从 $a, b$ 开始反复作带余除法，直到余数为零。

此算法称为**辗转相除法**，也称<ruby>**欧几里得算法**<rt>Euclid's algorithm</rt></ruby>。


---

# 例子：计算 $\gcd(99, 78)$

用辗转相除法计算 $\gcd(99, 78)$ 的过程可以用如下序列表示
$$
99, 78, 21, 15, 6, 3, 0.
$$
从第三项开始，每一项都是前两项相除的余数；这样反复做带余除法，直到余数为 $0$。

前一次的除数是下一次的被除数，而余数（可视为被除数的“残留”）是一下次的除数；被除数与除数前后角色翻转，此即“辗转”之义。

---

```cpp
int gcd(int a, int b) {
    return b == 0 ? a : gcd(a, a % b);
}
```

---

# 辗转相除法的时间复杂度

<div class=question>

设 $a \ge b \ge 1$。辗转相除计算 $\gcd(a, b)$ 最多可能做多少次除法？

</div>

---

用辗转相除法计算 $a, b$ 的最大公因数，假设一共做了 $n$ 次除法运算，那么我们得到两个序列
- 余数序列：$r_0 = a, r_1 = b, \dots, r_n = \gcd(a, b), r_{n+1} = 0$。
- 商序列：$q_1, q_2, \dots, q_n$。

对每个 $i = 1, \dots, n$，有
$$
r_{i+1} = r_{i-1} - q_i r_i.
$$

---

<div class=proposition>

设 $a, b$ 是正整数，$a \ge b$，$r$ 是 $a$ 除以 $b$ 的余数。那么 $r < a/2$。

</div>

**证明** $\quad$ 若 $b \le a/2$，那么根据余数的定义有 $r < b$。若 $b > a/2$，那么 $r = a - b < a/2$。

---

<div class=proposition>

设 $a, b$ 是整数，$a \ge b \ge 1$。用辗转相除法计算 $\gcd(a,b)$，做除法的次数不超过 $1 + 2 \log_2 b$。

</div>

**证明**：假设一共做了 $n$ 次除法，写出余数序列
$$ r_0 = a, r_1 = b, r_2,\dots, r_n = \gcd(a, b), r_{n+1} = 0,$$
我们有
$$
r_0 \ge r_1 > r_2 > \dots > r_{n} > r_{n+1} = 0.
$$
根据上一页的命题，我们有
$$
r_{i-1} > 2 r_{i+1} \qquad \text{for}\ 1 \le i \le n.
$$
分别看 $r_0, r_2, \dots$ 和 $r_1, r_3, \dots$，有
$$
\begin{aligned}
a &= r_0 > 2 r_2 > 4 r_4 > \dots, \\
b &= r_1 > 2 r_3 > 4 r_5 > \dots
\end{aligned}
$$

---

若 $n$ 是奇数，我们有
$$
\begin{aligned}
a &= r_0 \ge  2^{(n-1)/2} r_{n-1} \ge 2^{(n-1)/2}\\
b &= r_1 \ge 2^{(n-1)/2}r_n \ge 2^{(n-1)/2}
\end{aligned}
$$
也就是有 $b \ge 2^{(n-1)/2}$，所以
$$n \le 1 + 2\log_2 b.$$

若 $n$ 为偶数，此时 $n \ge 2$，有 $r_{n-1} > r_n \ge 1$ 且 $r_{n} \mid r_{n-1}$，所以 $r_{n-1} \ge 2r_n$，我们有
$$
\begin{aligned}
a &= r_0 > 2^{n/2} r_n \ge 2^{n/2} \\
b &= r_1 \ge 2^{(n-2)/2} r_{n-1} \ge 2^{n/2} r_n \ge 2^{n/2}
\end{aligned}
$$
也就是有 $b \ge 2^{n/2}$，所以
$$
n \le 2 \log_2 b.
$$



---

# 计算 lcm(a, b)

<div class=question>

求正整数 $a, b$ 的最小公倍数。

</div>


---

<div class=proposition>

对任意正整数 $a, b$ 有 $\lcm(a, b) = ab/\gcd(a, b)$。

</div>

**证明** 设 $d = \gcd(a, b)$，则根据最大公因数的定义，存在整数 $m, n$ 使得 $a = dm$，$b = dn$ 且 $\gcd(m, n) = 1$。

令 $L = ab/d$，代入 $a = dm, b = dn$ 得 $L = dmn$。于是有 $L = an = bm$，可见 $L$ 是 $a, b$ 的公倍数。

设 $M$ 是 $a$ 和 $b$ 的任意一个公倍数，即 $a \mid M$ 且 $b\mid M$。以 $a = dm$ 代入 $a \mid M$ 得 $dm \mid M$，所以存在整数 $k$ 使得 $M = dmk$。以 $b = dn$ 和 $M = dmk$ 代入 $b\mid M$，得 $dn \mid dmk$。两边约去 $d$，得 $n \mid mk$。由于 $\gcd(m, n) = 1$，根据欧几里得引理，必有 $n \mid k$。所以存在整数 $t$，使 $k = nt$，代入 $M = dmk$，得 $M = dm(nt) = (dmn)t = Lt$。因为 $t$ 是整数，所以 $L \mid M$。

因为 $a, b$ 的任意公倍数都能被 $L$ 整除，且 $L$ 是 $a, b$ 的公倍数，所以 $L$ 就是 $a, b$最小公倍数。

---

# 丢番图方程 $ax + by = c$

<div class=question>

设 $a, b, c$ 是整数，求方程 $ax + by = c$ 的整数解。

</div>

根据 Bézout's identity，$\Z a + \Z b = \gcd(a, b)\Z$，所以方程有解当且仅当 $\gcd(a, b) \mid c$。

---

<div class=proposition>

设 $a, b, c$ 是整数，$a, b$ 不都是 $0$。设整数 $x_0, y_0$ 满足 $ax_0 + b y_0 = c$，那么方程 $ax + by  = c$ 的全部整数解为
$$
x = x_0 + {b\over\gcd(a, b)} t, \quad y = y_0 -  {a \over \gcd(a, b)}t
$$
其中 $t$ 是任意整数。

</div>

**证明**：先证充分性。
令 $d = \gcd(a, b)$。将 $x = x_0 + {b\over d} t$ 和 $y = y_0 - {a\over d}t$ 代入 $ax + by$，得
$$a(x_0 + {b\over d} t) + b(y_0 -  {a \over d}t) = ax_0 + by_0 + {ab\over d}t - {ba\over d}t = ax_0 + by_0 = c$$
所以 $(x_0 + {b\over d}t, y_0 - {a\over d}t)$ 是方程的解。

---

再证必要性。
设 $(x, y)$ 是方程的任意一组整数解，即 $ax + by = c$，同时我们有 $ax_0 + by_0 = c$，两式相减，得 $a(x- x_0) + b(y - y_0) = 0$，即
$$a(x - x_0) = -b(y - y_0)$$
设 $a = da'$，$b = db'$，此时必然有 $\gcd(a', b') = 1$，代入上式并除以 $d$，得
$$
\begin{equation}
a'(x - x_0) = -b'(y - y_0) \tag{1}\label{eq1}
\end{equation}
$$
于是可见 $b'$ 整除 $a'(x - x_0)$。由于 $\gcd(a', b') = 1$，根据欧几里得引理，我们有
$$ b' | (x - x_0) $$
也就是说，存在整数 $t$ 使得 $x - x_0 = b't$，即 $x = x_0 + b't$。

若 $b' = 0$，即 $b = 0$，此时必有 $a \ne 0$，则 $x$ 的值唯一，是 $x = x_0 = c/a$，而 $y$ 可取任一整数。此时 $a' = \pm 1$，而 $y =y_0 - a't$ 确实可以取到每个整数。

若 $b' \ne 0$，将 $x - x_0 = b't$ 代入 $\eqref{eq1}$，得 $a'b't = -b'(y - y_0)$，除以 $-b'$，得 $-a't = y - y_0$，即 $y = y_0 - a't$。

---

# 丢番图方程 $ax + by = \gcd(a, b)$

<div class=question>

设 $a, b$ 是整数，求方程 $ax + by = \gcd(a, b)$ 的整数解。

</div>

---

# 扩展 gcd 算法

我们用辗转相除法计算 $\gcd(a, b)$，除了可以得到 $\gcd(a, b)$，还能得到两个整数 $x, y$ 使得 $ax + by = \gcd(a, b)$。这就是所谓**扩展 gcd 算法**。

具体的计算方法有两种：一是正推，一是倒推。

---

# 正推的扩展 gcd 算法

用辗转相除法计算 $\gcd(a, b)$，写出余数序列
$$r_0=a, r_1=b, \dots, r_n = \gcd(a, b), r_{n+1} = 0.$$

我们可以按 $i = 0, 1, \dots, n+1$ 的顺序，把每个 $r_i$ 写成
$$ ax_i + b y_i  $$
的形式，其中 $x_i, y_i$ 是整数。

最后 $x_n, y_n$ 就使得 $\gcd(a, b) = ax_n + by_n$.

---

我们取 $x_0 = 1, y_0 = 0$ 和 $x_1 = 0, y_1 = 1$。


## 从 $(x_{i-1}, y_{i-1})$ 和 $(x_i, y_i)$ 推 $(x_{i+1},y_{i+1})$
将 $r_{i-1} = ax_{i-1} + by_{i-1}$ 和 $r_i = ax_i + by_i$ 代入
$$ r_{i+1} = r_{i-1} - q_i r_i  $$
得
$$ r_{i+1} = (ax_{i-1}+by_{i-1}) - q_i(ax_i + by_i) $$
改写成
$$ r_{i+1} = a(x_{i-1} - q_ix_i) + b(y_{i-1} - q_iy_i). $$
我们可以取
$$ x_{i+1} = x_{i-1} - q_i x_i, \quad y_{i+1} = y_{i-1} - q_i y_i. $$
---

我们以计算 $\gcd(99, 78)$ 为例，演示正推的扩展 gcd 算法。
$$
\begin{matrix}
\hline
i & q_i & r_i   &  x_i & y_i  \\ \hline
\color{gray} 0 &  &  99  & 1 & 0 & \\ \hline
\color{gray} 1 & 1 & 78 & 0 & 1 \\ \hline
\color{gray} 2 & 3 & 21 & 1 & -1 \\ \hline
\color{gray} 3 & 1 & 15 & -3 & 4 \\ \hline
\color{gray} 4 & 2 & 6 & 4 & -5 \\ \hline
\color{gray} 5 & 2 & \color{red} 3 & \color{red} -11 & \color{red} 14 \\ \hline
\color{gray} 6 &  & 0 & 26 & -33\\ \hline
\end{matrix}
$$

---

```cpp
pair<int,int> extgcd(int a, int b) {
    int u = 1, v = 0;
    while (b != 0) {
        int q = a % b;
        a -= q * b;
        u -= q * v;
        swap(a, b);
        swap(u, v);
    }
    return {a, u};
}
```

`extgcd(a, b)` 返回的两个整数依次是
- $\gcd(a, b)$
- 一个整数 $x$ 使得 $b$ 整除 $(\gcd(a, b) - ax)$

---

# 倒推的扩展 gcd 算法

用辗转相除法计算 $\gcd(a, b)$，写出余数序列
$$r_0=a, r_1=b, \dots, r_n = \gcd(a, b), r_{n+1} = 0.$$
我们可以按 $i = n, n-1, \dots, 0$ 的顺序，把 $\gcd(a, b)$ 写成
$$ x_i r_i + y_i r_{i+1} $$
的形式，其中 $x_i, y_i$ 是整数。

最后，$x_0, y_0$ 就使得 $x_0 a + y_0 b = \gcd(a, b)$。

---


$r_n$ 就是 $\gcd(a, b)$，我们取 $x_n = 1$，$y_n = 0$。

## 从 $(x_i, y_i)$ 推 $(x_{i-1}, y_{i-1})$

<!-- 首先我们写出
$$
\begin{align}
\gcd(a, b) &= x_i r_i + y_i r_{i+1} \label{eq} \tag{1} \\
\gcd(a, b) &= x_{i-1} r_{i-1} + y_{i-1} r_i \label{eq2} \tag{2}
\end{align}
$$ -->
将 $r_{i+1} = r_{i-1} - q_ir_i$ 代入 $\gcd(a, b) = x_i r_i + y_i r_{i+1}$，得
$$\gcd(a,b) = x_ir_i + y_i(r_{i-1} - q_ir_i),$$
改写成
$$ \gcd(a,b) = y_i r_{i-1}  + (x_i - y_iq_i) r_i. $$
将此式与 $\gcd(a, b) = x_{i-1}r_{i-1} + y_{i-1} r_i$ 对比，可见我们可以取
$$
x_{i-1} = y_i, \quad y_{i-1} = x_i - y_i q_i.
$$


---

我们以计算 $\gcd(99, 78)$ 为例，演示倒推的扩展 gcd 算法。

$$
\begin{matrix}
\hline
i & q_i & r_i   &  x_i & y_i  \\ \hline
\color{gray} 0 &   & 99  & \color{red} -11 & \color{red} 14 \\ \hline
\color{gray} 1 & 1 & 78 & 3 & -11 \\ \hline
\color{gray} 2 & 3 & 21 & -2 & 3 \\ \hline
\color{gray} 3 & 1 & 15 & 1 & -2 \\ \hline
\color{gray} 4 & 2 & 6 & 0 & 1 \\ \hline
\color{gray} 5 & 2 & \color{red} 3 & 1 & 0\\ \hline
\color{gray} 6 & & 0 &  &\\ \hline
\end{matrix}
$$

---

```cpp
int extgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int q = a % b;
    int g = extgcd(b, a - q * b, y, x);
    y -= x * q;
    return g;
}
```

---

<div class=columns>
<div>

# 正推

$$
\begin{matrix}
\hline
i & q_i & r_i   &  x_i & y_i  \\ \hline
\color{gray} 0 &  &  99  & 1 & 0 \\ \hline
\color{gray} 1 & 1 & 78 & 0 & 1 \\ \hline
\color{gray} 2 & 3 & 21 & 1 & -1 \\ \hline
\color{gray} 3 & 1 & 15 & -3 & 4 \\ \hline
\color{gray} 4 & 2 & 6 & 4 & -5 \\ \hline
\color{gray} 5 & 2 & \color{red} 3 & \color{red} -11 & \color{red} 14 \\ \hline
\color{gray} 6 &  & 0 & 26 & -33\\ \hline
\end{matrix}
$$

</div>

<div>

# 倒推

$$
\begin{matrix}
\hline
i & q_i & r_i   &  x_i & y_i  \\ \hline
\color{gray} 0 &   & 99  & \color{red} -11 & \color{red} 14 \\ \hline
\color{gray} 1 & 1 & 78 & 3 & -11 \\ \hline
\color{gray} 2 & 3 & 21 & -2 & 3 \\ \hline
\color{gray} 3 & 1 & 15 & 1 & -2 \\ \hline
\color{gray} 4 & 2 & 6 & 0 & 1 \\ \hline
\color{gray} 5 & 2 & \color{red} 3 & 1 & 0\\ \hline
\color{gray} 6 & & 0 &  &\\ \hline
\end{matrix}
$$

</div>
</div>

正推和倒推给出的 $x, y$ 是一样的，这并非巧合。

---

# C++ 里的 % 运算符和 / 运算符

设 $a, b$ 是整数，$b \ne 0$。
- 如果 $b$ 整除 $a$，那么 $a \% b = 0$。如果 $b$ 不整除 $a$，此时必有 $a \ne 0$，那么
    - $a\%b \ne 0$，
    - $a\%b$ 的符号与 $a$ 相同，
    - $|a\%b| < |b|$。
- `a == (a / b) * b + (a % b)` 总是成立。

---

# 扩展 gcd 算法给出的 x, y 的大小

<div class=proposition>

设 $a, b$ 是整数，$a \ne 0$ 且 $b \ne 0$，设 $g = \gcd(a, b)$。那么 `extgcd(a, b, x, y)` 给出的 $x, y$ 满足
$$ |x| \le {|b| \over g}, \quad |y| \le {|a| \over g}. $$

</div>

---

**证明**：用归纳法。回忆到条件是 $a\ne 0$ 且 $b\ne 0$。
当 $a\%b = 0$ 时，$g = |b|$，`extgcd(a, b, x, y)` 给出 $(x, y) = (0, 1)$。此时 $|a| \ge |b|$，$0 \le {|b| \over g} = 1$ 且 $1 \le {|a| \over g}$，命题成立。

当 $a \%b \ne 0$ 时，根据归纳假设，递归调用 `extgcd(b, a % b, y, x)` 给出的 $(x', y')$ 满足 $|x'| \le {|a\%b|\over g}$，$|y'| \le {|b| \over g}$。设 $q =$ `a / b`，根据 $x = y'$ 和 $y = x' - qy'$，有
$$ |x| = |y'|\le {|b| \over g} $$
和
$$
|y| = |x'-qy'| \le |x'| + |qy'| \le {|a\%b| \over g} + {|qb| \over g}.  
$$
回忆到 $a\%b$ 与 $qb$ 符号相同，所以 $|a\%b| + |qb| = |a\%b + qb| = |a|$。于是有
$$
|y| \le {|a| \over g}.
$$

---

用同样的方法，我们还可以证明

<div class=proposition>

设 $a, b$ 是整数，$a \ne 0$，$b \ne 0$ 且 $|a| \ne |b|$，设 $g = \gcd(a, b)$。
那么 `extgcd(a, b, x, y)` 给出的 $x, y$ 满足
$$ |x| \le {|b| \over 2g}, \quad |y| \le {|a| \over 2g}. $$

</div>


---

# 解丢番图方程 $ax + by = c$

此方程有解当且仅当 $\gcd(a,b)\mid c$。

具体的，如果 $\gcd(a, b) = 0$，也就是 $a = b = 0$，那么当且仅当 $c = 0$ 时有解，此时任意整数 $x, y$ 都是解。

如果 $a, b$ 不全是 $0$，那么
1. 用扩展 gcd 算法算出 $\gcd(a, b)$ 和整数 $x_0, y_0$ 使得 $ax_0 + by_0 = \gcd(a, b)$。
2. 如果 $\gcd(a, b) \mid c$，那么 $({c\over\gcd(a,b)} x_0, {c\over\gcd(a,b)} y_0)$ 就是 $ax + by = c$ 的一个解，否则方程无解。

---


在计算时需要注意
- 当 $c$ 较大时，${c\over\gcd(a,b)}$ 乘 $x_0$ 可能溢出。

我们可以这样做
- 设 $q$ 和 $c'$ 分别是 $c$ 除以 $a$ 的商和余数。那么 $(q+{c'\over \gcd(a,b)}x_0, {c'\over\gcd(a,b)} y_0)$ 是 $ax + by = c$ 的一个解。

---


# 同余式

<div class=definition>

设 $N\in \Z$。称 $a,b\in\Z$ 是 mod $N$ **同余**的，如果 $N\mid a - b$；此关系也写作
$$a\equiv b \pmod{N}.$$

</div>

---

# 线性同余方程

<div class=question>

设 $a, b, c$ 是整数，$b \ge 1$。求方程 $ax \equiv c \pmod{b}$ 的整数解。

</div>

整数 $x$ 使得 $ax \equiv c \pmod{b}$，也就是说存在整数 $y$ 使得 $by = ax - c$。于是可见同余方程 $ax \equiv c \pmod {b}$ 和丢番图方程 $ax + by = c$ 同解。我们立即得到

- 存在整数 $x$ 使得 $ax \equiv c \pmod{b}$ 当且仅当 $\gcd(a, b) \mid c$。
- 设整数 $x_0$ 是方程 $ax \equiv c \pmod{b}$ 的一个解，那么此方程的全部整数解为 $x = x_0 + {b \over \gcd(a, b)}t$，其中 $t$ 是任意整数。也就是说 $ax \equiv c \pmod b$ 和 $x \equiv x_0 \pmod{{b\over\gcd(a, b)}}$ 等价。

--- 

# 线性同余方程组

<div class=question>

设 $a_1, b_1, a_2, b_2$ 是整数，$a_1 \ge 1$，$a_2 \ge 1$。
求方程组 $\begin{cases} x \equiv b_1 \pmod{a_1} \\ x \equiv b_2 \pmod{a_2} \end{cases}$ 的整数解。


</div>

---

整数 $x$ 满足 $\begin{cases} x \equiv b_1 \pmod{a_1} \\ x \equiv b_2 \pmod{a_2} \end{cases}$，也就是说 $x$ 使得
- 存在整数 $k_1, k_2$ 满足 $x = b_1 + a_1 k_1$ 且 $x = b_2 + a_2k_2$。

所以这样的 $x$ 和满足 $b_1 + a_1 k_1 = b_2 + a_2k_2$ 的整数对 $(k_1, k_2)$ 一一对应。可见 $k_1$ 就是丢番图方程 $a_1 X - a_2 Y = b_2 - b_1$ 的解 $X$。设 $X_0$ 是一个解，那么全部解为
$$k_1 = X_0 + {a_2\over \gcd(a_1, a_2)}t$$
其中 $t$ 是任意整数。将上式代入 $x = b_1 + a_1k_1$，得
$$
x = b_1 + a_1 X_0 + {a_1a_2 \over\gcd(a_1, a_2)}t.
$$
注意到 $a_1a_2/\gcd(a_1, a_2)$ 就是 $\lcm(a_1, a_2)$。于是可见
- 方程组 $\begin{cases} x \equiv b_1 \pmod{a_1} \\ x \equiv b_2 \pmod{a_2} \end{cases}$ 等价于 $x \equiv b_1 + a_1X_0 \pmod{\lcm(a_1, a_2)}$。


---

# 素数

设 $p\in \Z\setminus \set{0, \pm 1}$。如果 $p$ 除了 $\pm 1$ 和 $\pm p$ 之外没有别的因数，则称 $p$ 是**素元**。正的素元称为**素数**。

---


# 算术基本定理

任何非零整数 $n$ 都有素因子分解
$$
n = \pm p_1^{a_1} \dots p_r^{a_r},
$$
其中 $r \in\Z_{\ge 0}$（当 $r = 0$ 时右式规定为 $1$），$p_1, \dots, p_r$ 是相异素数，$a_1,\dots, a_r\in \Z_{\ge 1}$，而且此分解不论顺序是唯一的。

**证明** $\quad$ 关于分解的存在性，处理 $n \ge 1$ 的情形即可。我们寻求形如 $n = p_1^{a_1}\dots p_r^{a_r}$ 的分解。如果 $n$ 既非 $1$ 又非素数，则分解为 $n = ab$，其中 $1< a, b < n$。继续对 $a, b$ 递归地操作，最终可表 $n$ 为若干个素数的乘积，容许重复。

---

唯一性仍可简化到 $n \ge 1$ 的情形。设 $p_1^{a_1}\dots p_r^{a_r} = q_1^{b_1}\dots q_s^{b_s}$，其中 $p_1, \dots, p_r$ 是相异素数，$q_1, \dots, q_s$ 也是相异素数，而 $a_i, b_j \in\Z_{\ge 1}$。注意到 $r = 0$ 当且仅当 $s = 0$，此时两边都是 $1$。故以下不妨设 $r, s \ge 1$。

由于 $p_1 \mid q_1^{b_1} \dots q_s^{b_s}$，反复应用欧几里得引理可知存在 $1\le j \le s$ 使得 $p_1 \mid q_j$；这进一步蕴含 $p_1 = q_j$。重排下标后不妨假设 $p_1 = q_1$，必要时等号两边互换，不妨假设 $a_1 \le b_1$。于是
$$
p_2^{a_2} \dots p_r^{a_r} = p_1^{b_1-a_1} q_2^{b_2}\dots q_s^{b_s}
$$
再次应用欧几里得引理可见 $p_1$ 不整除左式，故 $b_1 = a_1$。按此递归地论证，即得分解的唯一性。

---

# 算术基本定理的推论

- 对于任何素数 $p$ 和非零整数 $n$，我们有 $p\mid n$ 当且仅当 $p$ 在 $n$ 的素因子分解中出现，相应的指数 $a\in\Z_{\ge 1}$ 由以下性质唯一确定：$p^{a} \mid n$ 而 $p^{a+1}\not\mid n$，数论中的标准记法如下
    - 设 $p$ 为素数，我们以符号 $p^a \Div n$ 表达 $p^a \mid n$ 而 $p^{a+1} \not\mid n$。

- 考虑正整数 $n = \prod_{i=1}^{r} p_i^{a_i}$ 和 $m = \prod_{i=1}^{r} p_i^{b_i}$，其中 $p_1, \dots, p_r$ 是相异素数而 $a_i, b_i \in \Z_{\ge 0}$，则

    - $m \mid n \iff \forall i\in\set{1, \dots, r},\ b_i \le a_i.$

    - $\gcd(n, m) = \prod_{i=1}^{r} p_i^{\min\set{a_i, b_i}}, \qquad \lcm(n, m) = \prod_{i=1}^{r} p_i^{\max\set{a_i, b_i}}.$
    
        对于任意多个正整数的 $\gcd$ 和 $\lcm$ 也有类似结果。

---

# 有无穷多个素数

素数列 $2, 3, 5, 7, 11, \ldots$ 是数论关切的基本对象；这方面最古老也是最基础的结果是

<div class=proposition>

存在无穷多个素数。

</div>

**证明** $\quad$ 对任意一列素数 $p_1 < \cdots < p_n$，考虑
$$m := p_1 \cdots p_n + 1,$$
则 $m > 1$，而且它不被 $p_1,\dots, p_n$ 中任一个素数整除。因此 $m$ 的素因子分解中必有不同于 $p_1, \dots, p_n$ 的素数。


