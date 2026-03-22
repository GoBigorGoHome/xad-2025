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
    
    int B = 333;
    vector<vector<int>> b((n + B - 1) / B);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        b[i / B].push_back(x);
    }
    
    int q = n;
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int p, x;
            cin >> p >> x;
            p--;
            for (int i = 0; i < (int) b.size(); i++) {
                if (p <= (int) b[i].size()) {
                    b[i].insert(b[i].begin() + p, x);
                    if ((int) b[i].size() == 2 * B) {
                        vector<int> t(b[i].begin() + B, b[i].end());
                        b.insert(b.begin() + i + 1, t);
                        b[i].resize(B);
                    }
                    break;
                }
                p -= (int) b[i].size();
            }
        } else {
            int p;
            cin >> p;
            p--;
            for (int i = 0; i < (int) b.size(); i++) {
                if (p < (int) b[i].size()) {
                    cout << b[i][p] << '\n';
                    break;
                }
                p -= (int) b[i].size();
            }
        }
    }
}