/**
 *    author:  zjs
 *    created: 23.07.2026 15:55:42
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    int m = sqrt(n);
    int q = n / (m + 1);
    cout << q + m << '\n';
    for (int i = 1; i <= q; i++)
        cout << i << ' ';
    for (int i = m; i >= 1; i--)
        cout << n / i << ' ';
    cout << '\n';
}