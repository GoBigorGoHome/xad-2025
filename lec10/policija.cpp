#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int low[maxn], dfn[maxn], num = 0;
int last[maxn];
vector<int> g[maxn];
vector<int> child[maxn];
void dfs(int u, int p)
{ // p是u的父节点
   low[u] = dfn[u] = ++num;
   for (int v : g[u])
      if (dfn[v] == 0)
      {
         // uv 是树边
         child[u].push_back(v);
         dfs(v, u);
         low[u] = min(low[u], low[v]);
      }
      else if (v != p)
      {
         // uv 是回边
         low[u] = min(low[u], dfn[v]);
      }
   last[u] = num;
}
bool is_houdai(int a, int b)
{ // a是不是b的后代，a是否在子树b里
   return dfn[b] <= dfn[a] && dfn[a] <= last[b];
}
int which_child(int a, int b)
{ // 点a在点b的哪个孩子里
   if (dfn[a] <= dfn[b] || dfn[a] > last[b])
      return 0; // a不在b的子树里。
   // 在child[b]找“满足 dfn[x] <= dfn[a]的最后一个x”
   int l = 0, r = (int)child[b].size();
   while (l + 1 < r)
   {
      int m = (l + r) / 2;
      if (dfn[child[b][m]] <= dfn[a])
         l = m;
      else
         r = m;
   }
   return child[b][l];
}

int main()
{
   int n, m;
   cin >> n >> m;
   for (int i = 0; i < m; i++)
   {
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
   }
   dfs(1, 0); // 点1是DFS的起点
   int Q;
   cin >> Q;
   while (Q--)
   {
      int t, a, b, c, d;
      cin >> t;
      int cut = 0;
      if (t == 1)
      {
         cin >> a >> b >> c >> d;
         if (low[c] > low[d])
            swap(c, d);
         cut = low[d] == dfn[d] && (is_houdai(a, d) ^ is_houdai(b, d));
      }
      else
      {
         cin >> a >> b >> c;
         for (int x : {a, b})
         {
            int y = which_child(x, c);
            if (y && low[y] >= dfn[c] && !is_houdai(a + b - x, y))
            {
               cut = 1;
               break;
            }
         }
      }
      if (cut)
         cout << "no\n";
      else
         cout << "yes\n";
   }
   return 0;
}