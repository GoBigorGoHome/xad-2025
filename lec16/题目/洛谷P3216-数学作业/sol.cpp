#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif


int k_power_sum(int x, long long n, int k, int mod) {
    vector<vector<int>> C(k + 1, vector<int>(k + 1));
    for (int i = 0; i <= k; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    vector<int> p2(k + 1);
    p2[0] = 1;
    for (int i = 1; i <= k; i++)
        p2[i] = p2[i - 1] * 2 % mod;

    vector<long long> w(k + 1);
    w[k] = 1;
    long long s = 0;
    // 循环不变量：答案 == ans + \sum_{i=0..k} w[i] * f_{n,k}(x)
    while (n > 0) {
        if (n & 1) {
            s += w[0];
            for (int i = 0; i <= k; i++) {
                for (int j = i + 1; j <= k; j++)
                    w[i] += w[j] * C[j][i] % mod;
                w[i] = w[i] % mod * x % mod;
            }
        }
        for (int i = 0; i <= k; i++) {
            long long t = 0;
            for (int j = i; j <= k; j++)
                t += C[j][i] * w[j] % mod;
            w[i] = (w[i] + t % mod * x) % mod * p2[i] % mod;
        }
        x = (long long) x * x % mod;
        n >>= 1;
    }
    return s % mod;
}

int power(long long x, unsigned long long n, int mod) {
    long long ans = 1;
    while (n > 0) {
        if (n & 1)
            ans = ans * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return (int) ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    unsigned long long n;
    int m;
    cin >> n >> m;
    n++;
    long long ans = 0;
    int len = 1;
    for (unsigned long long l = 1; l < n; l *= 10) {
        unsigned long long r = min(l * 10, n);
        long long t = (r - 1) % m * k_power_sum(l * 10 % m, r - l, 0, m) % m - k_power_sum(l * 10 % m, r - l, 1, m);
        ans = ans * power(10, len * (r - l), m) % m + t;
        len++;
    }
    ans %= m;
    if (ans < 0)
        ans += m;
    cout << ans << '\n';
}