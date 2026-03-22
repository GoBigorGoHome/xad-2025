// 超时
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
    int n; cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    
    int B = (int) sqrt(n);
    int NB = (n + B - 1) / B;

    vector<multiset<long long>> b(NB);
    vector<long long> add(NB);

    for (int i = 0; i < n; i++)
        b[i / B].insert(a[i]);

    int q = n;
    while (q--) {
        int type, l, r, c;
        cin >> type >> l >> r >> c;
        l--;
        int lb = (l + B - 1) / B;
        int rb = r / B;
        if (type == 0) {
            if (lb > rb) {
                for (int i = l; i < r; i++) {
                    b[lb - 1].extract(a[i]); // since C++17
                    a[i] += c;
                    b[lb - 1].insert(a[i]);
                }
            } else {
                for (int i = l; i < lb * B; i++) {
                    b[lb - 1].extract(a[i]);
                    a[i] += c;
                    b[lb - 1].insert(a[i]);
                }
                for (int i = rb * B; i < r; i++) {
                    b[rb].extract(a[i]);
                    a[i] += c;
                    b[rb].insert(a[i]);
                }
                for (int i = lb; i < rb; i++)
                    add[i] += c;
            }
        }
        else {
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
                    auto it = b[i].lower_bound(c - add[i]);
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