#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif


const int mod = 1e9 + 7;
const int maxk = 2005;
int C[maxk][maxk]; // 组合数
int p2[maxk]; // 2的幂

// 非递归写法
int solve(int x, long long n, int k) {
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

int main() {
    long long n;
    int a, k;
    cin >> n >> a >> k;

    for (int i = 0; i <= k; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    p2[0] = 1;
    for (int i = 1; i <= k; i++)
        p2[i] = p2[i - 1] * 2 % mod;

    int ans = solve(a, n + 1, k);
    if (k == 0) {
        ans--;
        if (ans < 0) ans += mod;
    }
    cout << ans << '\n';
}