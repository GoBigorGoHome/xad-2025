/*
分块。
f[i][j]：argmax_k next[k] s.t. j * B <= k < (j + 1) * B  && prev[k] < i
for i <= j * B

TLE 了
*/
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

    vector<int> last((int) 5e5 + 5, -1);
    vector<int> prev(n, -1); 
    for (int i = 0; i < n; i++) {
        prev[i] = last[a[i]];
        last[a[i]] = i;
    }
    vector<int> next(n + 1, n);
    next[n] = -1;
    for (int i = 0; i < n; i++)
        if (prev[i] != -1)
            next[prev[i]] = i;

    int B = (int) sqrt(n);
    int NB = n / B;
    
    vector<vector<int>> f;
    for (int j = 0; j < NB; j++) {
        vector<int> t(j * B + 1, n);
        for (int i = j * B; i < (j + 1) * B; i++) {
            if (prev[i] < j * B && next[t[prev[i] + 1]] < next[i]) {
                t[prev[i] + 1] = i;
            }
        }
        for (int i = 0; i < j * B; i++) // 可以看作求“前缀和”
            if (next[t[i + 1]] < next[t[i]])
                t[i + 1] = t[i];
        f.push_back(t);
    }

    auto query = [&](int l, int r) {
        int lb = (l + B - 1) / B;
        int rb = r / B;
        if (lb > rb) {
            for (int i = l; i < r; i++)
                if (prev[i] < l && next[i] >= r)
                    return a[i];
        } else {
            for (int i = l; i < lb * B; i++)
                if (prev[i] < l && next[i] >= r)
                    return a[i];
            for (int i = rb * B; i < r; i++)
                if (prev[i] < l && next[i] >= r)
                    return a[i];
            for (int i = lb; i < rb; i++)
                if (next[f[i][l]] >= r)
                    return a[f[i][l]];
        }
        return 0;
    };

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(l - 1, r) << '\n';
    }
}