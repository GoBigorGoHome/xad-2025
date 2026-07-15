/**
 *    author:  zjs
 *    created: 15.07.2026 10:48:13
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

template<typename T>
pair<T, T> extgcd(T a, T b) {
    T u = 1, v = 0;
    while (b != 0) {
        T q = a / b;
        a -= q * b;
        u -= q * v;
        swap(a, b);
        swap(u, v);
    }
    assert(a > 0);
    return {a, u};
}

template<typename T>
bool diophantine(T a, T b, T c, T &x, T &y, T &g) {
  if (a == 0 && b == 0) {
    if (c == 0) {
      x = y = g = 0;
      return true;
    }
    return false;
  }
  if (a == 0) {
    if (c % b == 0) {
      x = 0;
      y = c / b;
      g = abs(b);
      return true;
    }
    return false;
  }
  if (b == 0) {
    if (c % a == 0) {
      x = c / a;
      y = 0;
      g = abs(a);
      return true;
    }
    return false;
  }
  g = extgcd(a, b, x, y);
  if (c % g != 0) {
    return false;
  }
  T dx = c / a;
  c -= dx * a;
  T dy = c / b;
  c -= dy * b;
  x = dx + (T) ((__int128) x * (c / g) % b);
  y = dy + (T) ((__int128) y * (c / g) % a);
  g = abs(g);
  return true;
  // |x|, |y| <= max(|a|, |b|, |c|) [tested]
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long n, m;
    int k;
    cin >> n >> m >> k;
    vector<long long> a(k);
    for (int i = 0; i < k; i++)
        cin >> a[i];
    
    using i128 = __int128_t;
    i128 M = 1;
    for (long long x : a)
        M = M * x / gcd(M, x);
    
    int A = 1, B = 0;
    for (int i = 0; i < k; i++) {
        // A, B
        // a[i], -i
    }
    
}