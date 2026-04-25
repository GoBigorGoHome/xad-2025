#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
int num, L[maxn], R[maxn];

bool is_ancestor(int a, int b) { // a 是不是 b 的祖先
    return L[a] <= L[b] && L[b] <= R[a];
}

int anc[maxn][19];
int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = 18; i >= 0; i--) {
        if (anc[u][i] && !is_ancestor(anc[u][i], v))
            u = anc[u][i];
    }
    return anc[u][0];
}

vector<int> g[maxn];
int depth[maxn];
void dfs(int u, int p) {
    L[u] = ++num;
    anc[u][0] = p;
    depth[u] = depth[p] + 1;
    for (int i = 1; i < 19; i++)
        anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (int v : g[u])
        if (v != p) {
            dfs(v, u);
        }
    R[u] = num;
}

int w[maxn];
int cnt[2 * maxn];
int ans[maxn];
vector<pair<int,int>> op[maxn];
void get_up(int u, int p) {
    int key = w[u] + depth[u];
    int before = cnt[key];
    for (auto [k, type] : op[u])
        cnt[k] += type;
    for (int v : g[u])
        if (v != p)
            get_up(v, u);
    ans[u] += cnt[key] - before;
}

int n, m;
void get_down(int u, int p) {
    int key = w[u] - depth[u] + n;
    int before = cnt[key];
    for (auto [k, type] : op[u]) {
        cnt[k] += type;
    }
    for (int v : g[u])
        if (v != p)
            get_down(v, u);
    ans[u] += cnt[key] - before;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    
    dfs(1, 0);

    vector<int> s(m), t(m), LCA(m);
    for (int i = 0; i < m; i++) {
        cin >> s[i] >> t[i];
        LCA[i] = lca(s[i], t[i]);
        ans[LCA[i]] += depth[s[i]] == depth[LCA[i]] + w[LCA[i]];
    }
    for (int i = 0; i < m; i++) {
        int k = depth[s[i]];
        op[s[i]].push_back({k, 1});
        op[LCA[i]].push_back({k, -1});
    }
    get_up(1, 0);

    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; i++)
        op[i].clear();
    
    for (int i = 0; i < m; i++) {
        int time = depth[s[i]] + depth[t[i]] - 2 * depth[LCA[i]];
        int k = time - depth[t[i]] + n;
        op[t[i]].push_back({k, 1});
        op[LCA[i]].push_back({k, -1}); 
    }
    get_down(1, 0);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    cout << '\n';
}