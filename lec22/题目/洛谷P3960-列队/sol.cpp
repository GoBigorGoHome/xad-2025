/*
每次整队前后，只有最后一列的人才可能改行。

一个人在最后一列只有两种可能性：
1. 此人从没离过队。此人一开始就在最后一列，并且所在的行从来没有人离队。
2. 此人离队归来后到最后一列。

如果一个人一开始不在最后一列，并且没离过队，那么他不可能到过最后一列，也就不可能改行。

我们把人分成两类：流动人员、非流动人员。
流动人员：一开始在最后一列的人 和 离队过的人。或者说，到过最后一列的人。

性质：每一行的非流动人员在前头，流动人员在末尾。

我们维护流动人员。

最后一列的人单独维护，称它们为特殊流动人员，其他流动人员称为普通流动人员。


对于每一行，我们维护
1. 一开始在这一行的人，哪些人成了流动人员。把这些人的编号存入一个列表。
2. 这一行末尾的普通流动人员的列表。

回答询问 (x, y)
首先判断这个人是非流动人员还是流动人员。
如果是非流动人员，问题归为查询第 x 行的第 y 个非流动人员的编号。
如果是流动人员，
*/


/*
题目：有 10^{18} 个人站成一行，从左到右从 1 开始编号。
有 Q 个操作，第 i 个操作是：让从左数第 x_i 个人离开。Q <= 10^6, 1 <= x_i <= 10^{18} - i + 1.
输出每次离开的人的编号。
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

    fenwick(int n, T v) : fenwick(std::vector<T>(n, v)) {
    }

    void add(int p, int v) {
        while (p < (int) this->size()) {
            (*this)[p] += v;
            p |= p + 1;
        }
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

#include <ext/pb_ds/assoc_container.hpp>

template <typename K, typename V, typename Comp = std::less<K>>
using ordered_map = __gnu_pbds::tree<
    K, V, Comp,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
>;

template <typename K, typename Comp = std::less<K>>
using ordered_set = ordered_map<K, __gnu_pbds::null_type, Comp>;

// Supports
//  auto iterator = ordered_set().find_by_order(idx); // (0-indexed)
//  int num_strictly_smaller = ordered_set().order_of_key(key);

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
        g[qry[i].x].push_back(i);
    
    fenwick<int> f(m - 1, 1);
    for (int x = 0; x < n; x++) {
        vector<int> drop;
        for (int i : g[x]) {
            int y = f.max_prefix(qry[i].y);
            if (y < m - 1) {
                qry[i].ans = (long long) x * m + y;
                drop.push_back(y);
                f.add(y, -1);
            }
        }
        // 把 f 恢复原状
        for (int y : drop)
            f.add(y, 1);
    }
    
    ordered_set<int> last_col;
    vector<ordered_set<int>> tail(n);
    vector<long long> moved_people;

    for (int i = 0; i < n; i++) {
        moved_people.push_back((long long)(i + 1) * m - 1);
        last_col.insert(i);
    }

    for (auto & [x, y, ans] : qry) {
        auto it = last_col.find_by_order(x);
        if (y == m - 1) {
            ans = moved_people[*it];
        } else {
            if (ans == -1) {
                int order = y - (m - 1 - (int) tail[x].size());
                auto it2 = tail[x].find_by_order(order);
                ans = moved_people[*it2];
                tail[x].erase(it2);
            }
            tail[x].insert(*it);
        }
        last_col.erase(it);
        last_col.insert((int) moved_people.size());
        moved_people.push_back(ans);
    }
    for (int i = 0; i < q; i++)
        cout << qry[i].ans + 1 << '\n';
}