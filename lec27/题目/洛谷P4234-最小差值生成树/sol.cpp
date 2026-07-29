/**
 *    author:  zjs
 *    created: 21.07.2026 21:42:04
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
const int maxm = 2e5 + 5;
int u[maxm], v[maxm], w[maxm];
const int maxw = 1e4;
vector<int> e[maxw * 4];
void add(int x, int l, int r, int ql, int qr, int id) {
    if (r < ql || qr < l) return;
    if (ql <= l && r <= qr) {
        e[x].push_back(id);
        return;
    }
    int mid = (l + r) / 2;
    add(x * 2, l, mid, ql, qr, id);
    add(x * 2 + 1, mid + 1, r, ql, qr, id);
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
        while (op.size() > s)
            undo();
    }

    int size(int x) {
        return sz[find(x)];
    }
};
int n, m;
const int maxn = 5e4 + 5;
dsu g(maxn);

void clear(int x, int l, int r) {
    e[x].clear();
    if (l == r)
        return;
    int mid = (l + r) / 2;
    clear(x * 2, l, mid);
    clear(x * 2 + 1, mid + 1, r);
}
bool solve(int x, int l, int r) {
    int s = g.op.size();
    for (int i : e[x]) {
        g.merge(u[i], v[i]);
    }
    bool ok = g.size(1) == n;
    if (!ok && l < r) {
        int mid = (l + r) / 2;
        ok = solve(x * 2, l, mid) || solve(x * 2 + 1, mid + 1, r);
    }
    g.rollback(s);
    return ok;
}

bool check(int d) {
    clear(1, 1, maxw - d);
    for (int i = 0; i < m; i++) {
        add(1, 1, maxw - d, max(1, w[i] - d), w[i], i);
    }
    return solve(1, 1, maxw - d);
}

int binary_search(int ok, int ng) {
    while (abs(ok - ng) > 1) {
        int d = (ok + ng) / 2;
        if (check(d))
            ok = d;
        else
            ng = d;
    }
    return ok;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        cin >> u[i] >> v[i] >> w[i];
    cout << binary_search(maxw - 1, -1) << '\n';
}
/*
二分答案 d：是否存在一个生成树满足，边权的极差 <= d？
对于每个 x = 1, ..., maxw - d，判断：是否存在一个生成树满足，边权都在 [x, x + d] 内？

x <= w <= x + d   ==> w - d <= x <= w
边权是 w 的边，存活时段是 [w - d, w]
*/
