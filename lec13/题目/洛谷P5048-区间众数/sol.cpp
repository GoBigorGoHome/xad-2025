// 静态区间众数，强制在线。

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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int N = (int) 5e5 + 1;

    int B = (int) sqrt(n);
    int NB = n / B;

    vector<vector<int>> f(NB, vector<int>(NB));

    for (int i = 0; i < NB; i++) {
        int mx = 0;
        vector<int> cnt(N);
        for (int j = i; j < NB; j++) {
            for (int k = j * B; k < (j + 1) * B; k++) {
                if (++cnt[a[k]] > mx) {
                    mx = cnt[a[k]];
                }
            }
            f[i][j] = mx;
        }
    }

    vector<vector<int>> pos(N);
    vector<int> rank(n);
    for (int i = 0; i < n; i++) {
        rank[i] = (int) pos[a[i]].size();
        pos[a[i]].push_back(i);
    }

    int mx = 0;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l ^= mx;
        r ^= mx;
        if (l > r) swap(l, r);
        --l;

        int lb = (l + B - 1) / B, rb = r / B;
        if (lb >= rb) {
            mx = 0;
            for (int i = l; i < r; i++) {
                int j = rank[i] + mx;
                while (j < (int) pos[a[i]].size() && pos[a[i]][j] < r)
                    j++;
                if (mx < j - rank[i]) {
                    mx = j - rank[i];
                }
            }
        } else {
            mx = f[lb][rb - 1];
            for (int i = l; i < lb * B; i++) {
                int j = rank[i] + mx;
                while (j < (int) pos[a[i]].size() && pos[a[i]][j] < r)
                    j++;
                if (mx < j - rank[i]) {
                    mx = j - rank[i];
                }
            }
            for (int i = rb * B; i < r; i++) {
                int j = rank[i] - mx;
                while (j >= 0 && pos[a[i]][j] >= l)
                    j--;
                if (mx < rank[i] - j) {
                    mx = rank[i] - j;
                }
            }
        }
        cout << mx << '\n';
    }
}