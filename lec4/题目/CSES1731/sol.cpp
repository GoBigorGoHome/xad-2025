#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

template <int sigma_size, char alpha>
struct Trie {
  vector<array<int, sigma_size>> go;

  int new_node() {
    go.push_back({});
    return go.size() - 1;
  }

  Trie() {
    new_node(); //创建根节点
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
};

int main() {
  string s;
  int k;
  cin >> s >> k;
  Trie<26, 'a'> trie;
  vector<int> id(k);
  for (int i = 0; i < k; i++) {
    string w;
    cin >> w;
    id[i] = trie.add(w);
  }
  vector<bool> is_word(trie.go.size());
  for (int i : id) {
    is_word[i] = true;
  }
  const int mod = 1e9 + 7;
  int n = s.size();
  vector<int> f(n + 1);
  f[0] = 1;
  for (int i = 0; i < n; i++) {
    int p = 0;
    for (int j = i; j < n; j++) {
      p = trie.go[p][s[j] - 'a'];
      if (p == 0)
        break;
      if (is_word[p]) {
        f[j + 1] += f[i];
        if (f[j + 1] >= mod)
            f[j + 1] -= mod;
      }
    }
  }
  cout << f[n] << '\n';
}