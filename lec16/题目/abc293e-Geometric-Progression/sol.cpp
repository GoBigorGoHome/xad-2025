#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int mod;

long long f(long long x, long long n) {
    if (n == 0)
        return 0;
    if (n & 1)
        return (1 + x * f(x, n - 1)) % mod;
    return (1 + x) * f(x * x % mod, n >> 1) % mod;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int A; long long X;
    cin >> A >> X >> mod;
    debug(f(9, 2));
    debug(f(18, 1));
    cout << f(A, X) % mod << '\n';
}