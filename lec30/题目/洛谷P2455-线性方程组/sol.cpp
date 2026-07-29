/**
 *    author:  zjs
 *    created: 19.07.2026 22:53:32
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

bool is_zero(double x) {
    return abs(x) < 1e-6;
}

// a 是增广矩阵，w 是变元的个数
void gauss_elimination(vector<vector<double>> &a, int w) {
    debug(w);
    int h = a.size();
    // 第一步：化为行梯矩阵：把每个主元下方的元素变成0
    int r = 0; // 已经做了 r 次消元
    for (int c = 0; c < w; c++) { // 消掉第 c 个变元
        int id = -1;
        for (int i = r; i < h; i++)
            if (!is_zero(a[i][c])) {
                id = i;
                break;
            }
        if (id == -1) continue; // 第 c 个变元已经没了，不需要消
        debug(id, r);
        if (id != r) {
            swap(a[id], a[r]);
        }
        double inv = 1 / a[r][c];
        for (int i = r + 1; i < h; i++) {
            // 把 a[i][c] 变成 0
            if (is_zero(a[i][c])) continue;
            double coeff = -a[i][c] * inv;
            // 第 i 行加上 coeff * 第 r 行
            for (int j = c; j <= w; j++)
                a[i][j] += coeff * a[r][j];
        }
        r++;
    }
    debug(a);
    // 第二步：化为简化行梯矩阵：把行梯矩阵的每个主元都变成 1，把每个主元上方的元素都变成0
    while (r--) {
        for (int c = 0; c < w; c++) {
            if (!is_zero(a[r][c])) {
                // 把第 r 行乘以 1/a[r][c]
                double inv = 1 / a[r][c];
                a[r][c] = 1;
                for (int j = c + 1; j <= w; j++)
                    a[r][j] *= inv;
                debug(r, a[r]);
                for (int i = 0; i < r; i++) {
                    if (is_zero(a[i][c])) continue;
                    // 把第 i 行加上 -a[i][c] 乘以第 r 行
                    double coeff = -a[i][c];
                    for (int j = c; j <= w; j++)
                        a[i][j] += coeff * a[r][j];
                }
                debug(a);
                break;
            }
        }
    }
    debug(a);
}

int solve_linear_system(vector<vector<double>> a, vector<double> b, vector<double>& x) {
    int h = a.size(); // 有 h 个方程
    int w = a[0].size(); // 有 w 个未知数
    for (int i = 0; i < h; i++)
        a[i].push_back(b[i]);
    gauss_elimination(a, w);
    int r = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            if (!is_zero(a[i][j])) {
                r++;
                x[j] = a[i][w];
                break;
            }
        }
    // 先判是否无解
    for (int i = r; i < h; i++) {
        if (!is_zero(a[i][w])) {
            return -1;
        }
    }
    // 再判是否有无穷多个解
    if (r < w) {
       return 0;
    }
    return 1;
}

int main() {
    int n;
    cin >> n;
    vector<vector<double>> a(n, vector<double>(n));
    vector<double> b(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
        cin >> b[i];
    }
    vector<double> x(n);
    int res = solve_linear_system(a, b, x);
    if (res < 1)
        cout << res << '\n';
    else {
        for (int i = 0; i < n; i++)
            cout << 'x' << i +1 << '=' << x[i] << '\n';
    }
}
