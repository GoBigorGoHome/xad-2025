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
int p2[maxk]; // 二的幂
int k;

vector<long long> solve(int x, long long n) { // 返回一个长度是 k + 1 的数组
    vector<long long> ans(k + 1);
    if (n == 0)
        return ans;
    if (n & 1) {
        auto f = solve(x, n - 1);
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= i; j++)
                ans[i] += C[i][j] * f[j] % mod;
            ans[i] = ans[i] % mod * x;
        }
        ans[0]++;
        for (int i = 0; i <= k; i++)
            ans[i] %= mod;
        return ans;
    }
    auto f = solve((long long) x * x % mod, n / 2);
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < i; j++)
            ans[i] += f[j] * C[i][j] % mod * p2[j] % mod;
        ans[i] = (ans[i] % mod * x + (f[i] * p2[i] % mod * (1 + x) % mod)) % mod;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    int a;
    cin >> n >> a >> k;
    for (int i = 0; i <= k; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }

    p2[0] = 1;
    for (int i = 1; i <= k; i++)
        p2[i] = p2[i - 1] * 2 % mod;

    long long ans = solve(a, n + 1)[k];

    if (k == 0) {
        ans--;
        if (ans < 0)
            ans += mod;
    }
    cout << ans << '\n';
}