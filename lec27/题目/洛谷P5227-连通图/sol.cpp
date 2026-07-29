/**
 *    author:  zjs
 *    created: 21.07.2026 13:17:58
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
const int maxn = 1e5 + 5;
const int maxm = 2e5 + 5;
int u[maxm], v[maxm];
vector<int> t[maxm];
dsu g(maxn);
vector<int> e[maxn * 4];
void add(int x, int l, int r, int ql, int qr, int id) {
    if (ql <= l && r <= qr) {
        e[x].push_back(id);
        return;
    }
    if (r < ql || qr < l)
        return;
    int mid = (l + r) / 2;
    add(x * 2, l, mid, ql, qr, id);
    add(x * 2 + 1, mid + 1, r, ql, qr, id);
}

int n, m;
void solve(int x, int l, int r) {
    int s = g.op.size();
    for (int i : e[x]) {
        g.merge(u[i], v[i]);
    }
    if (l == r) {
        if (g.size(1) == n)
            cout << "Connected\n";
        else
            cout << "Disconnected\n";
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
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> u[i] >> v[i];
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int c;
        cin >> c;
        while (c--) {
            int id;
            cin >> id;
            t[id].push_back(i);
        }
    }
    for (int i = 1; i <= m; i++) {
        if (t[i].empty()) {
            g.merge(u[i], v[i]);
        }
        else {
            int p = 0;
            for (int x : t[i]) {
                add(1, 0, k - 1, p, x - 1, i);
                p = x + 1;
            }
            add(1, 0, k - 1, p, k - 1, i);
        }
    }
    solve(1, 0, k - 1);
}
