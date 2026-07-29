/**
 *    author:  zjs
 *    created: 28.07.2026 20:49:48
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

pair<vector<int>,vector<int>> get_primes(int n) {
    vector<int> lpf(n + 1);
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (lpf[i] == 0) {
            lpf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p * i > n || p > lpf[i]) break;
            lpf[p * i] = p;
        }
    }
    return {primes, lpf};
}

// Lucy_Hedgehog’s algorithm
long long prime_count(long long n) {
    const int k = (int) sqrt(n);
    vector<long long> v; // n, n/2, n/3, ..., n
    for (int i = 1; i <= k; i++)
        v.push_back(n / i);
    for (int i = n / (k + 1); i >= 1; i--)
        v.push_back(i);
    // 对于 i = 1, 2, ..., k+1 有 n/i == v[i-1]。
    // 对于 i = 1, 2, ..., k 还有，i 是唯一的满足 n/d == n/i 的正整数 d。我们称这些值为大值。
    const int m = (int) v.size();
    vector<long long> f(m);
    for (int i = 0; i < m; i++)
        f[i] = v[i] - 1;
    
    auto [p, lpf] = get_primes(k);
    const int s = (int) p.size();
    for (int i = 0; i < s; i++) {
        f[0] -= f[p[i] - 1] - i;
        if (i == s - 1) break;
        const long long L = (long long) p[i] * p[i];
        const int lim = k / p[i];
        for (int j = p[i + 1] - 1; j < m && v[j] >= L; j++) {
            if (j < k && lpf[j + 1] < p[i + 1]) continue;
            if (j + 1 <= lim) {
                f[j] -= f[(j + 1) * p[i] - 1] - i;
            } else { // v[j] / p[i] <= k
                f[j] -= f[m - v[j] / p[i]] - i;
            }
        }
    }
    return f[0];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    cout << prime_count(n) << '\n';
}