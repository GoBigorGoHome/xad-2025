#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

long long f[105][105][10000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    memset(f, -0x3f, sizeof f);
    int N, F;
    long long T;
    cin >> N >> F >> T;
    f[0][0][0] = 0;
    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;
        f[i][0][0] = 0;
        for (int j = 1; j <= i; j++)
            for (int k = 0; k < 10000; k++)
                if (k < i - j)
                    f[i][j][k] = f[i - 1][j][k];
                else
                    f[i][j][k] = max(f[i - 1][j][k], f[i - 1][j - 1][k - (i - j)] + a);
    }
    for (int k = 0; k < 10000; k++)
        if (f[N][F][k] >= T) {
            cout << k << '\n';
            return 0;
        }
    cout << "NO\n";
}