#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

struct fenwick {
    vector<int> a;
    int n;
    fenwick(int n_) : a(n_ + 1), n(n_) {}
    void add(int i, int v) {
        while (i <= n) {
            a[i] += v;
            i += i & -i;
        }
    }
    int sum(int i) {
        int res = 0;
        while (i > 0) {
            res += a[i];
            i -= i & -i;
        }
        return res;
    }
};

struct Query {
    int l, r, id;
};

bool cmp(Query a, Query b) {
    return a.r < b.r;
}

template<typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<Query> b(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        b[i] = {l, r, i};
    }
    sort(b.begin(), b.end(), cmp);

    int B = (int) sqrt(n);
    int NB = (n + B - 1) / B;

    vector<int> pos(n);
    vector<priority_queue<int>> positions(NB);
    vector<min_pq<int>> history(NB);

    auto update =[&](int ib) {
        int l = ib * B;
        int r = min(l + B, n);
        for (int i = l; i < r; i++) {
            if (!history[ib].empty() && history[ib].top() < pos[i]) {
                int t = pos[i];
                pos[i] = history[ib].top();
                history[ib].pop();
                history[ib].push(t);
            }
        }
        history[ib] = {};
    };

    fenwick f(n);

    auto build = [&](int ib) { // 重建 positions[ib]
        int l = ib * B;
        int r = min(l + B, n);
        positions[ib] = {};
        for (int i = l; i < r; i++)
            if (pos[i])
                positions[ib].push(pos[i]);
    };

    vector<int> ans(q);
    auto ptr = b.begin();

    for (int i = 1; i <= n; i++) {
        int l = a[i];
        int r = n;
        int lb = (l + B  - 1) / B;
        int rb = r / B;
        // debug(l, r, lb, rb);
        int x = 0;
        if (lb > rb) {
            update(lb - 1);
            for (int j = l; j < r; j++) {
                if (pos[j] > x) {
                    swap(pos[j], x);
                }
            }
            // 重建 positions[lb - 1]
            build(lb - 1);
        } else {
            if (l != lb * B) {
                update(lb - 1);
                debug(pos);
                for (int j = l; j < lb * B; j++)
                    if (pos[j] > x)
                        swap(pos[j], x);
                // debug(pos);
                build(lb - 1);
                // debug(pos);
            }
            debug(x);
            for (int ib = lb; ib < rb; ib++) {
                if (!positions[ib].empty() && positions[ib].top() > x) {
                    if (x)
                        positions[ib].push(x);
                    history[ib].push(x);

                    x = positions[ib].top();
                    positions[ib].pop();
                }
            }
            debug(x);
            if (r != rb * B) {
                update(rb);
                for (int j = rb * B; j < r; j++)
                    if (pos[j] > x)
                        swap(pos[j], x);
                build(rb);
            }
            if (x)
                f.add(x, -1);
  
            update(a[i] / B); // 在做下面两步之前必须先清空 a[i] 所在的块的历史
            pos[a[i]] = i;
            positions[a[i] / B].push(i);
            f.add(i, 1);
        }
        debug(a[i], x);
        debug(pos);
        while (ptr != b.end() && ptr->r == i) {
            ans[ptr->id] = f.sum(ptr->r) - f.sum(ptr->l - 1);
            ++ptr;
        }
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}
/*
9 1
3 7 2 4 6 5 9 8 1
5 8
*/