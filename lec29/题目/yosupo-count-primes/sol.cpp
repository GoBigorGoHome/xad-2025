/**
 *    author:  zjs
 *    created: 10.06.2026 20:54:54
**/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

template <integral T>
struct fenwick {
    vector<T> a;
    fenwick(int n) : a(n) {}

    fenwick(const vector<T>& a_) : a(a_) {
        for (size_t i = 0; i < a.size(); i++)
            if ((i | (i + 1))  < a.size())
                a[i | (i + 1)] += a[i];
    }

    fenwick(int n, T v) : fenwick(vector<T>(n, v)) {}

    // 返回前n项之和，即 a[0] + ... + a[n - 1]
    T sum(int n) {
        n = min(n, (int) a.size());
        T ans = 0;
        while (n > 0) {
            ans += a[n - 1];
            n &= n - 1;
        }
        return ans;
    }
    // 返回 a[l] + ... + a[r - 1]
    T sum(int l, int r) {
        return sum(r) - sum(l);
    }

    void push_back(T v) {
        size_t p = a.size();
        for (size_t len = 1; len & p; len <<= 1)
            v += a[p ^ len];
        a.push_back(v);
    }

    void add(int p, T v) {
        while (p < (int) a.size()) {
            a[p] += v;
            p |= p + 1;
        }
    }
    // Returns the length of the longest prefix with sum <= v
    int max_prefix(T v) {
        T sum = 0;
        size_t p = 0;
        for (size_t len = bit_floor(a.size()); len > 0; len >>= 1) {
            if (p + len <= a.size() && !(v < sum + a[p + len - 1])) {
                sum += a[p + len - 1];
                p += len;
            }
        }
        return (int) p;
    }
};

struct sieve_result {
    vector<int> primes;
    vector<int> lpf;
};

sieve_result linear_sieve(int n) {
    if (n <= 0) return {};
    vector<int> primes;
    vector<int> lpf(n + 1);
    for (int i = 2; i <= n; i++) {
        if (lpf[i] == 0) {
            primes.push_back(i);
            lpf[i] = i;
        }
        for (int p : primes) {
            if (p * i > n || p > lpf[i]) break;
            lpf[p * i] = p;
        }
    }
    lpf[1] = INT_MAX; // 置 lpf[1] 为无穷大
    return {primes, lpf};
}

int main() { // 1438 ms
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    int T = (int) cbrt(n);
    int M = max<int>(T, n / (T + 1));
    // 找出不超过 n**{2/3} 的素数
    auto [primes, lpf] = linear_sieve(M);
    // 计算 A
    int A = upper_bound(primes.begin(), primes.end(), T) - primes.begin();
    // 计算 P2(n, A)
    long long p2 = 0;
    for (int i = A, j = (int) primes.size(); i < (int) primes.size() && (long long) primes[i] * primes[i] <= n; i++) {
        long long q = n / primes[i];
        while (primes[j - 1] > q)
            j--;
        p2 += j - i;
    }

    // 计算 \phi(n, A)
    long long phi = 0;
    // 计算平凡叶子的贡献
    vector<int> mu(T + 1);
    mu[1] = 1;
    for (int i = 1; i <= T; i++) {
        if (mu[i] == 0) continue;
        phi += mu[i] * (n / i);
        for (int p : primes) {
            if (p * i > T || p == lpf[i]) // 若 p == lpf[i]，那么 p * i 有平方因子，不管它。
                break;
            mu[p * i] = -mu[i];
        }
    }
    vector<vector<int>> g(M + 1);
    for (int i = 2; i <= M; i++)
        g[lpf[i]].push_back(i);
    // 计算特殊叶子的贡献
    fenwick<int> f(M, 1);
    for (int p : views::take(primes, A)) {
        for (int i = T / p + 1; i <= T; i++) {
            if (mu[i] && lpf[i] > p) {
                phi -= mu[i] * f.sum(n/(i * p));
            }
        }
        // 筛掉 lpf == p 的数
        for (int v : g[p])
            f.add(v - 1, -1);
    }
    cout << phi + A - 1 - p2 << '\n';
}