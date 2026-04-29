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

vector<int> V[maxn];
int L[maxn], R[maxn], num;

void dfs(int u, int p) {
    L[u] = ++num;
    V[a[u]].push_back(L[u]);
    for (int v : g[u])
        if (v != p)
            dfs(v, u);
    R[u] = num;
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
    dfs(1, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, c;
        cin >> u >> c;
        cout << upper_bound(V[c].begin(), V[c].end(), R[u]) - lower_bound(V[c].begin(), V[c].end(), L[u]) << '\n';
    }
}