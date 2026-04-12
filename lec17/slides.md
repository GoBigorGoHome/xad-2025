---
marp: true
math: mathjax
paginate: true
theme: lecture
title: 根号分治
---

# 根号分治

对于一个问题，若规模较小，采用一种算法，若规模较大，采用另一种算法。


---

# 预备知识：基本不等式

设 $x, y$ 是正实数。则 $x, y$ 的算术平均数大于等于 $x,y$ 的几何平均数，即
$$
(x+y)/2 \ge \sqrt{xy}.
$$
等号只在 $x=y$ 时成立。

**证明**：$(x-y)^2 \ge 0 \implies (x+y)^2 \ge 4xy \implies (x+y)/2 \ge \sqrt{xy}$。


##### 推论

设实数 $a, b > 0$。函数 $f(x) = ax + b/x$（$x > 0$）在 $x = \sqrt{b/a}$ 处取到最小值 $2\sqrt{ab}$。



---

# [abc259_h](https://atcoder.jp/contests/abc259/tasks/abc259_h) Yet Another Path Counting

我们有一个 $N\times N$ 的网格。第 $i$ 行第 $j$ 列的格子里有一个整数 $a_{i,j}$。

考虑从某个格子开始，向右或向下走到相邻的格子里若干（可以是零）次所得的路径。求这样的路径中，满足起点和终点格子里的数相同的路径的数量，模 $998244353$。

两条路径不同，若它们经过的格子（括起点和终点格子）的集合不同。

###### 限制

- $1 \le N \le 400$
- $1 \le a_{i,j} \le N^2$


---

# 解法

把格子按照里面的数分类。把写有整数 $x$ 的格子称为“$x$-格子”。对于 $x = 1, 2, \dots, N^2$，设 $x$-格子有 $c_x$ 个。

设定一个阈值 $B$。对每个 $x = 1, 2, \dots, N^2$，
- 若 $c_x \le B$，枚举每一对 $x$-格子 $(i_1, j_1)$，$(i_2, j_2)$，若 $i_1 \le i_2$ 且 $j_1 \le j_2$，算一个组合数 ${i_2 - i_1 + j_2 - j_1 \choose i_2 - i_1}$。时间 $O(c_x^2)$。
- 若 $c_x > B$，在整个网格上做一次递推。令 $f[i][j]$ 为从某个 $x$-格子到格子 $(i,j)$ 的路径的数量之和。有递推式 $f[i][j] = f[i-1][j] + f[i][j-1] + [a_{i,j} = x]$。时间 $O(N^2)$。

---

对所有满足 $c_x \le B$ 的 $x$，我们考虑和 $\sum_{x: c_x \le B} c_x^2$。有
$$
\sum_{x : c_x \le B} c_x^2 \le \sum_{x : c_x \le B} c_x B = B\sum_{x : c_x \le B} c_x \le BN^2.
$$

满足 $c_x > B$ 的 $x$ 不超过 $N^2/B$ 个，所以这一部分的总时间是 $O(N^4/B)$。

我们考虑 $B$ 的取值让 $BN^2 + N^4/B$ 最小。我们取 $B = N$，总时间就是 $O(N^3)$。

---

# 代码

```cpp
const int mod = 998244353;
int a[401][401], dp[401][401], C[800][400];
vector<pair<int, int>> pos[160000 + 5];

int main() {
  int n; cin >> n;
  for (int i = 0; i < 2 * n; i++) C[i][0] = 1;
  for (int i = 1; i < 2 * n; i++)
    for (int j = 1; j <= min(n - 1, i); j++)
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
  
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
      pos[a[i][j]].push_back({i, j});
    }

  long long ans = 0;
  for (int i = 1; i <= n * n; i++) {
    if (pos[i].size() > n) {
      for (int j = 1; j <= n; j++)
        for (int k = 1; k <= n; k++) {
          dp[j][k] = (dp[j - 1][k] + dp[j][k - 1]) % mod;
          if (a[j][k] == i) {
            dp[j][k]++;
            ans += dp[j][k];
          }
        }
    } else {
      for (int j = 0; j < pos[i].size(); j++)
        for (int k = j; k < pos[i].size(); k++) {
          int dx = pos[i][k].first - pos[i][j].first;
          int dy = pos[i][k].second - pos[i][j].second;
          if (dx >= 0 && dy >= 0) ans += C[dx + dy][dx];
        }
    }
  }
  cout << ans % mod << '\n';
}
```

---

# 模型

集合 $S$ 含有 $N$ 个元素。$T_1, \dots, T_M$ 是 $S$ 的一个划分。我们要计算 $f(T_i)$，$1 \le i \le M$。

性质：$f(T_i)$ 有两种算法
- 法一：时间是 $O(|T_i|^2)$
- 法二：时间是 $O(N)$ 

取一阈值 $B$。若 $|T_i| \le B$ 用法一计算 $f(T_i)$，若 $|T_i| > B$ 用法二计算 $f(T_i)$。

法一的总时间是 $O(NB)$，法二的总时间是 $O(N^2/B)$。

取 $B = \sqrt{N}$，总时间是 $O(N\sqrt{N})$。

---

# [abc365_g](https://atcoder.jp/contests/abc365/tasks/abc365_g) AtCoder Office

<div class=columns>
<div>

有 $N$ 个人在 AtCoder 办公式工作。办公室记录人员进出，至今已有 $M$ 条记录。

第 $i$（$1 \le i \le M$）条记录是一对整数 $(T_i, P_i)$，表示在 $T_i$ 时刻第 $P_i$ 个人进或出办公室。

已知开始记录时所有人都在办公室外，现在所有人也都在办公室外。

回答 $Q$ 个询问，格式如下。

第 $i$（$1 \le i \le Q$）个询问给你两个整数 $(A_i, B_i)$。求自开始记录以来，第 $A_i$ 和第 $B_i$ 个人都在办公室的总时长。

</div>

<div>

###### 限制

- $2 \le N, M \le 2 \times 10^5$
- $1 \le T_1 < T_2 < \dots < T_M \le 10^9$
- $1 \le P_i \le N$
- $1 \le Q \le 2 \times 10^5$
- $1 \le A_i < B_i \le N$
- 输入的值都是整数。

</div>

</div>

---

# 解法

一共有 $M/2$ 个区间。取阈值 $C$。对于询问 $(A, B)$
- 若 $A$，$B$ 两人的区间都不超过 $C$ 个，暴力处理这个询问，时间是 $O(C)$。处理所有这样的询问的总时间是 $O(QC)$。
- 否则不妨设 $A$ 的区间超过 $C$ 个，这样的人不超过 $M/(2C)$ 个。对每个这样的人 $A$，用**累积和**与**交错和**这两个技巧可以在 $O(M)$ 时间内**预处理**出其余每个人跟 $A$ 都在办公室的时长：
  - 设从 $l$ 时刻到 $r$ 时刻，$B$ 一直在办公室。那么
$[l, r]$ 时段内 $A$，$B$ 两人都在办公室的时长 =  $[l, r]$ 时段内 $A$ 在办公室的时长 = 截至 $r$ 时刻 $A$ 在办公室内的累积时长 - 截至 $l$ 时刻 $A$ 在办公室内的累积时长。

  回答询问时查表即可。这样的预处理的总时间是 $O(M^2/(2C))$。

总时间是 $O(QC + M^2/(2C))$，取 $C = M/\sqrt{2Q}$，总时间就成为 $O(M\sqrt{Q})$。

---

# 代码

<div class=columns>

```cpp
void solve() {
  int n, m; cin >> n >> m;
  vector<pair<int,int>> rec(m);
  for (int i = 0; i < m; i++) cin >> rec[i].first >> rec[i].second;
  vector<vector<pair<int,int>>> seg(n + 1);
  vector<int> last(n + 1);
  for (auto [t, p] : rec)
    if (!last[p]) last[p] = t;
    else {
      seg[p].push_back({last[p], t});
      last[p] = 0;
    }

  int lim = 1000;

  unordered_map<int, vector<int>> ans;

  for (int i = 1; i <= n; i++) {
    if (seg[i].size() > lim) {
      vector<int> alt_sum(n + 1);// 交错和
      int sum_i = 0;  // cumulative sum of time when person i was in office
      bool in = false;// is person i in office now?
      int prev_i = 0; // the last time when person i entered or exited office
      for (auto [t, p] : rec) {
        if (p == i) {
          sum_i += in * (t - prev_i);
          prev_i = t;
          in ^= 1;
        }
        alt_sum[p] = sum_i + in * (t - prev_i) - alt_sum[p];
      }
      ans[i] = alt_sum;
    }
  }
```

```cpp
  int q; cin >> q;
  while (q--) {
    int a, b; cin >> a >> b;
    if (seg[a].size() > lim)
      cout << ans[a][b] << '\n';
    else if (seg[b].size > lim)
      cout << ans[b][a] << '\n';
    else {
      int t = 0, i = 0;
      for (auto [l, r] : seg[a]) {
        while (i < seg[b].size() && seg[b][i].second <= r) {
          t += clamp(seg[b][i].second, l, r) - clamp(seg[b][i].first, l, r);
          i++;
        }
        if (i < seg[b].size()) // seg[b][i].second > r
          t += clamp(seg[b][i].second, l, r) - clamp(seg[b][i].first, l, r);
      }
      cout << t << '\n';
    }
  }
}
```

---

# 模型

集合 $S$ 含有 $N$ 个元素。$T_1, T_2, \dots, T_M$ 是 $S$ 的一个划分。

有一个函数 $f(T_i, T_j)$（$1 \le i, j\le M$），满足 $f(T_i, T_j) = f(T_j, T_i)$。

回答 $Q$ 个询问，每个询问给你两个整数 $i, j$（$1 \le i, j \le M$），求 $f(T_i, T_j)$。

##### 性质

计算 $f(T_i, T_j)$ 有两种方法：
法一： 在 $O(|T_i| + |T_j|)$ 时间内计算 $f(T_i, T_j)$。
法二： 对于 $T_i$，在 $O(N)$ 时间内算出所有的 $f(T_i, T_j)$，$j = 1, \dots, M$。


---

取一个阈值 $B$。对于满足 $|T_i| > B$ 的子集 $T_i$，我们用法二预处理出所有 $f(T_i, T_j)$。这样的 $T_i$ 不超过 $N/B$ 个。总时间是 $O(N^2/B)$，空间是 $O(MN/B)$。

对于询问 $i, j$
- 若 $|T_i|$ 和 $|T_j|$ 都不大于 $B$，则用法一计算 $f(T_i, T_j)$，时间 $O(B)$。这样的询问最多 $Q$ 个，总时间 $O(QB)$。
- 若 $|T_i|$ 或 $|T_j|$ 大于 $B$，则查表。 

总时间是 $O(N^2/B + QB)$。取 $B = N/\sqrt{Q}$，总时间是 $O(N\sqrt{Q})$。

---


# [abc219_g](https://atcoder.jp/contests/abc219/tasks/abc219_g) Propagation（传播）


给你一个有 $N$ 个点和 $M$ 条边的简单无向图，点从 $1$ 到 $N$ 编号，点 $i$ 上写有整数 $i$。

给你 $Q$ 个询问。对每个 $i = 1, 2, \dots, Q$，第 $i$ 个询问给你整数 $x_i$（$1 \le x_i \le N$）。这个询问要你做下述操作。
- 设写在点 $x_i$ 上的整数是 $X$。把点 $x_i$ 的每个邻点上所写的整数改为 $X$。

求依次处理所有询问后，每个点上所写的整数。

###### 限制

- $1 \le N, Q \le 2 \times 10^5$
- $0 \le M \le \min(2\times 10^5, N(N-1)/2)$


---

# 解法

如果每个点的度都不大，那么暴力更新是可承受的。

注意到所有点的度之和是 $2M$。
取阈值 $B$，若点 $u$ 的度大于 $B$，称 $u$ 为**重点**，否则称为**轻点**。

对于第 $i$ 个询问，首先**设法**求出当前写在点 $x_i$ 上的数。然后
- 若 $x_i$ 是轻点，更新 $x_i$ 的邻点，记下这些点最近一次被更新是在第 $i$ 个询问；
- 否则不更新 $x_i$ 的邻点，只记下点 $x_i$ 最近一次做传播中心是在第 $i$ 个询问，和这时点 $x_i$ 上的数。

问题是怎么求出当前写在点 $x_i$ 上的数。
- 枚举与 $x_i$ 相邻的**重点**，这样的点至多有 $2M/B$ 个。找出这些点最晚成为传播中心的时间，看是否晚于当前记录的点 $x_i$ 上一次被更新的时间。

我们取 $B = \sqrt{2M}$。这样就能在 $O(\sqrt{2M})$ 时间内处理一个询问。

---

# 代码

<div class=columns>

```cpp
const int maxn = 2e5 + 5;
vector<int> g[maxn];
int last_updated[maxn];
int last_propagate[maxn];
int val[maxn];
int B;

int get_current_val(int u) {
  int t = last_updated[u];
  for (int v : g[u]) {
    if (g[v].size() <= B) break;
    t = max(t, last_propagate[v]);
  }
  return t == 0 ? u : val[t];
}

bool cmp(int u, int v) {
  return g[u].size() > g[v].size();
}
```

```cpp
void solve() {
  int n, m, q; cin >> n >> m >> q;
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 1; i <= n; i++)
    sort(g[i].begin(), g[i].end(), cmp);
  B = sqrt(2 * m);
  for (int i = 1; i <= q; i++) {
    int x; cin >> x;
    val[i] = get_current_val(x);
    last_propagate[x] = i;
    if (g[x].size() <= B)
      for (int v : g[x])
        last_updated[v] = i;
  }
  for (int i = 1; i <= n; i++)
    cout << get_current_val(i) << ' ';
  cout << '\n';
}
```


