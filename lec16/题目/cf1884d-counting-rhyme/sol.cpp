/*
对每个 d = 1, ..., n 定义
f[d] := 满足 gcd(a[i], a[j]) == d 的 i, j 有多少对。

对每个d = 1, ..., n 定义
g[d] := 满足 d | gcd(a[i], a[j]) 的  i, j 有多少对，
即满足 d | a[i] 且 d | a[j] 的 i, j 有多少对。

对每个d = 1, ..., n 定义
mul[d]：a[1], ..., a[n] 中有多少个 d 的倍数    

g[d] = {mul[d] \choose 2}

f[d] = g[d] - \sum_{k >= 2} f[k*d]


对每个 i = 1, ..., n 定义
div[i] := 有多少个 k 满足 a[k] 整除 i

原问题的答案为 sum_{d = 1}^{n} [div[d] == 0] * f[d]

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
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> cnt(n + 1);
        vector<int> mul(n + 1);
        vector<int> div(n + 1);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            cnt[x]++;
        }
        // sum over multiples
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j += i)
                mul[i] += cnt[j];

        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j += i)
                div[j] += cnt[i];

        vector<long long> f(n + 1);

        long long ans = 0;
        for (int  i = n; i >= 1; i--) {
            f[i] = (long long) mul[i] * (mul[i] - 1) / 2;
            for (int j = 2 * i; j <= n; j += i)
                f[i] -= f[j];
            if (div[i] == 0)
                ans += f[i];
        }
        cout << ans << '\n';
    }
}