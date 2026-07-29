#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define ZERO (1e-10)
#define INF int(1e9+1)
#define CL(A,I) (memset(A,I,sizeof(A)))
#define DEB printf("DEB!\n");
#define D(X) cout<<"  "<<#X": "<<X<<endl;
#define EQ(A,B) (A+ZERO>B&&A-ZERO<B)
typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
#define IN(n) int n;scanf("%d",&n);
#define FOR(i, m, n) for (int i(m); i < n; i++)
#define F(n) FOR(i,0,n)
#define FF(n) FOR(j,0,n)
#define FT(m, n) FOR(k, m, n)
#define aa first
#define bb second
void ga(int N,int *A){F(N)scanf("%d",A+i);}
#define MX (100005)
#define LG (19)
#define QR (1<<LG)
struct DC{
    struct DSU{
        int C[MX],M[MX],U[MX],Q[MX],q[MX],W,N;
        int gc(int a){return C[a]=(a==C[a]?a:gc(C[a]));}
        void con(int a,int b){
            if(gc(a)==gc(b))return;
            C[gc(a)]=gc(b);
        }
        DSU(){W=N=0,CL(U,-1),CL(M,-1);}
        void CLR(){F(W)M[Q[i]]=-1;F(N)U[q[i]]=-1;W=N=0;}
        int mp(int u){if(!~U[u])U[u]=N,q[N++]=u;return U[u];}
        void st(int u,int x){
            u=mp(u);
            if(!~M[x])M[x]=u,Q[W++]=x;
            C[u]=M[x];
        }
        void pre(){F(N)gc(i);}
        int GC(int a){return gc(mp(a));}
        void CON(int a,int b){con(mp(a),mp(b));}
    }C[LG];
    DC(){F(MX)C->st(i,i);}
    map<ii,int> l;
    int I,A[MX],X[MX],Y[MX],D[MX];
    void CLR(){l.clear(),I=0;}
    void ADD(int a,int b){A[I]=1,X[I]=a,Y[I]=b,D[I]=INF,l[minmax(a,b)]=I++;}
    void DEL(int a,int b){A[I]=-1,D[l[minmax(a,b)]]=I++;}
    void QY(int a,int b){A[I]=0,X[I]=a,Y[I++]=b;}
    void GO(vi&o){if(I)rc(0,I-1,1,o);}
    vector<pair<ii,int>> G[LG];
    void st(int x,int d){C[d].st(x,C[d-1].GC(x));}
    void rc(int b,int e,int d,vi&o){
        C[d].CLR(),G[d].clear();
        FT(b,e+1)st(X[k],d),st(Y[k],d);
        for(auto&h:G[d-1])st(h.aa.aa,d),st(h.aa.bb,d);
        for(auto&h:G[d-1])if(h.bb>e)C[d].CON(h.aa.aa,h.aa.bb);
                          else if(h.bb>=b)G[d].PB(h);
        C[d].pre();
        if(b==e){
            if(!A[b])o.PB(C[d].GC(X[b])==C[d].GC(Y[b]));
            return;
        }
        int m=(b+e)/2;
        rc(b,m,d+1,o);
        FT(b,m+1)if(A[k]>0)G[d].PB({{X[k],Y[k]},D[k]});
        rc(m+1,e,d+1,o);
    }
}T;
int N,Q,A[MX],X[MX],Y[MX],V[MX],O[MX];
set<ii> F;
vi o;
int main(void){
    scanf("%d%d",&N,&Q),CL(O,-1);
    F(Q){
        scanf("%d%d%d",A+i,X+i,Y+i);
        if(!A[i])scanf("%d",V+i);
    }
    FF(10){
        T.CLR(),F.clear();
        F(Q)if(!A[i]){
                if(V[i]<=j)T.ADD(X[i],Y[i]),F.insert(minmax(X[i],Y[i]));
            }else if(A[i]^1)T.QY(X[i],Y[i]);
            else if(F.count(minmax(X[i],Y[i])))T.DEL(X[i],Y[i]),F.erase(minmax(X[i],Y[i]));
        o.clear(),T.GO(o);
        F((int)o.size())if(!~O[i]&&o[i])O[i]=j;
    }
    F((int)o.size())printf("%d\n",O[i]);
    return 0;
}
