---
# try also 'default' to start simple
theme: seriph
# random image from a curated Unsplash collection by Anthony
# like them? see https://unsplash.com/collections/94734566/slidev
background: https://cover.sli.dev
# some information about your slides (markdown enabled)
title: 字符串
info: |
  ## Repetitions in Strings
# apply UnoCSS classes to the current slide
class: text-center
# https://sli.dev/features/drawing
style: |
  @import './styles/lecture.css'
drawings:
  persist: false
# slide transition: https://sli.dev/guide/animations.html#slide-transitions
transition: slide-left
# enable MDC Syntax: https://sli.dev/features/mdc
mdc: true
# duration of the presentation
duration: 35min
lineNumbers: true
---

# 字符串

Repetitions in Strings


<!--
The last comment block of each slide will be treated as slide notes. It will be visible and editable in Presenter Mode along with the slide. [Read more in the docs](https://sli.dev/guide/syntax.html#notes)
-->

---
transition: fade-out
---

# 今日内容


- border
- Z 数组
- 回文子串
- 周期


---

# 记号和约定

- 字符串下标从 $1$ 开始。
- 设 $x$ 是字符串，记号 $|x|$ 表示 $x$ 的长度。
- 符号 $\epsilon$ 表示空串。

---

# border

<div class="definition">

设 $x$, $y$ 是字符串。若 $y$ 是 $x$ 的前缀也是 $x$ 的后缀，并且 $y \ne x$，就称 $y$ 是 $x$ 的一个 **border**。
 </div>

- 例：`aabaabaa` 的 border 有 $\epsilon$，`a`，`aa`，`aabaa`。
- 例：`ab` 的 border 有 $\epsilon$。

<div class=topic-box v-click>

- 任何非空字符串至少有一个 border，$\epsilon$。
- $x$ 的 border 的 border 也是 $x$ 的 border。
</div>


---

# $\operatorname{Border}(x)$

<div class="definition">

设 $x$ 是非空字符串。定义函数
$$
\operatorname{Border}(x) = \text{$x$ 的最长 border.}
$$
</div>

- 例：$\operatorname{Border}(\mathtt{aabaabaa}) = \mathtt{aabaa}$
- 例：$\operatorname{Border}(\mathtt{aa}) = \mathtt{a}$
- 例：$\operatorname{Border}(\mathtt{a}) = \epsilon$


---

<div class="proposition">

令 $x$ 是一个非空字符串，$m$ 是使得 $\operatorname{Border}^{k}(x)$ 有定义的最大整数 $k$（因此 $\operatorname{Border}^{m}(x) = \epsilon$）。那么 $x$ 的所有 border，按长度递减顺序列出来，是
$$\operatorname{Border}(x), \operatorname{Border}^2 (x), \dots, \operatorname{Border}^m(x).$$
</div>

- 例：`aabaabaa` 的 border 有 `aabaa`，`aa`，`a`，$\epsilon$。


---

# border 数组

<div class=definition>

设 $x$ 是一个长度为 $n$ 的非空字符串。我们定义数组 $\border$：$\border[1], \dots, \border[n]$。  
对 $i = 1, \dots, n$，
$$
\border[i] := |\mathrm{Border}(x[1..i])|.
$$

我们把数组 $\border$ 称为 $x$ 的 **border 数组**。

</div>


<div class=topic-box v-click>

- $x$ 的 border 数组记录了 $x$ 的每个前缀的最长 border 的长度。
- $0 \le \border[i] < i$。
</div>

---

<div class=example>

$x = \texttt{aabaabaa}$ 的 border 数组。

| $i$ | $x[1..i]$ |  $\border[i]$    |
|------|------|----------|
| 1 | $\texttt{a}$   | 0     |
| 2 | $\texttt{aa}$   | 1     |
| 3 | $\texttt{aab}$   | 0     |
| 4 | $\texttt{aaba}$ | 1 |
| 5 | $\texttt{aabaa}$  | 2 | 
| 6 | $\texttt{aabaab}$ | 3  |
| 7 | $\texttt{aabaaba}$ | 4 | 
|8 | $\texttt{aabaabaa}$ | 5 | 

</div>

<style>
.slidev-layout td, .slidev-layout th {
    padding: 0.2rem;
}
</style>


---

# 求 border 数组


<div class=question>

给定字符串 $x$，求 $x$ 的 border 数组。
</div>

<v-click>

用**递推法**求 $x$ 的 border 数组。

设 $x$ 的长度是 $n$。

根据定义，$\border[1] = 0$。  
对于 $i = 2, \dots, n$，我们利用 $\border[1], \dots, \border[i-1]$ 来算出 $\border[i]$。
</v-click>


---

对于正整数 $j = 1, 2, \dots, i-1$，我们注意到
<div class=topic-box>

$x[1..j]$ 是 $x[1..i]$ 的 border $\iff$ $x[1..j-1]$ 是 $x[1..i-1]$ 的 border 且 $x[j] = x[i]$
</div>

![](./计算border.png){width=60%}

<v-click>

为了求 $\border[i]$，我们从大到小**枚举** $x[1..i-1]$ 的每个 border 的长度 $k$，检查是否有 $x[k+1] = x[i]$。

![](./计算border_2.png){width=60%}
</v-click>

---

# 枚举 $x[1..i-1]$ 的 border 长度

<div class=topic-box>

设 $x[1..i-1]$ 有 $m$ 个 border，那么这 $m$ 个 border 的长度从大到小依次是
$$
\border[i-1], \border^2[i-1], \dots, \border^m[i-1].
$$
</div>

---

# 代码

```cpp
vector<int> border_array(string x) {
  int n = x.size();
  vector<int> border(n);
  border[0] = 0;
  for (int i = 1; i < n; i++) {
    int j = border[i - 1];
    while (j > 0 && x[j] != x[i]) {
      j = border[j - 1];
    }
    if (x[j] == x[i])
      j++;
    border[i] = j;
  }
  return border;
}
```

---
layout: two-cols-header
---

# 时间复杂度

::left:: 

````md magic-move 

```cpp
vector<int> border_array(string x) {
  int n = x.size();
  vector<int> border(n);
  border[0] = 0;
  for (int i = 1; i < n; i++) {
    int j = border[i - 1];
    while (j > 0 && x[j] != x[i]) {
      j = border[j - 1];
    }
    if (x[j] == x[i])
      j++;
    border[i] = j;
  }
  return border;
}
```

```cpp
vector<int> border_array(string x) {
  int n = x.size();
  vector<int> border(n);
  border[0] = 0;
  int j = 0;
  for (int i = 1; i < n; i++) {
    while (j > 0 && x[j] != x[i]) {
      j = border[j - 1];
    }
    if (x[j] == x[i])
      j++;
    border[i] = j;
  }
  return border;
}
```

````

:: right::


<v-click>

考查 `j` 的变化

- 第 8 行 `j = border[j - 1]` 让 $j$ 变小。
- 第 11 行 `j++` 让 $j$ 增加 1。
- `j` 的初始值是 0，`j` 始终大于等于 0。
- 第 11 行 `j++` 最多执行 `n - 1` 次。
</v-click>


<div class=topic-box v-click>

`j = border[j - 1]` 最多执行 $n - 1$ 次。
</div>


<style>
.two-cols-header {
  column-gap: 50px; /* Adjust the gap size as needed */
}
</style>

---

<div class=definition>

设 $x, y, z$ 是字符串。若 $z$ 是 $x$ 的前缀且 $z$ 是 $y$ 的前缀，则称 $z$ 是 $x$ 和 $y$ 的**公共前缀**（common prefix）。$x$ 和 $y$ 的最长公共前缀记作 $\lcp(x, y)$。
</div>

- 例：$\lcp(\texttt{ab}, \texttt{ac}) = \texttt{a}$
- 例：$\lcp(\texttt{ba}, \texttt{ac}) = \epsilon$

---

# Z 数组

<div class=definition>

设 $x$ 是一个长度为 $n$ 的非空字符串。我们定义数组 $Z$：$Z[2], Z[3],\dots, Z[n]$。  
对 $i = 2, 3, \dots, n$，
$$
Z[i] := |\lcp(x, x[i..n])|.
$$

我们把数组 $Z$ 称为 $x$ 的 **Z 数组**。
</div>


<div class=topic-box v-click>

$x$ 的 Z 数组记录了 $x$ 和它自己的每个后缀的最长公共前缀的长度。
</div>

<div class=remark v-click>

我们用不到 $Z[1]$，所以干脆不定义它。实际上 $Z[1]$ 也没有合适的定义。  
有的资料把 $Z[1]$ 定义为 $\lcp(x, x[1..n])$，也就是 $x$ 的长度。有的资料把 $Z[1]$ 定义为 $0$。
</div>


---

<div class=example>

$x = \texttt{aabaabaa}$ 的 Z 数组。

| $i$ | $x[i..8]$ |  $Z[i]$    |
|------:|------:|----------:|
| 1 | $\texttt{aabaabaa}$   |     |
| 2 | $\texttt{abaabaa}$   | 1     |
| 3 | $\texttt{baabaa}$   | 0     |
| 4 | $\texttt{aabaa}$ | 5 |
| 5 | $\texttt{abaa}$  | 1 | 
| 6 | $\texttt{baa}$ | 0  |
| 7 | $\texttt{aa}$ | 2 | 
|8  | $\texttt{a}$ | 1 | 

</div>

<style>
.slidev-layout td, .slidev-layout th {
    padding: 0.2rem;
}
table{ width:50%;}
</style>

---

# 计算 Z 数组

<div class=question>

给定长为 $n$ 的字符串 $x$，求 $x$ 的 Z 数组。

</div>

<v-click>

- 采用暴力比较的方法求 $Z[2]$。  
$\texttt{a{\color{green}a}baabaa}$  
$\texttt{ {\color{green}a}abaabaa}$
- 用**递推法**求 $Z[3], \dots, Z[n]$
</v-click>

---


$x = \texttt{abbabaabbabaaaabbabbaa}$。  
假设我们已经算出 $Z[2]$ 到 $Z[9]$，现在要计算 $Z[10]$。  



<v-click>

我们做一些**推理**

</v-click>
<v-clicks>

- 我们知道 $Z[7] = 7$，这意味着 $x[7..13] = x[1..7]$  
![](./z-box.png){width=60%}
- $x[7..13] = x[1..7] \implies x[10..13] = x[4..7]$  
![](./z-box-2.png){width=60%}
- 我们又知道 $Z[4] = 2$，这意味着 $x[4..5] = x[1..2]$ 且 $x[6] \ne x[3]$
- 又 $x[10..13] = x[4..7]$，所以 $x[10..11] = x[4..5] = x[1..2]$ 且 $x[12] = x[6] \ne x[3]$
- 所以 $Z[10] = 2$
</v-clicks>

<div class=topic-box v-click>

利用已经算出来的东西，我们可以避免不必要的字符比较。
</div>

<style>

img {
  margin-top: 0.5rem;
  margin-bottom: 0.6rem;
}

</style>

---

# Z-box

<div class=definition>

设 $x$ 是一个长为 $n$ 的字符串，对每个 $i = 2, \dots, n$，我们把区间 $[i, i+Z[i] - 1]$ 称为一个 **Z-box**。

</div>

![](./def-z-box.png){width=60%}

<div class=caption>

$Z[7] = 7$，$[7,13]$ 是一个 Z-box。
</div>


<div class=topic-box v-click>

Z-box 标志着一个等于前缀的子串。  
或者说 Z-box 标志着一个再次出现的前缀。
</div>

---

<div class=topic-box>

假设我们已经算出了 $Z[2], \dots, Z[i - 1]$，现在要计算 $Z[i]$。
</div>

<v-click>

我们维护目前发现的右端点最大的 Z-box，设它是 $[l, r]$，那么有 
$$r = l + Z[l] - 1 \quad \text{且} \quad r = \max_{2 \le j < i} (j + Z[j] - 1)$$
</v-click>

<v-clicks depth=2>

- 如果 $i > r$，那么我们采用暴力比较的方法算出 $Z[i]$。
- 如果 $i \le r$，那么根据 $x[l..r] = x[1..r-l+1]$ 可知
  $$x[i..r] = x[i-l+1..r-l+1]$$
  也就是说，子串 **$x[i..r]$ 在前面出现过**。
  - 如果 $Z[i - l + 1] < r - i + 1$，那么 $Z[i] = Z[i - l + 1]$。
  - 如果 $Z[i - l + 1] > r - i + 1$，那么 $Z[i] = r - i + 1$。
  - 如果 $Z[i - l + 1] = r - i + 1$，那么 $Z[i] \ge r - i + 1$。  
  我们从 $x[r + 1]$ 与 $x[r - i + 2]$ 开始继续比较。
</v-clicks>

---

```cpp
vector<int> z_array(string x) {
  int n = x.size();
  vector<int> z(n); // 字符串下标从 0 开始。
  int l = 0, r = 0; // [l,r) 是目前发现的右端点最大的 Z-box. 
  for (int i = 1; i < n; i++) {
      z[i] = i < r ? min(z[i - l], r - i) : 0;
    while (i + z[i] < n && x[z[i]] == x[i + z[i]])
      z[i]++;
    if (r < i + z[i]) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}
```


<v-clicks>

- 根据前一页的分析，只有 `z[i - l] == r - i` 时，第 9 行 `z[i]++` 才可能执行。  
- 此时 `z[i]` 的初始值是 `r - i`，所以 `z[i]++` 执行多少次，`r` 就增大多少。
- 最初 `r == 0`，又 `r` 始终不超过 `n`，所以第 9 行 `z[i]++` 执行至多 `n` 次。

我们可以在 $O(n)$ 时间内计算一个长为 $n$ 的字符串的 Z 数组。
</v-clicks>

---

# 字符串匹配

<div class=question>

给定长为 $m$ 的字符串 $P$ 和长为 $n$ 的字符串 $T$，求 $P$ 在 $T$ 里出现的位置。

如果 $T[i..i+m-1] = P$，我们说 $P$ 在 $T$ 的位置 $i$ 出现。

</div>

我们称 $P$ 为**模式串**（pattern），称 $T$ 为**文本串**（text）。

<div class=remark v-click>

我们总是假设 $m \le n$。
</div>


---

# 用 border 数组进行字符串匹配

1. 算出文本串 $P$ 的 border 数组。
2. 算一个数组 $a = a[1], \dots, a[n]$。  
    - $a[i]$ 的定义：既是 $T[1..i]$ 的后缀又是 $P$ 的前缀的字符串，最长有多长。
    - $P$ 在 $T$ 的位置 $j$ 出现 $\iff$ $a[j + m - 1] = m$

<div class=example v-click>

$\begin{aligned}
P &= \texttt{a b c a b c a c a b}, & m = 10. \\  
T &= \texttt{b a b c b a b c a b c a a b c a b c a b c a c a b \ c}, & n = 26.\\  
a &= \texttt{0 1 2 3 0 1 2 3 4 5 6 7 1 2 3 4 5 6 7 5 6 7 8 9 {\color{red}10} 3}.
\end{aligned}
$

</div>

---

用**递推法**计算 $a$ 数组

<div class=topic-box>

假设我们已经算出 $a[1], \dots, a[i - 1]$，现在要计算 $a[i]$。
</div>

<div class=example>

计算 $a[4]$.

$\begin{aligned}
P &= \texttt{a b c a b c a c a b}, & m = 10. \\  
T &= \texttt{b a b c b a b c a b c a a b c a b c a b c a c a b c}, & n = 26.\\  
a &= \texttt{0 1 2 ? }
\end{aligned}
$
</div>
<v-clicks>

- 注意到 $a[4] \le a[3] + 1$.
- 我们先看 $T[4]$ 是否等于 $P[a[3] + 1]$，也就是比较 $T[4]$ 和 $P[3]$.
- $T[4] = P[3]$，所以 $a[4] = a[3] + 1 = 3$.

</v-clicks>



---

<div class=example>

计算 $a[20]$.

$\begin{aligned}
P &= \texttt{a b c a b c a c a b}, & m = 10. \\  
T &= \texttt{b a b c b a b c a b c a a b c a b c a b c a c a b c}, & n = 26.\\  
a &= \texttt{0 1 2 3 0 1 2 3 4 5 6 7 1 2 3 4 5 6 7 ?}
\end{aligned}
$
</div>
<v-clicks>

- $a[19] = 7$ 而 $T[20] \ne P[8]$，所以 $a[20] \le 7$。
- 对于 $j = 1, \dots, 7$，我们注意到
  $$T[20-j+1..20] = P[1..j] \iff \text{$P[1..j-1]$ 是 $P[1..7]$ 的 border 且 $T[20] = P[j]$}$$  
- 借助 $P$ 的 border 数组，我们从大到小枚举 $P[1..7]$ 的每个 border 的长度 $k$，检查 $T[20]$ 和 $P[k+1]$ 是否相等。
- $\border[7] = 4$ 而 $T[20] = P[5]$，所以 $a[20] = 5$。
</v-clicks>

---

用**递推法**计算 $a$ 数组

<div class=topic-box>

假设我们已经算出 $a[1], \dots, a[i - 1]$，现在要计算 $a[i]$。

</div>

- 注意到 $a[i] \le a[i - 1] + 1$。
- 如果 $t[i] = p[a[i-1] + 1]$ 那么 $a[i] = a[i - 1] + 1$。
- 否则如果 $a[i] > 0$ 那么 $p[1..a[i] - 1]$ 是 $p[1..a[i - 1]]$ 的一个后缀，  
也就是说 $p[1..a[i] - 1]$ 是 $p[1..a[i - 1]]$ 的一个 border。  
  - 借助 $p$ 的 border 数组，我们可以从大到小枚举 $p[1..a[i] - 1]$ 的每个 border 的长度 $k$，检查是否有 $p[k+1] = p[i]$。

---

我们把上面讲的用 border 数组进行字符串匹配的算法称为 **KMP 算法**。

<div class=remark v-click>

KMP 是 Knuth，Morris，Pratt 三个姓的缩写。

</div>

---

````md magic-move
```cpp
vector<int> kmp_search(string t, string p, const vector<int>& border) {
  vector<int> res;
  int n = t.size();
  int m = p.size();
  int k = 0;
  for (int i = 0; i < n; i++) {
    while (k > 0 && t[i] != p[k])
      k = border[k - 1];
    if (t[i] == p[k])
      k++;
    if (k == m) {
      res.push_back(i - m + 1);
      k = border[k - 1];
    }
  }
  return res;
}
```


```cpp
vector<int> kmp_search(string t, string p, const vector<int>& border) {
  vector<int> res;
  int n = t.size();
  int m = p.size();
  int k = 0;
  for (int i = 0; i < n; i++) {
    while (k > 0 && (k == m || t[i] != p[k])) // 把 k = border[k-1] 的操作写在一处
      k = border[k - 1];
    if (t[i] == p[k])
      k++;
    if (k == m) {
      res.push_back(i - m + 1);
    }
  }
  return res;
}
```

```cpp
vector<int> kmp_search(string t, string p, vector<int> border) {
  vector<int> res;
  int n = t.size();
  int m = p.size();
  int k = 0;
  for (int i = 0; i < n; i++) {
    while (k > 0 && t[i] != p[k]) // p[m] == '\0'，通常 t[i] != '\0'. 也就是说，通常 t[i] != p[m].
      k = border[k - 1];
    if (t[i] == p[k])
      k++;
    if (k == m) {
      res.push_back(i - m + 1);
    }
  }
  return res;
}
```

````

---

# 用 Z 数组进行字符串匹配

1. 算出模式串 $P$ 的 Z 数组。
2. 计算一个数组 $b = b[1], \dots, b[n]$。
    - $b[i]$ 的定义：$T[i..n]$ 和 $P$ 的最长公共前缀的长度。
    - $P$ 在 $T$ 的位置 $j$ 出现 $\iff$ $a[j] = m$。 

<div class=example v-click>

$\begin{aligned}
P &= \texttt{a b c a b c a c a b}, & m = 10. \\  
T &= \texttt{b a b c b a b c a b c a a b c a \ b c a b c a c a b c}, & n = 26.\\  
b &= \texttt{0 3 0 0 0 7 0 0 4 0 0 1 7 0 0 {\color{red}10}  0 0 4 0 0 1 0 3 0 0}.
\end{aligned}
$

</div>

---

计算数组 $b$ 和计算模式串 $P$ 的 Z 数组的方法是类似的。

```cpp
vector<int> z_search(string p, string t, vector<int> z) {
  vector<int> res;
  int m = p.size();
  int n = t.size();
  int l = 0, r = 0;
  for (int i = 0; i < n; i++) {
    int k = i < r ? min(r - i, z[i - l]) : 0;
    while (k < m && i + k < n && p[k] == t[i + k]) {
      k++;
    }
    if (r < i + k) {
      l = i;
      r = i + k;
    }
    // k 就是我们说的 b[i]
    if (k == m) {
      res.push_back(i);
    }
  }
  return res;
}
```

---


# 字符串匹配问题的简便写法

- `border_array()` 和 `kmp_search()` 的代码差不多。
- `z_array()` 和 `z_search()` 的代码也差不多。

实际上，我们可以用 `border_array()` 或 `z_array()` 来解决字符串匹配问题。
1. 用一个在模式串 $P$ 和文本串 $T$ 里都没出现过的特殊字符（比如 #）把 $P$ 和 $T$ 连接起来，得到一个新字符串
  $$ S = P\texttt{\#}T $$
2. 计算 $S$ 的 border 数组或 Z 数组。
    - $T[i,i+m-1] = P \iff S[i+m + 1, i+2m] = P \iff Z[i + m + 1] = m \iff \border[i+2m] = m$. 

---

# 回文子串



---

# 周期



---
