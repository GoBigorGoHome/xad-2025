/**
 *    author:  zjs
 *    created: 04.06.2026 00:03:45
**/
#include <bits/stdc++.h>
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

    fenwick(int n, T v) : fenwick(std::vector<T>(n, v)) {}

    void add(int p, int v) {
        while (p < (int) this->size()) {
            (*this)[p] += v;
            p |= p + 1;
        }
    }

    void push_back(T v) {
        size_t n = this->size();
        std::vector<T>::push_back(v);
        for (size_t len = 1; len & n; len <<= 1)
            (*this)[n] += (*this)[n ^ len];
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
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];
    
    vector<int> ans(n);
    fenwick<int> f(n, 1);
    for (int i = n - 1; i >= 0; i--) {
        int pos = f.max_prefix(p[i] - 1);
        ans[pos] = i + 1;
        f.add(pos, -1);
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
    cout << '\n';
}