/**
 *    author:  zjs
 *    created: 05.07.2026 12:20:58
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int a[105];
int dp[105][105];
int solve(int l, int r) {
    if (l + 1 == r)
        return 0;
    if (dp[l][r] != -1)
        return dp[l][r];
    int ans = INT_MAX;
    for (int i = l + 1; i < r; i++)
        ans = min(ans, a[r] - a[l] - 2 + solve(l, i) + solve(i, r));
    return dp[l][r] = ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int p, q;
    cin >> p >> q;
    for (int i = 1; i <= q; i++)
        cin >> a[i];
    a[q + 1] = p + 1;
    memset(dp, -1, sizeof dp);
    cout << solve(0, q + 1) << '\n';
}