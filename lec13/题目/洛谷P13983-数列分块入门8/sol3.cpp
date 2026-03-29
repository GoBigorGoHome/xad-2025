#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

// 这题是区间推平操作。分块不是最合适的解法。

// 推平区间 [l, r)
// 1. 查询 a[r] 的值，把 r 设置为左端点
// 2. 查询区间 [l, r)
// 3. 删除区间 [l, r)
// 4. 把 l 设置为左端点
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    map<int,int> a;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int q = n;
    while (q--) {
        int l, r, c;
        cin >> l >> r >> c;
        --l;
        auto lptr = a.insert({l, prev(a.upper_bound(l))->second}).first;
        auto rptr = a.insert({r, prev(a.upper_bound(r))->second}).first;
        int ans = 0;
        for (auto it = lptr; it != rptr; ++it) {
            auto [i, v] = *it;
            if (v == c) {
                ans += next(it)->first - i;
            }
        }
        a.erase(lptr, rptr);
        a[l] = c;
        cout << ans << '\n';
    }
}