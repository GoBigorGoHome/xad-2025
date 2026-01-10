#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> rad(2 * n - 1);

    int l = -1, r = -1;
    for (int i = 0; i < 2 * n - 1; i++) {
        int p = i / 2;
        int q = (i + 1) / 2;
        int k = r < q ? 0 : min(r - p, rad[2 * (l + r) - i]);
        while (0 <= q - k - 1 && p + k + 1 < n && s[q - k - 1] == s[p + k + 1]) {
            k++;
        }
        rad[i] = k;
        if (r < p + k) {
            r = p + k;
            l = q - k;
        }
        if (r == n - 1) {
            string t = s.substr(0, n - (r - l + 1));
            reverse(t.begin(), t.end());
            cout << s << t << '\n';
            break;
        }
    }
} 