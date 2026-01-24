#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

struct Hash { // 不要起名为 hash，因为标准库里有名为 hash 的结构体。
  const long long mod = 1e9 + 7;
  long long base = 857; // 随机设置
  static vector<long long> power; // 为了避免重复计算
  vector<long long> pref;
  int n;

  void ensure_power(int sz) {
    int cur = (int) power.size();
    if (cur < sz) {
      power.resize(sz);
      for (int i = cur; i < sz; i++) {
        power[i] = power[i - 1] * base % mod;
      }
    }
  }

  Hash(string s) {
    n = (int) s.size();
    ensure_power(n + 1);
    pref.resize(n + 1);
    pref[0] = 0;
    for (int i = 0; i < n; i++) {
      pref[i + 1] = (pref[i] * base % mod + s[i]) % mod;
    }
  }

  long long get(int l, int r) {
    long long res = pref[r + 1] - power[r - l + 1] * pref[l] % mod;
    if (res < 0) res += mod;
    return res;
  }

   long long get(string s) {
    ensure_power(s.size());
    long long res = 0;
    for (char c : s) {
      res = (res * base + c) % mod;
    }
    return res;
  }
};

vector<long long> Hash::power(1, 1);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    Hash h("");
    set<long long> a;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        a.insert(h.get(s));
    }
    cout << a.size() << '\n';
}