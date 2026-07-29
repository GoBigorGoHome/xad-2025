
/**
 *    author:  zjs
 *    created: 15.06.2026 10:30:10
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

struct convex_hull_trick { 
    struct line {
        long long k, b;
    };
    vector<line> lines; // 直线序列
    vector<long long> r; // 交点序列
    void add(long long k, long long b) {
        assert(lines.empty() || lines.back().k <= k); //每次加入的直线的斜率递增
        while (!lines.empty()) {
            auto [k2, b2] = lines.back();
            long long x;  //计算直线 (k, b) 和直线 (k2, b2) 的交点
            if (k == k2) {
                if (b < b2) return;
                x = LLONG_MIN;
            } else {
                // k * x + b >= k2 * x + b2  ==>  x >= (b2 - b) / (k - k2)
                x = (b2 - b) / (k - k2);
                if (x * k + b < x * k2 + b2)
                    x++;
            }
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
dp[i] = min_{j} { dp[j] + (s + sumT[i] - sumT[j]) * (sumC[n] - sumC[j]) }

令 A[j] = -(sumC[n] - sumC[j])
B[i] = s + sumT[i]
C[j] = -sumT[j]

dp[j] + (B[i] + C[j]) * -A[j]
= A[j] * -B[i] - A[j] * C[j] + dp[j]

dp[i] = -max(A[j] * B[i] + A[j] * C[j] - dp[j])
*/

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, s;
    cin >> n >> s;
    vector<pair<int,int>> tc(n);
    int totC = 0;
    for (int i = 0; i < n; i++) {
        cin >> tc[i].first >> tc[i].second;
        totC += tc[i].second;
    }
    convex_hull_trick lines;
    long long dp = 0;
    int sumT = 0, sumC = 0;
    for (auto [T, C] : tc) {
        long long A = sumC - totC;
        long long B = A * -sumT - dp; // A * -sumT 可能暴 int.
        lines.add(A, B);
        sumC += C;
        sumT += T;
        int X = s + sumT;
        dp = -lines.query(X);
    }
    cout << dp << '\n';
}