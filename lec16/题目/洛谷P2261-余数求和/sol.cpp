#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    long long ans = (long long) n * k;
    long long sum = 0;
    for (int i = 1; i <= n;) {
        if (i > k) break;
        int j = k / i;
        int ni = min(n, k / j) + 1;
        ans -= (long long) (i + ni - 1) * (ni - i) / 2 * j;
        i = ni;
    }
    cout << ans - sum << '\n';
}