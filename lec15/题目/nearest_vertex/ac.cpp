#include <bits/stdc++.h>
#define ll long long
#define debug(x) cout << #x << " = " << x << '\n'
#define all(a) a.begin(), a.end()
using namespace std;
const int mxn = 5e4 + 3;
const ll  mod = 1e9 + 7;
const int inf32 = 2e9;
const ll  inf64 = 7e18;
int n, q, m, a[mxn], S, pos[mxn], h[mxn];
vector<int> g[mxn], col[mxn], heavy;
int dp[2][mxn][250];
int up[mxn][16]; // mảng này để tính LCA
void dfs0(int u, int p){
    // giá trị ở đỉnh u là một giá trị chủ đạo
    if (pos[a[u]] != -1) dp[0][u][pos[a[u]]] = 0;
    for (int v : g[u]) if (v != p){
        up[v][0] = u, h[v] = h[u] + 1;
        dfs0(v, u);
        for (int c = 0; c < m; ++c){
            dp[0][u][c] = min(dp[0][u][c], 1 + dp[0][v][c]);
        }
    }
}
void dfs1(int u, int p){
    if (pos[a[u]] != -1) dp[1][u][pos[a[u]]] = 0;
    vector<vector<int>> vt;
    vt.resize(m);
    for (int v : g[u]) if (v != p){
        for (int c = 0; c < m; ++c)
            vt[c].push_back(dp[0][v][c]);
    }
    // sắp xếp lại các down[v][c] theo thứ tự tăng dần
    for (int c = 0; c < m; ++c)
        sort(all(vt[c]));
    for (int v : g[u]) if (v != p){
        for (int c = 0; c < m; ++c){
            dp[1][v][c] = min(dp[1][v][c], 1 + dp[1][u][c]);
            // u có ít nhất 2 con
            if ((int)vt[c].size() > 1){
                // nếu down[v][c] không phải nhỏ nhất trong các con của u
                // thì ta có thể chọn nhỏ nhất
                if (dp[0][v][c] != vt[c][0])
                    dp[1][v][c] = min(dp[1][v][c], 2 + vt[c][0]);
                else {
                    // nếu down[v][c] là nhỏ nhất nhưng có ít nhất 2 cái nhỏ nhất
                    // thì vẫn chọn nhỏ nhất được
                    if (vt[c][1] == vt[c][0])
                        dp[1][v][c] = min(dp[1][v][c], 2 + vt[c][0]);
                    // ngược lại phải chọn nhỏ thứ nhì
                    else
                        dp[1][v][c] = min(dp[1][v][c], 2 + vt[c][1]);
                }
            }
        }
        dfs1(v, u);
    }
}
int lca(int u, int v){
    if (h[u] != h[v]){
        if (h[u] < h[v]) swap(u, v);
        int k = h[u] - h[v];
        for (int j = 0; (1 << j) <= k; ++j)
            if (k >> j & 1) u = up[u][j];
    }
    if (u == v) return u;
    for (int j = log2(h[u]); j >= 0; --j){
        if (up[u][j] != up[v][j])
            u = up[u][j], v = up[v][j];
    }
    return up[u][0];
}
void solve(){
    cin >> n >> q;
    S = sqrt(n);
    for (int i = 1; i <= n; ++i)
        cin >> a[i], col[a[i]].push_back(i);
    for (int i = 1, u, v; i <= n - 1; ++i){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i)
        pos[i] = -1;
    // dùng mảng pos để nén các giá trị chủ đạo
    for (int i = 1; i <= n; ++i)
        if ((int)col[i].size() > S) heavy.push_back(i), pos[i] = m++;
    // khởi tạo mảng với dương vô cùng
    for (int t = 0; t < 2; ++t){
        for (int u = 1; u <= n; ++u){
            for (int c = 0; c < m; ++c)
                dp[t][u][c] = inf32;
        }
    }
    dfs0(1, 0); // tính dp[0] (DOWN)
    dfs1(1, 0); // tính dp[1] (UP)
    
    for (int j = 1; j < 16; ++j){
        for (int u = 1; u <= n; ++u)
            up[u][j] = up[up[u][j - 1]][j - 1];
    }
    while(q--){
        int u, x;
        cin >> u >> x;
        if (col[x].empty()){
            cout << -1 << '\n';
            continue;
        }
        if ((int)col[x].size() <= S){
            int res = inf32;
            for (int v : col[x])
                res = min(res, h[u] + h[v] - 2 * h[lca(u, v)]);
            cout << res << '\n';
        } else {
            cout << min(dp[0][u][pos[x]], dp[1][u][pos[x]]) << '\n';
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}