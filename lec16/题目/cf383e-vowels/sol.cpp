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
    // 计算全是辅音的单词有多少个。
    const int L = 24;
    vector<int> f(1 << L);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int mask = 0;
        string s;
        cin >> s;
        for (char c : s)
            mask |= 1 << (c - 'a');
        f[mask]++;
    }
    for (int i = 0; i < L; i++)
        for (int j = 0; j < 1 << L; j++)
            if (j >> i & 1)
                f[j] += f[j ^ 1 << i];
    int ans = 0;
    for (int x : f)
        ans ^= (n - x) * (n - x);
    cout << ans << '\n';
}