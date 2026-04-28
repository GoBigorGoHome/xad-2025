#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

const int maxn = 1e5 + 5;
vector<int> g[maxn];
int sz[maxn], heavy_child[maxn];

void get_size(int u, int p) {
    sz[u] = 1;
    for (int v : g[u])
        if (v != p) {
            get_size(v, u);
            sz[u] += sz[v];
            if (sz[heavy_child[u]] < sz[v])
                heavy_child[u] = v;
        }
}

int cnt[maxn], nc; //全局数据结构
int col[maxn];
int ans[maxn];

int preorder[maxn], num;

void dfs(int u, int p, bool keep) {
    int l = num;
    preorder[num++] = u;
    for (int v : g[u]) {
        if (v != p && v != heavy_child[u]) {
            dfs(v, u, false);
        }
    }
    int r = num;
    if (heavy_child[u])
        dfs(heavy_child[u], u, true);
    for (int i = l; i < r; i++) {
        nc += ++cnt[col[preorder[i]]] == 1;
    }
    ans[u] = nc;
    if (!keep) {
        for (int i = l; i < num; i++) {
            cnt[col[preorder[i]]] = 0;
        }
        nc = 0;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
        cin >> col[i];
    get_size(1, 0);
    dfs(1, 0, true);
    int m;
    cin >> m;
    while (m--) {
        int u;
        cin >> u;
        cout << ans[u] << '\n';
    }
}