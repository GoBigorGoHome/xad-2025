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
    for (int d = maxv; d >= 1; d--) {
        long long sum = 0;
        long long sum2 = 0;
        for (int x = d; x <= maxv; x += d) {
            sum += (long long) cnt[x] * x;
            sum2 += (long long) cnt[x] * x * x;
        }
        sum %= mod;
        f[d] = (sum * sum - sum2) % mod * inv[2] % mod; 
        for (int i = 2 * d; i <= maxv; i += d)
            f[d] -= f[i];
        f[d] %= mod;
        ans += f[d] * inv[d] % mod;
    }
    ans %= mod;
    if (ans < 0) ans += mod;
    cout << ans << '\n';
}