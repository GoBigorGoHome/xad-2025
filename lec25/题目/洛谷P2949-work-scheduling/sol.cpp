/**
 *    author:  zjs
 *    created: 28.06.2026 16:02:58
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    struct Task {
        int deadline, profit;
    };

    int N;
    cin >> N;
    vector<Task> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i].deadline >> a[i].profit;
    }
    sort(a.begin(), a.end(), [](Task x, Task y) { return x.deadline < y.deadline; });

    priority_queue<int, vector<int>, greater<int>> q;
    for (auto [d, p] : a) {
        if ((int) q.size() < d)
            q.push(p);
        else if (q.top() < p) {
            q.pop();
            q.push(p);
        }
    }
    long long ans = 0;
    while (q.size()) {
        ans += q.top();
        q.pop();
    }
    cout << ans << '\n';
}