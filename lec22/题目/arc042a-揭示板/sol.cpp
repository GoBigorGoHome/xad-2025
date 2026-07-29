/**
 *    author:  zjs
 *    created: 03.06.2026 16:39:11
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
    vector<int> a;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    vector<bool> seen(n + 1);
    for (int x : views::reverse(a))
        if (!seen[x]) {
            cout << x << '\n';
            seen[x] = true;
        }
    for (int i = 1; i <= n; i++)
        if (!seen[i])
            cout << i << '\n';
}