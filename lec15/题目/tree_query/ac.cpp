#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxN = 2e5;
int n, q, 
    c[maxN + 1],
    par[maxN + 1],
    lan[maxN + 1];
vector <int> w[maxN + 1];
void init(){
    cin>>n>>q;
    for (int i = 1; i < n; i++){
        int u, v; cin>>u>>v;
        w[u].push_back(v);
        w[v].push_back(u);
    }
}
void dfs(int u, int pre){
    for (int v: w[u]){
        if (v == pre)
            par[u] = pre;
        else dfs(v, u);
    }
}
void solve(){
    dfs(1, 0);
    for (int i = 1; i <= q; i++){
        int type, u; cin>>type>>u;
        if (type == 1){
            int x; cin>>x;
            lan[u] += x;
            c[par[u]] += x;
        }
        else cout<<c[u] + lan[par[u]]<<'\n';
    }
}
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    init(); solve();
}