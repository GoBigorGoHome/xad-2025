/**
 *    author:  zjs
 *    created: 05.07.2026 00:19:48
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

long long dp[400][401];
int color[400];
int X[401];
int n;

long long solve(int p, int len) {
    if (len == 0)
        return 0;
    if (len == 1)
        return X[color[p]] + 1;
    if (dp[p][len])
        return dp[p][len];
    long long ans = LLONG_MAX;
    for (int i = 1; i < len; i++) {
        if (color[p] == color[(p + i - 1) % n])
            ans = min(ans, solve(p, i) + solve((p + i) % n, len - i));
    }
    int q = (p + len - 1) % n;
    if (color[p] == color[q]) {
        for (int i = 1; i < len; i++) {
            if (color[p] == color[(p + i - 1) % n])
                ans = min(ans, solve(p, i) + len - i + solve((p + i) % n, len - i - 1));
        }
    }
    return dp[p][len] = ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> color[i];
    for (int i = 1; i <= n; i++)
        cin >> X[i];

    long long ans = LLONG_MAX;
    for (int i = 0; i < n; i++)
        ans = min(ans, solve(i, n));
    cout << ans << '\n';
}