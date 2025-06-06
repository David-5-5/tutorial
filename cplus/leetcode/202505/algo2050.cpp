#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 13. 图 DP
class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        int ans = 0;
        vector<vector<int>> g(n);
        vector<int> degree(n), finish(n), queue;

        for (auto& r : relations) {
            int u = r[0]-1, v = r[1]-1;
            g[u].push_back(v);
            degree[v] ++;
        }

        for (int i=0; i<n; ++i) if (degree[i]==0)
            queue.push_back(i);
        
        while (queue.size()) {
            vector<int> nextq;
            for (auto& u: queue) {
                finish[u] += time[u];                       // u 的完成时间
                // 设置前序为 u 的最大开始时间
                for (auto v: g[u]) {
                    finish[v] = max(finish[v], finish[u]);  // 设置 v 的最大开始时间
                    degree[v] --;
                    if (degree[v] == 0) nextq.push_back(v);
                }
                ans = max(ans, finish[u]);
            }

            queue = move(nextq);
        }
        return ans;
    }
};;