/**
 *    author:  zjs
 *    created: 14.06.2026 23:26:05
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

struct convex_hull_trick { // 每次加入的直线的斜率严格递增
    struct line {
        long long k, b;
    };
    vector<line> lines; // 直线序列
    vector<long long> r; // 交点序列
    void add(long long k, long long b) {
        while (!lines.empty()) {
            // 计算直线 (k, b) 和直线 lines.back() 的交点
            auto [k2, b2] = lines.back();
            assert(k2 < k);
            // k * x + b >= k2 * x + b2  ==>  x >= (b2 - b) / (k - k2)
            long long x = (b2 - b) / (k - k2);
            if (x * k + b < x * k2 + b2)
                x++;
            if (r.size() && x <= r.back()) {
                r.pop_back();
                lines.pop_back();
            } else {
                r.push_back(x);
                break;
            }
        }
        lines.push_back({k, b});
    }
    long long query(long long x) {
        assert(!lines.empty());
        auto pos = upper_bound(r.begin(), r.end(), x) - r.begin();
        return x * lines[pos].k + lines[pos].b;
    }
};

/*
dp[i] = min { dp[j] + ((i - j - 1) + s[i] - s[j] - L) ** 2 }  0 <= j <= i - 1

令 A(i) = i + s[i]
令 B(j) = s[j] + j + L + 1

dp[i] = min { dp[j] + (A(i) - B(j)) ** 2 }  0 <= j <= i - 1

dp[j] + (A(i) - B(j)) ** 2
= dp[j] + A(i) ** 2 + - 2 * A(i) * B(j) + B(j) ** 2
= (B(j) * (-2 * A(i)) + B(j) ** 2 + dp[j]) + A(i) ** 2 

B(j) * (-2 * A(i)) + B(j) ** 2 + dp[j] 可看作直线 y = B(j) * x + B(j) ** 2 + dp[j] 在 x = -2 * A(i) 处的值

模型 dp[i] = min_{0 <= j <= i - 1} \set{ B[j] + K[j]*X[i] + A[i] }
*/

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, L;
    cin >> n >> L;
    convex_hull_trick lines;
    long long dp = 0;
    long long s = 0;
    for (int i = 0; i < n; ) {
        long long B = s + i + L + 1;
        lines.add(B, -(B * B + dp));
        int len;
        cin >> len;
        s += len;
        i++;
        long long A = s + i;
        dp = -lines.query(2 * A) + A * A;
    }
    cout << dp << '\n';
}