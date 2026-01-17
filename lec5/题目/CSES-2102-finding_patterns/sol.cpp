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

  vector<int> link; // 后缀链接
  vector<int> bfs; // 按 BFS 序存储的节点
  int get(int p, int i) { //试图从节点p走边i
    while (p != -1 && !go[p][i]) {
      p = link[p];
    }
    return p == -1 ? 0 : go[p][i];
  }

  void calc_suffix_link() {
    link.resize(go.size());
    bfs.resize(go.size());
    int p = 0, q = 0; // 队列的开头和结尾

    link[0] = -1; // 根节点没有后缀链接
    bfs[q++] = 0; // 根节点入队

    while (p != q) {
      int u = bfs[p++]; //出队
      for (int i = 0; i < sigma_size; i++) {
        if (go[u][i]) {
          link[go[u][i]] = get(link[u], i);
          bfs[q++] = go[u][i];
        }
      }
    }
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

  debug(trie.go.size());
  
  trie.calc_suffix_link();
  int p = 0;
  vector<bool> vis(trie.go.size());
  for (char c : t) {
    p = trie.get(p, c - 'a');
    vis[p] = true;
  }
  // 反向传播
  for (int i = trie.go.size() - 1; i > 0; i--) {
    int u = trie.bfs[i];
    if (vis[u])
      vis[trie.link[u]] = true;    
  }
  // 输出答案
  for (int i : id) {
    if (vis[i])
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}