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
    vector<long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    
    int B = (int) sqrt(n);
    int NB = (n + B - 1) / B;
    debug(B);
    vector<vector<long long>> b(NB);
    vector<long long> add(NB);

    auto build = [&](int i) {
        int l = i * B, r = min(n, (i + 1) * B);
        b[i].assign(a.begin() + l, a.begin() + r);
        sort(b[i].begin(), b[i].end());
    };

    for (int i = 0; i < NB; i++) {
        build(i);
    }

    int q = n;
    while (q--) {
        int type, l, r;
        long long c;
        cin >> type >> l >> r >> c;
        l--;
        int lb = (l + B - 1) / B;
        int rb = r / B;
        
        if (type == 0) {
            if (lb > rb) {
                for (int i = l; i < r; i++) {
                    a[i] += c;
                }
                build(lb - 1);
            } else {
                for (int i = l; i < lb * B; i++)
                    a[i] += c;
                for (int i = rb * B; i < r; i++)
                    a[i] += c;
                for (int i = lb; i < rb; i++)
                    add[i] += c;
                if (l != lb * B) {
                    build(lb - 1);
                    // 也可以写
                    // inplace_merge(a.begin() + l / B * B, a.begin() + l, a.begin() + lb * B);
                }
                if (r != rb * B) {
                    build(rb);
                }
            }
        } else {
            long long ans = LLONG_MIN;
            if (lb > rb) {
                for (int i = l; i < r; i++)
                    if (a[i] + add[lb - 1] < c)
                        ans = max(ans, a[i] + add[lb - 1]);
            } else {
                for (int i = l; i < lb * B; i++)
                    if (a[i] + add[lb - 1] < c)
                        ans = max(ans, a[i] + add[lb - 1]);
                for (int i = rb * B; i < r; i++) {
                    if (a[i] + add[rb] < c)
                        ans = max(ans, a[i] + add[rb]);
                }
                for (int i = lb; i < rb; i++) {
                    auto it = lower_bound(b[i].begin(), b[i].end(), c - add[i]);
                    if (it != b[i].begin())
                        ans = max(ans, *prev(it) + add[i]);
                }
            }
            if (ans == LLONG_MIN)
                ans = -1;
            cout << ans << '\n';
        }
    }
}