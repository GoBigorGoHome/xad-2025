#include <bits/stdc++.h>
using namespace std;

const int maxn = 2.5e4 + 5;
struct S { int l, r; };
S a[maxn];
bool cmp(S a, S b) { return a.l < b.l; }

int solve(int n, int x, int y) {
  sort(a, a + n, cmp);
  int r = 0, ans = 0;
  // x <= y
  for (int i = 0; i < n; ) {
    while (i < n && a[i].l <= x) {
      r = max(r, a[i].r);
      i++;
    }
    if (r < x) return -1; // 没有进展
    ans++; //选一个区间
    if (r >= y) return ans; // 够了
    x = r + 1;
  }
  return -1;
}

int main() {
  int N, T;
  cin >> N >> T;
  for (int i = 0; i < N; i++)
    cin >> a[i].l >> a[i].r;
  
  cout << solve(N, 1, T) << '\n';
}
