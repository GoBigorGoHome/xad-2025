/**
 *    author:  zjs
 *    created: 19.06.2026 22:41:09
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
            // debug(u);
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

template<integral T>
struct fenwick : std::vector<T> {
    using std::vector<T>::vector;

    fenwick(const std::vector<T>& a) : std::vector<T>(a) {
        for (size_t i = 0; i < this->size(); i++) {
            if ((i | (i + 1))  < this->size())
                (*this)[i | (i + 1)] += (*this)[i];
        }
    }

    fenwick(int n, T v) : fenwick(std::vector<T>(n, v)) {}

    void add(int p, T v) {
        while (p < (int) this->size()) {
            (*this)[p] += v;
            p |= p + 1;
        }
    }

    void push_back(T v) {
        size_t n = this->size();
        std::vector<T>::push_back(v);
        for (size_t len = 1; len & n; len <<= 1)
            (*this)[n] += (*this)[n ^ len];
    }

    T sum(int n) {
        n = std::min(n, (int) this->size());
        T ans = 0;
        while (n > 0) {
            ans += (*this)[n - 1];
            n &= n - 1;
        }
        return ans;
    }

    T sum(int l, int r) {
        return sum(r) - sum(l);
    }

    int max_prefix(T v) {
        T sum = 0;
        size_t at = 0;
        for (size_t len = std::bit_floor(this->size()); len > 0; len >>= 1) {
            if (at + len <= this->size() && !(v < sum + (*this)[at + len - 1])) {
                sum += (*this)[at + len - 1];
                at += len;
            }
        }
        return (int) at;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    vector<int> value(n);
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto seq = centroid_decomposition(g);
    vector<vector<fenwick<int>>> data(n);

    struct Info {
        int centroid, dist, id;
    };
    vector<vector<Info>> anc(n);

    vector<bool> del(n);
    vector<int> dist(n);
    for (int centroid : seq) {
        vector<fenwick<int>> f;
        vector<int> postorder;
        int sz = 0;
        int max_dist = 0;
        [&](this auto dfs, int u, int p, int depth) -> void {
            // part 1
            for (int v : g[u]) {
                if (del[v] || v == p) continue;
                dfs(v, u, depth + 1);
            }
            // part 2
            postorder.push_back(u);
            anc[u].push_back({centroid, depth, (int) f.size()});
            dist[u] = depth;
            max_dist = max(max_dist, depth);
            // part 3
            if (p == centroid) {
                vector<int> sum(max_dist + 1);
                for (int v :  views::drop(postorder, sz)) {
                    sum[dist[v]] += value[v];
                }
                f.push_back(sum);
                sz = (int) postorder.size();
                max_dist = 0;
            }
        }(centroid, -1, 0);

        for (int v : postorder)
            max_dist = max(max_dist, dist[v]);
        vector<int> sum(max_dist + 1);
        for (int v : postorder)
            sum[dist[v]] += value[v];
        f.push_back(sum);

        data[centroid] = f;
        del[centroid] = true; // 别忘了
    }

    int ans = 0;
    while (m--) {
        int type, x, k;
        cin >> type >> x >> k;
        x ^= ans; k ^= ans;
        x--;
        if (!(0 <= x && x < n))
            break;

        if (type == 0) { // 查询
            ans = 0;
            for (auto [c, d, i] : anc[x]) {
                ans += data[c].back().sum(k - d + 1);
                if (c != x) {
                    ans -= data[c][i].sum(k - d + 1);
                }
            }
            cout << ans << '\n';
        } else {
            int delta = k - value[x];
            value[x] = k;
            for (auto [c, d, i] : anc[x]) {
                data[c].back().add(d, delta);
                if (c != x)
                    data[c][i].add(d, delta);
            }
        }
    }
}