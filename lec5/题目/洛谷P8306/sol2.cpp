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
struct compact_trie {
  struct Node {
    vector<int> go;
    unsigned long long mask;
  };
  vector<Node> node;
  int new_node() {
    node.push_back({});
    return node.size() - 1;
  }

  compact_trie() {
    new_node(); //创建根节点
  }

  int get_pos(int p, int i) {
      return __builtin_popcountll(node[p].mask & ((1ull << i) - 1));
  }

  int go(int p, char c) {
    int i = ctoi(c);
    if (node[p].mask >> i & 1)
        return node[p].go[get_pos(p, i)];
    return 0;
  }

  int add(string s) {
    int p = 0;
    for (char c : s) {
      int i = ctoi(c);
      int pos = get_pos(p, i);
      if ((node[p].mask >> i & 1) == 0) {
        int k = new_node();
        node[p].go.insert(node[p].go.begin() + pos, k);
        node[p].mask |= 1ull << i;
      }
      p = node[p].go[pos];
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
        compact_trie<62> trie;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            trie.add(s[i]);
        }
        vector<int> cnt(trie.node.size());
        for (int i = 0; i < n; i++) {
            int p = 0;
            for (char c : s[i]) {
                p = trie.go(p, c);
                cnt[p]++;
            }
        }
        for (int i = 0; i < q; i++) {
            string t;
            cin >> t;
            int p = 0;
            for (char c : t) {
                p = trie.go(p, c);
                if (p == 0) break;
            }
            cout << (p == 0 ? 0 : cnt[p]) << '\n';
        }
    }
}

/*
1
3 3
fusufusu
fusu
anguei
fusu
anguei
kkksc
*/