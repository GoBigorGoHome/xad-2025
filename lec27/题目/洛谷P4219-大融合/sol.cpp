/**
 *    author:  zjs
 *    created: 22.07.2026 13:31:03
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
vector<pair<int,int>> q;
void solve(int p, int l, int r) {
    int s = (int) g.op.size();
    for (auto [x, y] : e[p])
        g.merge(x, y);
    if (l == r) {
        auto [x, y] = q[l];
        cout << (long long) g.size(x) * g.size(y) << '\n';
    } else {
        int mid = (l + r) / 2;
        solve(p * 2, l,  mid);
        solve(p * 2 + 1, mid + 1, r);
    }
    g.rollback(s);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    map<pair<int,int>, vector<int>> time; // time[{x, y}]：边 (x,y) 开始存活的时刻的列表
    while (m--) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (x > y) swap(x, y);
        if (op == 'Q')
            q.push_back({x, y});
        time[{x, y}].push_back((int) q.size());
    }
    int N = (int) q.size();
    for (auto [edge, t] : time) {
        auto [x, y] = edge;
        for (int i = 1; i < (int) t.size(); i++) {
            add(1, 0, N - 1, t[i - 1], t[i] - 2, x, y);
        }
        add(1, 0, N - 1, t.back(), N - 1, x, y);
    }
    solve(1, 0, N - 1);
}
/*
这题的对时间分治解法，我觉得很新颖。想法是：在处理对边 (x, y) 的询问时，我们把边 (x, y) 删除，答案就是剩下的图上点 x 所在的连通的大小乘以点 y 所在的连通块的大小。 
*/