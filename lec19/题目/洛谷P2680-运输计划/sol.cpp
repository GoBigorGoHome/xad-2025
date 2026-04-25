#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
vector<pair<int,int>> g[maxn];
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

long long dist[maxn]; // dist[i]：根到点i的距离
int we[maxn]; //we[i]：点i的父边的长度。
vector<int> postorder; //用非递归的方式计算子树和
void dfs(int u, int p) {
    L[u] = ++num;
    anc[u][0] = p;
    for (int i = 1; i < 19; i++)
        anc[u][i] = anc[anc[u][i - 1]][i - 1];
    for (auto [v, w] : g[u])
        if (v != p) {
            dist[v] = dist[u] + w; 
            dfs(v, u);
            we[v] = w;
        }
    R[u] = num;
    postorder.push_back(u);
}

int a[maxn];
int n, m;
int s[maxn], t[maxn], LCA[maxn];
long long len[maxn];
long long max_len;

bool check(long long k) {
    memset(a, 0, sizeof a);
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (len[i] > k) {
            cnt++;
            // 把 s[i] 到 t[i] 的路径上的边值加 1
            a[s[i]]++;
            a[t[i]]++;
            a[LCA[i]] -= 2;
        }
    }
    //计算子树和
    for (int v : postorder) {
        a[anc[v][0]] += a[v]; 
    }
    for (int i = 1; i <= n; i++)
        if (a[i] == cnt && max_len - we[i] <= k)
            return true;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    dfs(1, 0);
    for (int i = 0; i < m; i++) {
        cin >> s[i] >> t[i];
        LCA[i] = lca(s[i], t[i]);
        len[i] = dist[s[i]] + dist[t[i]] - 2 * dist[LCA[i]];
    }

    max_len = *max_element(len, len + m);
    long long ok = max_len, ng = -1;
    while (ok - ng > 1) {
        long long k = (ok + ng) / 2;
        if (check(k))
            ok = k;
        else
            ng = k;
    }
    cout << ok << '\n';
}