#include <bits/stdc++.h>
using namespace std;


const int maxn = 2500 + 5;
int n, m, k;
vector<int> g[maxn];
long long p[maxn]; //景点的分数
vector<int> cand[maxn];
int dist[maxn][maxn];
const int INF = 1e9;

void bfs(int s) {
  for (int i = 1; i <= n; i++)
    dist[s][i] = INF;
  queue<int> q;
  q.push(s);
  dist[s][s] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : g[u])
    if (dist[s][v] == INF) {
      dist[s][v] = dist[s][u] + 1;
      q.push(v);
    }
  }
}

bool cmp(int i, int j) {
  return p[i] > p[j];
}

int main() {
  cin >> n >> m >> k;
  for (int i = 2; i <= n; i++) cin >> p[i];
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v); g[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) bfs(i);

  vector<int> ad;
  for (int i = 2; i <= n; i++)
    if (dist[1][i] <= k + 1) ad.push_back(i);
  sort(ad.begin(), ad.end(), cmp);
  
  for (int i = 2; i <= n; i++)
    for (int v : ad)
      if (v != i && dist[i][v] <= k + 1) {
        cand[i].push_back(v);
        if (cand[i].size() == 3) break;
      }

  long long ans = 0;

  for (int b = 2; b <= n; b++)
    for (int c = b + 1; c <= n; c++)
      if (dist[b][c] <= k + 1)
        for (int a : cand[b])
          for (int d : cand[c])
            if (a != c && a != d && b != d)
              ans = max(ans, p[a] + p[b] + p[c] + p[d]);
  cout << ans << '\n';         
}