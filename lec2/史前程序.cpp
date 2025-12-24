#include <bits/stdc++.h>
using namespace std;


struct S {
  int sum;
  int min_prefix;
  int id;
};

bool cmp(S x, S y) {
  if (x.sum >= 0 && y.sum < 0)
    return true;
  if (x.sum < 0 && y.sum >= 0)
    return false;
  if (x.sum >= 0 && y.sum >= 0)
    return x.min_prefix > y.min_prefix;
  return x.min_prefix - x.sum < y.min_prefix - y.sum;
}



void solve() {
  int n; cin >> n;
  vector<S> a(n);
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    int sum = 0, min_prefix = 0;
    for (char c : s) {
      sum += c == '(' ? 1 : -1;
      min_prefix = min(min_prefix, sum);
    }
    a[i] = {sum, min_prefix, i};
  }
  sort(a.begin(), a.end(), cmp);
  int sum = 0;
  bool ok = true;
  for (S t : a) {
    if (sum + t.min_prefix < 0) {
      ok = false;
      break;
    }
    sum += t.sum;
  }
  ok = ok && sum == 0;
  if (!ok) cout << "impossible\n";
  else for (S t : a)
      cout << t.id + 1 << '\n';
}

int main() {
    solve();
}