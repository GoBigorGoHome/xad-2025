#include <bits/stdc++.h>
#define ll long long
#define debug(x) cout << #x << " = " << x << '\n'
#define all(a) a.begin(), a.end()
using namespace std;
const int mxn = 1e5 + 3;
const int mod = 1e9 + 7;
const int inf32 = 2e9;
const ll  inf64 = 7e18;
int n,q,m,a[mxn],S,dco[mxn],cnt[mxn];
bool vis[mxn];
int tin[mxn],tout[mxn],timer=0,tour[mxn<<1];
int up[mxn][17],h[mxn];
int seg[2][mxn<<2]; // 0 = chỉ số đỉnh, 1 = số lần xuất hiện giá trị
vector<int>g[mxn];
struct Q{int l,r,lc,id;};
vector<Q>qr;
map<int,int>co;
void build(int id, int l, int r){
    if(l==r){
        seg[0][id]=l;
        return;
    }
    int mid=(l+r)>>1;
    build(id<<1,l,mid),build(id<<1|1,mid+1,r);
    seg[0][id]=-1;
}
void update(int id, int l, int r, int i, int val){
    if(l==r){
        seg[1][id]+=val;
        return;
    }
    int mid=(l+r)>>1;
    if(i<=mid) update(id<<1,l,mid,i,val);
    else update(id<<1|1,mid+1,r,i,val);
    if (seg[1][id<<1]>seg[1][id<<1|1]){
        seg[1][id]=seg[1][id<<1];
        seg[0][id]=seg[0][id<<1];
    }else{
        seg[1][id]=seg[1][id<<1|1];
        seg[0][id]=seg[0][id<<1|1];
    }
}
void upd(int u){
    // nếu đỉnh u đã xuất hiện trước đó trong đoạn, xóa lần xuất hiện đó đi
    if(vis[u]) update(1,1,m,a[u],-1);
    else update(1,1,m,a[u],1);
    vis[u]^=1;
}
void dfs(int u){
    tin[u]=++timer, tour[timer]=u;
    for (int v:g[u]) if(v!=up[u][0]){
        h[v]=h[u]+1, up[v][0]=u;
        dfs(v);
    }
    tout[u]=++timer, tour[timer]=u;
}
int lca(int u, int v){
    if(h[u]!=h[v]){
        if (h[u]<h[v]) swap(u,v);
        int k=h[u]-h[v];
        for (int j=0; (1<<j)<=k; ++j)
            if (k>>j&1) u=up[u][j];
    }
    if(u==v) return u;
    for (int j=log2(h[u]); j>=0; --j)
        if(up[u][j]!=up[v][j]) u=up[u][j],v=up[v][j];
    return up[u][0];
}
void solve(){
    cin>>n>>q;
    S=sqrt(n);
    map<int,bool>mp;
    for (int i=0; i<n; ++i){
        cin>>a[i];
        mp[a[i]]=true;
    }
    for (auto i:mp){
        co[i.first]=++m,dco[m]=i.first;
    }
    for (int i=0; i<n; ++i)
        a[i]=co[a[i]];
    for (int i=0,u,v; i<n-1; ++i){
        cin>>u>>v;
        --u,--v;
        g[u].push_back(v),g[v].push_back(u);
    }
    dfs(0),build(1,1,m);
    for (int j=1; j<17; ++j){
        for (int u=0; u<n; ++u)
            up[u][j]=up[up[u][j-1]][j-1];
    }
    for (int i=0,u,v; i<q; ++i){
        cin>>u>>v;
        --u,--v;
        if (tin[u]>tin[v]) swap(u,v);
        int lc=lca(u,v);
        if (lc==u) qr.push_back({tin[u],tin[v],lc,i});
        else qr.push_back({tout[u],tin[v],lc,i});
    }
    sort(all(qr),[&](Q a, Q b){
        if((a.l/S)!=(b.l/S)) return (a.l/S)<(b.l/S);
        else{
            if ((a.l/S) & 1) return a.r>b.r;
            else return a.r<b.r;
        }
    });
    vector<int>res(q);
    int l1=0,r1=-1,l2,r2;
    for (auto qry:qr){
        l2=qry.l,r2=qry.r;
        while(r1+1<=r2) ++r1,upd(tour[r1]);
        while(r1>r2) upd(tour[r1]),--r1;
        while(l1<l2) upd(tour[l1]),++l1;
        while(l1-1>=l2) --l1,upd(tour[l1]);
        int u=tour[qry.l],v=tour[qry.r];
        if(qry.lc!=u&&qry.lc!=v) upd(qry.lc);
        int len=h[u]+h[v]-2*h[qry.lc];
        if(seg[1][1]>=(len+1)/2+1) res[qry.id]=dco[seg[0][1]];
        else res[qry.id]=-1;
        if(qry.lc!=u&&qry.lc!=v) upd(qry.lc);
    }
    for(auto i:res)
        cout<<i<<'\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}