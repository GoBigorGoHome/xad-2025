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
    int x = INT_MAX;
    while (x > 1) {
        x = sqrt(x);
        cout << x << '\n';
    }
}