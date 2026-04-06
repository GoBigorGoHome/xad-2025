// 值域线段树
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
    int maxn = 1 << 20;

    vector<vector<int>> f(maxn + 1);
    vector<int> np(maxn + 1); // number of prime factors
    vector<int> val;
    for (int i = 2; ; i++) {
        if (np[i] <= 1) { // i 是素数幂
            bool is_prime = np[i] == 0;
            for (int j = i; j <= maxn; j += i) {
                np[j] += is_prime;
                f[j].push_back((int) val.size());
            }
            val.push_back(i);
            if (i > (int) 1e6)
                break;
        }
    }

    int N = (int) val.size() - 1; // N = 78734
    
    vector<int> pos(2 * N, -1); // 线段树

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> L(q), R(q);
    for (int i = 0; i < q; i++) {
        cin >> L[i] >> R[i];
        L[i]--;
        R[i]--;
    }
    vector<int> I(q);
    iota(I.begin(), I.end(), 0);
    sort(I.begin(), I.end(), [&](int i, int j) {return R[i] < R[j];});

    vector<int> ans(q);
    auto it = I.begin();
    for (int i = 0; i < n; i++) {
        for (int d : f[a[i]]) {
            int p = d + N;
            pos[p] = i;
            for (p >>= 1; p; p >>= 1) {
                pos[p] = min(pos[2 * p], pos[2 * p + 1]);
            }
        }
        for ( ;it != I.end() && R[*it] == i; ++it) {
            int l = N, r = 2 * N;
            int p = r;
            while (l < r) {
                if (l & 1) {
                    debug(l, pos[l]);
                    if (pos[l] < L[*it]) {
                        p = l;
                        break;
                    }
                    l++;
                }
                if (r & 1) {
                    if (pos[r - 1] < L[*it])
                        p = r - 1;
                    r--;
                }
                l >>= 1;
                r >>= 1;
            }
            while (p < N) {
                if (pos[p * 2] < L[*it])
                    p = p * 2;
                else
                    p = p * 2 + 1;
            }
            debug(N, p);
            ans[*it] = val[p - N] - 1;
        }
    }
    for (int x : ans)
        cout << x << '\n';
}
