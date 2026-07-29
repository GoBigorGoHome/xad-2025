/**
 *    author:  zjs
 *    created: 22.06.2026 16:47:53
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
const int maxn = 2e5 + 5;
bool del[maxn];
int sz[maxn];

vector<int> g[maxn];

void get_size(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == p || del[v]) continue;
        get_size(v, u);
        sz[u] += sz[v];
    }
}

int find_centroid(int u) {
    get_size(u, 0);
    int p = 0;
    int tree_sz = sz[u];
    while (1) { //从点 u 出发，走到树的重心
        int next = -1; // 找下一个要去的点
        for (int v : g[u]) {
            if (del[v] || v == p) continue;
            if (sz[v] * 2 > tree_sz) {
                next = v;
                break;
            }
        }
        if (next == -1) break;
        p = u;
        u = next;
    }
    return u;
}   

vector<int> divide() {
    vector<int> seq;
    seq.push_back(find_centroid(1));
    for (int i = 0; i < (int) seq.size(); i++) {
        int u = seq[i];
        del[u] = true;
        for (int v : g[u]) {
            if (!del[v])
                seq.push_back(find_centroid(v));
        }
    }
    for (int u : seq)
        del[u] = false;
    return seq;
}
//以上是树的重心分解。
int pv[maxn];
int c[maxn];
int cnt[maxn];
vector<int> city;
void dfs(int u, int p) {
    pv[u] = p;
    if (++cnt[c[u]] == 1) {
       city.push_back(c[u]); 
    }
    for (int v : g[u]) {
        if (del[v] || v == p) continue;
        dfs(v, u);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // 选定一个城市，要求首都一定要包括这个城市，最少要合并多少次？这问题比较容易。
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<int>> towns(k + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        towns[c[i]].push_back(i);
    }
    vector<bool> vis(k + 1);
    int ans = k;
    for (int u : divide()) {
        dfs(u, 0);//找出在当前块中出现过的城市，每个城市出现次数
        del[u] = true;
        // BFS
        bool ok = true;
        vector<int> q;
        q.push_back(c[u]);
        vis[c[u]] = true;
        for (int i = 0; i < (int) q.size(); i++) {
            if (cnt[q[i]] != (int) towns[q[i]].size()) {
                ok = false;
                break;
            }
            for (int v : towns[q[i]]) {
                while ((v = pv[v]) && !vis[c[v]]) {
                    q.push_back(c[v]);
                    vis[c[v]] = true;
                }
            }
        }
        if (ok) {
            ans = min(ans, (int) q.size() - 1);
        }
        //清除全局状态
        for (int ct : q)
            vis[ct] = false;
        for (int x : city)
            cnt[x] = 0;
        city.clear();
    }
    cout << ans << '\n';
}