---
marp: true
math: mathjax
paginate: true
theme: lecture
title: 求和
---

# 求和

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

long long f(long long x, long long n) {
    if (n == 0)
        return 0;

    if (n & 1)
        return (1 + x * f(x, n - 1)) % mod;

    return (1 + x) * f(x * x % mod, n >> 1) % mod;
}
```

---

# 非递归写法

```cpp
int mod;
long long f(long long x, long long n) {
    long long ans = 0;
    long long prod = 1;
    // 答案 == ans + prod * f(x, n)
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

# 扩展

<div class=question>

对于非负整数 $n, k$，考虑多项式 $f_{n}^{k}(X) = \sum_{i=0}^{n-1} i^k X^i$。

给定整数 $x$ 和正整数 $M$，求 $f_n^k(x) \bmod M$。

</div>


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

$f_0^{k} = 0$。对于 $n \ge 1$，有

$$
f_n^{k} = 
\begin{cases}

2^k (1 + x) f_{n/2}^{k}(x^2) + x \sum_{t = 0}^{k-1} {k \choose t} 2^{t} \cdot f_{n/2}^{t}(x^2), \quad & \text{$n$ 是偶数} \\

0^k + x \sum_{t=0}^{k} {k \choose t} f_{n-1}^{t}(x), \quad & \text{$n$ 是奇数}

\end{cases}

$$

</div>


---

# 例题 数列求和

[洛谷P4948](https://www.luogu.com.cn/problem/P4948)

给定整数 $n, a, k$，求 $\sum_{i=1}^{n} i^k a^i$，模 $10^9 + 7$。

- $1 \le n \le 10^{18}$
- $1 \le a \le 10^9$
- $0 \le k \le 2000$

---

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

$k \bmod i = k - i \cdot \lfloor k / i \rfloor$.