/*

*/

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
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    const int mod = 998244353;
    vector<long long> c(n + 1);
    for (int i = n; i >= 1; i--) {
        long long sa = 0, sb = 0;
        for (int j = i; j <= n; j += i) {
            sa += a[j];
            sb += b[j];
        }
        c[i] = (sa % mod) * (sb % mod);
        for (int j = 2 * i; j <= n; j += i) {
            c[i] -= c[j];
        }
        c[i] %= mod;
        if (c[i] < 0)
            c[i] += mod;
    }
    for (int i = 1; i <= n; i++)
        cout << c[i] << ' ';
    cout << '\n';
}