/*
给最优解加一个限制

每次涂色两端的格子一定是涂成目标颜色。就是说两端的格子以后不会再被涂色了。

子问题 (l, r)：把第l到第r个格子由无色涂成目标颜色，最少要涂多少次？

推论：若 color[l] == color[r]，那么有一个最优解的第一步是把第 l 到第 r 个格子都涂成第 color[l]。
此时子问题 (l, r) 化为子问题 (l, r - 1)。这一点不容易看出来。
考虑两端的两个格子。
*/


/**
 *    author:  zjs
 *    created: 04.07.2026 22:58:40
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

// dp[l][r]：把第l到第r个格子由无色涂成目标颜色，最少要涂多少次？
string color;
int dp[50][50];

// 笨方法
int solve(int l, int r) {
    if (l == r) return 1;
    if (dp[l][r] != -1)
        return dp[l][r];
    int ans = 100;
    // 第一步是把第 l 到第 i 个格子涂成颜色 color[l]
    for (int i = l; i < r; i++)
        if (color[i] == color[l]) // 这个条件不写也行。
            ans = min(ans, solve(l, i) + solve(i + 1, r));

    // 第一步是把第 l 到第 r 个格子涂成 color[l]
    if (color[l] == color[r])
        ans = min(ans, solve(l, r - 1));
    return dp[l][r] = ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> color;
    // string s;
    // cin >> s;
    // for (char c : s)
    //     if (color.empty() || c != color.back())
    //         color.push_back(c);
    // debug(color);
    memset(dp, -1, sizeof dp);
    cout << solve(0, (int) color.size() - 1) << '\n';
}

// ujpnpjmj  5
// jpnpjmj 4