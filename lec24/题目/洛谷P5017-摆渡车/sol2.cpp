/**
 *    author:  zjs
 *    created: 17.06.2026 21:07:01
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> t(n);
    for (int i = 0; i < n; i++)
        cin >> t[i];
    sort(t.begin(), t.end());
    t.push_back(t.back() + 2 * m);

    vector<int> sum(n + 1);
    for (int i = 0; i < n; i++)
        sum[i + 1] = t[i] + sum[i];
    vector<int> dp(n + 1, INT_MAX);
    for (int i = 0; i < n; i++) {
        dp[i] = min(dp[i], i * t[i] - sum[i]); // 摆渡车第一次出发是在 t[i] 时刻
        int wait = 0; //乘坐连续运行的车的那些人的等待时间之和
        // 双指针
        int ptr = i + 1;
        for (int j = i + 1; j <= n; j++) {
            if (t[j] >= t[i] + m) {//在t[i]时刻出发，连续运行若干次，下一次在 t[j] 时刻出发。
                int r = (t[j] - t[i]) % m;
                int last = t[j] - r - m; // 上一趟车的出发时刻
                while (t[ptr] <= last) {
                    int s = (t[ptr] - t[i]) % m;
                    if (s)
                        wait += m - s;
                    ptr++;
                }
                int wait_2 = t[j] * (j - ptr) - (sum[j] - sum[ptr]);
                dp[j] = min(dp[j], dp[i] + wait + wait_2);
            }
        }
    }
    cout << dp[n] << '\n';
}