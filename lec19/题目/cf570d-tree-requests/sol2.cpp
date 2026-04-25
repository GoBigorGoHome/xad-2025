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
bitset<26> s[maxn];
vector<int> order[maxn];
int L[maxn], R[maxn], num;

void dfs(int u, int depth) {
    L[u] = ++num;
    int prev = order[depth].empty() ? 0 : order[depth].back();
    s[num] = s[prev];
    s[num].flip(c[u] - 'a');
    order[depth].push_back(num);
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
    dfs(1, 1);
    for (int i = 0; i < m; i++) {
        int v, h;
        cin >> v >> h;
        bitset<26> ans;
        auto l = lower_bound(order[h].begin(), order[h].end(), L[v]);
        auto r = upper_bound(order[h].begin(), order[h].end(), R[v]);
        for (auto ptr : {l, r})
            if (ptr != order[h].begin())
                ans ^= s[*(ptr - 1)];
        cout << (ans.count() > 1 ? "No" : "Yes") << '\n';
    }
}