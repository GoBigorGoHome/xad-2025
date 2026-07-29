#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 4;
bool del[maxn];
int sz[maxn];

struct Edge {
    int to, w;
};
vector<Edge> g[maxn];

void get_size(int u, int p) {
    sz[u] = 1;
    for (auto [v, _] : g[u]) {
        if (v == p || del[v]) continue;
        get_size(v, u);
        sz[u] += sz[v];
    }
}

int find_centroid(int u, int p, int tree_size) {
    for (auto [v, _] : g[u]) {
        if (v == p || del[v]) continue;
        if (sz[v] * 2 > tree_size)
            return find_centroid(v, u, tree_size);
    }
    return u;
}

vector<int> seq; //重心序列
void divide(int u) {
    get_size(u, 0);
    int c = find_centroid(u, 0, sz[u]);
    seq.push_back(c);
    del[c] = true;
    for (auto [v, _] : g[c]) { // !注意：是 g[c] 不是 g[u]
        if (!del[v])
            divide(v);
    }
}

vector<int> dist;
void dfs(int u, int p, int d) {
    dist.push_back(d);
    for (auto [v, w] : g[u]) {
        if (del[v] || v == p) continue;
        dfs(v, u, d + w);
    }    
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    // 如果是多测，记得清空 seq 和 del
    divide(1);
    
    vector<int> q(m);
    vector<bool> ans(m);
    for (int i = 0; i < m; i++)
        cin >> q[i];

    memset(del, 0, sizeof del);
    const int maxk = 1e7;
    vector<bool> vis(maxk + 1);
    vis[0] = true;

    for (int c : seq) {
        del[c] = true;
    
        dist.clear();
        int ptr = 0;

        for (auto [v, w] : g[c]) {
            if (del[v]) continue;
            dfs(v, 0, w); // ==> dist
            // 查询
            for (int i = ptr; i < dist.size(); i++) {
                for (int j = 0; j < m; j++)
                    if (dist[i] <= q[j] && vis[q[j] - dist[i]])
                        ans[j] = true;
            }
            // 把子树 v 里的点到 c 的距离加到 vis 里
            for (int i = ptr; i < dist.size(); i++) {
                if (dist[i] <= maxk)
                    vis[dist[i]] = true;
            }
            ptr = dist.size();
        }
        // 清空 vis
        for (int d : dist)
            if (d <= maxk)
                vis[d] = false;
    }
    for (int i = 0; i < m; i++)
        if (ans[i])
            cout << "AYE\n";
        else
            cout << "NAY\n";
}