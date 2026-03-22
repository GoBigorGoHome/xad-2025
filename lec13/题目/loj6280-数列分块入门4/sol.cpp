//区间加，区间和
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

    vector<long long> add(NB);
    vector<long long> sum(NB);
    for (int i = 0; i < n; i++)
        sum[i / B] += a[i];
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
                    a[i] += c;
                    sum[lb - 1] += c;
                }
            } else {
                for (int i = l; i < lb * B; i++) {
                    a[i] += c;
                    sum[lb - 1] += c;
                }
                for (int i = rb * B; i < r; i++) {
                    a[i] += c;
                    sum[rb] += c;
                }
                for (int i = lb; i < rb; i++)
                    add[i] += c;
            }
        } else {
            long long ans = 0;
            if (lb > rb)
                for (int i = l; i < r; i++)
                    ans += a[i] + add[lb - 1];
            else {
                for (int i = l; i < lb * B; i++)
                    ans += a[i] + add[lb - 1];
                for (int i = rb * B; i < r; i++)
                    ans += a[i] + add[rb];
                for (int i = lb; i < rb; i++)
                    ans += sum[i] + add[i] * B;
            }
            ans %= c + 1;
            if (ans < 0) ans += c + 1;
            cout << ans << '\n';
        }
    }
}
