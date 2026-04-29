#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

const int maxn = 5e5 + 5;
vector<int> g[maxn];
char c[maxn];
int s[maxn];
vector<int> V[maxn];
int L[maxn], R[maxn], num;

void dfs(int u, int depth) {
    L[u] = ++num;
    s[num] = s[V[depth].back()] ^ 1 << (c[u] - 'a');
    V[depth].push_back(num);
    for (int v : g[u])
        dfs(v, depth + 1);
    R[u] = num;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        g[p].push_back(i);
    }
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= n; i++)
        V[i].push_back(0);
    dfs(1, 1);
    for (int i = 0; i < m; i++) {
        int v, h; cin >> v >> h;
        auto l = lower_bound(V[h].begin(), V[h].end(), L[v]);
        auto r = upper_bound(V[h].begin(), V[h].end(), R[v]);
        int ans = s[*(r - 1)] ^ s[*(l - 1)];
        cout << (ans & (ans - 1) ? "No" : "Yes") << '\n';
    }
}
