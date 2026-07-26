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

long long gcd(long long a, long long b) {
    return b == 0 ? abs(a) : gcd(b, a % b);
}

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
    return {a, u};
}

// a * x = c (mod b)
template<typename T>
bool diophantine(T a, T b, T c, T &x, T &g) {
    assert(a != 0 && b != 0);
    auto res = extgcd(a, b);
    g = res.first;
    x = res.second;
    if (c % g != 0) {
        return false;
    }
    T dx = c / a;
    c -= dx * a;
    x = ((dx + x * (c / g)) % (b / g));
    g = abs(g);
    return true;
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

    long long A = 1, B = 0;
    for (int i = 0; i < k; i++) {
      // x = B (mod A)
      // x = -i (mod a[i])
      // A * X = -i - B (mod a[i])
      long long x, g;
      bool ok = diophantine(A, a[i], -i - B, x, g);
      if (!ok || n / A < a[i] / g) {
        cout << "NO\n";
        return 0;
      }
      B += A * x; // abs(x) < a[i] / g  ==> abs(A * x) < lcm(A, a[i])
      A *= a[i] / g;
      B %= A;
    }
    if (B <= 0)
      B += A;
    if (B + k - 1 > m) {
      cout << "NO\n";
      return 0;
    }
    debug(A, B);
    for (int i = 0; i < k; i++) {
      if (gcd(A, B + i) != a[i]) {
        cout << "NO\n";
        return 0;
      }
    }
    cout << "YES\n";
}