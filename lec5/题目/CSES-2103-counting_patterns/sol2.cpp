#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

template<int sigma_size, char alpha>
struct Trie {
  vector<array<int, sigma_size>> go;
  int new_node() {
    go.push_back({});
    return (int) go.size() - 1;
  }

  Trie() {
    new_node();
  }

  int add(string s) {
    int p = 0;
    for (char c : s) {
      int i = c - alpha;
      if (go[p][i] == 0) {
        go[p][i] = new_node();
      }
      p = go[p][i];
    }
    return p;
  }

  vector<pair<int,int>> get_suffix_link() {
    vector<pair<int,int>> q;
    for (int i = 0; i < sigma_size; i++)
        if (go[0][i])
            q.push_back({go[0][i], 0});

    for (int j = 0; j < q.size(); j++) {
        int u = q[j].first, v = q[j].second;
        for (int i = 0; i < sigma_size; i++)
            if (go[u][i])
                q.push_back({go[u][i], go[v][i]});
            else
                go[u][i] = go[v][i];
    }
    return q;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  string t;
  int k;
  cin >> t >> k;
  Trie<26, 'a'> trie;
  vector<int> id(k);
  for (int i = 0; i < k; i++) {
    string p;
    cin >> p;
    id[i] = trie.add(p);
  }

  auto fail = trie.get_suffix_link();
  int p = 0;
  vector<int> cnt(trie.go.size());
  for (char c : t) {
    p = trie.go[p][c - 'a'];
    cnt[p]++;
  }
  // 反向传播
  reverse(fail.begin(), fail.end());
  for (auto [u, v] : fail)
    cnt[v] += cnt[u];
  // 输出答案
  for (int i : id) {
    cout << cnt[i] << '\n';
  }
}