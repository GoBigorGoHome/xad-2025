

/*
离线回答询问。
*/

/**
 *    author:  zjs
 *    created: 19.06.2026 14:35:15
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif


const int maxn = 1e5 + 5;
bool del[maxn];
int sz[maxn];
vector<int> g[maxn];
void get_sz(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (del[v] || v == p) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

int tree_sz;
int find_centroid(int u, int p) {
    for (int v : g[u]) {
        if (del[v] || v == p) continue;
        if (sz[v] * 2 > tree_sz)
            return find_centroid(v, u);
    }
    return u;
}

vector<int> preorder;
int dist[maxn];
void dfs(int u, int p, int depth) {
    preorder.push_back(u);
    sz[u] = 1;
    dist[u] = depth;
    for (int v : g[u]) {
        if (v == p || del[v]) continue;
        dfs(v, u, depth + 1);
        sz[u] += sz[v];
    }
}

struct Query {
    int k, id;
};
vector<Query> q[maxn];
int ans[maxn];
int cnt[maxn];

void query(int x) {
    for (auto [k, id] : q[x])
        if (k >= dist[x])
            ans[id] += cnt[k - dist[x]];
}

void divide(int u) {
    // 1. 计算每个子树的大小
    get_sz(u, 0);
    // 2. 找到重心
    tree_sz = sz[u];
    int c = find_centroid(u, 0);
    debug(c);
    // 3. 从重心开始跑一次 DFS
    dfs(c, 0, 0);
    // 4. 统计
    for (int v : preorder) {
        cnt[dist[v]]++;
    }

    query(c);

    int l = 1;
    for (int v : g[c]) {
        if (del[v]) continue;
        int r = l + sz[v];
        for (int i = l; i < r; i++)
            cnt[dist[preorder[i]]]--;
        for (int i = l; i < r; i++) {
            query(preorder[i]);
        }
        for (int i = l; i < r; i++)
            cnt[dist[preorder[i]]]++;
        l = r;
    }
    // 5. 清空全局状态
    for (int x : preorder)
        cnt[dist[x]] = 0;
    preorder.clear();
    // 6. 删除点 c，递归处理 c 的每个子树
    del[c] = true;
    for (int v : g[c]) {
        if (del[v]) continue;
        divide(v);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
            q[i].clear();
            del[i] = false;
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for (int i = 0; i < m; i++)
            ans[i] = 0;
        for (int i = 0; i < m; i++) {
            int x, k;
            cin >> x >> k;
            q[x].push_back({k, i});
        }
        divide(1);
        for (int i = 0; i < m; i++)
            cout << ans[i] << '\n';
    }
}