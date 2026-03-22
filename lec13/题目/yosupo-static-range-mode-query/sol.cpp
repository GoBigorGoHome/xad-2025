#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

template<typename T>
vector<T> compress(vector<T>& a) {
    vector<int> I(a.size());
    iota(I.begin(), I.end(), 0);
    sort(I.begin(), I.end(), [&](int i, int j) { return a[i] < a[j]; });

    vector<T> b;
    for (int i : I) {
        if (b.empty() || b.back() < a[i])
            b.push_back(a[i]);
        a[i] = (int) b.size() - 1;
    }
    return b;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    auto val = compress(a);

    int B = (int) sqrt(n);
    int NB = n / B;

    vector<vector<pair<int,int>>> mode(NB, vector<pair<int,int>>(NB));
    
    int N = (int) val.size();

    for (int i = 0; i < NB; i++) {
        int mx = 0, v = -1;
        vector<int> cnt(N);
        for (int j = i; j < NB; j++) {
            for (int k = j * B; k < (j + 1) * B; k++) {
                if (++cnt[a[k]] > mx) {
                    mx = cnt[a[k]];
                    v = a[k];
                }
            }
            mode[i][j] = {v, mx};
        }
    }

    vector<vector<int>> pos(N);
    vector<int> rank(n);
    for (int i = 0; i < n; i++) {
        rank[i] = (int) pos[a[i]].size();
        pos[a[i]].push_back(i);
    }
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        int lb = (l + B - 1) / B, rb = r / B;
        int mx = 0, v = -1;
        if (lb >= rb) {
            for (int i = l; i < r; i++) {
                int j = rank[i] + mx;
                while (j < (int) pos[a[i]].size() && pos[a[i]][j] < r)
                    j++;
                if (mx < j - rank[i]) {
                    mx = j - rank[i];
                    v = a[i];
                }
            }
        } else {
            v = mode[lb][rb - 1].first;
            mx = mode[lb][rb - 1].second;
            for (int i = l; i < lb * B; i++) {
                int j = rank[i] + mx;
                while (j < (int) pos[a[i]].size() && pos[a[i]][j] < r)
                    j++;
                if (mx < j - rank[i]) {
                    mx = j - rank[i];
                    v = a[i];
                }
            }
            for (int i = rb * B; i < r; i++) {
                int j = rank[i] - mx;
                while (j >= 0 && pos[a[i]][j] >= l)
                    j--;
                if (mx < rank[i] - j) {
                    mx = rank[i] - j;
                    v = a[i];
                }
            }
        }
        cout << val[v] << ' ' << mx << '\n';
    }
}