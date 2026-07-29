#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

const int maxn = 1e4 + 5;

vector<pair<int,int>> g[maxn];
int sz[maxn];
int heavy_son[maxn];
int dist[maxn];

void prepare(int u, int p) {
    sz[u] = 1;
    for (auto [v, w] : g[u])
        if (v != p) {
            dist[v] = dist[u] + w;
            prepare(v, u);
            sz[u] += sz[v];
            if (sz[heavy_son[u]] < sz[v])
                heavy_son[u] = v;
        }
}


bool seen[int(1e8)]; // 全局DS

vector<int> preorder;

int m, q[100]; bool ans[100];

void dfs(int u, int p) {
    debug(u);
    int l = preorder.size(), r = l + 1;
    preorder.push_back(u);
    // 1. 先处理 u 的轻子树
    for (auto [v, _] : g[u])
        if (v != p && v != heavy_son[u]) {
            dfs(v, u);
            // 把子树 v 里点的贡献从全局DS中移除
            // 移除之后，全局 DS 已经空了，重置全局状态即可。
            // 我们从全局 DS 点删一个点的贡献时，不需要维护全局状态。
            for (; r < preorder.size(); r++)
                seen[dist[preorder[r]]] = false;
        }
    // 2. 再处理 u 的重子树
    if (heavy_son[u]) {
        dfs(heavy_son[u], u);
    }
    // 3. 处理子树 u
    // 3.1 把点 u 和 u 的轻子树里的操作加到全局DS里
    // 3.2 回答关于子树 u 的询问
    for (int i = l; i < r; i++) {
        for (int j = 0; j < m; j++) {
            int k = 2 * dist[u] + q[j] - dist[preorder[i]];
            if (0 <= k && k < (int) 1e8 && seen[k])
                ans[j] = true;
        }
        debug(preorder[i], dist[preorder[i]]);
        seen[dist[preorder[i]]] = true;
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    for (int i = 0; i < m; i++)
        cin >> q[i];
    prepare(1, 0);
    dfs(1, 0);
    for (int i = 0; i < m; i++)
        cout << (ans[i] ? "AYE" : "NAY") << '\n';
}