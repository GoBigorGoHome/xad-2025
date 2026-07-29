/**
 *    author:  zjs
 *    created: 12.06.2026 21:42:48
**/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

/*
notes:
lower_bound(x)  ==>  !(elem < x)  ==>  elem should be inclusive r-bound
upper_bound(x)  ==>  x < elem  ==> elem should be exclusive r-bound
*/

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
            if (x * k + b < x * k2 + b)
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
    int n;
    cin >> n;
    convex_hull_trick lines;
    long long F = 0, S = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        lines.add(i,  i * S - F);
        long long a;
        cin >> a;
        S += a;
        F += a * (i + 1);
        ans = max(ans, lines.query(-S) + F);
    }
    cout << ans << '\n';
}
