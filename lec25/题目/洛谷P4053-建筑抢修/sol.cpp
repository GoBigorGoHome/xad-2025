/*
这是一个任务安排问题。以下我们使用“任务”，“开始期限”，“结束期限”。

给最优解加一些限制，让它更规则。
考虑一个最优解。我们可以调整做任务的顺序，优先做 deadline 早的任务。
设任务 x 和任务 y 是某个最优解中相邻的两个任务，先做 x 后做 y，且 D[x] > D[y]。这里，D[x] 表示任务 x 的 deadline.
我们交换任务 x 和任务 y 的顺序，先做 y 后做 x。
与交换顺序之前相比，任务 y 的完成时间提前，任务 x 的完成时间 = 原来任务 y 的完成时间。
二者都能及时完成。

我们把全部任务按 deadline 从小到大排序，得到一任务序列 S。我们要求 S 的一个最长的可完成的子序列。
我们可以证明：按下述方法可以得到一个最长的可完成的子序列。
依次枚举 S 里的每个任务，若当前任务可完成，就做当前任务，否则若已做的任务中用时最长的那个任务的用时比当前任务的用时更长，就用当前任务替换那个任务。
*/
/**
 *    author:  zjs
 *    created: 28.06.2026 16:00:34
**/
#include <bits/stdc++.h>
#include <cassert> // <bits/stdc++.h> does not include cassert since GCC 16.
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

#include <bits/stdc++.h>
using namespace std;

struct Task {
    int time, deadline;
};

bool cmp(Task a, Task b) {
    return a.deadline < b.deadline;
}

int main() {
    int N;
    cin >> N;
    vector<Task> a(N);
    for (int i = 0; i < N; i++)
        cin >> a[i].time >> a[i].deadline;

    sort(a.begin(), a.end(), cmp);
    priority_queue<int> q;

    long long sum = 0;
    for (auto [t, d] : a) {
        if (sum + t <= d) {
            q.push(t);
            sum += t;
        } else if (q.top() > t) {
            sum -= q.top();
            q.pop();
            q.push(t);
            sum += t;
        }
    }
    cout << q.size() << '\n';
}
