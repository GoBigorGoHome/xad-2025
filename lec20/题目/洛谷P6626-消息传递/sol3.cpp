/**
 *    author:  zjs
 *    created: 19.06.2026 20:02:21
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

// Requires -std=c++23 to compile.
// Nodes are 0-indexed.
vector<int> centroid_decomposition(const vector<vector<int>>& tree) {
    int n = (int) tree.size();
    vector<int> sz(n);
    vector<bool> del(n);
    vector<int> seq;

    [&](this auto divide, int x) -> void {
        [&](this auto get_sz, int u, int p) -> void {
            sz[u] = 1;
            for (int v : tree[u]) {
                if (del[v] || v == p) continue;
                get_sz(v, u);
                sz[u] += sz[v];
            }
        }(x, -1);

        int c = [&](this auto find_centroid, int u, int p, int tree_sz) -> int {
            for (int v : tree[u]) {
                if (del[v] || v == p) continue;
                if (sz[v] * 2 > tree_sz)
                    return find_centroid(v, u, tree_sz);
            }
            return u;
        }(x, -1, sz[x]);

        seq.push_back(c);
        del[c] = true;

        for (int v : tree[c]) // 这里容易写错，是 tree[c]，不是 tree[x]！
            if (!del[v])
                divide(v);
    }(0);

    return seq;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    struct Query {
        int k, id;
    };
    vector<vector<Query>> q(n);
    for (int i = 0; i < m; i++) {
        int x, k;
        cin >> x >> k;
        x--;
        q[x].push_back({k, i});
    }

    auto seq = centroid_decomposition(g);

    vector<bool> del(n);
    vector<int> sz(n);
    vector<int> dist(n);
    vector<int> cnt(n);
    vector<int> ans(m);

    auto query = [&](int x) {
        for (auto [k, id] : q[x]) {
            if (k >= dist[x])
                ans[id] += cnt[k - dist[x]];
        }
    };

    for (int c : seq) {
        vector<int> preorder;

        [&](this auto dfs, int u, int p, int depth) -> void {
            preorder.push_back(u);
            sz[u] = 1;
            dist[u] = depth;
            for (int v : g[u]) {
                if (del[v] || v == p) continue;
                dfs(v, u, depth + 1);
                sz[u] += sz[v];
            }
        }(c, -1, 0);

        for (int u : preorder)
            cnt[dist[u]]++;
        query(c);
        int l = 1;
        for (int u : g[c]) {
            if (del[u]) continue;
            int r = l + sz[u];
            for (int i = l; i < r; i++)
                cnt[dist[preorder[i]]]--;
            for (int i = l; i < r; i++)
                query(preorder[i]);
            for (int i = l; i < r; i++)
                cnt[dist[preorder[i]]]++;
            l = r;
        }
        for (int u : preorder)
            cnt[dist[u]] = 0;
        del[c] = true;
    }
    for (int x : ans)
        cout << x << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
}