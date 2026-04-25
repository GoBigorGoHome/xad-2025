#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

const int maxn = 5e5 + 5;

vector<int> g[maxn];
//全局DS
bitset<26> a[maxn];

char c[maxn];
bitset<26> ans[maxn];
vector<pair<int,int>> query[maxn];

void dfs(int u, int depth) {
    for (auto [h, id] : query[u]) {
        ans[id] = a[h];
    }
    a[depth].flip(c[u] - 'a');
    for (int v : g[u])
        dfs(v, depth + 1);
    
    for (auto [h, id] :  query[u]) {
        ans[id] ^= a[h];
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 0; i < m; i++) {
        int v, h;
        cin >> v >> h;
        query[v].push_back({h, i});
    }
    dfs(1, 1);
    for (int i = 0; i < m; i++) {
        cout << (ans[i].count() < 2 ? "Yes" : "No") << '\n';
    }
}