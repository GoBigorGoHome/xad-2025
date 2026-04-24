---
marp: true
math: mathjax
paginate: true
theme: lecture
title: 求和
---

# 求和

$\DeclareMathOperator{\lcm}{lcm}$
$\DeclarePairedDelimiter{\floor}{\lfloor}{\rfloor}$
$\DeclareMathOperator{\bit}{bit}$
$\newcommand{\bitand}{\mathbin{\&}}$
$\newcommand{\bitor}{\mathbin{\mathrm{or}}}$

---

# 内容

- 等比数列求和及其扩展
- 数论分块
- 对倍数求和
- 对子集求和

---

# 等比数列的和

<div class=question>

给定整数 $A$，正整数 $N, M$，求 $1 + A + A^2 + \dots + A^{N-1}$，模 $M$。
</div>

---

<div class=definition>

对于非负整数 $n$，考虑多项式 $f_n(x) := 1 + x + x^2 + \dots + x^{n-1}$。
特别的，$f_0(x) = 0$。
</div>

我们要求的就是 $f_N(A) \bmod M$。
* $f_N(A) = {A^{N} - 1 \over A - 1}$，如果 $(A - 1)$ 和 $M$ 互素，那么 $(A - 1)$ 在模 $M$ 下有乘法逆元。
* 以下我们考虑一般情况，即 $(A - 1)$ 和 $M$ 未必互素。


---

<div class=topic-box>

$$
f_n(x) = 1 + x + x^2 + \dots + x^{n-1}
$$

</div>

当 $n$ 是偶数时，我们把偶次项和奇次项分开，写成
$$
f_n(x) = (1 + x^2 + x^4 + \dots + x^{n-2}) + (x + x^3 + x^5 + \dots + x^{n-1})
$$

---

注意到
$$
1 + x^2 + x^4 + \dots + x^{n-2} = 1 + x^2 + (x^2)^2 +  \dots + (x^2)^{n/2-1} = f_{n/2}(x^2)
$$
而
$$
x + x^3 + x^5 + \dots + x^{n-1} = x \cdot (1 + x^2 + x^4 + \dots + x^{n-2}) = x \cdot f_{n/2}(x^2)
$$
于是有
<div class=topic-box>

$$f_n(x) = f_{n/2}(x^2) + x \cdot f_{n/2}(x^2), \quad \text{$n$ 是偶数.}$$
</div>

当 $n$ 是奇数时，
$$
f_n(x) = 1 + x\cdot(1 + x + \dots + x^{n-2}) = 1 + x \cdot f_{n-1}(x).
$$

---

<div class=proposition>

$f_0(x) = 0$。对于 $n \ge 1$，有
$$
f_n(x) = 
\begin{cases}
(1 + x) f_{n/2}(x^2), \quad &\text{$n$ 是偶数}, \\
1 + x \cdot f_{n-1}(x), \quad & \text{$n$ 是奇数}.

\end{cases}
$$
</div>

* 这跟计算 $x^n$ 的快速幂算法有点像。

---

# 例题 Geometric Progression

[abc293_e](https://atcoder.jp/contests/abc293/tasks/abc293_e)

给定整数 $A, X, M$，求 $\sum_{i=0}^{X-1} A^i$，模 $M$。

- $1 \le A, M \le 10^9$
- $1 \le X \le 10^{12}$

---

## 递归写法


```cpp
int mod;

int power_sum(long long x, long long n) {
    if (n == 0)
        return 0;

    if (n & 1)
        return (1 + x * power_sum(x, n - 1)) % mod;

    return (1 + x) * power_sum(x * x % mod, n >> 1) % mod;
}
```

---

## 非递归写法

```cpp
int power_sum(long long x, long long n, int mod) {
    long long ans = 0;
    long long prod = 1;
    // 答案 == ans + prod * power_sum(x, n)
    while (n) {
        if (n & 1) {
            ans = (ans + prod) % mod;
            prod = (prod * x) % mod;
        }
        prod = prod * (1 + x) % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ans;
}
```

---

# 习题 LCM 111

[arc050_c](https://atcoder.jp/contests/arc050/tasks/arc050_c)

整数 $x$ 的十进制写法是 $A$ 个 $1$，整数 $y$ 的十进制写法是 $B$ 个 $1$。求 $x$ 和 $y$ 的最小公倍数除以 $M$ 的余数。

- $1 \le A, B \le 10^{18}$
- $2 \le M \le 10^9$

---

# 分析

我们知道 $\lcm(x, y) = {xy\over \gcd(x, y)}$，考虑 $\gcd(x, y)$。

我们把十进制写法是 $n$ 个 $1$ 的整数记作 $f(n)$，那么 $x = f(A), y = f(B)$。

注意到
$$\gcd(f(A), f(B)) = f(\gcd(A, B)).$$


设 $d = \gcd(A, B)$，又设 $A = kd$。

注意到
$$f(kd) / f(d) = 1 + 10^d + (10^d)^2 + \dots + (10^d)^{k-1}.$$

所以问题就归结为计算两个等比数列的和。


---

```cpp
int power(int x, long long n, int mod) {
    int ans = 1;
    while (n > 0) {
        if (n & 1)
            ans = (long long) ans * x % mod;
        x = (long long) x * x % mod;
        n >>= 1;
    }
    return ans;
}

int power_sum(int x, long long n, int mod) {
   int ans = 0;
   int prod = 1;
   while (n > 0) {
        if (n & 1) {
            ans = (ans + prod) % mod;
            prod = (long long) prod * x % mod;
        }
        prod = (long long) prod * (1 + x) % mod;
        x = (long long) x * x % mod;
        n >>= 1;
   }
   return ans;
}

int main() {
    long long a, b;
    int m;
    cin >> a >> b >> m;
    long long d = __gcd(a, b);
    int ans = (long long) power_sum(power(10, d, m), a / d, m) * power_sum(10, b, m) % m;
    cout << ans << '\n';
}
```

---

# 扩展

<div class=question>

给定非负整数 $N, K$，整数 $A$ 和正整数 $M$，求 $\sum_{i=0}^{N-1} i^K A^i$，模 $M$。

</div>

---

对于非负整数 $n, k$，考虑多项式 $f_{n}^{k}(x) = \sum_{i=0}^{n-1} i^k x^i$。

我们要求的就是 $f_N^K(A) \bmod M$。

---

<div class=topic-box>

$$
f_{n}^{k}(x) = \sum_{i=0}^{n-1} i^k x^i.
$$

</div>

当 $n$ 是偶数时，我们把偶次项和奇次项分开，写成
$$
f_n^k(x) = \sum_{i=0}^{n/2-1} (2i)^k x^{2i}  +  \sum_{i=0}^{n/2-1} (2i + 1)^k x^{2i + 1}
$$

---

<div class=columns>
<div>

偶次项

$$
\begin{aligned}
&\sum_{i=0}^{n/2-1} (2i)^k x^{2i} \\ 
&= 2^k \cdot \sum_{i=0}^{n/2-1} i^k (x^2)^i  \\
&= 2^k \cdot f_{n/2}^k(x^2)
\end{aligned}
$$

</div>

<div>

奇次项


$$
\begin{aligned}
&\sum_{i=0}^{n/2-1} (2i + 1)^k x^{2i + 1} \\ 
&= x \sum_{i=0}^{n/2-1} (2i + 1)^k x^{2i} \\
&= x  \sum_{i=0}^{n/2-1} \sum_{t=0}^{k}{k\choose t}(2i)^t x^{2i} \\
&= x \sum_{t = 0}^{k} {k \choose t} 2^{t} \sum_{i=0}^{n/2-1} i^{t} (x^2)^i \\
&=x \sum_{t = 0}^{k} {k \choose t} 2^{t} \cdot f_{n/2}^{t}(x^2)
\end{aligned}
$$
</div>

---

<div class=topic-box>

当 $n$ 是偶数时，有

$$
\begin{aligned}

f_{n}^{k}(x) &= 2^k \cdot f_{n/2}^k(x^2) + x \sum_{t = 0}^{k} {k \choose t} 2^{t} \cdot f_{n/2}^{t}(x^2) \\

&= 2^k (1 + x) f_{n/2}^{k}(x^2) + x \sum_{t = 0}^{k-1} {k \choose t} 2^{t} \cdot f_{n/2}^{t}(x^2)

\end{aligned}
$$


</div>


---


<div class=topic-box>

$$
f_{n}^{k}(x) = \sum_{i=0}^{n-1} i^k x^i.
$$

</div>

当 $n$ 是奇数时

<div class=columns>
<div>

$$
\begin{aligned}
f_n^k(x) &= 0^{k}  +  \sum_{i=1}^{n-1} i^k x^i \\
&= 0^{k}  +  \sum_{i=0}^{n-2} (i+1)^k x^{i+1} \\
&= 0^{k}  +  x \sum_{i=0}^{n-2} (i+1)^k x^{i}

\end{aligned}
$$

</div>

<div>

$$
\begin{aligned}
&= 0^{k}  +  x \sum_{i=0}^{n-2} \sum_{t = 0}^{k} {k \choose t} i^t x^{i} \\
&= 0^k + x \sum_{t=0}^{k} {k \choose t} \sum_{i=0}^{n-2}  i^tx^i \\
&= 0^k + x \sum_{t=0}^{k} {k \choose t} f_{n-1}^{t}(x)
\end{aligned}
$$

</div>

</div>


---


<div class=proposition>

$f_0^{k}(x) = 0$。

对于 $n \ge 1$，有
$$
f_n^{k}(x) = 
\begin{cases}

2^k (1 + x) f_{n/2}^{k}(x^2) + x \sum_{t = 0}^{k-1} {k \choose t} 2^{t} \cdot f_{n/2}^{t}(x^2), \quad & \text{$n$ 是偶数} \\

0^k + x \sum_{t=0}^{k} {k \choose t} f_{n-1}^{t}(x), \quad & \text{$n$ 是奇数}

\end{cases}

$$

</div>


---


$$
f_n^{k}(x) = 
\begin{cases}
2^k (1 + x) f_{n/2}^{k}(x^2) + x \sum_{t = 0}^{k-1} {k \choose t} 2^{t} \cdot f_{n/2}^{t}(x^2), \quad & \text{$n$ 是偶数} \\

0^k + x \sum_{t=0}^{k} {k \choose t} f_{n-1}^{t}(x), \quad & \text{$n$ 是奇数}
\end{cases}
$$
我们可以把上面的式子看作一个**递推式**：

- 若 $n$ 是偶数，我们由 $f_{n/2}^0(x^2), f_{n/2}^{1}(x^2), \dots, f_{n/2}^{k}(x^2)$ 推出 $f_{n}^{k}(x)$。
- 若 $n$ 是奇数，我们由 $f_{n-1}^0(x), f_{n-1}^{1}(x), \dots, f_{n-1}^{k}(x)$ 推出 $f_{n}^{k}(x)$。

更进一步，我们也可以说
- 若 $n$ 是偶数，我们由 $f_{n/2}^0(x^2), f_{n/2}^{1}(x^2), \dots, f_{n/2}^{k}(x^2)$ 推出 $f_{n}^{0}(x), f_{n}^{1}(x), \dots, f_{n}^{k}(x)$。
- 若 $n$ 是奇数，我们由 $f_{n-1}^0(x), f_{n-1}^{1}(x), \dots, f_{n-1}^{k}(x)$ 推出 $f_{n}^{0}(x), f_{n}^{1}(x), \dots, f_{n}^{k}(x)$。

总之，利用上面的式子，我们可以在 $O(k^2)$ 的时间内，由一个长为 $k+1$ 的序列推出另一个长为 $k+1$ 的序列。


---

# 例题 数列求和

[洛谷P4948](https://www.luogu.com.cn/problem/P4948)

给定整数 $n, a, k$，求 $\sum_{i=1}^{n} i^k a^i$，模 $10^9 + 7$。

- $1 \le n \le 10^{18}$
- $1 \le a \le 10^9$
- $0 \le k \le 2000$

---

## 递归写法

```cpp
const int mod = 1e9 + 7;
const int maxk = 2005;
int C[maxk][maxk]; // 组合数
int p2[maxk]; // p2[i]：2的i次方
int k;

vector<long long> solve(int x, long long n) { //返回一个长度是 k + 1 的数组
    vector<long long> ans(k + 1);
    if (n == 0)
        return ans;
    if (n & 1) {
        auto f = solve(x, n - 1);
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= i; j++)
                ans[i] += C[i][j] * f[j] % mod;
            ans[i] = ans[i] % mod * x;
        }
        ans[0]++;
        for (int i = 0; i <= k; i++)
            ans[i] %= mod;
        return ans;
    }
    auto f = solve((long long) x * x % mod, n / 2);
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < i; j++)
            ans[i] += f[j] * C[i][j] % mod * p2[j] % mod;
        ans[i] = (ans[i] % mod * x + (f[i] * p2[i] % mod * (1 + x) % mod)) % mod;
    }
    return ans;
}
```

---

```cpp
int main() {
    long long n;
    int a;
    cin >> n >> a >> k;
    for (int i = 0; i <= k; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }

    p2[0] = 1;
    for (int i = 1; i <= k; i++)
        p2[i] = p2[i - 1] * 2 % mod;

    long long ans = solve(a, n + 1)[k];

    if (k == 0) {
        ans--;
        if (ans < 0)
            ans += mod;
    }
    cout << ans << '\n';
}
```

---

## 非递归写法

仿照前面的等比数列求和的非递归写法，我们维护一列系数 $w_0, w_1, \dots, w_K$ 以及三个变量 $s$、$x$、$n$，使得等式
$$
f_{N}^{K}(A) = s + \sum_{i=0}^{K} w_i \cdot f_{n}^{i}(x)
$$
总是成立。

一开始 $s = 0$，$x= A$，$n = N$，$w_K = 1$，$w_0, w_1, \dots, w_{K-1}$ 都是 $0$。

最后，$n$ 变成 $0$ 而 $s$ 就是所求的 $f_N^K(A)$。

---

当 $n$ 是奇数时，我们有
$$
\begin{aligned}
s + \sum_{i=0}^{K} w_i \cdot f_{n}^{i}(x) &= s + \sum_{i=0}^{K} w_i \cdot (0^i + x\sum_{j=0}^{i} {i \choose j} f_{n-1}^{j}(x)) \\
&= s + w_0 + \sum_{i=0}^{K} w_i \cdot (x\sum_{j=0}^{i} {i\choose j} f_{n-1}^{j}(x)) \\
&= s + w_0 + x\sum_{i=0}^{K} w_i \sum_{j=0}^{i} {i\choose j} f_{n-1}^{j}(x) \\
&= s + w_0 + x\sum_{j=0}^{K} f_{n-1}^{j} \sum_{i=j}^{K} w_i {i \choose j}\\
\end{aligned}
$$
<div class=topic-box>

$n \gets n - 1$；$x$ 不变；$s \gets s + w_0$；$w_j \gets x\sum_{i=j}^{K} w_i {i \choose j}$。

</div>

---

当 $n$ 是偶数时，我们有
$$
\begin{aligned}
s + \sum_{i=0}^{K} w_i \cdot f_{n}^{i}(x) &= s + \sum_{i=0}^{K} w_i \cdot(2^i \cdot f_{n/2}^{i}(x^2) + x \sum_{j = 0}^{i} {i \choose j} 2^{j} \cdot f_{n/2}^{j}(x^2)) \\

&= s + \sum_{j=0}^{K} f_{n/2}^{j}(x^2) \cdot 2^j( w_j + x \sum_{i = j}^{K} {i \choose j} w_i) \\
\end{aligned}
$$

<div class=topic-box>

$n \gets n / 2$；$s$ 不变；$w_j \gets 2^j( w_j + x \sum_{i = j}^{K} {i \choose j} w_i)$；$x\gets x^2$。

</div>

---

```cpp
const int mod = 1e9 + 7;
const int maxk = 2005;
int C[maxk][maxk]; // 组合数
int p2[maxk]; // 二的幂

int solve(int x, long long n, int k) {
    vector<long long> w(k + 1);
    w[k] = 1;
    long long s = 0;
    while (n > 0) {
        if (n & 1) {
            s += w[0];
            for (int i = 0; i <= k; i++) {
                for (int j = i + 1; j <= k; j++)
                    w[i] += w[j] * C[j][i] % mod;
                w[i] = w[i] % mod * x % mod;
            }
        }
        for (int i = 0; i <= k; i++) {
            long long t = 0;
            for (int j = i; j <= k; j++)
                t += C[j][i] * w[j] % mod;
            w[i] = (w[i] + t % mod * x) % mod * p2[i] % mod;
        }
        x = (long long) x * x % mod;
        n >>= 1;
    }
    return s % mod;
}

int main() {
    long long n;
    int a, k;
    cin >> n >> a >> k;

    // 计算组合数和2的幂

    int ans = solve(a, n + 1, k);
    if (k == 0) {
        ans--;
        if (ans < 0) ans += mod;
    }
    cout << ans << '\n';
}
```

---

# 例题 数学作业

对于正整数 $n$，定义 Concatenate($n$) 为，把 $1, 2, \dots, n$ 依次连接起来得到的数。

例如 Concatenate($13$) = $12345678910111213$。

给定正整数 $N, M$，求 Concatenate($N$) $\bmod M$。

- $1 \le N \le 10^{18}$，$1 \le M \le 10^9$。


---

对于正整数 $l, r$（$l \le r$），我们把依次连接 $l, l + 1, \dots, r$ 所得的数记作 $f(l, r)$。那么 Concatenate($n$) 就是 $f(1, n)$。

如果 $l, r$ 在十进制下都是 $k$ 位数，那么 $f(l, r)$ 可表为
$$
\sum_{i=l}^{r} i \cdot 10^{k(r - i)}.
$$
做指标变换，令 $j = r - i$，把上式写成
$$
\sum_{j=0}^{r - l} (r - j)\cdot 10^{kj}  = r \sum_{j=0}^{r-l} (10^k)^j - \sum_{j=0}^{r-l} j \cdot (10^k)^j.
$$

---

## 模板

```cpp
int k_power_sum(int x, long long n, int k, int mod) {
    vector<vector<int>> C(k + 1, vector<int>(k + 1));
    for (int i = 0; i <= k; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    vector<int> p2(k + 1);
    p2[0] = 1;
    for (int i = 1; i <= k; i++)
        p2[i] = p2[i - 1] * 2 % mod;

    vector<long long> w(k + 1);
    w[k] = 1;
    long long s = 0;
    // 循环不变量：答案 == ans + \sum_{i=0..k} w[i] * f_{n,k}(x)
    while (n > 0) {
        if (n & 1) {
            s += w[0];
            for (int i = 0; i <= k; i++) {
                for (int j = i + 1; j <= k; j++)
                    w[i] += w[j] * C[j][i] % mod;
                w[i] = w[i] % mod * x % mod;
            }
        }
        for (int i = 0; i <= k; i++) {
            long long t = 0;
            for (int j = i; j <= k; j++)
                t += C[j][i] * w[j] % mod;
            w[i] = (w[i] + t % mod * x) % mod * p2[i] % mod;
        }
        x = (long long) x * x % mod;
        n >>= 1;
    }
    return s % mod;
}
```

---

```cpp
int power(long long x, unsigned long long n, int mod) {
    long long ans = 1;
    while (n > 0) {
        if (n & 1)
            ans = ans * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return (int) ans;
}

int main() {
    unsigned long long n;
    int m;
    cin >> n >> m;
    n++;
    long long ans = 0;
    int len = 1;
    for (unsigned long long l = 1; l < n; l *= 10) {
        unsigned long long r = min(l * 10, n);
        long long t = (r - 1) % m * k_power_sum(l * 10 % m, r - l, 0, m) % m - k_power_sum(l * 10 % m, r - l, 1, m);
        ans = ans * power(10, len * (r - l), m) % m + t;
        len++;
    }
    ans %= m;
    if (ans < 0)
        ans += m;
    cout << ans << '\n';
}
```

---


# 数论分块

<div class=question>

计算 $\sum_{i=1}^{N} f(\lfloor N/i \rfloor)$.


</div>



---

## 分析

- 当 $1 \le i \le \floor{\sqrt{N}}$ 时，$\floor{N/i}$ 最多取 $\floor{\sqrt{N}}$ 个值。
这时 $\floor{N/i}$ 确实取 $\floor{\sqrt{N}}$ 个值。当 $i + 1 \le \sqrt{N}$ 时，有
    $$
    N/i - N/(i+1) = N/(i(i+1)) > 1.
    $$
    所以
    $$\floor{N/i} > \floor{N/(i + 1)}.$$
- 当 $\floor{\sqrt{N}} + 1 \le i \le N$ 时，有 $1 \le N/i < \sqrt{N}$。此时 $\floor{N/i}$ 最多取 $\floor{\sqrt{N}}$ 个值。

综上可得 $\floor{N/i}$ 的值不超过 $2\floor{\sqrt{N}}$ 个。

---

## 例子

$N = 15$
$$
\begin{array}{|c|c|}
\hline
i & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & \dots & 15\\
\hline
\floor{N/i} & 15 & 7 & 5 & 3 & 3 & 2 & 2 & 1 & \dots & 1\\
\hline
\end{array}
$$

$N=16$
$$
\begin{array}{|c|c|}
\hline
i & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & 9 & \dots & 16\\
\hline
\floor{N/i} & 16 & 8 & 5 & 4 & 3 & 2 & 2 & 2 & 1 & \dots & 1\\
\hline
\end{array}
$$

---

<div class=proposition>

对于正整数 $n$ 有 $\floor{n/\floor{\sqrt{n}}} > \floor{n/(\floor{\sqrt{n}} + 1)}$.
</div>

---


<div class=proof>

设 $k = \floor{\sqrt{n}}$，下面我们证明 $\floor{n/k} \ne \floor{n/(k+1)}$。我们有
$$\begin{equation} 
k^2 \le n < (k + 1)^2. \tag{$\star$}
\end{equation} 
$$
把 $(\star)$ 写成 $k^2 \le n \le k^2 + 2k$，可见 $\floor{n/ k}$ 可能是 $k$，$k + 1$ 或 $k + 2$。
而把 $(\star)$ 写成 $k^2 - 1 < n < (k + 1)^2$，又可见 $\floor{n/(k+1)}$ 可能是 $k-1$ 或 $k$。如果 $\floor{n/ k} = \floor{n/(k+1)}$，那只能是二者都等于 $k$。

另一方面 
$$
\floor{n/(k+1)} = k \implies n/(k+1) \ge k \implies n/k \ge k+1 \implies \floor{n/k} \ge k+1.
$$
所以 $\floor{n/k}$ 和 $\floor{n/(k+1)}$ 都等于 $k$ 是不可能的。

</div>

---

```cpp
long long ans = 0;
for (int i = 1; i <= N; ) {
    int j = N / i;
    int ni = N / j + 1;
    ans += (ni - i) * f(j);
    i = ni;
}
```

---

<div class=question>

计算 $\sum_{i=1}^{N} i \cdot f(\lfloor N/i \rfloor)$.


</div>

---

```cpp
long long ans = 0;
for (int i = 1; i <= N; ) {
    int j = N / i;
    int ni = N / j + 1;
    ans += (i + ni - 1) * (ni - i) / 2 * f(j);
    i = ni;
}
```

---

# 例题 余数求和

[洛谷P2261](https://www.luogu.com.cn/problem/P2261)

求 $\sum_{i=1}^{n} k \bmod i$.

- $1 \le n, k \le 10^9$.

---

## 分析

注意到 
$$
k \bmod i = k - i \cdot \floor{k / i},
$$
于是
$$
\sum_{i=1}^{n} k \bmod i = \sum_{i=1}^{n} k - i \cdot \floor{k / i} = nk - \sum_{i=1}^{n} i \cdot \floor{k / i}.
$$

---

```cpp
int main() {
    int n, k;
    cin >> n >> k;
    long long ans = (long long) n * k;
    for (int i = 1; i <= n;) {
        if (i > k)
            break;
        int j = k / i;
        int ni = min(n, k / j) + 1;
        ans -= (long long) (i + ni - 1) * (ni - i) / 2 * j;
        i = ni;
    }
    cout << ans - sum << '\n';
}
```

---

# 扩展

<div class=question>

给定二元函数 $f$ 和正整数 $n, m$ 满足 $n \le m \le 10^9$。计算
$$\sum_{i=1}^{n} f(\floor{n/i}, \floor{m/i}).$$

</div>

---

# 对倍数求和

---

# 例题 Couting Rhyme

[codeforces 1884D](https://codeforces.com/problemset/problem/1884/D)

给你整数序列 $a_1, a_2, \dots, a_n$。
求满足下列条件的整数对 $(i, j)$ 的数量。
- $1 \le i < j \le n$
- 不存在整数 $k$（$1 \le k \le n$）使得 $a_k$ 整除 $a_i$ 且 $a_k$ 整除 $a_j$。


$1 \le n \le 10^6$，$1 \le a_i \le n$。
多组数据，$n$ 的总和不超过 $10^6$。

---

对每个 $d = 1, \dots, n$ 定义
- $f(d) \coloneqq$ 满足 $\gcd(a_i, a_j) = d$ 的 $(i, j)$ 有多少对。

对每个 $x = 1, \dots, n$ 定义
- $\mathrm{div}(x) \coloneqq$ $a_1, \dots, a_n$ 中有多少项是 $x$ 的因数。

答案就是
$$
\sum_{d = 1}^{n} f(d) [\mathrm{div(d) = 0}].
$$

---

现在考虑如何计算 $f(d)$。
先放松限制，对每个 $d = 1, \dots, n$ 定义
- $g(d) \coloneqq$ 满足 $d \mid a_i$ 且 $d \mid a_j$ 的 $i, j$ 有多少对。

也就是说，把条件从「$d$ 是 $a_i$ 和 $a_j$ 的**最大公因数**」放松为「$d$ 是 $a_i$ 和 $a_j$ 的**公因数**」。

我们有
$$
f(d) = g(d) - \sum_{k=2}^{\floor{n/d}} f(k\cdot d).
$$

---

对每个 $d = 1, \dots, n$ 定义
- $\mathrm{mul}(d)\coloneqq$ $a_1, \dots, a_n$ 中有多少项是 $d$ 的倍数。

于是有
$$
g(d) = {\mathrm{mul}(d) \choose 2}.
$$

---

对每个 $x = 1, \dots, n$ 定义
- $\mathrm{cnt}(x) \coloneqq$ $a_1, \dots, a_n$ 中有多少项等于 $x$。

那么
$$
\mathrm{mul}(x) = \sum_{k=1}^{\floor{n/x}} \mathrm{cnt}(k\cdot x).
$$
而
$$
\mathrm{div}(x) = \sum_{d \mid x} \mathrm{cnt}(d).
$$
二者都可以通过枚举倍数来计算。

---

```cpp
int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> cnt(n + 1);
        vector<int> mul(n + 1);
        vector<int> div(n + 1);
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            cnt[x]++;
        }
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j += i)
                mul[i] += cnt[j];

        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j += i)
                div[j] += cnt[i];

        vector<long long> f(n + 1);

        long long ans = 0;
        for (int  i = n; i >= 1; i--) {
            f[i] = (long long) mul[i] * (mul[i] - 1) / 2;
            for (int j = 2 * i; j <= n; j += i)
                f[i] -= f[j];
            if (div[i] == 0)
                ans += f[i];
        }
        cout << ans << '\n';
    }
}
```

---

我们知道 
$$\sum_{i=1}^{n} {1\over i} = O(\ln n).$$
所以上述解法的时间是 $O(n \log n)$。

---

# 例题 GCD 卷积

https://judge.yosupo.jp/problem/gcd_convolution

给定整数序列 $a_1,\dots, a_N$ 和 $b_1, \dots, b_N$，计算序列 $c_1, \dots, c_N$，定义如下
$$
c_k = (\sum_{\gcd(i, j) = k} a_i b_j) \bmod 998244353.
$$

- $1 \le N \le 10^6$
- $0 \le a_i, b_i < 998244353$

---

一如上一题的思路，我们有

$$
c_k = \sum_{k 是 i,j 的公因数} a_i b_j - \sum_{t = 2}^{\floor{n/k}} c_{tk}.
$$
而
$$
\sum_{k 是 i,j 的公因数} a_i b_j = (\sum_{k \mid i} a_i) (\sum_{k \mid j} b_j) = (\sum_{t=1}^{\floor{n/k}}a_{tk}) (\sum_{t=1}^{\floor{n/k}} b_{tk}).
$$

---

```cpp
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    const int mod = 998244353;
    vector<long long> c(n + 1);
    for (int i = n; i >= 1; i--) {
        long long sa = 0, sb = 0;
        for (int j = i; j <= n; j += i) {
            sa += a[j];
            sb += b[j];
        }
        c[i] = (sa % mod) * (sb % mod);
        for (int j = 2 * i; j <= n; j += i) {
            c[i] -= c[j];
        }
        c[i] %= mod;
        if (c[i] < 0)
            c[i] += mod;
    }
    for (int i = 1; i <= n; i++)
        cout << c[i] << ' ';
    cout << '\n';
}
```

---

# 例题 LCMs

[agc038c](https://atcoder.jp/contests/agc038/tasks/agc038_c)

给定长为 $N$ 的整数序列 $A_0, A_1, \dots, A_{N-1}$。求
$$
\sum_{i=0}^{N-2} \sum_{j=i+1}^{N-1} \lcm(A_i, A_j).
$$
$\lcm(a, b)$ 表示 $a$ 和 $b$ 的最小公倍数。

由于答案可能很大，输出它除以 $998244353$ 的余数。

- $1 \le N \le 200000$
- $1 \le A_i \le 10^6$

---

我们知道 $\lcm(A_i, A_j) = {A_i A_j \over \gcd(A_i, A_j)}$。

对于每个 $d = 1, 2, \dots, 10^6$，我们计算
$$
f(d) := \sum_{\substack{0 \le i < j \le N-1 \\ \gcd(A_i, A_j) = d}} A_i A_j.
$$
那么答案就是
$$
\sum_{d = 1}^{10^6} f(d) / d.
$$
一如前两题的套路，我们有
$$
f(d) = \sum_{\substack{0 \le i < j \le N-1 \\ d \mid A_i\ 且\ d \mid A_j}} A_i A_j - \sum_{t=2}^{\floor{10^6/d}} f(td).
$$

---

现在考虑如何计算 $\sum_{\substack{0 \le i < j \le N-1 \\ d \mid A_i\ 且\ d \mid A_j}} A_i A_j$。有不止一种计算方法。
不难看出它等于
$$
{1\over 2}(\sum_{\substack{0 \le i,j \le N-1 \\ d \mid A_i\ 且\ d \mid A_j}} A_i A_j - \sum_{\substack{0 \le i \le N-1 \\ d \mid A_i}} A_i^2)
$$
即
$$
{1\over 2}((\sum_{\substack{0 \le i \le N-1 \\ d \mid A_i}} A_i)^2 - \sum_{\substack{0 \le i \le N-1 \\ d \mid A_i}} A_i^2).
$$

---

对每个 $x = 1, 2, \dots, 10^6$，定义
- $\mathrm{cnt}(x)$：$A_0, \dots, A_{N-1}$ 中有多少项等于 $x$。

那么
$$
\sum_{\substack{0 \le i \le N-1 \\ d \mid A_i}} A_i = \sum_{\substack{1 \le x \le 10^6 \\ d \mid x}} \mathrm{cnt}(x) \cdot x,
$$
而
$$
\sum_{\substack{0 \le i \le N-1 \\ d \mid A_i}} A_i^2 = \sum_{\substack{1 \le x \le 10^6 \\ d \mid x}} \mathrm{cnt}(x) \cdot x^2.
$$

---

```cpp
int main() {
    int n; cin >> n;
    const int maxv = 1e6;
    vector<int> cnt(maxv + 1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }
    const int mod = 998244353;
    vector<int> inv(maxv + 1); //递推法计算逆元
    inv[1] = 1;
    for (int i = 2; i <= maxv; i++)
        inv[i] = (long long) (mod - mod / i) * inv[mod % i] % mod;
    long long ans = 0;
    vector<long long> f(maxv + 1);
    for (int d = maxv; d >= 1; d--) {
        long long sum = 0;
        long long sum2 = 0;
        for (int x = d; x <= maxv; x += d) {
            sum += (long long) cnt[x] * x;
            sum2 += (long long) cnt[x] * x * x;
        }
        sum %= mod;
        f[d] = (sum * sum - sum2) % mod * inv[2] % mod; 
        for (int i = 2 * d; i <= maxv; i += d)
            f[d] -= f[i];
        f[d] %= mod;
        ans += f[d] * inv[d] % mod;
    }
    ans %= mod;
    if (ans < 0) ans += mod;
    cout << ans << '\n';
}
```

---

# 对子集求和

<div class=question>

设 $A$ 是一个 $n$ 元集合。$A$ 有 $2^n$ 个子集，它们构成的集合称为 $A$ 的**幂集**， 记作 $P(A)$。

给定函数 $f: P(A) \to \mathbb{Z}$，定义函数 $F : P(A) \to \mathbb{Z}$ 如下
$$
F(S) := \sum_{T \subseteq S} f(T).
$$
对每个 $S\subseteq A$，求 $F(S)$。
</div>



---

不失一般性，取 $A = \set{1, 2, \dots, n}$。

对于每个 $S \subseteq A$，我们把 $S$ 的子集进行分类。对每个 $i = 0, 1, \dots, n$，定义
$$
G(S, i) := \set{T \subseteq S : T 和 S 的差别只在前 i 个元素}
$$
所谓前 $i$ 个元素指的是 $1, \dots, i$。

根据定义，我们有 $G(S, 0) = \set{S}$ 而 $G(S, n) = P(S)$。
对于 $i \ge 1$，有递推式
$$
G(S, i) = \begin{cases}
G(S, i-1), \quad & 若i \not\in S \\
G(S, i-1) \sqcup G(S \setminus i, i), & 若 i \in S
\end{cases}
$$
<div class=remark>

- $\sqcup$ 表示无交并，也就是说 $X \sqcup Y$ 暗含着集合 $X,Y$ 不相交。
- $S \setminus i$ 表示把从 $S$ 中去掉 $i$ 所得的集合。
- $G(S \setminus i, i)$ 等于 $G(S \setminus i, i-1)$。

</div>

---

对于每个 $S\subseteq \set{1, \dots, n}$ 和每个 $i = 0, \dots, n$，定义
$$
F(S, i) := \sum_{T \in G(s, i)} f(T).
$$
边界条件：$F(S, 0) = f(S)$。
递推式
$$
F(S, i) = \begin{cases}
F(S,i-1), & 若i \not\in S \\
F(S,i-1) + F(S \setminus i, i), & 若 i \in S
\end{cases}
$$

$F(S)$ 就是 $F(S, n)$。

---

为了编程的方便，我们通常取 $A = \set{0, 1, \dots, n-1}$，用整数 $s$ 表示 $A$ 的子集 $S$
$$
i \in S \iff s\ 的二进制第\ i\ 位是 1.
$$

对应
$$
\begin{array}   {|c|c|}\hline
S \subseteq \set{0, \dots, n-1}  & 0 \le s \le 2^{n} -1\\ \hline
T \subseteq S & t \bitand s = t\\ \hline
S \cap T & s \bitand t \\ \hline
S \cup T & s \bitor t \\ \hline
S \setminus i & s \oplus 2^i \\ \hline
\end{array}
$$


<!-- 可见 $0 \le s < 2^n$。这样，函数 $f$ 和 $F$ 就是长为 $2^n$ 的数组。

对于每个 $s = 0, \dots, 2^{n} - 1$ 和每个 $i = 0, \dots, n$，定义
$$
G(s, i) := \set{t \bitand s = t : t 和 s只在前i个数位上不同}
$$
其中 $\bitand$ 表示按位与。

根据定义，有 $G(s, 0) = \set{s}$。对于 $i = 0, \dots, n-1$，有递推式
$$
G(s, i+1) = \begin{cases}
G(s,i), & 若 s 的第 i 位是 0 \\
G(s,i) \sqcup G(s \oplus 2^i, i+1), & 若 s 的第 i 位是 1
\end{cases}
$$
其中 $\oplus$ 表示按位异或。 -->



---

```cpp
for (int s = 0; s < 1 << n; s++)
    F[s] = f[s];

for (int i = 0; i < n; i++)
  for (int s = 0; s < 1 << n; s++)
    if (s >> i & 1)
      F[s] += F[s ^ (1 << i)];
```
时间：$O(n2^n)$。

---

# 例题 Compatible Numbers
[Codeforces 165E](https://codeforces.com/contest/165/problem/E)

称整数 $x$ 和 $y$ **相容**，如果 $x \bitand y = 0$. 例如 $90$（$1011010_2$）和 $36$（$100100_2$）相容，因为 $1011010_2 \bitand 100100_2 = 0$，而 $3$（$11_2$）和 $6$（$110_2$）不相容，因为 $11_2 \bitand 110_2 = 10_2$。

给你 $n$ 个正整数 $a_1, \dots, a_n$，对于每个 $i = 1, \dots, n$，在 $a_1, \dots, a_n$ 中找出一个与 $a_i$ 相容的数，若不存在这样的数，输出 $-1$。

- $1 \le n \le 10^6$
- $1 \le a_i \le 4\times 10^6$

---

# 分析

注意到 $4 \times 10^6 < 2^{22}$。

$a_i$ 与 $a_j$ 相容也就是说 $a_j$ 是 $(2^{22} - 1) \oplus a_i$ 的子集。


对于每个 $s = 0, \dots, 2^{22} - 1$，定义
$$
f(s) := \begin{cases}
s, &若存在 i 使得 a_i = s \\
- 1, &若不存在 i 使得 a_i = s
\end{cases}
$$
和
$$
F(s) := \begin{cases}
某个 a_i, &若存在 a_i 满足 a_i \subseteq s \\
- 1, &若不存在 a_i 满足 a_i \subseteq s
\end{cases}
$$

用上述对子集求和的方法，可以从 $f$ 算出 $F$。

---

```cpp
int main() {
    const int L = 22;
    vector<int> f(1 << L, -1);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        f[a[i]] = a[i];
    }
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < 1 << L; j++) {
            if (j >> i & 1 && f[j] == -1)
                f[j] = f[j ^ (1 << i)];
        }
    }
    for (int i = 0; i < n; i++) {
        cout << f[((1 << L) - 1) ^ a[i]] << ' ';
    }
    cout << '\n';
}
```

---

# 例题 Vowels

[Codeforces 383E](https://codeforces.com/contest/383/problem/E)

集合 $A$ 由前 24 个小写英文字母，a 到 x，构成。
给你 $n$ 个长度为 3 的单词，每个单词也由 a 到 x 构成。

对于 $A$ 的每个子集 $S$（一共 $2^{24}$ 个子集），定义
- $\mathrm{cnt}(S)$：$n$ 个单词中，有多少个单词至少包含一个 $S$ 中的字母。
约定 $\mathrm{cnt}(\varnothing) = n$。

求 $(\mathrm{cnt}(S))^2$ 的异或和。

$1 \le n \le 10^4$。

---

## 解法

对于 $A$ 的每个子集 $S$，定义
- $F(S)$：$n$ 个单词中，有多少个单词只含有 $S$ 中的字母。

那么
$$\mathrm{cnt}(S) = n - F(A \setminus S).$$

又定义
- $f(S)$：$n$ 个单词中，有多少个单词恰含有 $S$ 中的字母。

那么
$$
F(S) = \sum_{T \subseteq S} f(T).
$$

---

```cpp
int main() {
    const int L = 24;
    vector<int> f(1 << L);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        int mask = 0;
        for (char c : s)
            mask |= 1 << (c - 'a');
        f[mask]++;
    }
    for (int i = 0; i < L; i++)
        for (int j = 0; j < 1 << L; j++)
            if (j >> i & 1)
                f[j] += f[j ^ 1 << i];
    int ans = 0;
    for (int x : f)
        ans ^= (n - x) * (n - x);
    cout << ans << '\n';
}
```

---


# 例题 Or Plus Max

[arc100c](https://atcoder.jp/contests/arc100/tasks/arc100_c)

给你一个长为 $2^N$ 的整数序列 $A_0, A_1, \dots, A_{2^N-1}$。

对每个整数 $K = 1, 2, \dots, 2^{N}-1$，解决下述问题：
- 设 $i, j$ 是整数。求 $\max \set{A_i + A_j : 0 \le i < j \le 2^N-1 \ 且 \ (i \bitor j) \le K}$，
其中 $\bitor$ 表示按位或运算。

$1 \le N \le 18$
$1 \le A_i\le 10^9$

---

## 约定

对每个 $K = 0, 1, \dots, 2^{N} - 1$，我们把
- 设 $i, j$ 是整数。求 $\max \set{A_i + A_j : 0 \le i < j \le 2^N-1 \ 且 \ (i \bitor j) \le K}$，

称为问题 $K$。

指标 $i$ 和 $j$ 的取值范围总是 $0$ 到 $2^{N}-1$，以下不再写出。

---

## 解法

对每个 $x = 0, \dots, 2^{N}-1$，定义
- $f(x) := \max\set{A_i + A_j : i < j \,且\, (i \cup j) \subseteq x}.$

于是问题 $K$ 的答案就是 $\sum_{0 \le x \le K} f(x)$.

注意到
- 条件 $(i \cup j) \subseteq x$ 也就是 $i \subseteq x$ 且 $j \subseteq x$.

更进一步，可见 
- $f(x)$ 就是集合 $\set{A_i : i \subseteq x}$ 中第一大和第二大的两个数之和。

---

```cpp
int main() {
    int n; cin >> n;
    vector<pair<int,int>> f(1 << n);
    for (int i = 0; i < 1 << n; i++)
        cin >> f[i].first;

    for (int i = 0; i < n; i++)
        for (int s = 0; s < 1 << n; s++)
            if (s >> i & 1) {
                auto [v1, v2] = f[s];
                auto [v3, v4] = f[s ^ (1 << i)];
                vector<int> t = {v1, v2, v3, v4};
                sort(t.rbegin(), t.rend());
                f[s] = {t[0], t[1]};
            }

    int ans = 0;
    for (int k = 1; k < 1 << n; k++) {
        ans = max(ans, f[k].first + f[k].second);
        cout << ans << '\n';
    }
}
```
