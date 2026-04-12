#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int mod;
long long f(long long x, long long n) {
    long long sum = 0;
    long long prod = 1;
    // 答案 == sum + prod * f(x, n)
    while (n) {
        if (n & 1) {
            sum = (sum + prod) % mod;
            prod = (prod * x) % mod;
        }
        prod = prod * (1 + x) % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return sum;
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