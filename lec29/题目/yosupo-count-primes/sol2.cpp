/**
 *    author:  zjs
 *    created: 23.07.2026 12:37:19
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

// Lucy_Hedgehog’s algorithm
long long prime_count(long long n) {
    vector<long long> v; // n/i listed in descending order.
    const int k = sqrt(n);
    for (int i = 1; i <= k; i++)
        v.push_back(n / i);
    for (int i = n / (k + 1); i >= 1; i--)
        v.push_back(i);
    const int m = (int) v.size();

    vector<long long> f(m);
    for (int i = 0; i < m; i++)
        f[i] = v[i] - 1; 
    int cnt = 0; // 已经遇到的素数的个数
    for (int p = 2; p <= k; p++) {
        if (f[m - p] == f[m - p + 1]) // p 不是素数
            continue;
        for (int i = 0; i < m; i++) {
            if (v[i] < (long long) p * p) break;
            long long t = v[i] / p;
            long long j = t <= k ? m - t : n / t - 1; // j 是 t 的下标
            f[i] -= f[j] - cnt;
        }
        cnt++;
    }
    return f[0];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    cout << prime_count(n) << '\n';
}



// Lucy_Hedgehog’s algorithm:
// f(n, i)：从 2 到 n 中去掉最小素因子 <= p[i] 的合数之后，剩下的数的数量。
// f(n, p[i]) 中的数包括下列两部分：
// * 最小素因子 <= p[i] 的素数，即小于等于 p[i] 的素数，一共有 i 个。
// * [2,n]中最小素因子 > p[i] 的数。

// f(n, i) = f(n, i-1) - (2 到 n 中最小素因子等于 p[i] 的合数的数量)
// (2 到 n 中最小素因子等于 p[i] 的合数的数量) = (2 到 n/p 中最小素因子 >= p[i] 的数的数量）
// (2 到 n/p[i] 中最小素因子 >= p[i] 的数的数量）= (2 到 n/p 中最小素因子 > p[i-1] 的数的数量）
// (2 到 n/p[i] 中最小素因子 > p[i-1] 的数的数量）= f(n/p[i], i-1) - (2到 n/p[i] 中小于等于 p[i-1] 的素数的数量)
// (2到 n/p[i] 中     小于等于 p[i-1] 的素数的数量) = i - 1
// 
// 注意到小于 p[i] 的素数的个数，用 f 来表达，就是 f(p[i] - 1, i-1)。
//其实也是 f(p[i - 1], i-1)

// 于是得递推式
// f(n, i) = f(n, i-1) - (f(n/p[i], i-1) - (i-1))