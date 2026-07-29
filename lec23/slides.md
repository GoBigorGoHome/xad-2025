---
marp: true
math: mathjax
paginate: true
theme: lecture
title: 欧拉函数
---

# 欧拉函数



<div class=definition>

设 $n$ 是正整数，定义 $\varphi(n)$ 为不超过 $n$ 而与 $n$ 互素的正整数的个数。

</div>


- 例：$\varphi(1) = 1$，$\varphi(2) = 1$，$\varphi(3) = 2$，$\varphi(4) = 2$，$\varphi(5) = 4$，$\varphi(6) = 2$.

---

# 从素因子的角度看互素


一个数与 $n$ 互素也就是说它没有 $n$ 的素因子。

设 $m, n$ 是正整数，$n$ 无平方因子，我们不妨定义 $\varphi(m, n)$ 为不超过 $m$ 而与 $n$ 互素的数的个数。

于是有 $\varphi(m, n) = \varphi(m \bmod n, n) + \lfloor m/n \rfloor \varphi(n)$.

</div>

---

设 $p$ 是素数，则
$$\varphi(p) = p - 1,$$
又设 $k$ 是正整数，则
$$\varphi(p^k) = p^k - p^{k-1} = p^k(1 - {1\over p}),$$
对 $k \ge 2$ 还有
$$
\varphi(p^k) = p \varphi(p^{k-1}).
$$





---

# 用容斥原理计算 $\varphi(n)$

设 $n$ 的素因子有 $p_1, \dots, p_r$，根据容斥原理，$1, \dots, n$ 中与 $n$ 互素的数的个数等于
$$
\sum_{I \subseteq \set{1, \dots, r}} (-1)^{|I|} {n \over \prod_{i\in I} p_i}.
$$
于是得
$$
\varphi(n) = n \sum_{I \subseteq \set{1, \dots, r}} \prod_{i \in I} (-{1\over p_i}) = n\prod_{i=1}^{r} (1 - {1\over p_i}).
$$

---

# $\varphi$ 是积性函数


若正整数 $n, m$ 互素，则 $\varphi(nm) = \varphi(n) \varphi(m)$.


---

# 计算 $\varphi(n)$

对 $n$ 进行素因子分解，找出 $n$ 的全部素因子 $p_1, \dots, p_r$。
根据 $\varphi(n) = n \prod_{i=1}^{r}(1 - {1\over p_i})$ 来计算 $\varphi(n)$.

```cpp
int phi(int n) {
    int ans = n;
    for (int i = 2; i * i <= n; i++) {
        int cnt = 0;
        while (n % i == 0) {
            n /= i;
            cnt++;
        }
        if (cnt)
            ans -= ans / i;
    }
    if (n > 1)
        ans -= ans / n;
    return ans;
}
```

---

<div class=proposition>

设正整数 $n \ge 1$，$p$ 是素数。
- 若 $p \mid n$，则 $\varphi(pn) = p\varphi(n)$。
- 若 $p \not\mid n$，则 $\varphi(pn) = (p - 1) \varphi(n)$。
</div>

根据这个性质，我们可以利用素数筛法计算 $\varphi(1), \dots, \varphi(n)$。

---

# 用埃氏筛法计算 $\varphi(1), \dots, \varphi(n)$

```cpp
vector<int> phi_table(int n) {
    vector<int> phi(n + 1);
    phi[1] = 1;
    vector<bool> vis(n + 1);
    for (int i = 2; i <= n; i++)
        if (!vis[i]) // i是素数
            for (int j = 1; j * i <= n; j++)
                if (!vis[j * i]) {
                    phi[j * i] = phi[j] * (j % i ? i - 1 : i);
                    vis[j * i] = true;
                }
    return phi;
}
```

---

精简写法：

```cpp
vector<int> phi_table(int n) {
    vector<int> phi(n + 1);
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        if (phi[i] == 0) // i是素数
            for (int j = 1; j * i <= n; j++)
                if (phi[j * i] == 0)
                    phi[j * i] = phi[j] * (j % i ? i - 1 : i);
    return phi;
}
```


---

# 用线性筛法计算 $\varphi(1), \dots, \varphi(n)$


```cpp
vector<int> phi_table(int n) {
    vector<int> phi(n + 1);
    phi[1] = 1;
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (phi[i] == 0) { // i是素数
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p * i > n)
                break;
            if (i % p == 0) {
                phi[p * i] = p * phi[i];
                break;
            } else {
                phi[p * i] = (p - 1) * phi[i];
            }
        }
    }
    return phi;
}

```

---

# 欧拉定理

<div class=theorem>

设 $n$ 是正整数，$a$ 是整数，$a, n$ 互素。那么 $a^{\varphi(n)} \equiv 1 \pmod{n}$。
</div>

当 $n$ 是素数时，欧拉定理就是费马小定理。