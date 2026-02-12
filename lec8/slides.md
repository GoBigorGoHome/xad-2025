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
g(T) = \sum_{Y\supseteq T} f(Y).
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
\sum_{Y\supseteq T}(-1)^{|Y|-|T|} g(Y) &=   \sum_{Y\supseteq T}(-1)^{|Y|-|T|} \sum_{Z\supseteq Y} f(Z)  \quad {\color{red}交换求和次序}\\
& = \sum_{Z\supseteq T} \left(\sum_{Z\supseteq Y\supseteq T} (-1)^{|Y|-|T|} \right) f(Z).
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
\sum_{Y\subseteq T}(-1)^{|T|-|Y|} g(Y) &=   \sum_{Y\subseteq T}(-1)^{|T|-|Y|} \sum_{Z\subseteq Y} f(Z) \quad {\color{red} 交换求和次序}\\
& = \sum_{Z\subseteq T} \left(\sum_{Z\subseteq Y \subseteq T} (-1)^{|T|-|Y|}\right) f(Z)  \\
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

求满足条件的染色方案数，模 $10^9 + 7$。

$1 \le n, m, c \le 400$。
