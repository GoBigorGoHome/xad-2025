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
  int m, n;
  cin >> m >> n;
  Trie<2, '0'> trie;
  vector<string> s(m);
  for (int i = 0; i < m; i++) {
    int len; cin >> len;
    s[i].resize(len);
    for (int j = 0; j < len; j++)
      cin >> s[i][j];
    trie.add(s[i]);
  }
  vector<int> cnt_word(trie.go.size());
  vector<int> cnt_supper(trie.go.size());
  for (int i = 0; i < m; i++) {
    int p = 0;
    for (char c : s[i]) {
      cnt_supper[p]++;
      p = trie.go[p][c - '0'];
    }
    cnt_word[p]++;
  }
  // 回答询问
  for (int i = 0; i < n; i++) {
    int len;
    cin >> len;
    vector<int> t(len);
    for (int j = 0; j < len; j++)
        cin >> t[j];
    
    int p = 0;
    int ans = 0;
    for (int c : t) {
      p = trie.go[p][c];
      if (p == 0) break;
      ans += cnt_word[p];
    }
    if (p)
      ans += cnt_supper[p];
    cout << ans << '\n';
  }
}