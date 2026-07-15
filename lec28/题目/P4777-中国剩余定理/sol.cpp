/**
 *    author:  zjs
 *    created: 12.07.2026 21:23:40
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

pair<long long, long long> extgcd(long long a, long long b) {
    long long u = 1, v = 0;
    while (b != 0) {
        long long q = a / b;
        a -= q * b;
        u -= q * v;
        swap(a, b);
        swap(u, v);
    }
    assert(a > 0);
    return {a, u};
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long a = 1;
    long long b = 0; // 初始状态：x = 0 (mod 1)
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        long long na, nb;
        cin >> na >> nb;
        /*
        x = b (mod a)
        x = nb (mod na)

        x = a * k1 + b
        x = na * k2 + nb
        a * k1 + b = na * k2 + nb
        a * k1 - na * k2 = nb - b
        */
        auto [g, x] = extgcd(a, na); // a * x + na * y = g,   abs(x) < na
        debug(g, x);
        // a * xx + na * yy = nb - b
        auto [dx, c] = div(nb - b, a); // abs(c) < a
        long long X = (dx + x * (c / g)) % (na / g); // a * X + na * ? = nb - na
        b += a * X;
        a *= na / g; // a = lcm(a, na);
        b %= a;
        debug(a, (long long) b);
    }
    if (b < 0)
        b += a;
    cout << b << '\n';
}