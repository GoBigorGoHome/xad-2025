#include <bits/stdc++.h>
using namespace std;

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

const int maxn = 1e6 + 5;
dsu g(maxn);

struct edge {
    int u, v;
};
const int maxw = 1e5 + 5;
vector<edge> e[maxw];

int n, m;

void solve(int l, int r) {
    if (l == r) {
        if (g.size(1) == n) {
            cout << l << '\n';
            exit(0);
        }
        return;
    }
    int mid = (l + r) / 2;
    int s = g.op.size();
    for (int i = mid + 1; i <= r; i++)
        for (auto [u, v] : e[i])
            g.merge(u, v);
    solve(l, mid);
    
    g.rollback(s);
    for (int i = l; i <= mid; i++)
        for (auto [u, v] : e[i])
            g.merge(u, v);
    solve(mid + 1, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[w].push_back({u, v});
    }
    int k = maxw;
    for (int i = 0; i < maxw; i++)
        if (e[i].empty()) {
            k = i;
            break;
        }
    for (int i = k; i < maxw; i++) {
        for (auto [u, v] : e[i])
            g.merge(u, v);
    }
    if (k > 0) {
        solve(0, k - 1);
    }
    cout << k << '\n';
}
