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
    vector<int> p(n), ip(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        ip[p[i]] = i;
    }
    int B = (int) sqrt(n);
    int NB = (n + B - 1) / B;
    vector<vector<int>> s(NB, vector<int>(n + 1));
    vector<vector<int>> t(NB, vector<int>(n + 1));

    for (int i = 0; i < NB; i++) {
        int l = i * B, r = min(l + B, n);
        // 计算前缀和
        for (int j = 0; j < n; j++)
            s[i][j + 1] += s[i][j] + (l <= ip[j] && ip[j] < r);
        for (int j = 0; j < n; j++)
            t[i][j + 1] = t[i][j] + (l <= p[j] && p[j] < r);
    }

    vector<long long> add1(NB), add2(NB), sum1(NB), sum2(NB);
    vector<long long> a1(n), a2(n);

    auto work0 = [&](int l, int r, int x) {
        for (int i = l; i < r; i++) {
            a1[i] += x;
            sum1[i / B] += x;
            a2[ip[i]] += x;
            sum2[ip[i] / B] += x;
        }
    };

    auto work1 = [&](int l, int r, int x) {
        for (int i = l; i < r; i++) {
            a2[i] += x;
            sum2[i / B] += x;
            a1[p[i]] += x;
            sum1[p[i] / B] += x;
        }
    };

    auto query2 = [&](int l, int r) {
        long long ans = 0;
        for (int i = l; i < r; i++)
            ans += a1[i] + add1[i / B];
        return ans;
    };

    auto query3 = [&](int l, int r) {
        long long ans = 0;
        for (int i = l; i < r; i++)
            ans += a2[i] + add2[i / B];
        return ans;
    };

    while (q--) {
        int type, l, r, x;
        cin >> type >> l >> r;
        if (type < 2) cin >> x;
        l--;
        int lb = (l + B - 1) / B, rb = r / B;
        long long ans = 0;

        if (type == 0) {
            if (lb > rb) {
                work0(l, r, x);
            }
            else {
                work0(l, lb * B, x);
                work0(rb * B, r, x);
                for (int i = lb; i < rb; i++)
                    add1[i] += x;
            }
        } else if (type == 1) {
            if (lb > rb) {
                work1(l, r, x);
            } else {
                work1(l, lb * B, x);
                work1(rb * B, r, x);
                for (int i = lb; i < rb; i++)
                    add2[i] += x;
            }
        } else if (type == 2) {
            if (lb > rb) ans = query2(l, r);
            else {
                ans = query2(l, lb * B) + query2(rb * B, r);
                for (int i = lb; i < rb; i++)
                    ans += sum1[i] + add1[i] * B;
            }
            for (int i = 0; i < NB; i++)
                ans += add2[i] * (s[i][r] - s[i][l]);
        } else {
            if (lb > rb) ans += query3(l, r);
            else {
                ans = query3(l, lb * B) + query3(rb * B, r);
                for (int i = lb; i < rb; i++)
                    ans += sum2[i] + add2[i] * B;
            }
            for (int i = 0; i < NB; i++)
                ans += add1[i] * (t[i][r] - t[i][l]);
        }
        if (type >= 2) cout << ans << '\n';
    }
}