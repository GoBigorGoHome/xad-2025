#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

struct dsu {
  vector<int> ps; // parent or size
  dsu(int n) : ps(n + 1, -1) {} //编号从1开始
  int find(int x) {
    return ps[x] < 0 ? x : ps[x] = find(ps[x]);
  }
  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
      return false;
    if (ps[x] < ps[y]) // link by size
      swap(x, y);
    ps[y] += ps[x];
    ps[x] = y;
    return true;
  }
};

struct edge {
    int u, v, w;
};

bool cmp(const edge& x, const edge& y) {
    return x.w < y.w;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector<edge> e(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        e[i] = {u, v, w};
    }
    sort(e.begin(), e.end(), cmp);

    dsu g(n);

    vector<edge> f;
    long long ans = 0;
    for (auto t : e) {
        if (g.unite(t.u, t.v)) {
            ans += t.w;
            f.push_back(t);
        }
    }
    vector<int> c(k);
    for (int i = 0; i < k; i++) {
        cin >> c[i];
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;
            f.push_back({n + i, j, w});
        }
    }
    sort(f.begin(), f.end(), cmp);

    for (int s = 1; s < 1 << k; s++) {
        long long sum = 0;
        dsu gg(n + k);
        int ne = n + __builtin_popcount(s) - 1;

        for (auto t : f) {
            if (t.u >= n && (s >> t.u - n & 1) == 0)
                continue;
            if (gg.unite(t.u, t.v)) {
                sum += t.w;
                ne--;
                if (ne == 0) break;
            }
        }
        for (int i = 0; i < k; i++)
            if (s >> i & 1)
                sum += c[i];
        ans = min(ans, sum);
    }
    cout << ans << '\n';
}