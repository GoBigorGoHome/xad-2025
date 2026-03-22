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

    int B = (int) sqrt(n);

    struct S {
        int to;
        int step;
    };
    vector<S> b(n);
    
    for (int i = n - 1; i >= 0; i--) {
        int to = i + a[i];
        int r = min(n, (i / B + 1) * B);
        if (to >= r) {
            b[i] = {to, 1};
        } else {
            b[i] = {b[to].to, b[to].step + 1};
        }
    }
    
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int p;
            cin >> p;
            int ans = 0;
            while (p < n) {
                ans += b[p].step;
                p = b[p].to;
            }
            cout << ans << '\n';
        } else {
            int p, k;
            cin >> p >> k;
            int l = p / B * B;
            int r = min(n, l + B);
            a[p] = k;
            for (int i = p; i >= l; i--) {
                int to = i + a[i];
                if (to >= r)
                    b[i] = {to, 1};
                else
                    b[i] = {b[to].to, b[to].step + 1};
            }
        }
    }
}