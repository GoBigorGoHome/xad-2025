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


---

# 内容

等比数列求和极其扩展

数论分块

---

# 等比数列的和

<div class=question>



对于非负整数 $n$，考虑多项式 $f_n(X) := 1 + X + X^2 + \dots + X^{n-1}$。
特别的，$f_0(x) = 0$。

给定整数 $x$ 和正整数 $M$，求 $f_n(x) \bmod M$。

</div>

* $f_n(x) = {x^{n} - 1 \over x - 1}$，如果 $(x - 1)$ 和 $M$ 互素，那么 $(x - 1)$ 在模 $M$ 下有乘法逆元。
* 以下我们考虑一般情况，即 $(x - 1)$ 和 $M$ 未必互素。


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

# 数论分块

<div class=question>

计算 $\sum_{i=1}^{N} f(\lfloor N/i \rfloor)$.


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
\sum_{i=1}^{n} k \bmod i = \sum_{i=1}^{n} k - i \cdot \floor{k / i} = n(n+1)/2 - \sum_{i=1}^{n} i \cdot \floor{k / i}.
$$

---

# 扩展

<div class=question>

给定二元函数 $f$，计算 $\sum_{i=1}^{n} f(\floor{n/i}, \floor{m/i})$。

</div>
