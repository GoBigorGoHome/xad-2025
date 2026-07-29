/*
对每个块维护两个数据
1. 这个块自己的信息。把这个块视作以它的重心为根的有根树。
2. 这个块作为子树的信息。把这个块视作它的父块的一个子树。

分解的过程
1. 求出整个树的重心 c。
2. divide(c): #已知当前的块的中心是 c，分解这个块。
    从点 c 开始对当前的块做一次 DFS。求出点的 preorder。每个子树的大小，每个点到 c 的距离。
    对每个子树 u，求出 u 的重心。

可以非递归的实现。
*/

/**
 *    author:  zjs
 *    created: 20.06.2026 14:58:52
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

template <integral T>
struct fenwick {
    vector<T> a;

    fenwick(const vector<T>& a_) : a(a_) {
        for (size_t i = 0; i < a.size(); i++)
            if ((i | (i + 1))  < a.size())
                a[i | (i + 1)] += a[i];
    }

    fenwick(int n = 0, T v = 0) : fenwick(vector<T>(n, v)) {}

    // 返回前n项之和，即 a[0] + ... + a[n - 1]
    T sum(int n) {
        n = min(n, (int) a.size());
        T ans = 0;
        while (n > 0) {
            ans += a[n - 1];
            n &= n - 1;
        }
        return ans;
    }

    void add(int p, T v) {
        while (p < (int) a.size()) {
            a[p] += v;
            p |= p + 1;
        }
    }
};

const int maxn = 1e5 + 5;
int pc[maxn]; // pc[u]：在重心树上的父节点
fenwick<int> block[maxn], sub[maxn];
// 上面三个数组存储重心分解的结果。每次调用 centroid_decomposition 之前不必清空。

struct Info {
    int v, d; // v 是一个点。d 是 v 到某个重心的距离。
};

template<invocable<span<Info>> F>
vector<vector<int>> centroid_decomposition(const vector<vector<int>>& tree, F build) { //对每个点 u 返回一个列表 dist[u]，表示点 u 到所在个各个块里重心的距离。
    int n = (int) tree.size();
    // 算出整棵树的重心。
    int centroid = [&](this auto find_centroid, int u, int p) -> int {
        int sz = 1;
        for (int v : tree[u])
            if (v != p) {
                int res = find_centroid(v, u);
                if (res >= 0)
                    return res;
                sz += -res;
            }
        return sz * 2 < n ? -sz : u;
    }(0, -1);
    pc[centroid] = -1;
    debug(centroid);
    // 分解。
    vector<vector<int>> dist(n); // 返回值
    vector<bool> del(n);
    vector<int> sz(n);
    queue<int> q;
    q.push(centroid);
    while (!q.empty()) {
        centroid = q.front();// centroid是当前块的重心。
        q.pop();
        // 1. 从当前块的重心开始对当前块做一次DFS，算出每个子树的大小和每个点到重心的距离。
        vector<Info> seq; // a sequence of pairs (点, 点到重心的距离)
        [&](this auto dfs, int u, int p, int depth) -> void {
            seq.push_back({u, depth});
            sz[u] = 1;
            for (int v : tree[u]) {
                if (del[v] || v == p) continue;
                dfs(v, u, depth + 1);
                sz[u] += sz[v];
            }
        }(centroid, -1, 0);
        // 2. 找出 centroid 的每个子树的重心
        int l = 1;
        for (int u : tree[centroid]) {
            if (del[u]) continue;
            // 找出子树 u 的重心
            int c = u;
            int p = centroid;
            while (1) {
                bool found = true;
                for (int v : tree[c]) {
                    if (del[v] || v == p) continue;
                    if (sz[v] * 2 > sz[u]) {
                        p = c;
                        c = v;
                        found = false;
                        break;
                    }
                }
                if (found) break;
            }
            pc[c] = centroid;
            q.push(c);
            // 计算 sub[c]
            sub[c] = build({seq.begin() + l, seq.begin() + l + sz[u]});
            l += sz[u];
        }
        // 计算 block[centroid]
        block[centroid] = build(seq);
        // 删除当前块的重心
        del[centroid] = true;
        // 记录当前块里除了重心之外的每个点到重心的距离
        for (auto [v, d] : views::drop(seq, 1))
            dist[v].push_back(d);
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> value(n);
    for (int i = 0; i < n; i++)
        cin >> value[i];

    auto build = [&](span<Info> seq) {
        int max_d = 0;
        for (auto [v, d] : seq)
            max_d = max(d, max_d);
        vector<int> sum(max_d + 1);
        for (auto [v, d] : seq)
            sum[d] += value[v];
        return fenwick(sum);
    };

    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto dist = centroid_decomposition(g, build);

    int ans = 0;
    while (m--) {
        int type, x, k;
        cin >> type >> x >> k;
        x ^= ans; k ^= ans;
        x--;
        if (type == 0) {
            ans = block[x].sum(k + 1);
            for (int d : views::reverse(dist[x])) { // 在重心树上向上跳
                ans += block[pc[x]].sum(k - d + 1) - sub[x].sum(k - d + 1);
                x = pc[x];
            }
            cout << ans << '\n';
        } else {
            int delta = k - value[x];
            value[x] = k;
            block[x].add(0, delta);
            for (int d : views::reverse(dist[x])) {
                block[pc[x]].add(d, delta);
                sub[x].add(d, delta);
                x = pc[x];
            }
        }
    }
}
// 我觉得这种写法并不优美。