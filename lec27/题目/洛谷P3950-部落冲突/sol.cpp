/**
 *    author:  zjs
 *    created: 21.07.2026 22:19:58
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
const int maxn = 3e5 + 5;
int parent[maxn];
vector<int> adj[maxn];
void dfs(int u, int p) {
    parent[u] = p;
    for (int v : adj[u]) {
        if (v != p)
            dfs(v, u);
    }
}
vector<int> e[maxn * 4];
void add(int x, int l, int r, int ql, int qr, int u) {
    if (r < ql || qr < l) return;
    if (ql <= l && r <= qr) {
        e[x].push_back(u);
        return;
    }
    int mid = (l + r) / 2;
    add(x * 2, l, mid, ql, qr, u);
    add(x * 2 + 1, mid + 1, r, ql, qr, u);
}
struct dsu {
    vector<int> p;
    vector<int> sz;
    vector<int> op;

    dsu(int n) : p(n + 1), sz(n + 1, 1) {}

    int find(int x) {
        while (p[x] != 0) {
            x = p[x];
        }
        return x;
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        // small-to-large merging
        if (sz[x] > sz[y])
            swap(x, y);
        p[x] = y;
        sz[y] += sz[x];
        op.push_back(x);
    }
    
    void undo() { // 撤销最近一次的 merge 操作
        int x = op.back();
        op.pop_back();
        int y = p[x];
        p[x] = 0;
        sz[y] -= sz[x];
    }

    void rollback(int s) {
        while ((int) op.size() > s)
            undo();
    }

    int size(int x) {
        return sz[find(x)];
    }
};
dsu g(maxn);
vector<pair<int,int>> q;
void solve(int x, int l, int r) {
    int s = (int) g.op.size();
    for (int i : e[x]) {
        g.merge(i, parent[i]);
    }
    if (l == r) {
        auto [u, v] = q[l];
        cout << (g.find(u) == g.find(v) ? "Yes" : "No") << '\n';
    } else {
        int mid = (l + r) / 2;
        solve(x * 2, l, mid);
        solve(x * 2 + 1, mid + 1, r);
    }
    g.rollback(s);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(n, 0);
    vector<int> war;
    vector<vector<int>> t(n);
    for (int i = 1; i < n; i++)
        t[i].push_back(0);
    while (m--) {
        char op;
        cin >> op;
        if (op == 'Q') {
            int u, v;
            cin >> u >> v;
            q.push_back({u, v});
        } else if (op == 'C') {
            int u, v;
            cin >> u >> v;
            if (parent[u] != v)
                swap(u, v);
            t[u].push_back((int) q.size());
            war.push_back(u);
        } else {
            int x;
            cin >> x;
            debug(x);
            t[war[x - 1]].push_back((int) q.size());
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < (int) t[i].size(); j += 2) {
            int l = t[i][j];
            int r = j + 1 == (int) t[i].size() ? (int) q.size() : t[i][j + 1];
            add(1, 0, (int) q.size() - 1, l, r - 1, i);
        }
    }
    solve(1, 0, (int) q.size() - 1);
}
/*
1. 给边编号。考虑以n号点为根的有根树，对每个 i = 1, ..., n - 1，把点 i 的父边编号为 i。
2. 找出每条边的存活时段，加到线段树中。
3. 前序遍历线段树，加边、删边，到叶子节点时查询答案。
*/