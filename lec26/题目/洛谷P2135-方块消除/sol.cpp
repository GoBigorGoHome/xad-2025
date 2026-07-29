/**
 *    author:  zjs
 *    created: 05.07.2026 10:46:54
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
int color[50];
int a[50];
int dp[1000][50][50];

int solve(int cnt, int l, int r) {
    if (l == r) {
        return (a[l] + cnt) * (a[l] + cnt);
    }
    if (dp[cnt][l][r])
        return dp[cnt][l][r];
    int ans = (a[l] + cnt) * (a[l] + cnt) + solve(0, l + 1, r);
    for (int i = l + 1; i <= r; i++) {
        if (color[i] == color[l])
            ans = max(ans, solve(0, l + 1, i - 1) + solve(cnt + a[l], i, r));
    }
    return dp[cnt][l][r] = ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> color[i];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << solve(0, 0, n - 1)  << '\n';
}