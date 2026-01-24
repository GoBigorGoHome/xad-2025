#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif


template <typename F>
int binary_search(F check, int ok, int ng) {
    while (abs(ok - ng) > 1) {
        int x = (ok + ng) / 2;
        debug(x, check(x));
        if (check(x))
            ok = x;
        else
            ng = x;
    }
    return ok;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s;
    cin >> n >> s;
    Hash h(s);
    string rs(s.rbegin(), s.rend());
    Hash rh(rs);
    auto is_palindrome = [&] (int l, int r) {
        return h.get(l, r) == rh.get(n - 1 - r, n - 1 - l);
    };
    debug(is_palindrome(0, 1));
    auto check = [&](int k) {
        for (int i = 0; i <= n - 4 * k; i++)
            if (is_palindrome(i, i + 4 * k - 1) && is_palindrome(i, i + 2 * k - 1))
                return true;
        return false;
    };
    debug(check(3));
    cout << 4 * binary_search(check, 0, n / 4 + 1) << '\n';
}

