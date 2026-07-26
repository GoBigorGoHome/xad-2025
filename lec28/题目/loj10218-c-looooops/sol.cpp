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

using i64 = long long;
pair<i64, i64> extgcd(i64 a, i64 b) { // 返回 gcd(a, b) 和一个整数 x 满足 gcd(a, b) = a * x (mod b).
    i64 u = 1;
    i64 v = 0;
    while (b != 0) {
        i64 q = a / b;
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
    while (1) {
        i64 a, b, c, k;
        cin >> a >> b >> c >> k;
        if (k == 0)
            break;
        k = 1LL << k;
        // a + x * c = b (mod k)
        // x * c = b - a (mod k)
        auto [d, x] = extgcd(c, k);
        debug(d, x);
        if ((b - a) % d)
            cout << "FOREVER\n";
        else {
            x = x * ((b - a) / d) % (k / d);
            debug(x);
            if (x < 0)
                x += k / d;
            cout << x << '\n';
            // x = x0 + (k / d) * t
        }
    }
}

/*
0 55 0 24
3 3 0 24
3 2 1 4
5 4 1 24
5 4 1 31
0 0 0 0
*/