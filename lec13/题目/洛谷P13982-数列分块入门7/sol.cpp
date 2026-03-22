#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

// 区间修改，单点询问。

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    const int mod = 10007;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= mod;
        if (a[i] < 0) a[i] += mod;
    }
    struct F {
        int mul = 1;
        int add = 0;
    };

    int B = (int) sqrt(n);
    int NB = (n + B - 1) / B;
    vector<F> lz(NB);


    auto push = [&](int ib) {
        for (int i = ib * B; i < min(n, (ib + 1) * B); i++)
            a[i] = (a[i] * lz[ib].mul + lz[ib].add) % mod;
        lz[ib] = {1, 0};
    };

    int q = n;
    while (q--) {
        int type, l, r, c;
        cin >> type >> l >> r >> c;
        if (type == 2) {
            r--;
            int i = r / B;
            cout << (a[r] * lz[i].mul + lz[i].add) % mod << '\n';
        } else {
            l--;
            int lb = (l + B - 1) / B;
            int rb = r / B;
            c %= mod;
            if (c < 0) c += mod;
            F f;
            if (type == 0) f = {1, c};
            else f = {c, 0};
            if (lb > rb) {
                push(lb - 1);
                for (int i = l; i < r; i++) {
                    a[i] = (a[i] * f.mul + f.add) % mod;
                }
            } else {
                if (l < lb * B) {
                    push(lb - 1);
                    for (int i = l; i < lb * B; i++)
                        a[i] = (a[i] * f.mul + f.add) % mod;
                }
                if (rb * B < r) {
                    push(rb);
                    for (int i = rb * B; i < r; i++)
                        a[i] = (a[i] * f.mul + f.add) % mod;
                }
                for (int i = lb; i < rb; i++) {
                    lz[i].mul = (lz[i].mul * f.mul) % mod;
                    lz[i].add = (lz[i].add * f.mul + f.add) % mod;
                }
            }
        }
    }
}