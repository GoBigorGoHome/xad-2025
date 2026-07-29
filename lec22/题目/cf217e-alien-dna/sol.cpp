/**
 *    author:  zjs
 *    created: 01.06.2026 09:23:55
**/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

template<typename T>
struct fenwick : std::vector<T> {
    using std::vector<T>::vector;

    fenwick(const std::vector<T>& a) : std::vector<T>(a) {
        for (size_t i = 0; i < this->size(); i++) {
            if ((i | (i + 1))  < this->size())
                (*this)[i | (i + 1)] += (*this)[i];
        }
    }

    fenwick(int n, T v) : fenwick(std::vector<T>(n, v)) {
    }

    void add(int p, int v) {
        while (p < (int) this->size()) {
            (*this)[p] += v;
            p |= p + 1;
        }
    }

    T sum(int n) {
        n = std::min(n, (int) this->size());
        T ans = 0;
        while (n > 0) {
            ans += (*this)[n - 1];
            n &= n - 1;
        }
        return ans;
    }

    T sum(int l, int r) {
        return sum(r) - sum(l);
    }

    int max_prefix(T v) {
        T sum = 0;
        size_t at = 0;
        for (size_t len = std::bit_floor(this->size()); len > 0; len >>= 1) {
            if (at + len <= this->size() && !(v < sum + (*this)[at + len - 1])) {
                sum += (*this)[at + len - 1];
                at += len;
            }
        }
        return (int) at;
    }
};


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    int k, n;
    cin >> s >> k >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        l[i]--;
    }

    fenwick<int> f(k, 1);

    vector<int> ref(k, -1);
    int len = k;

    for (int i = n - 1; i >= 0; i--) {
        if (r[i] >= len)
            continue;
        for (int j = l[i] + 1; j < r[i] && r[i] < len; j += 2, len--) {
            int p = f.max_prefix(r[i]);
            int q = f.max_prefix(j);
            ref[p] = q;
            f.add(p, -1);
        }
        for (int j = l[i]; j < r[i] && r[i] < len; j += 2, len--) {
            int p = f.max_prefix(r[i]);
            int q = f.max_prefix(j);
            ref[p] = q;
            f.add(p, -1);
        }
        /*
        注1
        另一种写法：把上面的两个 for 循环合成一个。
        来自：https://www.cnblogs.com/Saka-Noa/p/17808426.html
        for (int t = 0, j = l[i] + 1; t < r[i] - l[i] && r[i] < len; t++, j += 2, len--) {
            if (j >= r[i])
                j = l[i];
            int p = f.max_prefix(r[i]);
            int q = f.max_prefix(j);
            ref[p] = q;
            f.add(p, -1);
        }

        注2
        此解法的时间是 O(k \log k)。这题 k 很大（3e6），如果实现常数较大，可能超时。
       */

    }

    string ans(k, ' ');
    int ptr = 0;
    for (int i = 0; i < k; i++) {
        if (ref[i] == -1)
            ans[i] = s[ptr++];
        else
            ans[i] = ans[ref[i]];
    }
    cout << ans << '\n';
}
