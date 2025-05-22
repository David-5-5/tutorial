#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 13. 图 DP
class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        // 参考题解，暴力，每增加一条边，执行一次bfs
        vector<vector<int>> g(n);
        for (int i=0; i<n-1; ++i) g[i].push_back(i+1);

        vector<int> vis(n, -1);
        auto bfs = [&](int i) -> int{
            deque<int> q{0};
            for (int step=1; ;++step) {
                deque<int> nxt;
                for (auto& x: q) {
                    vis[x] = i;
                    for (auto& y: g[x]) {
                        if (y == n-1) return step;
                        if (vis[y] < i) nxt.push_back(y);
                    }
                }
                q = move(nxt);
            }
            return -1;
        };

        int m = queries.size();
        vector<int> ans(m);
        for (int i=0; i<m; ++i) {
            g[queries[i][0]].push_back(queries[i][1]);
            ans[i] = bfs(i);
        }
        return ans;
    }
};;