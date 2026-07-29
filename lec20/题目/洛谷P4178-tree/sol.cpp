#include <bits/stdc++.h>
using namespace std;

template <integral T>
struct fenwick {
    vector<T> a;

    fenwick(const vector<T>& a_) : a(a_) {
        for (size_t i = 0; i < a.size(); i++)
            if ((i | (i + 1))  < a.size())
                a[i | (i + 1)] += a[i];
    }

    fenwick(int n = 0, T v = 0) : fenwick(vector<T>(n, v)) {}

    // 返回前n项之和，即 a[0] + ... + a[n - 1]
    T sum(int n) {
        n = min(n, (int) a.size());
        T ans = 0;
        while (n > 0) {
            ans += a[n - 1];
            n &= n - 1;
        }
        return ans;
    }
    // 返回 a[l] + ... + a[r - 1]
    T sum(int l, int r) {
        return sum(r) - sum(l);
    }

    void push_back(T v) {
        size_t p = a.size();
        for (size_t len = 1; len & p; len <<= 1)
            v += a[p ^ len];
        a.push_back(v);
    }

    void add(int p, T v) {
        while (p < (int) a.size()) {
            a[p] += v;
            p |= p + 1;
        }
    }
    // Returns the length of the longest prefix with sum <= v
    int max_prefix(T v) {
        T sum = 0;
        size_t p = 0;
        for (size_t len = bit_floor(a.size()); len > 0; len >>= 1) {
            if (p + len <= a.size() && !(v < sum + a[p + len - 1])) {
                sum += a[p + len - 1];
                p += len;
            }
        }
        return (int) p;
    }
};
const int maxn = 4e4 + 4;
bool del[maxn];
int sz[maxn];

struct Edge {
    int to, w;
};
vector<Edge> g[maxn];

void get_size(int u, int p) {
    sz[u] = 1;
    for (auto [v, _] : g[u]) {
        if (v == p || del[v]) continue;
        get_size(v, u);
        sz[u] += sz[v];
    }
}

int find_centroid(int u) {
    get_size(u, 0);
    int p = 0;
    int tree_sz = sz[u];
    while (1) {
        int next = -1;
        for (auto [v, _] : g[u]) {
            if (del[v] || v == p) continue;
            if (sz[v] * 2 > tree_sz) {
                next = v;
                break;
            }
        }
        if (next == -1) break;
        p = u;
        u = next;
    }
    return u;
}

vector<int> divide() {
    vector<int> seq;
    seq.push_back(find_centroid(1));
    for (int i = 0; i < (int) seq.size(); i++) {
        int u = seq[i];
        del[u] = true;
        for (auto [v, _] : g[u]) {
            if (!del[v])
                seq.push_back(find_centroid(v));
        }
    }
    for (int u : seq)
        del[u] = false;
    return seq;
}
// 以上是重心分解的代码

vector<int> dist;
void dfs(int u, int p, int d) {
    dist.push_back(d);
    for (auto [v, w] : g[u]) {
        if (del[v] || v == p) continue;
        dfs(v, u, d + w);
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    int k;
    cin >> k;

    fenwick<int> f(k + 1);
    f.add(0, 1);
    long long ans = 0;
    for (int u : divide()) {
        del[u] = true;
        int cnt = 0;
        for (auto [v, w] : g[u]) {
            if (del[v]) continue;
            dfs(v, 0, w);
            auto cur = views::drop(dist, cnt);
            cnt = (int) dist.size();
            for (int d : cur) {
                ans += f.sum(k - d + 1);
            }
            for (int d : cur) {
                if (d <= k)
                    f.add(d, 1);
            }
        }
        for (int d : dist)
            if (d <= k)
                f.add(d, -1);
        dist.clear();
    }
    cout << ans << '\n';
}