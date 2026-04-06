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
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> prev(n, -1), next(n, n);
    vector<int> last((int) 5e5 + 5, -1);
    for (int i = 0; i < n; i++) {
        prev[i] = last[a[i]];
        if (prev[i] != -1)
            next[prev[i]] = i;
        last[a[i]] = i;
    }

    int B = (int) sqrt(n);
    int NB = n / B;
    vector<int> f(NB, n);
    for (int i = 0; i < NB; i++) {
        int l = i * B, r = l + B;
        int t = l;
        for (int j = l + 1; j < r; j++)
            if (prev[j] < l && next[j] > next[t])
                t = j;
        f[i] = t;
    }

    debug(prev);
    debug(next);
    auto query = [&](int l, int r) {
        int lb = (l + B - 1) / B;
        int rb = r / B;
        for (int i = l; i < lb * B; i++)
            if (prev[i] < l && next[i] >= r)
                return a[i];
        for (int i = lb; i < rb; i++)
            if (prev[f[i]] < l && next[f[i]] >= r)
                return a[f[i]];
        for (int i = lb * B; i < r; i++)
            if (prev[i] < l && next[i] >= r)
                return a[i];
        return 0;
    };

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(l - 1, r) << '\n';
    }
}