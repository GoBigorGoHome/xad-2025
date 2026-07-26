/**
 *    author:  zjs
 *    created: 09.07.2026 00:12:00
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

pair<int,int> extgcd(int a, int b) { // 返回 gcd(a, b) 和一个整数 x 满足 gcd(a, b) = a * x (mod b).
    int u = 1;
    int v = 0;
    while (b != 0) {
        int q = a / b;
        a -= q * b;
        u -= q * v;
        swap(a, b);
        swap(u, v);
    }
    if (a < 0) {
        a = -a;
        u = -u;
    }
    return {a, u};
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int x, y, m, n, L;
    cin >> x >> y >> m >> n >> L;
    // x + m * t = y + n * t (mod L)
    // (m - n) * t = y - x (mod L)
    auto [d, k] = extgcd(m - n, L);
    if ((y - x) % d) {
        cout << "Impossible\n";
    } else {
        long long t = (long long) k * ((y - x) / d) % (L / d);
        if (t < 0)
            t += L / d;
        cout << t << '\n';
    }
}