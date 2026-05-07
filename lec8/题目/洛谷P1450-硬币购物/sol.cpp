/**
 *    author:  zjs
 *    created: 06.05.2026 14:35:39
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
    vector<int> c(4);
    for (int i = 0; i < 4; i++)
        cin >> c[i];

    int maxs = 1e5;
    vector<long long> dp(maxs + 1);
    dp[0] = 1;
    for (int x : c) {
        for (int i = x; i <= maxs; i++) {
            dp[i] += dp[i - x];
        }
    }

    int n;
    cin >> n;
    while (n--) {
        vector<int> d(4);
        for (int i = 0; i < 4; i++)
            cin >> d[i];
        int s;
        cin >> s;
        long long ans = 0;
        for (unsigned t = 0; t < 1 << 4; t++) {
            long long ns = s;
            for (int i = 0; i < 4; i++) {
                if (t >> i & 1)
                    ns -= (long long) (d[i] + 1) * c[i];
            }
            if (ns >= 0)
                ans += (popcount(t) & 1 ? -dp[ns] : dp[ns]);
        }
        cout << ans << '\n';
    }
}