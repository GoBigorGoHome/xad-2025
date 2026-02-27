---
# try also 'default' to start simple
theme: seriph
# random image from a curated Unsplash collection by Anthony
# like them? see https://unsplash.com/collections/94734566/slidev
# some information about your slides (markdown enabled)
title: 容斥原理
info: |
  ## Slidev Starter Template
  Presentation slides for developers.

  Learn more at [Sli.dev](https://sli.dev)
# apply UnoCSS classes to the current slide
class: text-center
# https://sli.dev/features/drawing
drawings:
  persist: false
# slide transition: https://sli.dev/guide/animations.html#slide-transitions
transition: slide-left
# enable MDC Syntax: https://sli.dev/features/mdc
mdc: true
# duration of the presentation
duration: 35min
colorSchema: light
---

# 容斥原理

The Principle of Inclusion-Exclusion   
包除原理 <twemoji-flag-japan />

---

## 也许你学过这样的容斥原理

![center](https://www.gameludere.com/wp-content/uploads/2020/03/IncExcPrinciple_Circles.png){h=80}

$$
\begin{split}
|A \cup B \cup C| &=|A| + |B| + |C| \\
& – |A \cap B| – |A \cap C| – |B \cap C| \\
& + |A \cap B \cap C|
\end{split}
$$

---

# 内容


- 一般的容斥原理
- 实用的容斥原理
- 例题

---

# 回忆一个恒等式

<p> </p>

设 $n$ 是非负整数，把 $x = -1$，$y = 1$ 代入二项式定理
$$
(x+y)^n = \sum_{i=0}^{n} {n\choose i} x^i y^{n-i},
$$
得
<aside class="float-right w-60 ml-6 mb-2 text-sm opacity-60 border-l pl-4">

当 $n = 0$ 时，$[n=0]$ 是 $1$，当 $n \ne 0$ 时，$[n = 0]$ 是 $0$。
这种记号叫作 **Iverson 括号**。 
</aside>
$$
\sum_{i=0}^{n} {n\choose i} (-1)^{i} = 0^{n} = [n = 0].
$$


---
layout: section
---

# 一般的容斥原理

---

<div class=theorem>

令 $S$ 是一个有 $n$ 个元素的集合。
设 $f$，$g$ 是两个从 $2^S$ 到 $\mathbb{R}$ 的映射。

如果对于所有 $T\subseteq S$ 有

$$
g(T) = \sum_{Y\supseteq T} f(Y),
$$

那么对于所有 $T\subseteq S$ 有

$$
f(T) = \sum_{Y\supseteq T} (-1)^{|Y|-|T|} g(Y).
$$
</div>



---

<div class=topic-box>

$$
\forall\, T\subseteq S,\ g(T) = \sum_{Y\supseteq T} f(Y) \implies \forall\, T\subseteq S,\ f(T) = \sum_{Y\supseteq T} (-1)^{|Y|-|T|} g(Y).
$$
</div>

证明：
$$
\begin{aligned}
\sum_{Y\supseteq T}(-1)^{|Y|-|T|} g(Y) &=   \sum_{Y\supseteq T}(-1)^{|Y|-|T|} \sum_{Z\supseteq Y} f(Z)  \\
& = \sum_{Z\supseteq T} \left(\sum_{Z\supseteq Y\supseteq T} (-1)^{|Y|-|T|} \right) f(Z). \quad {\color{red}交换求和次序}
\end{aligned}
$$

令 $m = |Z|- |T|$，我们有

$$ 
\sum_{\substack{Z\supseteq Y \supseteq T \\(Z,T固定)}} (-1)^{|Y|-|T|} = \sum_{i=0}^{m}(-1)^{i} {m \choose i} = [m = 0] = [Z=T]
$$

所以 $\sum_{Y\supseteq T}(-1)^{|Y|-|T|} g(Y) = f(T)$。



---

# 对偶形式

<div class=theorem>

如果对于所有 $T\subseteq S$ 有

$$
g(T) = \sum_{Y\subseteq T} f(Y),
$$

那么对于所有 $T\subseteq S$ 有

$$
f(T) = \sum_{Y\subseteq T} (-1)^{|T|-|Y|} g(Y).
$$

</div>

---

<div class=topic-box>

$$
\forall T\subseteq S,\ g(T) = \sum_{Y\subseteq T} f(Y) \implies \forall T\subseteq S,\ f(T) = \sum_{Y\subseteq T} (-1)^{|T|-|Y|} g(Y).
$$

</div>

证明：
$$
\begin{aligned}
\sum_{Y\subseteq T}(-1)^{|T|-|Y|} g(Y) &=   \sum_{Y\subseteq T}(-1)^{|T|-|Y|} \sum_{Z\subseteq Y} f(Z) \\
& = \sum_{Z\subseteq T} \left(\sum_{Z\subseteq Y \subseteq T} (-1)^{|T|-|Y|}\right) f(Z)   \quad {\color{red} 交换求和次序}
\end{aligned}
$$

令 $m = |T|- |Z|$，我们有

$$ 
\sum_{\substack{Z\subseteq Y \subseteq T\,(Z,T\,\text{固定})}} (-1)^{|T|-|Y|} = \sum_{i=0}^{m}(-1)^{i} {m \choose i} = [m = 0] = [Z=T]
$$

所以 $\sum_{Y\subseteq T}(-1)^{|Y|-|T|} g(Y) = f(T)$。


---
layout: section
---

# 实用的容斥原理

---

我们考虑的 $S$ 是一些**性质**的集合；对于 $S$ 里每一条性质，一个给定的集合 $A$ 里每个**元素**可能具有也可能不具有这条性质。取一个**权值**函数 $w: A\to \mathbb{R}$。

对于子集 $T\subseteq S$，令 $f_=(T)$ 为集合 $A$ 里**恰好**具有 $T$ 里每一条性质的元素的权值之和，令 $f_{\ge}(T)$ 为 $A$ 里**至少**具有 $T$ 里每一条性质的元素的权值之和。显然

$$
f_{\ge}(T) = \sum_{Y\supseteq T} f_{=}(Y).
$$

于是根据一般的容斥原理，有
$$
f_{=}(T) = \sum_{Y\supseteq T} (-1)^{|Y-T|} f_{\ge}(Y).
$$
特别地，不具有 $S$ 里的任何一条性质的元素的权值之和是
$$
f_{=}(\varnothing) = \sum_{Y\subseteq S} (-1)^{|Y|} f_{\ge}(Y).
$$

---

## 对偶形式

令 $f_{\le}(T)$ 为集合 $A$ 里**至多**有 $T$ 里的性质的元素的权值之和，显然有
$$
f_{\le}(T) = \sum_{Y\subseteq T}f_{=}(Y),
$$
于是根据一般的容斥原理的对偶形式，有
$$
f_{=}(T) = \sum_{Y\subseteq T} (-1)^{|T-Y|} f_{\le}(Y).
$$

---


最常用的权值函数就是 $w(x) = 1$。这时 

- $f_{=}(T)$ 就是集合 $A$ 里**恰好**具有 $T$ 里每一条性质的元素的个数。
- $f_{\ge}(T)$ 就是集合 $A$ 里**至少**具有 $T$ 里每一条性质的元素的个数。


---

# “容斥原理”名字的含义


<p> </p>

容斥原理典型应用是，$f_{\ge}(Y)$ 相对容易计算，我们用下式计算 $f_{=}(T)$

$$
f_{=}(T) = \sum_{Y\supseteq T}  (-1)^{|Y-T|} f_{\ge}(Y) \tag{$\bigstar$}.
$$

我们可以这样来看待 $(\bigstar)$，先用 $f_{\ge}(T)$ 作为 $f_{=}(T)$ 的近似值。然后减去
$$
\sum_{\substack{Y\supseteq T\\|Y\setminus T|=1}} f_{\ge}(Y),
$$
以获得一个更好的近似值。接着再把 
$$\sum_{\substack{Y\supseteq T\\|Y\setminus T|=2}} f_{\ge}(Y)$$
加回来，如此加加减减。这就是“容斥”二字的含义。



---

容斥原理的特例 $f_{=}(\varnothing) = \sum_{Y\subseteq S} (-1)^{|Y|} f_{\ge}(Y)$ 有一个简单的表述：
<div class=proposition>

集合 $A_1, A_2, \dots, A_n$ 是有限集 $A$ 的子集。对于每个 $\set{1, 2, \dots, n}$ 的子集 $T$，令
$$ A_T = \bigcap_{i \in T} A_i. $$
特别地，$A_{\varnothing} = A$.

那么，在集合 $A$ 里但不在任何一个子集 $A_i$ 里的元素个数是

$$
\sum_{T\subseteq \set{1,\dots, n}} (-1)^{|T|} |A_T|.
$$

</div>

---

在应用容斥原理
$$
\begin{equation}
f_{=}(T) = \sum_{Y\supseteq T} (-1)^{|Y-T|} f_{\ge}(Y)    \tag{$\bigstar$}
\end{equation}
$$
时，一个常见的情形是 **$f_{=}(T)$ 的值只跟集合 $T$ 的元素个数 $|T|$ 有关**。换言之，只要有 $|T|=|T'|$ 就有 $f_{=}(T) = f_{=}(T')$。这时 $f_{\ge}(T)$ 也只跟 $|T|$ 有关。

令 $m = |T|$，$n = |S|$。给定整数 $i$（$m \le i \le n$），满足 $S \supseteq Y \supseteq T$ 且 $|Y| = i$ 的集合 $Y$ 有$
{n - m \choose i - m}$ 个。  
我们令 $a(m) = f_{=}(T)$，$b(m) = f_{\ge}(T)$。那么 $(\bigstar)$ 变成
$$
a(m) = \sum_{m \le i \le n} {n - m \choose i - m} (-1)^{i - m} b(i).
$$


---

# 恰有 $k$ 个性质的元素

$$
\begin{aligned}
\sum_{\substack{T\subseteq S \\ |T|=k}} f_{=}(T) &= \sum_{\substack{T\subseteq S \\ |T|=k}} \sum_{Y\supseteq T}(-1)^{|Y|-|T|} f_{\ge}(Y) \\
&= \sum_{\substack{Y \subseteq S \\ |Y| \ge k}} (\sum_{\substack{T\subseteq Y \\ |T|=k}}  (-1)^{|Y|-|T|} ) f_{\ge}(Y)  \\
&=\sum_{\substack{Y \subseteq S \\ |Y| \ge k}} {|Y| \choose k} (-1)^{|Y|-k} f_{\ge}(Y)
\end{aligned}
$$

当 $f_{=}(T)$ 只跟 $T$ 的元素个数有关时，上面的结果可以写成

$$
\sum_{m=k}^{n} {n \choose m}{m \choose k}(-1)^{m-k} b(m).
$$


---

# 应用容斥原理的要素

- 计数对象的集合 $A$
- 权值函数 $w: A\to \R$，常常是 $w(x) = 1$。
- 性质集 $S$
- 对于子集 $Y\subseteq S$，看 $f_\ge(Y)$ 和 $f_{\le}(Y)$ 哪个容易计算，从下列两公式里选一个。
  $$
  f_{=}(T) = \sum_{Y\supseteq T} (-1)^{|Y-T|} f_{\ge}(Y)
  $$

<!-- for large vertical space -->

  $$
  f_{=}(T) = \sum_{Y\subseteq T} (-1)^{|T-Y|} f_{\le}(Y)
  $$

---
layout: section
---

# 例题

---

<div class=question>

把 $n$ 个不同的球放进 $m$ 个不同的盒子里（$n\ge m$），每个盒子里至少放一个。有多少种放置方法？

</div>

令 $A$ 为把 $n$ 个不同的球放进 $m$ 个不同的盒子里的方法构成的集合。

对于 $1 \le i \le m$，令 $A_i$ 为把 $n$ 个球放进 $m$ 个不同的盒子里，**第 $i$ 个盒子里一个球也不放**的放置方法的集合。

我们要求的恰是在 $A$ 里且不在任何一个子集 $A_i$ 里的放置方法的个数。应用容斥原理，答案是
$$
\sum_{i=0}^{m} {m \choose i} (-1)^{i} (m-i)^{n}.
$$

---

# 错位排列

<div class=question>

求 $1, 2, \dots, n$ 的错位排列数 $D_n$.
</div>

设 $A$ 为 $1, 2, \dots, n$ 的所有排列 $p = (p_1, \dots,p_n)$ 的集合；$A_i$ 为满足 $p_i = i$ 的排列的集合（$1 \le i \le n$）。

对于 $T \subseteq \set{1, \dots, n}$，有 $|A_T| = (n- |T|)!$。根据容斥原理
$$
D_n = \sum_{T \subseteq\set{1,\dots, n}} (-1)^{|T|}(n-|T|)! = \sum_{0 \le i \le n}{n\choose i} (-1)^i (n-i)! = \sum_{0 \le i \le n} (-1)^i {n! \over i!}.
$$

---

# 球染色

<div class=question>

有 $N$ 个球排成一行，有 $K$ 种颜色，要对每个球染色。规则是
- 相邻两球不同色。
- 每种颜色的球都有。

有多少种染色方法？

</div>

---

## 解法

若不要求每种颜色的球都有，只要求相邻两球不同色，染色方法数是 $K(K-1)^{N-1}$。
考虑容斥原理：
- 性质 $i$：有球被染成第 $i$ 种颜色。
- 性质集 $S = \set{1, \dots, K}$。
- 答案是 $f_{=}(S)$。
- 对于子集 $T\subseteq S$，$f_{\le}(T)$ 是只能用 $T$ 里的颜色染的方法数，有
  $$
  f_{\le}(T) = |T|(|T|-1)^{N-1}.
  $$

根据容斥原理，有
$$
\begin{aligned}
f_=(S) &= \sum_{T\subseteq S}(-1)^{|S|-|T|} f_{\le}(T) \\
&= \sum_{i=1}^{K} {K\choose i} (-1)^{K - i} i(i-1)^{N-1}.
\end{aligned}
$$

---

#  Coprime Sum

<div class=question>

给定正整数 $N, M$，求 $1, 2, \dots, N$ 中与 $M$ 互素的数之和。

</div>

设 $M$ 的素因子为 $p_1, \dots, p_k$。整数 $n$ 和 $M$ 互质，即 $n$ 不含质因子 $p_1, \dots, p_k$。

取性质集合 $S = \set{1, \dots, k}$，集合 $A=\set{1, \dots, N}$。
性质 $i\in S$ 表示 $x\in A$ 具有素因子 $p_i$，或者说 $p_i$ 整除 $x$。
取权值函数 $w(x) = x$。

所求即 $f_{=}(\varnothing)$。

而对于 $T\subseteq S$，元素 $x$ 至少具有 $T$ 里的性质就是说 $x$ 是 $\prod_{i\in T} p_i$ 的倍数。
令 $m = \prod_{i\in T} p_i$，$q = \lfloor N/m \rfloor$，我们有

$$f_{\ge}(T) = m(1 + q)q/2。$$

---

```cpp
long long coprime_sum(int n, int m) {
    vector<int> p = prime_divisors(m);
    long long ans = 0;
    for (int s = 0; s < 1 << p.size(); s++) {
        int prod = 1;
        for (int i = 0; i < p.size(); i++)
            if (s >> i & 1)
                prod *= p[i];
        int q = n / prod;
        long long sum = prod * ((1LL + q) * q / 2);
        if (__builtin_popcount(s) & 1)
            ans -= sum;
        else
            ans += sum;
    }
    return ans;
}
```

---

# 棋盘染色问题

[洛谷P6076](https://www.luogu.com.cn/problem/P6076)

用 $c$ 种颜色染一个 $n \times m$ 的棋盘，需满足下列条件
- 每个小方格可以染成 $c$ 种颜色中的一种，也可以不染色。
- 每一行至少有一个小方格被染色。
- 每一列至少有一个小方格被染色。
- 每种颜色在棋盘上至少出现一次。



$1 \le n, m, c \le 400$。


---

利用容斥原理，我们可以把“每种颜色在棋盘上至少出现一次”变成“只能用某 $k$ 种颜色”（$1 \le k \le c$）。

现在我们来解决下述问题

<div class=question>

用 $k$ 种颜色染一个 $n \times m$ 的棋盘，需满足下列条件
- 每个小方格可以染成 $k$ 种颜色中的一种，也可以不染色。
- 每一行至少有一个小方格被染色。
- 每一列至少有一个小方格被染色。 

求满足条件的染色方案数，模 $10^9 + 7$。

</div>

这个问题也可以用容斥原理来解决。  

---

## 方法一

- 取集合 $A$ 为用 $k$ 种颜色染一个 $n \times m$ 的棋盘，每个小方格可以染成 $k$ 种颜色中的一种，也可以不染色；  
染色方案的集合。
- 取性质集合 $S = \set{\mathrm{R}_1, \dots, \mathrm{R}_n, \mathrm{C}_1, \dots, \mathrm{C}_m}$。$\mathrm{R}_i$ 表示第 $i$ 行没被染色，$\mathrm{C}_j$ 表示第 $j$ 列没被染色。

对于 $T \subseteq S$，设 $T$ 里有 $a$ 个 R 元素，$b$ 个 C 元素，那么
$$f_{\ge}(T) = (k + 1)^{(n - a)(m - b)}.$$

应用容斥原理，得
$$
f_{=}(\varnothing) = \sum_{\substack{0 \le a \le n \\ 0 \le b \le m }} {n \choose a} {m \choose b} (-1)^{a + b} (k + 1)^{(n - a)(m - b)}.
$$

<!-- (k + 1) 的次数，一开始我想到的是 nm - (am + bn - ab)，其实有一个更简单的式子 (n - a) (m - b)，也就是删掉不涂色的 a 个行和 b 个列 -->

---

```cpp
const int mod = 1e9 + 7;
int C[405][405];
int power(int x, int n); //快速幂
int main() {
  for (int i = 0; i <= 400; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++)
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
  }
  int n, m, c; cin >> n >> m >> c;
  long long ans = 0;
  for (int k = 1; k <= c; k++) {
    long long sum = 0;
    for (int a = 0; a <= n; a++)
      for (int b = 0; b <= m; b++) {
        long long t = (long long) C[n][a] * C[m][b] % mod * power(k + 1, (n - a) * (m - b)) % mod;
        sum += ((a + b) & 1 ? -t : t);
      }
    long long t = sum % mod * C[c][k] % mod;
    ans += ((c - k) & 1 ? -t : t);
  }
  ans %= mod;
  if (ans < 0) ans += mod;
  cout << ans << '\n';
}
```

---

## 方法二

- 取集合 $A$ 为用 $k$ 种颜色染一个 $n \times m$ 的棋盘，每个小方格可以染成 $k$ 种颜色中的一种，也可以不染色，并且每一列至少有一个小方格被染色；染色方案的集合。
- 取性质集合 $S = \set{\mathrm{R}_1, \dots, \mathrm{R}_n}$。$\mathrm{R}_i$ 表示第 $i$ 行没被染色。

对于 $T \subseteq S$，设 $T$ 里有 $a$ 个元素，那么
$$f_{\ge}(T) = ((k + 1)^{n - a} - 1)^m.$$

应用容斥原理，得
$$
f_{=}(\varnothing) = \sum_{0 \le a \le n} {n \choose a} \cdot (-1)^a \cdot ((k + 1)^{n - a} - 1)^m.
$$

---

```cpp
const int mod = 1e9 + 7;
int C[405][405];
int power(int x, int n);

int main() {
  for (int i = 0; i <= 400; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++)
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
  }
  int n, m, c;
  cin >> n >> m >> c;
  long long ans = 0;
  for (int k = 1; k <= c; k++) {
    long long sum = 0;
    for (int a = 0; a <= n; a++) {
      long long t = (long long) C[n][a] * power(power(k + 1, n - a) - 1, m) % mod;
      sum += (a & 1 ? -t : t);
    }
    long long t = sum % mod * C[c][k] % mod;
    ans += ((c - k) & 1 ? -t : t);
  }
  ans %= mod;
  if (ans < 0) ans += mod;
  cout << ans << '\n';
}
```

---

实际上，我们可以从方法一的式子推出方法二的式子

$$
\begin{aligned}
&\sum_{\substack{0 \le a \le n \\ 0 \le b \le m }} {n \choose a} {m \choose b} (-1)^{a + b} (k + 1)^{(n - a)(m - b)} \\
&= \sum_{0 \le a \le n} {n \choose a} (-1)^{a} \sum_{0 \le b \le m} {m \choose b} (-1)^{b} \left((k + 1)^{(n - a)}\right)^{(m - b)} \\
&=  \sum_{0 \le a \le n} {n \choose a} (-1)^{a} \left((k + 1)^{(n - a)} - 1\right)^m. \quad \text{\color{red}二项式定理}
\end{aligned}
$$

---

# Kids Aren't Alright

[QOJ 11725](https://qoj.ac/contest/1742/problem/11725)

给定正整数 $m$。求有多少个非空的正整数集合满足其中的正整数的最大公因数是 $1$，最小公倍数是 $m$？

答案模 $998244353$。$1 \le m \le 10^{18}$。

---

若一个集合满足 $\mathrm{LCM} = m$，那么它的元素都是 $m$ 的因数。


令 $D(m)$ 为 $m$ 的因数构成的集合。取集合 $A$ 为 $D(m)$ 的子集构成的集合。

设 $m = p_1^{a_1} p_2^{a_2} \dots p_k^{a_k}$。

对于 $m$ 的每个素因子 $p_i$，考虑两个性质
- GCD 能被 $p_i$ 整除。
- LCM 不能被 $p_i^{a_i}$ 整除。

一共 $2k$ 个性质，它们构成性质集合 $S$。

我们要算的就是集合 $A$ 里有多少个元素 $X$ 不具有 $S$ 里的任何一个性质。 

当我们对每个 $i$ 确定了哪些性质需要满足之后，就可以确定有多少个数可以选入集合 $X$。

假设有 $t$ 个元素可以选入集合 $X$，那么非空集合 $X$ 有 $2^{t} - 1$ 个。

---

## $t$ 是 $k$ 个数的乘积

对于素因子 $p_i$，考虑四种情况
- GCD 能被 $p_i$ 整除。（乘以 $a_i$）
- LCM 不能被 $p_i^{a_i}$ 整除。（乘以 $a_i$）
- GCD 能被 $p_i$ 整除 **且** LCM 不能被 $p_i^{a_i}$ 整除。（乘以 $a_i - 1$）
- 无要求。（乘以 $a_i + 1$）



对每个 $p_i$ 要枚举四种情况，计算量是 $O(4^k)$ 而 $k \le 15$（一个不超过 $10^{18}$ 的整数 $m$ 至多有 $15$ 个素因子）。

注意到上述前两种情况算出来的 $t$ 是一样的，因此对每个 $p_i$ 只需要枚举三种情况就够了。计算量是 $O(3^k)$。


---



<div class=question>

给定正整数 $m \le 10^{18}$。设 $m = p_1^{a_1} p_2^{a_2} \dots p_k^{a_k}$。如何算出 $a_1, a_2, \dots, a_k$？

</div>

先分解出 $m$ 的不超过 $10^6$ 的素因子。此时剩下的数如果不是 $1$，那么它
- 要么是一个素数 $p$，
- 要么是一个素数的平方 $p^2$，
- 要么是两个素数的乘积 $pq$。

第一种情况可以用 Miller-Rabin 测试来检验。第二种情况可以通过开平方来检验。如果前两种情况都不是，那就是第三种情况。

---

# 素性测试

<div class=question>

给定大奇数 $n$，判断 $n$ 是不是素数。

</div>


<div v-click>

**试除**：用每个奇数 $3, 5, 7, 9, \dots, \lfloor \sqrt{n} \rfloor$ 除 $n$。

计算量 $O(\sqrt{n})$。当 $n$ 大到 $10^{18}$ 时，太慢。
</div>

---

# 概率性素性测试

## 整除测试

<div class=topic-box>

$n$ 是合数当且仅当存在奇数 $3 \le a \le \lfloor \sqrt{n} \rfloor$ 使得 $a \mid n$。

</div>

在 $3$ 到 $\lfloor \sqrt{n} \rfloor$ 之间随机选择一个奇数 $a$，检查 $a \mid n$。

---

## Fermat 测试

<div class=topic-box>

$n$ 是合数当且仅当存在整数 $2 \le a \le n - 2$ 使得 $a^{n-1} \ne 1 \pmod{n}$。

</div>

在 $2$ 到 $n-2$ 之间随机选择一个奇数 $a$，检查 $a^{n-1} \ne 1 \pmod{n}$。

---





<div class=proposition>

设 $n$ 是奇数，$n \ge 3$。如果 $n$ 是素数，那么
- 对每个整数 $a= 2, 3, \dots, n - 1$ 都有 $a^{n-1} = 1 \pmod{n}$。
- 方程 $x^2 = 1 \pmod{n}$ 的解只有 $x = \pm 1 \pmod{n}$。

</div>

---

## Miller-Rabin 测试

<div class=topic-box>

设 $n$ 是奇数，$n \ge 3$。设 $n - 1 = u2^{t}$，$u$ 是奇数。那么 $n$ 是合数当且仅当存在 $2 \le a \le n - 2$ 使得 $a^{u} \ne 1 \pmod{n}$ 且 $a^{u2^k} \ne -1 \pmod{n}$ for any $0 \le k < t$。

</div>