/**
 *    author:  zjs
 *    created: 15.05.2026 14:54:13
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
    int n;
    cin >> n;
    vector<long long> cnt(n + 1);
    for (int d = n; d >= 1; d--) {
        long long tot = (long long) (n / d) * (n / d);
        for (int i = 2 * d; i <= n; i += d)
            tot -= cnt[i];
        cnt[d] = tot;
    }
    long long sum = 0;
    for (int d = 1; d <= n; d++) {
        sum += d * cnt[d];
    }
    cout << sum << '\n';
}