#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

int lis(vector<int> a) {
	vector<int> b;
	for (int x : a) {
		auto it = lower_bound(b.begin(), b.end(), x);
		if (it == b.end())
			b.push_back(x);
		else *it = x;
	}
	return (int) b.size();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--;
		vector<int> b(a.begin() + l, a.begin() + r);
		cout << lis(b) << '\n';
	}
}
