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
    p = 0;
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
        int j = i - 1 - a[p].len; 
        if (s[j] == c)
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
  int k = 0;
  eertree tree;
  vector<int> cnt_suff(s.size() + 2);
  for (char c : s) {
    int p = tree.add((c - 'a' + k) % 26);
    if (cnt_suff[p] == 0) { //节点p是新的
      cnt_suff[p] = cnt_suff[tree.a[p].link] + 1;
    }
    k = cnt_suff[p];
    cout << k << ' ';
  }
  cout << '\n';
}