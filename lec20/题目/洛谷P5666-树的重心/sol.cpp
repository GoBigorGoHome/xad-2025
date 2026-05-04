/**
 *    author:  zjs
 *    created: 04.05.2026 16:10:15
**/
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

const int maxn = 3e5;
int a[maxn]; //树状数组
int n;
void add(int p, int v) {
    while (p <= n) {
        a[p] += v;
        p += p & -p;
    }
}

int sum(int p) {
    if (p < 0) return 0;
    if (p > n) p = n;
    int ans = 0;
    while (p > 0) {
        ans += a[p];
        p -= p & -p;
    }
    return ans;
}

int sum(int l, int r) {
    return sum(r) - sum(l - 1);
}

vector<int> g[maxn];
int sz[maxn], h[maxn], h2[maxn];
void get_size(int u, int p) {
    sz[u] = 1;
    h[u] = 0, h2[u] = 0;
    for (int v : g[u]) {
        if (v != p) {
            get_size(v, u);
            sz[u] += sz[v];
            if (sz[v] > h[u]) {
                h2[u] = h[u];
                h[u] = sz[v];
            } else if (sz[v] > h2[u]) {
                h2[u] = sz[v];
            }
        }
    }
}

vector<int> anc;
int cnt[maxn]; // cnt[u]：点u做重心的次数。

int cnt_anc(int L, int R) {//anc是一个递减序列
    return upper_bound(anc.rbegin(), anc.rend(), R)
        - lower_bound(anc.rbegin(), anc.rend(), L);
}

void dfs(int u, int p) {
    if (p) {
        anc.push_back(sz[u]);
        add(sz[u], 1);
    }
    // case 1
    cnt[u] += cnt_anc(2 * h[u], 2 * sz[u]);
    // case 2
    int L = n - 2 * sz[u];
    int R = n - 2 * h[u];
    // 去掉u的祖先的中满足条件的v
    cnt[u] -= cnt_anc(L, R);
    for (int v : g[u]) {
        if (v == p) continue;
        int new_h = (sz[v] == h[u] ? max(h2[u], n - sz[u]) 
                                : max(h[u], n - sz[u]));
        int new_sz = n - sz[v];
        int new_L = n - 2 * new_sz;
        int new_R = n - 2 * new_h;
        cnt[u] -= sum(new_L, new_R);
        cnt[u] += sum(L, R);
        dfs(v, u);
        cnt[u] -= sum(L, R);
        cnt[u] += sum(new_L, new_R);
    }
    if (p)
        anc.pop_back();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            g[i].clear();
            cnt[i] = 0;
            a[i] = 0;
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        get_size(1, 0);
        dfs(1, 0);

        long long ans = 0;
        for (int u = 1; u <= n; u++) {
            int L = n - 2 * sz[u];
            int R = n - 2 * h[u];
            cnt[u] += sum(L, R);
            ans += (long long) u * cnt[u];
        }
        cout << ans << '\n';
    }
}