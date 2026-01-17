#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, len;
    string s;
    cin >> n >> len >> s;
    s = s + s + s;
    vector<int> rad(2 * n);
    int l = -1, r = -1;
    for (int i = 0; i < 2 * n; i++) {
        int k = r < i ? 0 : min(r - i, rad[l + r - i]);
        while (0 <= i - k - 1 && i + k + 1 < 3 * n && s[i - k - 1] == s[i + k + 1])
            k++;
        rad[i] = k;
        if (i + k > r) {
            r = i + k;
            l = i - k;
        }
    }
    int ans = 0;
    for (int i = n; i < 2 * n; i++)
        if (rad[i] >= len / 2)
            ans++;
    cout << ans << '\n';
}