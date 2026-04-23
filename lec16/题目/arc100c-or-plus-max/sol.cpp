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
    int n;
    cin >> n;
    vector<pair<int,int>> f(1 << n);
    for (int i = 0; i < 1 << n; i++)
        cin >> f[i].first;
    
    for (int i = 0; i < n; i++)
        for (int s = 0; s < 1 << n; s++)
            if (s >> i & 1) {
                auto [v1, v2] = f[s];
                auto [v3, v4] = f[s ^ (1 << i)];
                vector<int> t = {v1, v2, v3, v4};
                sort(t.rbegin(), t.rend());
                f[s] = {t[0], t[1]};
            }
    int ans = 0;
    for (int k = 1; k < 1 << n; k++) {
        ans = max(ans, f[k].first + f[k].second);
        cout << ans << '\n';
    }
}