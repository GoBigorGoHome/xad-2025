// 静态区间逆序数
// 解法：（学来的，不是我想到的。解法来自 https://www.luogu.com.cn/article/cnfoejzy）
// 用数组比用 vector 块。为什么？

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
int a[maxn];
long long g[320][320];
long long f[320][maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    // vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int B = (int) sqrt(n);
    int NB = (n + B - 1) / B;
    int WB = n / B; // number of whole blocks

    // 预处理
    // 1. 整体排序
    vector<int> I(n);
    for (int i = 0; i < n; i++) {
        I[a[i] - 1] = i;
    }
    // 2. 块内排序
    vector<vector<int>> Ib(NB);
    for (int i : I) {
        Ib[i / B].push_back(i);
    }
    // 3. 计算 pref 数组，suff 数组
    // 利用树状数组
    fenwick fenw(n);
    vector<int> pref(n), suff(n);
    for (int l = 0; l < n; l += B) {
        int r = min(l + B, n);
        // 计算 pref
        int t = 0;
        for (int i = l; i < r; i++) {
            t += (i - l) - fenw.sum(a[i]);
            pref[i] = t;
            fenw.add(a[i], 1);
        }
        for (int i = l; i < r; i++)
            fenw.add(a[i], -1);
        // 计算 suff
        t = 0;
        for (int i = r - 1; i >= l; i--) {
            t += fenw.sum(a[i]);
            suff[i] = t;
            fenw.add(a[i], 1);
        }
        for (int i = l; i < r; i++)
            fenw.add(a[i], -1);
    }
    // 4. 计算 f 数组
    // vector<vector<long long>> f(WB, vector<long long>(n + 1));
    // f[i][j]: a[0, i) 与 a[j * B, (j + 1) * B) 之间的逆序数
    for (int ib = 0; ib < WB; ib++) {
        int l = ib * B;
        int r = l + B;
        int seen = 0;
        for (int i : I) {
            if (l <= i && i < r) {
                seen++;
            } else if (i < l) {
                f[ib][i + 1] = seen;
            } else {
                f[ib][i + 1] = B - seen;
            }
        }
        // 计算前缀和
        for (int i = 0; i < n; i++)
            f[ib][i + 1] += f[ib][i];
    }
    // 5. 计算 g 数组
    // vector<vector<long long>> g(WB + 1, vector<long long>(WB + 1));
    for (int i = 0; i < WB; i++)
        g[i][i + 1] = pref[(i + 1) * B - 1];
    for (int len = 2; len <= WB; len++)
        for (int l = 0; l + len <= WB; l++) {
            int r = l + len;
            g[l][r] = g[l][r - 1] + g[l + 1][r] - g[l + 1][r - 1] + (f[l][r * B] - f[l][(r - 1) * B]);
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
            ans = pref[r - 1] - (l > 0 ? pref[l - 1] : 0);
            int seen = 0;
            for (int i : Ib[lb - 1]) {
                if (i >= r) continue;
                if (i < l) ans -= seen;
                else seen++;
            }
        } else {
            ans = g[lb][rb] + (l < lb * B ? suff[l] : 0) + (rb * B < r ? pref[r - 1] : 0);
            // 边块与整块之间的逆序对
            for (int i = lb; i < rb; i++) {
                ans += f[i][lb * B] - f[i][l];
                ans += f[i][r] - f[i][rb * B];
            }
            // 两个边块之间的逆序对
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