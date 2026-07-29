/*
只用树状数组 和 vector
*/

/**
 *    author:  zjs
 *    created: 03.06.2026 14:56:57
**/
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

template<typename T>
struct fenwick : std::vector<T> {
    using std::vector<T>::vector;

    fenwick(const std::vector<T>& a) : std::vector<T>(a) {
        for (size_t i = 0; i < this->size(); i++) {
            if ((i | (i + 1))  < this->size())
                (*this)[i | (i + 1)] += (*this)[i];
        }
    }

    fenwick(int n, T v) : fenwick(std::vector<T>(n, v)) {}

    void add(int p, int v) {
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
    int n, m, q;
    cin >> n >> m >> q;
    struct Query {
        int x, y;
        long long ans = -1;
    };
    vector<Query> qry(q);
    for (int i = 0; i < q; i++) {
        cin >> qry[i].x >> qry[i].y;
        qry[i].x--;
        qry[i].y--;
    }

    vector<vector<int>> g(n);
    for (int i = 0; i < q; i++)
        if (qry[i].y != m - 1)
            g[qry[i].x].push_back(i);

    fenwick<int> f(m - 1, 1);
    for (int x = 0; x < n; x++) {
        vector<int> drop;
        fenwick<int> tail;
        int cnt = m - 1;

        for (int i : g[x]) {
            if (qry[i].y < cnt) {
                int y = f.max_prefix(qry[i].y);
                qry[i].ans = (long long) x * m + y;
                drop.push_back(y);
                f.add(y, -1);
                cnt--;
            } else {
                int p = tail.max_prefix(qry[i].y - cnt);
                tail.add(p, -1);
                qry[i].ans = -p - 1;
            }
            tail.push_back(1);
        }

        // 把 f 恢复原状
        for (int y : drop)
            f.add(y, 1);
    }

    vector<vector<long long>> seq(n + 1); // seq[n] 存储最后一列
    fenwick<int> last_col(n, 1);
    for (int i = 0; i < n; i++)
        seq[n].push_back((long long) (i + 1) * m - 1);

    for (auto & [x, y, ans] : qry) {
        int p = last_col.max_prefix(x);
        if (y == m - 1) {
            ans = seq[n][p];
        } else {
            if (ans < 0) {
                ans = seq[x][-ans - 1];
            }
            seq[x].push_back(seq[n][p]);
        }
        last_col.add(p, -1);
        last_col.push_back(1);
        seq[n].push_back(ans);

        cout << ans + 1 << '\n';
    }

}