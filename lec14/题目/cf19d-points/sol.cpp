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
    int B = (int) sqrt(N);
    int NB = (N + B - 1) / B;
    
    vector<multiset<int>> a(N), b(NB);
 
    auto work = [&](int l, int r, auto ok) -> int {
        int lb = (l + B - 1) / B;
        int rb = r / B;
        if (lb > rb) {
            for (int i = l; i < r; i++)
                if (ok(a[i]))
                    return i;
            return r;
        }
 
        for (int i = l; i < lb * B; i++)
            if (ok(a[i]))
                return i;
 
        for (int ib = lb; ib < rb; ib++)
            if (ok(b[ib]))
                for (int i = ib * B; i < (ib + 1) * B; i++)
                    if (ok(a[i]))
                        return i;
 
        for (int i = rb * B; i < r; i++)
            if (ok(a[i]))
                return i;
 
        return r;
    };
 
    for (int i = 0; i < n; i++) {
        if (type[i] == "add") {
            a[x[i]].insert(y[i]);
            b[x[i] / B].insert(y[i]);
        } else if (type[i] == "remove") {
            a[x[i]].extract(y[i]);
            b[x[i] / B].extract(y[i]);
        } else {
            auto ok = [y = y[i]](const multiset<int>& s) {
                return s.size() && *s.rbegin() > y; 
            };
            int j = work(x[i] + 1, N, ok);
            if (j == N)
                cout << -1 << '\n';
            else
                cout << real_x[j] << ' ' << *a[j].upper_bound(y[i]) << '\n';
        }
    }
}