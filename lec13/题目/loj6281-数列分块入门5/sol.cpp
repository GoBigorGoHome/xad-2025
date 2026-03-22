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

    vector<vector<int>> b(NB);
    vector<long long> sum(NB);
    for (int i = 0; i < n; i++) {
        sum[i / B] += a[i];
        if (a[i] > 1)
            b[i / B].push_back(i);
    }

    auto update = [&](int i) {
        int x = (int) sqrt(a[i]);
        sum[i / B] += x - a[i];
        a[i] = x;
    };

    int q = n;
    while (q--) {
        int type, l, r, c;
        cin >> type >> l >> r >> c;
        if (l > r) swap(l, r);
        l--;
        int lb = (l + B - 1) / B;
        int rb = r / B;
        if (type == 0) {
            if (lb > rb)
                for (int i = l; i < r; i++)
                    update(i);
            else {
                for (int i = l; i < lb * B; i++)
                    update(i);
                for (int i = rb * B; i < r; i++)
                    update(i);
                for (int i = lb; i < rb; i++)
                    for (int j = 0; j < (int) b[i].size(); ) {
                        update(b[i][j]);
                        if (a[b[i][j]] == 1) {
                            swap(b[i][j], b[i].back());
                            b[i].pop_back();
                        } else {
                            j++;
                        }
                    }
            }
        } else {
            long long ans = 0;
            if (lb > rb)
                for (int i = l; i < r; i++)
                    ans += a[i];
            else {
                for (int i = l; i < lb * B; i++)
                    ans += a[i];
                for (int i = rb * B; i < r; i++)
                    ans += a[i];
                for (int i = lb; i < rb; i++)
                    ans += sum[i];
            }
            cout << ans << '\n';
        }
    }
}