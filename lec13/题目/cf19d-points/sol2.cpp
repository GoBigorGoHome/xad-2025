#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

vector<int> compress(vector<int>& a) {
    vector<int> I(a.size());
    iota(I.begin(), I.end(), 0);
    sort(I.begin(), I.end(), [&](int i, int j) { return a[i] < a[j]; });

    vector<int> b;
    for (int i : I) {
        if (b.empty() || b.back() < a[i])
            b.push_back(a[i]);
        a[i] = (int) b.size() - 1;
    }
    return b; // 排序去重之后的 a
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<string> type(n);
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> type[i] >> x[i] >> y[i];
    vector<int> real_x = compress(x);
    
    int N = (int) real_x.size();
    vector<set<int>> a(N);
    vector<int> b(2 * N, -1); // 线段树。b[i]：块 i 里的纵坐标的最大值

    for (int i = 0; i < n; i++) {
        if (type[i] == "add") {
            a[x[i]].insert(y[i]);
            int p = x[i] + N;
            b[p] = *a[x[i]].rbegin();
            for (p /= 2; p > 0; p /= 2) {
                b[p] = max(b[p * 2], b[p * 2 + 1]);
            }
        } else if (type[i] == "remove") {
            a[x[i]].erase(y[i]);
            int p = x[i] + N;
            b[p] = a[x[i]].empty() ? -1 : *a[x[i]].rbegin();
            for (p /= 2; p > 0; p /= 2) {
                b[p] = max(b[p * 2], b[p * 2 + 1]);
            }
        } else {
            int l = x[i] + 1 + N, r = N + N;
            int p = -1;
            while (l < r) {
                if (l & 1) {
                    if (b[l] > y[i]) { p = l; break; }
                    l++;
                }
                if (r & 1) {
                    if (b[r - 1] > y[i]) p = r - 1;
                    r--;
                }
                l /= 2; r /= 2;
            }
            if (p == -1)
                cout << -1 << '\n';
            else {
                while (p < N) {
                    if (b[p * 2] > y[i])
                        p = 2 * p;
                    else
                        p = 2 * p + 1;
                }
                cout << real_x[p - N] << ' ' << *a[p - N].upper_bound(y[i]) << '\n';
            }
        }
    }
}