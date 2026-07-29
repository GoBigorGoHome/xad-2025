/**
 *    author:  zjs
 *    created: 15.06.2026 12:37:41
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
    // 一个人的等待时间 = 他乘的车的出发时刻 - 他到车站的时刻
    // 性质：
    // 1. 如果摆渡车到站后发现没人在等车，那它不应该立即出发，而应该等到有人来再出发。
    // 2. 假设某次摆渡车到站时已经有人在等车了。
    //      如果摆渡车等了几分钟才出发，但是在等待期间没有新的学生来，那不如不等。
    //      等待时间在 0 到 m - 1 之间。

    // 性质2的证明：
    // 在那种情况下，立即出发和等 m 分钟出发，效果是一样的。根据性质1，一旦花时间等了，就一定要等到有人到达的时刻才出发。
    
    // 推论：
    // 1. 摆渡车到达车站后，要么立即出发，要么等某个人到达车站再出发。
    // 2. 摆渡车首次出发的时刻应该是有人到车站的时刻。

    // 第一次发车的时刻在 [t[0], t[0] + m) 范围内
    vector<int> sum(n + 1);
    for (int i = 0; i < n; i++)
        sum[i + 1] = t[i] + sum[i];
    vector<int> dp(n, INT_MAX);
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        dp[i] = min(dp[i], i * t[i] - sum[i]); // 摆渡车第一次出发是在 t[i] 时刻
        vector<int> wait(n);
        for (int j = i + 1; j < n; j++) {
            int r = (t[j] - t[i]) % m;
            wait[j] = wait[j - 1] + (r ? m - r : 0);
            if (t[j] >= t[i] + m) {//在t[i]时刻出发，连续运行若干次，下一次在 t[j] 时刻出发。
                int last = t[j] - r - m; // 上一趟车的出发时刻
                int extra = 0; //在 t[j] 时刻出发的人，总的等待时间。
                int k = j;
                while (k > i && t[k] > last) {
                    extra += t[j] - t[k];
                    k--;
                }
                dp[j] = min(dp[j], dp[i] + wait[k] + extra);
            }
        }
        ans = min(ans, dp[i] + wait[n - 1]);
    }
    cout << ans << '\n';
}
