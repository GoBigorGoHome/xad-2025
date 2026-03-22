// 区间加，单点询问
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
    vector<long long> b(NB);
    int q = n;
    while (q--) {
        int type, l, r; long long c;
        cin >> type >> l >> r >> c;
        if (type == 0) {
            --l;
            int lb = (l + B - 1) / B;
            int rb = r / B;
            if (lb > rb)
                for (int i = l; i < r; i++) {
                    a[i] += c;
                }
            else {
                for (int i = l; i < lb * B; i++)
                    a[i] += c;
                for (int i = lb; i < rb; i++)
                    b[i] += c;
                for (int i = rb * B; i < r; i++)
                    a[i] += c;
            }
        } else {
            r--;
            cout << a[r] + b[r / B] << '\n';
        }
    }
}