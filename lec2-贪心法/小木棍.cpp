#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> need = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    vector<int> best(100000);
    for (int x = 1; x <= 10000; x++) {
        int y = 0;
        for (char c : to_string(x))
            y += need[c - '0'];
        // 拼 x 需要 y 根木棍 
        if (best[y] == 0)
            best[y] = x; // 用 y 根木棍能拼成的最小正整数是 x
    }
    for (int i = 1; i <= 20; i++)
        cout << best[i] << ' ';
}