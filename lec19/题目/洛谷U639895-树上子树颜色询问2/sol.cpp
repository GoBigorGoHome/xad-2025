#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

const int maxn = 2e5 + 5;
vector<int> g[maxn];
int a[maxn];

int cnt[maxn];
vector<pair<int,int>> query[maxn];
int ans[maxn];
void dfs(int u, int p) {
    for (auto [c, i] : query[u])
        ans[i] = cnt[c];
    cnt[a[u]]++;
    for (int v : g[u])
        if (v != p)
            dfs(v, u);
    for (auto [c, i] : query[u])
        ans[i] = cnt[c] - ans[i];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, c;
        cin >> u >> c;
        query[u].push_back({c, i});
    }
    dfs(1, 0);
    for (int i = 0; i < m; i++)
        cout << ans[i] << '\n';
}