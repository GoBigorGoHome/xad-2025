#include <bits/stdc++.h>
using namespace std;

int ask(int l, int r) {
    cout << "? " << l << ' ' << r << '\n';
    int res;
    cin >> res;
    return res;
}


int main() {
    int k = 1; // 回文半径
    int ans = 1;
    int n;
    cin >> n;
    // 先找奇回文子串
    for (int i = 1; i <= n; i++) {
        while (1 <= i - k && i + k <= n && ask(i - k, i + k)) {
            ans = 2 * k + 1;
            k++;
        }
    }
    // 再找偶回文子串
    for (int i = 1; i <= n; i++) {
        while (1 <= i - k + 1 && i + k <= n && ask(i - k + 1, i + k)) {
            ans = 2 * k;
            k++;
        }
    }
    cout << "! " << ans << '\n';
}