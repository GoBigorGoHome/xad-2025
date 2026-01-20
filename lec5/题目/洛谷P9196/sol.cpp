#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

template<int sigma_size, int (*ctoi)(char)>
struct Trie {
  vector<array<int, sigma_size>> go;
  int new_node() {
    go.push_back({});
    return go.size() - 1;
  }
  Trie() {
    new_node();
  }
  int add(string s) {
    int p = 0;
    for (char c : s) {
        int i = ctoi(c);
        if (go[p][i] == 0)
            go[p][i] = new_node();
        p = go[p][i];
    }
    return p;
  }
  vector<pair<int,int>> get_suffix_link() {
    vector<pair<int,int>> q;
    for (int i = 0; i < sigma_size; i++) {
        if (go[0][i])
            q.push_back({go[0][i], 0});
    }
    for (int j = 0; j < q.size(); j++) {
        auto [u, v] = q[j];
        for (int i = 0; i < sigma_size; i++)
            if (go[u][i])
                q.push_back({go[u][i], go[v][i]});
            else
                go[u][i] = go[v][i];
    }
    return q;
  }
};

string sigma = "AGUC#";
int ctoi(char c) {
  for (int i = 0; i < 5; i++)
    if (sigma[i] == c)
      return i;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<string> s(n);
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  Trie<5, ctoi> trie;
  vector<int> id(m);
  for (int i = 0; i < m; i++) {
    string p, q;
    cin >> p >> q;
    id[i] = trie.add(q + '#' + p);
  }
  debug(id);
  vector<int> cnt(trie.go.size());
  auto fail = trie.get_suffix_link();

  for (int i = 0; i < n; i++) {
    int p = 0;
    for (char c : s[i] + '#' + s[i]) {
      p = trie.go[p][ctoi(c)];
      cnt[p]++;
    }
  }
  reverse(fail.begin(), fail.end());
  for (auto [u, v] : fail)
    cnt[v] += cnt[u];
  for (int i : id)
    cout << cnt[i] << '\n';
}