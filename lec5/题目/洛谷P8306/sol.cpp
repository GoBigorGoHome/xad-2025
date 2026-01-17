#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int ctoi(char c) {
    if ('a' <= c && c <= 'z') {
        return c - 'a';
    }
    if ('A' <= c && c <= 'Z') {
        return c - 'A' + 26;
    }
    return c - '0' + 52;
}

template <int sigma_size>
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
      int i = ctoi(c);
      if (go[p][i] == 0) {
        go[p][i] = new_node();
      }
      p = go[p][i];
    }
    return p;
  }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;
        vector<string> s(n);
        Trie<62> trie;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            trie.add(s[i]);
        }
        vector<int> cnt(trie.go.size());
        for (int i = 0; i < n; i++) {
            int p = 0;
            for (char c : s[i]) {
                p = trie.go[p][ctoi(c)];
                cnt[p]++;
            }
        }
        for (int i = 0; i < q; i++) {
            string t;
            cin >> t;
            int p = 0;
            for (char c : t) {
                p = trie.go[p][ctoi(c)];
                if (p == 0) break;
            }
            cout << (p == 0 ? 0 : cnt[p]) << '\n';
        }
    }
}