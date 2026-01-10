#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

struct eertree {
  struct node {
    int len; //节点对应的回文子串的长度
    int link; //最长回文严格后缀对应的节点
    int go[26];

  };

  vector<node> a; //存储节点的数组
  vector<int> s; //当前字符串
  int p; //当前字符串的最长回文后缀对应的节点

  eertree() {
    a.push_back({-1, -1});
    a.push_back({0, 0});
    p = 1;
  }

  int add(int c) { //在当前字符串末尾添加字符c，c是0到25的整数
    int i = s.size(); // 已经添加了 i 个字符
    s.push_back(c);
    // 第一步
    while (p && (a[p].len == i || s[i - 1 - a[p].len] != c)) { // 沿着后缀链接跳
      p = a[p].link;
    }
    if (a[p].go[c] != 0) { // 没有新的回文子串
      p = a[p].go[c];
      return p;
    }
    // 第二步：新增一个节点，编号是 a.size()
    a[p].go[c] = a.size();
    int len = a[p].len + 2;
    // 计算新节点的后缀链接
    int link;
    if (p == 0) link = 1;
    else {
      while (1) { // 沿着后缀链接跳
        p = a[p].link;
        if (s[i - 1 - a[p].len] == c)
          break;
      }
      link = a[p].go[c];
    }
    p = a.size();
    a.push_back({len, link});
    return p;
  }
};

int main() {
  string s;
  cin >> s;
  eertree tree;
  vector<int> max_suff;
  for (char c : s) {
    max_suff.push_back(tree.add(c - 'a'));
  }
  int m = tree.a.size();
  vector<int> occ_as_max(m);
  for (int i : max_suff)
    occ_as_max[i]++;
  vector<int> occ(m);
  for (int i = m - 1; i > 1; i--) {
    occ[i] += occ_as_max[i];
    occ[tree.a[i].link] += occ[i];
  }
  long long ans = 0;
  for (int i = 2; i < m; i++)
    ans = max(ans, (long long) tree.a[i].len * occ[i]);
  cout << ans << '\n';
}