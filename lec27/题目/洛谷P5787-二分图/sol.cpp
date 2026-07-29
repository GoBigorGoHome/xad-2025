/**
 *    author:  zjs
 *    created: 21.07.2026 08:48:42
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

struct dsu {
    vector<int> p;
    vector<int> sz;
    vector<int> op;
    vector<int> d; //d[i]：点i相对于它的父节点的势差

    dsu(int n) : p(n + 1), sz(n + 1, 1), d(n + 1) {}

    pair<int,int> find(int x) {
        int sum = 0;
        while (p[x] != 0) {
            sum ^= d[x];
            x = p[x];
        }
        return {x, sum};
    }

    void merge(int x, int y) {
        auto [rx, dx] = find(x);
        auto [ry, dy] = find(y);
        if (rx == ry)
            return;
        // small-to-large merging
        if (sz[rx] > sz[ry])
            swap(rx, ry);
        p[rx] = ry;
        d[rx] = 1 ^ dy ^ dx;
        sz[ry] += sz[rx];
        op.push_back(rx);
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
        return sz[find(x).first];
    }
};
const int maxn = 1e5 + 5;
vector<pair<int,int>> e[maxn * 4];

void add(int x, int l, int r, int ql, int qr, int a, int b) {
    if (ql <= l && r <= qr) {
        e[x].push_back({a, b});
        return;
    }
    if (qr < l || r < ql)
        return;
    int mid = (l + r) / 2;
    add(2 * x, l, mid, ql, qr, a, b);
    add(2 * x + 1, mid + 1, r, ql, qr, a, b);
}

dsu g(maxn);

void solve(int x, int l, int r) {
    int s = g.op.size();
    bool ok = true;
    debug(x, l, r, e[x]);
    for (auto [a, b] : e[x]) {
        auto [ra, da] = g.find(a);
        auto [rb, db] = g.find(b);
        if (ra == rb && da == db) {
            ok = false;
            break;
        }
        g.merge(a, b);
    }
    if (!ok) {
        for (int i = l; i <= r; i++)
            cout << "No\n";
    } else {
        if (l == r)
            cout << "Yes\n";
        else {
            int mid = (l + r) / 2;
            solve(x * 2, l, mid);
            solve(x *2 + 1, mid + 1, r);
        }
    }
    g.rollback(s);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int x, y, l, r;
        cin >> x >> y >> l >> r;
        add(1, 1, k, l + 1, r, x, y);
    }
    solve(1, 1, k);
}