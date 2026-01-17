#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

struct binary_trie {
  int width; //二进制位数
  vector<array<int,2>> go;
  int new_node() {
    go.push_back({});
    return go.size() - 1;
  }

  binary_trie(int width) : width(width) {
    new_node();
  }

  int add(int x) {
    int p = 0;
    for (int i = width - 1; i >= 0; i--) {
      int b = x >> i & 1;
      if (go[p][b] == 0) {
        go[p][b] = new_node();
      }
      p = go[p][b];
    }
    return p;
  }

  int max_xor(int x) {
    int ans = 0;
    int p = 0;
    for (int i = width - 1; i >= 0; i--) {
      int b = x >> i & 1;
      if (go[p][b ^ 1]) {
        ans |= 1 << i;
        p = go[p][b ^ 1];
      } else {
        p = go[p][b];
      }
    }
    return ans;
  }
};

const int maxn = 1e5 + 5;
vector<pair<int, int>> g[maxn];
int f[maxn];
void dfs(int u, int p) {
  for (auto [v, w] : g[u])
    if (v != p) {
      f[v] = f[u] ^ w;
      dfs(v, u);
    }
}

int main() {
  int n; cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v, w; cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }
  dfs(1, 0);
  binary_trie trie(31);
  for (int i = 1; i <= n; i++)
    trie.add(f[i]);
  int ans = 0;
  for (int i = 1; i <= n; i++)
    ans = max(ans, trie.max_xor(f[i]));
  cout << ans << '\n';
}
