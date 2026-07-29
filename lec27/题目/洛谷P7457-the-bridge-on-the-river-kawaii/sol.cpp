/**
 *    author:  zjs
 *    created: 22.07.2026 00:27:58
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
vector<pair<int,int>> e[maxn * 4];

void add(int p, int l, int r, int ql, int qr, int x, int y) {
    if (r < ql || qr < l) return;
    if (ql <= l && r <= qr) {
        e[p].push_back({x, y});
        return;
    }
    int mid = (l + r) / 2;
    add(p * 2, l, mid, ql, qr, x, y);
    add(p * 2 + 1, mid + 1, r, ql, qr, x, y);
}
struct dsu { // 0-indexed
    vector<int> p;
    vector<int> sz;
    vector<int> op;

    dsu(int n) : p(n, -1), sz(n, 1) {}

    int find(int x) {
        while (p[x] != -1) {
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
        p[x] = -1;
        sz[y] -= sz[x];
    }

    void rollback(int s) {
        while (s < (int) op.size())
            undo();
    }

    int size(int x) {
        return sz[find(x)];
    }
};
dsu g(maxn);
bool ok[maxn];
vector<pair<int,int>> q;
void solve(int p, int l, int r) {
    int s = (int) g.op.size();
    for (auto [x, y] : e[p]) {
        g.merge(x, y);
    }
    if (l == r) {
        auto [x, y] = q[l];
        ok[l] = g.find(x) == g.find(y);
    } else {
        int mid = (l + r) / 2;
        solve(p * 2, l, mid);
        solve(p * 2 + 1, mid + 1, r);
    }
    g.rollback(s);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    map<pair<int,int>, pair<int,int>> info;
    
    struct Bridge {
        int x, y, s, t;
    };
    vector<Bridge> b[10];
    
    while (m--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (x > y) swap(x, y);
        if (type == 0) {
            int v;
            cin >> v;
            info[{x, y}] = {v, (int) q.size()};
        } else if (type == 1) {
            auto [v, s] = info[{x, y}];
            info.erase({x, y});
            b[v].push_back({x, y, s, (int) q.size()});
        } else {
            q.push_back({x, y});
        }
    }
    for (auto [k, val] : info) {
        auto [x, y] = k;
        auto [v, s] = val;
        b[v].push_back({x, y, s, (int) q.size()});
    }
    int N = (int) q.size();
    debug(N);
    vector<int> ans(N, -1);
    for (int v = 0; v < 10; v++) {
        for (auto [x, y, s, t] : b[v]) {
            add(1, 0, N - 1, s, t - 1, x, y);
        }
        solve(1, 0, N - 1);
        for (int i = 0; i < N; i++)
            if (ok[i] && ans[i] == -1)
                ans[i] = v;
    }
    for (int i = 0; i < N; i++)
        cout << ans[i] << '\n';
}