#include <bits/stdc++.h>
using namespace std;

int power_sum(int x, long long n, int mod) {
   int ans = 0;
   int prod = 1;
   while (n > 0) {
        if (n & 1) {
            ans = (ans + prod) % mod;
            prod = (long long) prod * x % mod;
        }
        prod = (long long) prod * (1 + x) % mod;
        x = (long long) x * x % mod;
        n >>= 1;
   }
   return ans;
}

int power(int x, long long n, int mod) {
    int ans = 1;
    while (n > 0) {
        if (n & 1)
            ans = (long long) ans * x % mod;
        x = (long long) x * x % mod;
        n >>= 1;
    }
    return ans;
}

int main() {
    long long a, b;
    int m;
    cin >> a >> b >> m;
    long long d = __gcd(a, b);
    int ans = (long long) power_sum(power(10, d, m), a / d, m) * power_sum(10, b, m) % m;
    cout << ans << '\n';
}