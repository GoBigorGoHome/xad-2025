// 选择一个块长 B
// 先把 a[0] 到 a[n-1] 每 B 个分一块，存在一个 vector<int> 里。
// 插入元素 x:
// 1. 找到 x 应该插入到哪一块
// 2. 把 x 插入到那一块，用 vector::insert()
// 3. 如果块长达到 2*B，就把它分成两个长为 B 的块。 

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int B = 333;
    int NB = (n + B - 1) / B;
    // NOTE: 用 forward_list 比用 vector 慢。
    // 这种数据结构叫《块状链表》，在 NOI 大纲里是 NOI 级，难度系数 8。
    std::forward_list<vector<int>> b;

    for (int i = NB - 1; i >= 0; i--) {
        int l = i * B;
        int r = min((i + 1) * B, n);
        b.push_front({a.begin() + l, a.begin() + r});
    }


    int q = n;
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int p, x;
            cin >> p >> x;
            p--;
            for (auto it = b.begin(); it != b.end(); ++it) {
                if (p <= (int) it->size()) {
                    it->insert(it->begin() + p, x);
                    if ((int) it->size() == 2 * B) {
                        vector<int> t(it->begin() + B, it->end());
                        b.insert_after(it, t);
                        it->resize(B);
                    }
                    break;
                }
                p -= (int) it->size();
            }
        } else {
            int p;
            cin >> p;
            p--;
            for (auto it = b.begin(); it != b.end(); ++it) {
                if (p < (int) it->size()) {
                    cout << (*it)[p] << '\n';
                    break;
                }
                p -= (int) it->size();
            }
        }
    }
}