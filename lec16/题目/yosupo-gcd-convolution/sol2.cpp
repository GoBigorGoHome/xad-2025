/*

*/

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

const int mod = 998244353;

vector<long long> gcd_covolution(vector<long long>& a, vector<long long>& b, int n) {
    // 第一步：计算 sum over multiples (supersets)
    vector<bool> is_prime(n + 1, true);
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            for (int j = n / i; j >= 1; j--) {
                a[j] += a[j * i];
                b[j] += b[j * i];
            }
            for (int j = 2 * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    // 第二步：给 c[i] 赋初值
    vector<long long> c(n + 1);
    for (int i = 1; i <= n; i++)
        c[i] = (a[i] % mod) * (b[i] % mod) % mod;
    // 第三步：扣除（这一步不好懂）
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            for (int j = 1; j * i <= n; j++)
                c[j] -= c[j * i];
        }
    }
    for (int i = 1; i <= n; i++) {
        c[i] %= mod;
        if (c[i] < 0)
            c[i] += mod;
    }
    return c;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<long long> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    auto c = gcd_covolution(a, b, n);

    for (int i = 1; i <= n; i++)
        cout << c[i] << ' ';
    cout << '\n';
}