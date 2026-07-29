/**
 *    author:  zjs
 *    created: 10.06.2026 20:38:45
**/
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
    long long n;
    cin >> n;
    vector<long long> ans;
    for (long long x = n; x >= 1; ) {
        long long y = n / x;
        ans.push_back(y);
        x = n / (y + 1);
    }
    cout << ans.size() << '\n';
    for (long long q : ans)
        cout << q << ' ';
    cout << '\n';
}
