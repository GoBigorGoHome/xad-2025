#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const int N=1e5+10;

vector<int> g[N];
int n,m;
int c[N];
int top[N];
int q[N];
int ans[N];
vector<int>mount[N];

void dfs(int now=1,int f=0){
    int buf=top[c[now]];
    for(int x : mount[now]){
        if(ans[x] != -1){
            ans[x]=(top[q[x]]!=ans[x]);
        }else{
            ans[x]=top[q[x]];
        }
    }
    for (int to : g[now])
        if(to != f){
            top[c[now]] = to;
            dfs(to, now);
        }
    top[c[now]] = buf;
}

void input(){
    cin >> n >> m;
    for(int i=1;i<=n;i++)
        cin >> c[i];
    int p1,p2;
    for(int i=1;i<n;i++){
        cin >> p1 >> p2;
        g[p1].push_back(p2);
        g[p2].push_back(p1);
    }
    for(int i=0;i<m;i++){
        cin >> p1 >> p2 >> q[i];
        if(c[p1]==q[i]||c[p2]==q[i]){
            ans[i]=1;
        }else{
            ans[i]=-1;
            mount[p1].push_back(i);
            mount[p2].push_back(i);
        }
    }
}

int main(){
    input();
    dfs();
    for(int i=0;i<m;i++)
        cout << ans[i];
    cout << '\n';
    return 0;
}
