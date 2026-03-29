#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
const int mod = 10007;

struct F { 
    int mul = 1;
    int add = 0;
};

F composite(F x, F y) { // 先 y 后 x
    return {x.mul * y.mul % mod, (x.mul * y.add + x.add) % mod};
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= mod;
    }


    vector<F> lz(2 * n);

    auto apply = [&](int i, F f) {
        lz[i] = composite(f, lz[i]);
    };
    auto push = [&](int i) { // 下传标记
        apply(2 * i, lz[i]);
        apply(2 * i + 1, lz[i]);
        lz[i] = {1, 0};
    };

    // 正整数 n 是 int 类型，n 的二进制位数等于 32 - __builtin_clz(n)
    int LOG = 31 - __builtin_clz(n); // log2(n) 向下取整
    int q = n;
    while (q--) {
        int type, l, r, c;
        cin >> type >> l >> r >> c;
        if (type == 2) {
            int v = a[r - 1];
            int p = r - 1 + n;
            while (p > 0) {
                v = (lz[p].mul * v + lz[p].add) % mod;
                p /= 2;
            }
            if (v < 0) v += mod;
            cout << v << '\n';
        } else {
            c %= mod;
            F f;
            if (type == 0) f = {1, c};
            else f = {c, 0};
            l--;
            l += n;
            r += n;
            for (int i = LOG; i >= 1; i--) {
                if (l >> i << i != l)
                    push(l >> i);
                if (r >> i << i != r)
                    push(r >> i);
            }
            while (l < r) {
                if (l & 1) apply(l++, f);
                if (r & 1) apply(--r, f);
                l /= 2;
                r /= 2;
            }
        }
    }
}

---

# 