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

    vector<int> shortestDistanceAfterQueries2(int n, vector<vector<int>>& queries) {
        // 参考题解，DP, 每个节点记录prev[i]
        // dp[i]  = min(dp[j]+1), where j ∈ prev[i]
        vector<int> dp(n);
        iota(dp.begin(), dp.end(), 0);
        vector<vector<int>> prev(n);
        // for (int i=0; i<n-1; i++) prev[i+1].push_back(i);    
        
        cout << dp[n-1] << endl;
        int m = queries.size();
        vector<int> ans(m);

        for (int i=0; i<m; ++i) {
            auto& q = queries[i];

            prev[q[1]].push_back(q[0]);
            for (int r=q[1]; r<n; ++r) {
                dp[r] = min(dp[r], dp[r - 1] + 1);  // 和上面注释行 2 选 1
                for (auto& l: prev[r])
                    dp[r] = min(dp[r], dp[l]+1);
            }
            ans[i] = dp[n-1];
        }

        return ans;
    }
};
