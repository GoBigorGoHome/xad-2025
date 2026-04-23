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
    const int L = 22;
    vector<int> f(1 << L, -1);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        f[a[i]] = a[i];
    }
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < 1 << L; j++) {
            if (j >> i & 1 && f[j] == -1)
                f[j] = f[j ^ (1 << i)];
        }
    }
    for (int i = 0; i < n; i++) {
        cout << f[((1 << L) - 1) ^ a[i]] << ' ';
    }
    cout << '\n';
}