#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

// 分块
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    
    int B = (int) sqrt(n);
    int NB = (n + B - 1) / B;
    
    vector<bool> mark(NB);
    vector<int> val(NB);

    auto push = [&](int ib) {
        if (mark[ib]) {
            for (int i = ib * B; i < (ib + 1) * B; i++) {
                a[i] = val[ib];
            }
            mark[ib] = false;
        }
    };
    int q = n;
    while (q--) {
        int l, r, c;
        cin >> l >> r >> c;
        l--;
        int lb = (l + B - 1) / B;
        int rb = r / B;
        int ans = 0;
        debug(l, r, lb, rb);
        if (lb > rb) {
            push(lb - 1);
            for (int i = l; i < r; i++) {
                ans += a[i] == c;
                a[i] = c;
            }
        } else {
            if (l < lb * B) {
                push(lb - 1);
                for (int i = l; i < lb * B; i++) {
                    ans += a[i] == c;
                    a[i] = c;
                }
            }
            if (rb * B < r) {
                push(rb);
                for (int i = rb * B; i < r; i++) {
                    ans += a[i] == c;
                    a[i] = c;
                }
            }
            for (int i = lb; i < rb; i++) {
                if (mark[i]) {
                    ans += (val[i] == c) * B;
                } else {
                    for (int j = i * B; j < (i + 1) * B; j++)
                        ans += a[j] == c;
                }
                mark[i] = true;
                val[i] = c;
            }
        }
        cout << ans << '\n';
    }
}