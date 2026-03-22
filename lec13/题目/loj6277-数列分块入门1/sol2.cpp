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
    vector<long long> a(2 * n);
    for (int i = 0; i < n; i++)
        cin >> a[i + n];

    int q = n;
    while (q--) {
        int type, l, r; long long c;
        cin >> type >> l >> r >> c;
        if (type == 0) {
            l--;
            l += n;
            r += n;
            while (l < r) {
                if (l & 1) a[l++] += c;
                if (r & 1) a[--r] += c;
                l /= 2;
                r /= 2;
            }
        } else {
            r--;
            r += n;
            long long ans = 0;
            while (r) {
                ans += a[r];
                r /= 2;
            }
            cout << ans << '\n';
        }
    }
}