/**
 *    author:  zjs
 *    created: 14.06.2026 19:52:26
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    long long C;
    cin >> N >> C;

    /*
    for i >= 2, we have
    dp[i] = min { dp[j] + h[i] * h[i] - 2 * h[i] * h[j] + h[j] * h[j] + C }  1 <= j <= i - 1.
    
    h[j] * (-2 * h[i]) + (h[j] * h[j] + dp[j]) + (h[i] * h[i] + C)

    dp[i] = min_j { h[j] * (-2 * h[i]) + (h[j] * h[j] + dp[j]) } + h[i] * h[i] + C

    dp[i] = - max_j {  h[j] * (2 * h[i]) - (h[j] * h[j] + dp[j]) } + h[i] * h[i] + C
    */
    convex_hull_trick lines;
    long long h;
    cin >> h;
    long long dp = 0;
    for (int i = 2; i <= N; i++) {
        lines.add(h, -(dp + h * h));
        cin >> h;
        dp = -lines.query(2 * h) + (h * h + C);
    }
    cout << dp << '\n';
}