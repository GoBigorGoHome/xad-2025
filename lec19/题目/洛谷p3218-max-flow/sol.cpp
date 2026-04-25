#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e4 + 5;
vector<int> g[maxn];
int num, L[maxn], R[maxn];

bool is_ancestor(int a, int b) { // a 是不是 b 的祖先
    return L[a] <= L[b] && L[b] <= R[a];
}

int anc[maxn][16];

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = 15; i >= 0; i--) {
        if (anc[u][i] && !is_ancestor(anc[u][i], v))
            u = anc[u][i];
    }
    return anc[u][0];
}

void dfs(int u, int p) {
    L[u] = ++num;
    anc[u][0] = p;
    for (int i = 1; i < 16; i++)
        anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (int v : g[u])
        if (v != p) {
            dfs(v, u);
        }
    R[u] = num;
}

int a[maxn];
void get_sum(int u, int p) { // 求子树和
    for (int v : g[u])
        if (v != p) {
            get_sum(v, u);
            a[u] += a[v];
        }
}

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    while (k--) {
        int s, t;
        cin >> s >> t;
        int u = lca(s, t);
        a[s]++;
        a[t]++;
        a[u]--;
        a[anc[u][0]]--;
    }
    get_sum(1, 0);
    cout << *max_element(a + 1, a + n + 1) << '\n';
}