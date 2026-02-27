#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

const int mod = 1e9 + 7;
int C[405][405];

int power(int x, int n) {
    int ans = 1;
    while (n) {
        if (n & 1)
            ans = (long long) ans * x % mod;
        x = (long long) x * x % mod;
        n >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i <= 400; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            if (C[i][j] >= mod)
                C[i][j] -= mod;
        }
    }

    int n, m, c;
    cin >> n >> m >> c;
    long long ans = 0;
    for (int k = 1; k <= c; k++) {
        long long sum = 0;
        for (int a = 0; a <= n; a++)
            for (int b = 0; b <= m; b++) {
                long long t = (long long) C[n][a] * C[m][b] % mod * power(k + 1, n * m - (a * m + b * n - a * b)) % mod;
                sum += ((a + b) & 1 ? -t : t);
            }
        long long t = sum % mod * C[c][k] % mod;
        ans += ((c - k) & 1 ? -t : t);
    }
    ans %= mod;
    if (ans < 0) ans += mod;
    cout << ans << '\n';
}