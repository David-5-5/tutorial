#include <bits/stdc++.h>
using namespace std;

// 九、状态压缩 DP（状压 DP） 9.2 排列型状压 DP ② 相邻相关
class Solution {
public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        int ans = 1;
        unordered_map<long long, int> memo;

        function<void(int, int, int)> dfs = [&](int u, int v, int state) -> void {
            int cnt = __builtin_popcount(state);
            if (cnt > ans) ans = cnt;

            long long key = (long long)u * 1000000 * 1000000 + v * 1000000 + state;
            if (memo.count(key)) return;
            memo[key] = 1;

            for (int x : g[u]) {
                if ((state >> x) & 1) continue;
                for (int y : g[v]) {
                    if (x == y) continue;
                    if ((state >> y) & 1) continue;
                    if (label[x] == label[y]) {
                        dfs(min(x,y), max(x,y), state | (1 << x) | (1 << y));
                    }
                }
            }
        };

        for (int i = 0; i < n; ++i) {
            for (int x : g[i]) {
                for (int y : g[i]) {
                    if (x == y || label[x] != label[y]) continue;
                    dfs(min(x,y), max(x,y), (1 << i) | (1 << x) | (1 << y));
                }
            }
        }

        for (int u = 0; u < n; ++u) {
            for (int v : g[u]) {
                if (u < v && label[u] == label[v]) {
                    dfs(u, v, (1 << u) | (1 << v));
                }
            }
        }

        return ans;
    }
};