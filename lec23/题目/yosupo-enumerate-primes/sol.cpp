/**
 *    author:  zjs
 *    created: 10.06.2026 18:57:27
**/
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

vector<int> get_primes(int n) { // 1710 ms
    vector<int> primes;
    vector<bool> flag(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!flag[i]) {
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p * i > n) break;
            flag[p * i] = true;
            if (i % p == 0) break;
        }
    }
    return primes;
}

vector<bool> eratos(int n) { // 4691 ms
    vector<bool> flag(n + 1);
    for (int i = 2; i <= n; i++)
        if (!flag[i]) {
            for (int j = i * 2; j <= n; j += i)
                flag[j] = true;
        }
    return flag;
}

// vector<int> get_primes(int n) { // MLE.
//     vector<int> primes;
//     vector<int> lpf(n + 1);
//     for (int i = 2; i <= n; i++) {
//         if (lpf[i] == 0) {
//             primes.push_back(i);
//             lpf[i] = i;
//         }
//         for (int p : primes) {
//             if (p * i > n) break;
//             lpf[p * i] = p;
//             if (p == lpf[i]) break;
//         }
//     }
//     return primes;
// }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, a, b;
    cin >> n >> a >> b;
    auto flag = eratos(n);
    int cnt = 0;
    vector<int> ans;
    for (int i = 2; i <= n; i++) {
        if (!flag[i]) {
            if (cnt % a == b)
                ans.push_back(i);
            ++cnt;
        }
    }
    cout << cnt << ' ' << ans.size() << '\n';
    for (int p : ans)
        cout << p << ' ';
    cout << '\n';
    // vector<int> primes = get_primes(n);

    // int k = (int) primes.size();
    // int x = (k - b + a - 1) / a;
    // cout << k << ' ' << x << '\n';
    // for (int i = b; i < k; i += a)
    //     cout << primes[i] << ' ';
    // cout << '\n';
}