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

struct Edge {
  int u, v;
  long long w;
};

int comp(Edge x, Edge y) { return x.w < y.w; }

int main() {
  int l, r; cin >> l >> r;
  dsu g(r + 1);
  vector<Edge> e;
  for (int d = 1; d <= r; d++) {
    int t = (l + d - 1) / d;
    int i = t * d; // i是l,l+1,...,r第一个d的倍数
    for (int j = i + d; j <= r; j += d)
      e.push_back({i, j, (long long) t * j});
  }
  sort(e.begin(), e.end(), comp);
  long long ans = 0;
  for (Edge t : e)
    if (g.unite(t.u, t.v))
      ans += t.w;
  cout << ans << '\n';
  return 0;
}
