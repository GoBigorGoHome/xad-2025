// 静态区间逆序数
// 解法：（学来的，不是我想到的。解法来自 https://codeforces.com/blog/entry/54082?#comment-476418）
// 1. 预处理
// f[l][R]：inv[l, B*R)
// g[L][r]: inv[L*B, r)
// 把同一块里的元素排序。
// 如何在 O(n \sqrt(n)) 时间内计算 f 和 g？
// f[i][R] = f[i + 1][R] + ...
// 2. 回答询问 [l, r)
// 两个相离且有序的子列 a, b 之间的逆序数可以在 O(|a| + |b|) 的时间内算出来。
// given a subset S, we can determine order of each element in S in O(n) time.

// 前三个测试点超时。把 f 和 g 从 vector 改为普通数组后卡线通过。

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

struct fenwick {
    int n;
    vector<int> a;
    fenwick(int _n) : n(_n), a(n + 1) {}
    int sum(int p) {
        int res = 0;
        while (p) {
            res += a[p];
            p &= p - 1;
        }
        return res;
    }
    void add(int p, int v) {
        while (p <= n) {
            a[p] += v;
            p += p & -p;
        }
    }
};

const int maxn = 1e5 + 5;
long long f[maxn][320], g[320][maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    fenwick fenw(n);
    vector<int> pref_order(n); // order[i]: number of elements less than a[i] in range a[0], ..., a[i - 1]
    for (int i = 0; i < n; i++) {
        pref_order[i] = fenw.sum(a[i]);
        fenw.add(a[i], 1);
    }

    int B = (int) sqrt(n);
    int NB = (n + B - 1) / B;

    vector<int> I(n);
    for (int i = 0; i < n; i++) {
        I[a[i] - 1] = i;
    }
    vector<vector<int>> Ib(NB);

    for (int i : I) {
        Ib[i / B].push_back(i);
    }

    // vector<vector<long long>> f(n + 1, vector<long long>(NB + 1));
    // vector<vector<long long>> g(NB, vector<long long>(n + 1));

    vector<int> order(n);
    for (int rb = NB; rb >= 1; rb--) {
        int cnt = 0;
        for (int i : I) {
            if (i < rb * B) {
                order[i] = cnt++;
            }
        }
        for (int i = min(n, rb * B) - 1; i >= 0; i--) {
            int n_less = order[i] - pref_order[i];
            f[i][rb] = f[i + 1][rb] + n_less;
        }
    }

    for (int lb = 0; lb < NB; lb++) {
        int cnt = 0;
        for (int i : I) {
            if (i >= lb * B)
                order[i] = cnt++;
        }
        for (int i = lb * B; i < n; i++) {
            int cur_order = pref_order[i] - (a[i] - 1 - order[i]);
            int n_greater = (i - lb * B) - cur_order;
            g[lb][i + 1] = g[lb][i] + n_greater;
        }
    }

    long long ans = 0;
    while(q--) {
        long long l, r;
        cin >> l >> r;
        l ^= ans;
        r ^= ans;

        l--;
        int lb = (l + B - 1) / B;
        int rb = r / B;

        ans = 0;
        if (lb > rb) {
            ans = f[l][lb] - f[r][lb];
            int seen = 0;
            for (int i : Ib[lb - 1]) {
                if (i < l) continue;
                if (i < r) ans -= seen;
                else seen++;
            }
        } else {
            ans = g[lb][r] + f[l][rb] - f[lb * B][rb];
            if (l < lb * B && rb * B < r) {
                auto ptr = Ib[rb].begin();
                int seen = 0;
                for (int i : Ib[lb - 1]) {
                    if (i < l) continue;
                    for (; ptr != Ib[rb].end() && a[*ptr] < a[i]; ptr++) {
                        if (*ptr < r) {
                           seen++; 
                        }
                    }
                    ans += seen;
                }
            }
        }
        cout << ans << '\n';
    }
}