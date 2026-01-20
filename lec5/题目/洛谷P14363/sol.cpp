#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

template <int sigma_size, char alpha>
struct Trie {
    vector<array<int, sigma_size>> go;
    int new_node() {
        go.push_back({});
        return (int) go.size() - 1;
    }
    Trie() {
        new_node();
    }
    int add(string s) {
        int p = 0;
        for (char c : s) {
            int i = c - alpha;
            if (go[p][i] == 0) {
                go[p][i] = new_node();
            }
            p = go[p][i];
        }
        return p;
    }
    vector<pair<int,int>> get_suffix_link() {
        vector<pair<int,int>> q;
        for (int i = 0; i < sigma_size; i++)
            if (go[0][i])
                q.push_back({go[0][i], 0});
        
        for (int j = 0; j < (int) q.size(); j++) {
            int u = q[j].first, v = q[j].second;
            for (int i = 0; i < sigma_size; i++)
                if (go[u][i])
                    q.push_back({go[u][i], go[v][i]});
                else
                    go[u][i] = go[v][i];
        }
        return q;
    }
};

string work(string a, string b) {
    int n = (int) a.size();
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            for (int j = n - 1; j >= 0; j--)
                if (a[j] != b[j]) {
                    string k = a.substr(i, j - i + 1) + b.substr(i, j - i + 1);
                    return  a.substr(0, i) + '{' + k + '{' + b.substr(j + 1); // '{' 是 'z' 的下一个字符
                }
    return "";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    
    Trie<27, 'a'> trie;
    vector<int> id;
    for (int i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        string s = work(s1, s2);
        if (!s.empty())
            id.push_back(trie.add(s));
    }
    vector<int> weight(trie.go.size()); // 节点的权值
    for (int i : id)
        weight[i]++;
    // 正向传播
    for (auto [u, v] : trie.get_suffix_link())
        weight[u] += weight[v];
    // 回答询问
    for (int i = 0; i < q; i++) {
        string t1, t2;
        cin >> t1 >> t2;
        int ans = 0;
        if (t1.size() == t2.size()) {
            string t = work(t1, t2);
            int p = 0;
            for (char c : t) {
                p = trie.go[p][c - 'a'];
                ans += weight[p];
            }
        }
        cout << ans << '\n';
    }
}