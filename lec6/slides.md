---
# try also 'default' to start simple
theme: seriph
# random image from a curated Unsplash collection by Anthony
# like them? see https://unsplash.com/collections/94734566/slidev
background: https://cover.sli.dev
# some information about your slides (markdown enabled)
title: 字符串哈希
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
lineNumbers: true
colorSchema: light
---

# 字符串哈希



---

<div class=question>

给你一个长度是 $n$ 的字符串 $S$。$n$ 比较大，比如 $n = 10^6$。  
回答 $q$ 次询问，每次询问 $S$ 的两个长度相同的子串是否相等。  
具体地说，每个询问给你四个整数 $l_1, r_1, l_2, r_2$，满足 $r_1 - l_1 = r_2 - l_2$，问子串 $S[l_1..r_1]$ 和 $S[l_2..r_2]$ 是否相等。

</div>

<div v-click>

我们考虑这样一个不精确的，概率性的算法：
- 设计一个函数 $h$，自变量是一个字符串，函数值是一个非负整数。
- 给定 $l, r$，我们可以快速算出 $h(S[l..r])$。
- 对于询问 $l_1, r_1, l_2, r_2$，我们算出 $h(S[l_1..r_1])$ 和 $h(S[l_2..r_2])$，如果两个数相等，就回答两个子串相等，否则回答不相等。

</div>

<div v-click>

我们给出的答案可能是错的。不过只要函数 $h$ 选得合适，答案正确的概率就很高。

上述算法叫作**字符串哈希**（rolling hash），函数 $h$ 叫作**哈希函数**。

</div>

---

<div class=definition> 

设 $S, T$ 是两个字符串，如果 $S \ne T$ 而 $h(S) = h(T)$，我们说发生了哈希**冲突**（collision）。

特别地，我们把 $S, T$ 长度相等时的哈希冲突称为等长冲突。

</div>

<div v-click class=remark>

选择哈希函数的两个原则：
- 便于计算
- 冲突概率低
</div>

<!-- hash 这个词的含义 -->

---

# 哈希函数

- 把每个字符看作一个整数。  
通常是把字符集看作一段连续的整数。比如，假设字符集是 a 到 z，可以看作 0 到 25 或 97 到 122。
- 把字符串看作一个**多项式**。  
例如把字符串 $S = S_1S_2 \dots S_n$ 看作多项式 $f(x) = S_1 x^{n-1} + S_2 x^{n-2} + \dots + S_n$。 
- 选择两个正整数 $b$ 和 $m$。取哈希函数 $h(S) = (S_1 b^{n-1} + S_2 b^{n-2} + \dots + S_n) \bmod m$。  
$b$ 和 $m$ 是哈希函数的参数。

<div class=remark>

选择这样的哈希函数，是因为可以快速计算一个子串的哈希值。


</div>

---

# 计算子串的哈希值

<div class=question>

设 $S$ 是长为 $n$ 的字符串。对于给定的整数 $l, r$（$1 \le l \le r \le n$），如何快速算出子串 $S[l..r]$ 的哈希值？



</div>

<div v-click class=topic-box>

根据定义
$$h(S[l..r]) = (\sum_{i=l}^{r} S_i b^{r - i}) \bmod m,$$
注意到
$$h(S[l..r]) = h(S[1..r]) - b^{r - l+1} \cdot h(S[1..l-1]).$$

对于每个 $i = 1, \dots, n$，我们预先算出前缀 $S[1..i]$ 的哈希值和 $b^{i}$，就能快速算出子串 $S[l..r]$ 的哈希值。
</div>

---

# 参数 $b$ 和 $m$

<div class=question>

如何选择参数 $b$ 和 $m$ 能使哈希冲突的概率低？

</div>

直觉上，模数 $m$ 越大越好。

$b$ 不应太小，比如
- 当 $b = 1$ 时，`ab` 和 `ba` 冲突。
- 当 $b = 2$ 时，`ac` 和 `ba` 冲突。

<div class=topic-box>

为了避免这样的冲突，$b$ 应该大于等于字符集大小。  
我们可以把 $S_1 b^{n-1} + S_2 b^{n-2} + \dots + S_n$ 看作一个 $n$ 位的 **$b$ 进制数**，$S_1, S_2, \dots, S_n$ 是数字。  
当 $b \ge$ 字符集大小时，不会有两个字符串表示同一个数。
</div>

---

# 参数 $b$ 和 $m$

<div class=topic topic=Takeaways>


- $m$ 必须是素数。
- $(m - 1)/2$ 最好是素数。
- $b$ 应该和 $m$ 互素并且大于最大的字符（视作整数），除此之外对 $b$ 没有要求。
- 取 $m = 10^9 + 7$ 是个不错的选择。（$10^9+7$ 素数，$(10^9+7 - 1)/2 = 5\cdot 10^8 + 3$ 也是素数。）
- $b$ 应该**随机**选择。

</div>


---

# 代码实现




```cpp {*}{maxHeight: '440px'}
struct Hash { // 不要起名为 hash，因为标准库里有名为 hash 的结构体。
  const int mod = 1e9 + 7;
  long long base = 349; // 随机设置
  static vector<long long> power; // 为了避免重复计算
  vector<long long> pref;
  int n;

  void ensure_power(int sz) {
    int cur = (int) power.size();
    if (cur < sz) {
      power.resize(sz);
      for (int i = cur; i < sz; i++) {
        power[i] = power[i - 1] * base % mod;
      }
    }
  }

  Hash(string s) {
    n = (int) s.size();
    ensure_power(n + 1);
    pref.resize(n + 1);
    pref[0] = 0;
    for (int i = 0; i < n; i++) {
      pref[i + 1] = (pref[i] * base % mod + s[i]) % mod;
    }
  }

  long long get(int l, int r) {
    long long res = pref[r + 1] - power[r - l + 1] * pref[l] % mod;
    if (res < 0) res += mod;
    return res;
  }
};

vector<long long> Hash::power(1, 1);
```

---

# 例题 1

[洛谷P3370](https://www.luogu.com.cn/problem/P3370)

给你 $N$ 个字符串。每个字符串由数字和大小写字母组成。求 $N$ 个字符串中有多少个不同的字符串。

限制：$N \le 10000$，每个字符串的长度不超过 $1500$。

---

```cpp
struct Hash { // 不要起名为 hash，因为标准库里有名为 hash 的结构体。
  const long long mod = 1e9 + 7;
  long long base = 857; // 随机设置
  static vector<long long> power; // 为了避免重复计算
  // ...
  long long get(string s) {
    ensure_power(s.size());
    long long res = 0;
    for (char c : s) {
      res = (res * base + c) % mod;
    }
    return res;
  }
};
vector<long long> Hash::power(1, 1);

int main() {
    int n; cin >> n;
    Hash h("");
    set<long long> a;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        a.insert(h.get(s));
    }
    cout << a.size() << '\n';
}
```

---

# 例题 2

[洛谷P3805](https://www.luogu.com.cn/problem/P3805)

给你一个长为 $n$，由小写英文字母组成的字符串 $S$，求 $S$ 的最长回文子串的长度。

限制：$1 \le n \le 1.1 \times 10^7$。

<div v-click class=algorithm>

枚举回文中心，用**二分答案**的方法计算回文半径。

时间：$O(n\log n)$。（会超时）
</div>

---

```cpp
int main() {
    string s;
    cin >> s;
    int n = s.size();
    Hash h(s);
    reverse(s.begin(), s.end());
    Hash rh(s);
    int ans = 0;
    for (int i = 0; i < 2 * n - 1; i++) {
        int p = i / 2, q = (i + 1) / 2;
        int ok = 0, ng = min(q, n - 1 - p) + 1;
        while (abs(ok - ng) > 1) {
            int k = (ok + ng) / 2;
            int l = q - k, r = p + k;
            if (h.get(l, r) == rh.get(n - 1 - r, n - 1 - l))
                ok = k;
            else
                ng = k;
        }
        ans = max(ans, 2 * ok + (i % 2 == 0));
    }
    cout << ans << '\n';
}
```

---


# 例题 3

双倍回文 [洛谷P4287](https://www.luogu.com.cn/problem/P4287)

设 $x$ 是一个非空字符串，如果存在字符串 $w$ 使得 $x = w\rev{w}w\rev{w}$，则称 $x$ 是一个**双倍回文**。换句话说，若要 $x$ 是双倍回文，它的长度必须是 $4$ 的倍数，而且 $x$，$x$ 的前半部分，$x$ 的后半部分都要是回文。

给你一个长为 $n$ 的字符串 $S$，计算它的最长双倍回文子串的长度。

限制：$1 \le n \le 500000$。

<div v-click class=algorithm>
</div>

---
