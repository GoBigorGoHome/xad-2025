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
    int n;
    cin >> n;
    const int maxv = 1e6;
    vector<int> cnt(maxv + 1);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    const int mod = 998244353;
    vector<int> inv(maxv + 1); //递推法计算逆元
    inv[1] = 1;
    for (int i = 2; i <= maxv; i++)
        inv[i] = (long long) (mod - mod / i) * inv[mod % i] % mod;
    long long ans = 0;
    vector<long long> f(maxv + 1);
    // f[d]：sum of a[i] * a[j] such that gcd(a[i], a[j]) == d
    for (int d = maxv; d >= 1; d--) {
        long long sum = 0;
        // tot: sum of a[i] * a[j] such that d is a common divisor of a[i] and a[j]
        long long tot = 0;
        for (int i = d; i <= maxv; i += d) {
            tot += cnt[i] * i % mod * sum % mod;
            tot += (long long) cnt[i] * (cnt[i] - 1) / 2 % mod * ((long long) i * i % mod) % mod;
            sum = (sum + (long long) i * cnt[i]) % mod;
        }
        for (int i = 2 * d; i <= maxv; i += d)
            tot -= f[i];
        // if (tot > 0)
        //     debug(d, tot);
        f[d] = tot % mod;
        ans += f[d] * inv[d] % mod;
    }
    debug(f[1], f[2]);
    ans %= mod;
    if (ans < 0) ans += mod;
    cout << ans << '\n';
}