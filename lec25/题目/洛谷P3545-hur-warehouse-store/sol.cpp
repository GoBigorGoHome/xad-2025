/**
 *    author:  zjs
 *    created: 29.06.2026 09:13:43
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    
    priority_queue<pair<int,int>> q;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        if (sum >= b[i]) {
            q.push({b[i], i});
            sum -= b[i];
        } else if (q.size() && q.top().first > b[i]) {
            sum += q.top().first;
            q.pop();
            sum -= b[i];
            q.push({b[i], i});   
        }
    }
    cout << q.size() << '\n';
    while (q.size()) {
        cout << q.top().second + 1 << ' ';
        q.pop();
    }
    cout << '\n';
}