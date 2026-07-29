// 先放 1, 3, 然后用2把它们隔开
/**
 *    author:  zjs
 *    created: 16.05.2026 20:16:15
**/
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int x1, x2, x3;
    cin >> x1 >> x2 >> x3;
    // 枚举有多少个位置有3
    const int mod = 998244353;
    const int maxn = 3e6 + 5;
    auto power = [&](long long x, int n) {
        long long ans = 1;
        while (n) {
            if (n & 1)
                ans = ans * x % mod;
            x = x * x % mod;
            n >>= 1;
        }
        return ans;
    };
    vector<long long> f(maxn), invf(maxn);

    f[0] = 1;
    for (int i = 1; i < maxn; i++)
        f[i] = i * f[i - 1] % mod;
    invf[maxn - 1] = power(f[maxn - 1], mod - 2);
    for (int i = maxn - 1; i > 0; i--)
        invf[i - 1] = invf[i] * i % mod;

    auto choose = [&] (int n, int k) -> long long {
        // cerr << "choose: " << n << ' ' << k << '\n';
        if (k < 0 || k > n) return 0;
        return f[n] * invf[n - k] % mod * invf[k] % mod;
    };

    auto mchoose = [&](int n, int k) -> long long {
        return choose(n + k - 1, k);
    };

    long long ans = 0;

    for (unsigned i = 0; i < 4; i++) {
        for (int j = 0; j < x1; j++) {
            // if (popcount(i) + j > x3) continue;
            // if (popcount(i) + 2 * j > x2) continue;
            // 哪些地方有3
            int pos3 = popcount(i) + j;
            ans += choose(x1 - 1, j) * mchoose(pos3, x3 - pos3) % mod * mchoose(x1 + x3 + 1, x2 - (popcount(i) + 2 * j)) % mod;
        }
    }
    cout << ans % mod << '\n';
}