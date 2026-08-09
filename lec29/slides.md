---
marp: true
math: mathjax
paginate: true
theme: lecture
title: 数论（二）
---

# 数论（二）

<div class=hidden>

$\newcommand{\Z}{\mathbb{Z}}$
$\newcommand{\R}{\mathbb{R}}$
$\DeclareMathOperator{\lcm}{lcm}$
$\DeclareMathOperator{\extgcd}{extgcd}$
$\newcommand{\Div}{\mathrel{\Vert}}$
$\newcommand{\floor}[1]{\left\lfloor #1 \right\rfloor}$
$\renewcommand{\%}{\mathbin{\text{\%}}}$

</div>

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

对于任何素数 $p$ 和非零整数 $n$，我们有 $p\mid n$ 当且仅当 $p$ 在 $n$ 的素因子分解中出现，相应的指数 $a\in\Z_{\ge 1}$ 由以下性质唯一确定：$p^{a} \mid n$ 而 $p^{a+1}\not\mid n$，数论中的标准记法如下
- 设 $p$ 为素数，我们以符号 $p^a \Div n$ 表达 $p^a \mid n$ 而 $p^{a+1} \not\mid n$。

---

考虑正整数 $n = \prod_{i=1}^{r} p_i^{a_i}$ 和 $m = \prod_{i=1}^{r} p_i^{b_i}$，其中 $p_1, \dots, p_r$ 是相异素数而 $a_i, b_i \in \Z_{\ge 0}$，则

- $m \mid n \iff \forall i\in\set{1, \dots, r},\ b_i \le a_i.$

- $\gcd(n, m) = \prod_{i=1}^{r} p_i^{\min\set{a_i, b_i}}, \qquad \lcm(n, m) = \prod_{i=1}^{r} p_i^{\max\set{a_i, b_i}}.$

    对于任意多个正整数的 $\gcd$ 和 $\lcm$ 也有类似结果。

---

定义 $d(n)$ 为正整数 $n$ 的正因数的个数。例如 $d(1) = 1$，$d(2) = 2$，$d(12) = 6$。

<div class=corollary>

设正整数 $n$ 的素因子分解是 $n = p_1^{a_1} \dots p_r^{a_r}$，那么 $d(n) = (a_1 + 1) \dots (a_r + 1)$。

</div>

---

# 例题：Product of Divisors

求 $A^B$ 的全部正因数的乘积能被 $A$ 整除的次数，模 $998244353$。

- $2 \le A \le 10^{12}$
- $0 \le B \le 10^{18}$


---

<div class=proposition>

$n$ 的正因数的乘积等于 $\sqrt{n}^{d(n)}$。

</div>

<div class=proof>

若 $x$ 是 $n$ 的因数且 $x \ne \sqrt{n}$，那么 $n/x$ 也是 $n$ 的因数。

</div>

---


# 有无穷多个素数

素数列 $2, 3, 5, 7, 11, \ldots$ 是数论关切的基本对象；这方面最古老也是最基础的结果是

<div class=proposition>

存在无穷多个素数。

</div>

**证明** $\quad$ 对任意一列素数 $p_1 < \cdots < p_n$，考虑
$$m := p_1 \cdots p_n + 1,$$
则 $m > 1$，而且它不被 $p_1,\dots, p_n$ 中任一个素数整除。因此 $m$ 的素因子分解中必有不同于 $p_1, \dots, p_n$ 的素数。



---

<div class=question>

给定正整数 $n$，找出不超过 $n$ 的全部素数。

</div>


---

# 素数筛

我们试图制造一个筛子。

我们把整数 $2, 3, \dots, n$ 放进筛子，启动筛子。筛子会把其中的合数全都筛出去，素数全都保留。

筛完之后，筛子里剩下的就是不超过 $n$ 的全部素数。

---

# 埃氏筛

```cpp
vector<int> get_primes(int n) {
    vector<int> primes;
    vector<bool> is_prime(n + 1, true);
    for (int i = 2; i <= n; i++)
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j <= n; j += i)
                is_prime[j] = false;
        }
    return primes;
}
```

时间复杂度：$O(n\log\log n)$。

---

# 埃氏筛的时间复杂度


---


# 线性筛



---




# Lucy_Hedgehog 算法

<div class=question>

给定正整数 $N$，求不超过 $N$ 的素数有多少个。$N \le 10^{11}$。

</div>

- 我们以 $p_i$ 表示第 $i$ 个素数。例如 $p_1 = 2$，$p_2 = 3$，$p_3 = 5$。
- 设 $x$ 是实数，以 $\pi(x)$ 表示不超过 $x$ 的素数的个数。
例如：$\pi(x) = 0$，若 $x < 2$；$\pi(5) = 3$；$\pi(10.5) = 4$；$\pi(50) = 15$。
我们要计算 $\pi(N)$。

---

## 计算 $\pi(N)$

<div class=definition>

对于实数 $x \ge 1$ 和正整数 $i$，定义 $F(x, i)$ 为从区间 $[2, x]$ 中去掉最小素因子 $\le p_i$ 的合数之后，剩下的整数的数量。此外，定义 $F(x, 0) := \floor{x} - 1$。

</div>

<div class=corollary>

设 $p_s$ 是不超过 $\sqrt{N}$ 的最大的素数，即 $s = \pi(\sqrt{N})$，那么 $\pi(N) = F(N, s)$。

</div>

---

<div class=proposition>

设 $n, i$ 是正整数。有以下递推式
$$
F(n,i) = \begin{cases} F(n, i-1), \quad & n < p_i^2, \\
F(n,i-1) - (F(\floor{n/p_i},i-1) - (i-1)), \quad & n \ge p_i^2.
\end{cases}
$$

</div>

**证明**：根据定义，我们有
$$ \begin{aligned} F(n,i) &= F(n, i-1) - 区间[2,n]上最小素因子是 p_i的合数的数量 \\
&= F(n,i-1) - 区间 [2,n/p_i]上最小素因子\ge p_i 的整数的数量 \\
\end{aligned}
$$
当 $n/p_i < p_i$，即 $n < p_i^2$ 时，区间 $[2,n/p_i]$ 上没有最小素因子 $\ge p_i$ 的整数，此时有
$$
F(n,i) = F(n,i-1).
$$
当 $n/p_i \ge p_i$，即 $n \ge p_i^2$ 时，区间 $[2,n/p_i]$ 上最小素因子 $\ge p  _i$ 的整数的个数是 
$$F(n/p_i, i-1) - (i-1).$$
显然有 $F(n/p_i, i-1) = F(\floor{n/p_i}, i-1)$。


---



<div class=lemma>

对于任意正整数 $a, b, c$ 有 $\floor{\floor{a/b}/c} = \floor{a/(bc)}$。

</div>

<div class=proof>

设 $a$ 用带余除法表作 $a = bq_1 + r_1$，其中 $0 \le r_1 < b$。再设 $q_1$ 用带余除法表作 $q_1 = cq_2 + r_2$，其中 $0 \le r_2 < c$。于是 $\floor{\floor{a/b}/c} = q_2$。

将 $q_1 = cq_2 + r_2$ 代入 $a = bq_1 + r_1$，得
$$ a = b(cq_2 + r_2) + r_1 = (bc)q_2 + (br_2 + r_1)$$
显然有 $br_2 + r_1 \ge 0$，我们只需要证明 $br_2 + r_1 < bc$。我们有
$$ br_2 + r_1 \le b(c-1) + (b-1) = bc - 1 < bc.  $$
</div>

---

## 计算 $F(N, s)$
 
<div class=question>

给定正整数 $N$。令 $s = \pi(\sqrt{N})$。根据递推式
$$
F(n,i) = \begin{cases} F(n, i-1), \quad & n < p_i^2, \\
F(n,i-1) - (F(\floor{n/p_i},i-1) - (i-1)), \quad & n \ge p_i^2.
\end{cases}
$$
计算 $F(N, s)$。

</div>

<div class=proposition>

我们需要计算的子问题形如 $F(\floor{N/d}, i)$，其中 $d$ 满足
- $1 \le d \le N$，
- $d$ 是 $p_{i+1}, \dots, p_{s}$ 中一些相异的素数的乘积。因而有 $d = 1$ 或 $d \ge p_{i+1}$。   
</div>

<!-- 我感觉这其实就是在应用容斥原理。这里值得深挖。 -->




---

<div class=definition>

设 $n$ 是正整数，定义集合
$$
Q_n := \set{\lfloor n/x \rfloor : x\in\Z, 1 \le x \le n}.
$$
</div>

例如
- $Q_{15} = \set{15, 7, 5, 3, 2, 1}$，
- $Q_{16} = \set{16, 8, 5, 4, 3, 2, 1}$，
- $Q_{17} = \set{17, 8, 5, 4, 3, 2, 1}$。

---

<div class=proposition>

设 $n$ 是正整数。令 $k = \floor{\sqrt{n}}$。那么集合 $Q_n$ 里有 $k + \floor{n/(k+1)}$ 个元素，从大到小排列是
$$\floor{n/1}, \floor{n/2}, \dots, \floor{n/k}, \floor{n/(k+1)}, \dots, 2, 1.$$
其中 $\floor{n/(k+1)}, \dots, 2, 1$ 是连续的。


</div>

在 $Q_n$ 里，我们把 $\floor{n/1}, \floor{n/2}, \dots, \floor{n/k}$ 称为**大值**，把 $\floor{n/(k+1)}, \dots, 2, 1$ 称为**小值**。

---

<div class=lemma>

设 $x_1, x_2, n$ 是正整数，$x_1 < x_2 \le \floor{\sqrt{n}} + 1$，那么 $\floor{n/x_1} > \floor{n/x_2}$。
</div>

<div class=proof>

由 $x_1 < x_2$ 可知 $n/x_1 > n/x_2$，因此 $\floor{n/x_1} \ge \floor{n/x_2}$。下面证明等号不能成立，从而得到严格大于。

假设 $y = \floor{n/x_1} = \floor{n/x_2}$，即 $y \le n/x_2$ 且 $n/x_1 < y+1$，即
$$yx_2 \le n < (y+1)x_1. \label{Eq:1}\tag{1}$$
于是我们有 $yx_2 < (y+1)x_1$，即 $y(x_2 - x_1) < x_1$，又 $x_2 - x_1 \ge 1$，所以
$$y < x_1.$$

另一方面，根据题设，有 $x_1 \le \floor{\sqrt{n}}$，所以 $x_1^2 \le n$；结合 $\eqref{Eq:1}$ 式的右边 $n < (y+1)x_1$，得 $x_1^2 < (y+1)x_1$，所以 $x_1 < y+1$，即
$$y \ge x_1.$$

所以 $y$ 不存在。
</div>

---

<div class=corollary>

设 $n,d, x$ 是正整数，$1 \le d \le \floor{\sqrt{n}}$。那么
$$ \floor{n/x} = \floor{n/d} \iff x = d. $$

</div>

也就是说，对于 $Q_n$ 里的每个大值，若把它表作 $\floor{n/d}$，那么 $d$ 是唯一的。



---

<div class=lemma>

设 $n, x$ 是正整数，$1 \le x \le \sqrt{n}$。那么 $\floor{n/\floor{n/x}} = x$。

</div>

<div class=proof>

令 $y = \floor{n/x}$，我们证明 $\floor{n/y} = x$。

根据上一个命题，有 $\floor{n/x} > \floor{n/(x+1)}$，即 $y > \floor{n/(x+1)}$，所以
$$  y > n/(x+1).  $$
又 $y = \floor{n/x} \le n/x$，所以
$$ n/(x+1) < y \le n/x.  $$
即
$$ x \le n/y < x+1,$$
即 $\floor{n/y} = x$.

</div>

---

<div class=corollary>

$\set{1, 2, \dots, \floor{\sqrt{n}}} \subseteq Q_n$.

</div>


<div class=corollary>

令 $k = \floor{\sqrt{n}}$。$Q_n$ 里的元素从小到大排列是
$$1, 2, \dots, k-1, k, \floor{n/k}, \floor{n/(k-1)}, \dots,  \floor{n/2}, \floor{n/1}.$$
其中，$k$ 可能等于 $\floor{n/k}$。

<div>


---

```cpp
long long prime_count(long long n) {
    const int k = (int) sqrt(n);
    vector<long long> v; // n, n/2, n/3, ..., n
    for (int i = 1; i <= k; i++)
        v.push_back(n / i);
    for (int i = n / (k + 1); i >= 1; i--)
        v.push_back(i);
    // 对于 i = 1, 2, ..., k+1 有 n/i == v[i-1]。
    // 对于 i = 1, 2, ..., k 还有，i 是唯一的满足 n/d == n/i 的正整数 d。我们称这些值为大值。
    const int m = (int) v.size();
    vector<long long> f(m);
    for (int i = 0; i < m; i++)
        f[i] = v[i] - 1;
    
    auto [p, lpf] = get_primes(k);
    const int s = (int) p.size();
    for (int i = 0; i < s; i++) {
        f[0] -= f[p[i] - 1] - i;
        if (i == s - 1) break;
        const long long L = (long long) p[i] * p[i];
        const int lim = k / p[i];
        for (int j = p[i + 1] - 1; j < m && v[j] >= L; j++) {
            if (j < k && lpf[j + 1] < p[i + 1]) continue;
            if (j + 1 <= lim) {
                f[j] -= f[(j + 1) * p[i] - 1] - i;
            } else { // v[j] / p[i] <= k
                f[j] -= f[m - v[j] / p[i]] - i;
            }
        }
    }
    return f[0];
}
```

时间：$O({n^{3/4} \over \log n})$。






---

<div class=proposition>

设 $n$ 是正整数。对于任意正整数 $t$，定义 $g_n(t)$ 为 $Q_n$ 中大于等于 $t$ 的元素的个数，那么
$$
  g_n(t) = \begin{cases}
  k +  \floor{n/(k+1)} - t + 1, & \quad t \le k, \\
  \floor{n/t}, & \quad t \ge k + 1.
  \end{cases}
  $$

<div>

---

<div class=proposition>

设 $n$ 是正整数。若 $m \in Q_n$ 则 $Q_m \subseteq Q_n$。

</div>

---


<div class=proposition>

设 $n, x, y$ 是正整数，$y = \floor{n/x} \ge \sqrt{n}$。那么 $x = \floor{n/y}$。

</div>

<div class=proof>

题设 $y = \floor{n/x}$，即 $y \le n/x < y + 1$，即
$$xy \le n < xy + x \tag{1}\label{E:1}$$
又因为 $y \ge \sqrt{n}$，所以 $y^2 \ge n$。于是有 $xy \le n \le y^2$，由于 $y > 0$，有
$$x \le y \tag{2}\label{E:2}$$ 
把 $\eqref{E:1}$ 和 $\eqref{E:2}$ 结合，得 $xy \le n < xy + y$，即
$$x \le n/y < x+1$$
即 $\floor{n/y} = x$，命题得证。
</div>







---

# 积性函数的前缀和



