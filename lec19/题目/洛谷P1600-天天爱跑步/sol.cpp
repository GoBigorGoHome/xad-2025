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
vector<pair<int,int>> op_up[maxn], op_down[maxn];
void get_up(int u, int p) {
    int key = w[u] + depth[u];
    int before = cnt[key];
    for (auto [x, delta] : op_up[u])
        cnt[x] += delta;
    for (int v : g[u])
        if (v != p)
            get_up(v, u);
    ans[u] += cnt[key] - before;
}

void get_down(int u, int p) {
    int key = w[u] - depth[u] + maxn;
    int before = cnt[key];
    for (auto [x, delta] : op_down[u])
        cnt[x + maxn] += delta;
    for (int v : g[u])
        if (v != p)
            get_down(v, u);
    ans[u] += cnt[key] - before;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
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

    for (int i = 0; i < m; i++) {
        int s, t; cin >> s >> t;
        int u = lca(s, t);
        op_up[s].push_back({depth[s], 1});
        op_up[anc[u][0]].push_back({depth[s], -1});
        op_down[t].push_back({depth[s] - 2 * depth[u], 1});
        op_down[u].push_back({depth[s] - 2 * depth[u], -1});
    }

    get_up(1, 0);
    memset(cnt, 0, sizeof cnt);
    get_down(1, 0);

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    cout << '\n';
}