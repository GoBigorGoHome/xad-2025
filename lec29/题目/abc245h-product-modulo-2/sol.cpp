/**
 *    author:  zjs
 *    created: 18.07.2026 10:33:45
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

template<typename T> std::vector<std::pair<T, int>> factorize_p(T n) {
  assert(n > 0);
  std::vector<std::pair<T, int>> res;
  unsigned long long N = n;
  for (unsigned long long i = 2; i * i <= N; ++i) {
    int cnt = 0;
    while (N % i == 0) {
      N /= i;
      ++cnt;
    }
    if (cnt) {
      res.emplace_back(i, cnt);
    }
  }
  if (N > 1) {
    res.emplace_back(N, 1);
  }
  return res;
}

const int mod = 998244353;

long long power(long long x, long long n) {
    x %= mod;
    long long ans = 1;
    while (n > 0) {
        if (n & 1)
            ans = ans * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ans;
}

long long mchoose(long long n, long long r) {
    long long fz = 1, fm = 1;
    for (int i = 0; i < r; i++) {
        fz = fz * (n + i) % mod;
        fm = fm * (1 + i) % mod;
    }
    return fz * power(fm, mod - 2) % mod;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long k, n, m;
    cin >> k >> n >> m;
    long long ans = 1;
    for (auto [p, a] : factorize_p(m)) {
        debug(p, a);
        long long q = 1;
        for (int i = 0; i < a; i++)
            q *= p;
        long long r = n % q;
        int b = 0;
        if (r == 0) {
            b = a;
        } else {
            while (r % p == 0) {
                r /= p;
                b++;
            }
        }
        if (b < a) {
            //  mchoose(k, b) * power(p - 1, k) * power(p, (a - 1) * k - b) / ((p - 1) * power(p, a - 1 - b))
            //= mchoose(k, b) * power(p - 1, k - 1) * power(p, (a - 1) * (k - 1))
            ans *= mchoose(k, b) * power(p - 1, k - 1) % mod * power(p, (a - 1) * (k - 1)) % mod;
        } else { // b == a
            long long ex = 0;
            for (int i = 0; i < a; i++) {
                ex += mchoose(k, i) * power(p - 1, k) % mod * power(p, (a - 1) * k - i) % mod;
            }
            ex %= mod;
            ans *= power(q, k) - ex;
        }
        ans %= mod;
    }
    if (ans < 0)
        ans += mod;
    cout << ans << '\n';
}