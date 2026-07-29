/**
 *    author:  zjs
 *    created: 10.06.2026 18:41:48
**/
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

// vector<int> get_primes(int n) {
//     vector<int> primes;
//     vector<bool> flag(n + 1);
//     for (int i = 2; i <= n; i++) {
//         if (!flag[i]) {
//             primes.push_back(i);
//         }
//         for (int p : primes) {
//             if (p * i > n) break;
//             flag[p * i] = true;
//             if (i % p == 0) break;
//         }
//     }
//     return primes;
// }

vector<int> get_primes(int n) {
    vector<int> primes;
    vector<int> lpf(n + 1);
    for (int i = 2; i <= n; i++) {
        if (lpf[i] == 0) {
            primes.push_back(i);
            lpf[i] = i;
        }
        for (int p : primes) {
            if (p * i > n) break;
            lpf[p * i] = p;
            if (p == lpf[i]) break;
        }
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> primes = get_primes(n);
    while (q--) {
        int k;
        cin >> k;
        cout << primes[k - 1] << '\n';
    }
}