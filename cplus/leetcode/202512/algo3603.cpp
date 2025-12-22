#include <bits/stdc++.h>
using namespace std;


// 动态规划 - 网格图 DP - 2.1 基础
class Solution {
public:
    long long minCost(int m, int n, vector<vector<int>>& waitCost) {
        // 自行解答 BFS
        constexpr long long MAX_SAFE_INTEGER = (1LL << 53) - 1;
        vector cost(m, vector<long long>(n, MAX_SAFE_INTEGER));
        int status = 1; cost[0][0] = 1;
        vector<tuple<int, int, long long>> q; // i, j, c
        q.emplace_back(0, 0, 1);
        while (!q.empty()) {
            if (status) {
                vector<tuple<int, int, long long>> nxt;
                for (auto [i, j, c] : q) {
                    if (c > waitCost[i][j] + cost[i][j]) continue;  // 避免多余的元素
                    if (i + 1 < m && c + (i+2)*(j+1) < cost[i+1][j]) {
                        cost[i+1][j] = c + (i+2)*(j+1); nxt.emplace_back(i+1, j, cost[i+1][j]);
                    }
                    if (j + 1 < n && c + (i+1)*(j+2) < cost[i][j+1]) {
                        cost[i][j+1] = c + (i+1)*(j+2); nxt.emplace_back(i, j+1, cost[i][j+1]);
                    }
                } 

                q = move(nxt);
            } else {
                for (auto& [i, j, c] : q) {
                    c += waitCost[i][j];
                }
            }
            status ^= 1;
        }

        return cost[m-1][n-1];    
    }

    long long minCost2(int m, int n, vector<vector<int>>& waitCost) {
        // 自行解答 用 unordered_map 代替 vector
        int status = 1;
        unordered_map<long long, long long> q; // i*n+j, c
        q[0] = 1;
        while (!q.empty()) {
            if (q.count(m*n-1)) return q[m*n-1];
            if (status) {
                unordered_map<long long, long long> nxt;
                for (auto [pos, c] : q) {
                    int i = pos / n, j = pos % n;
                    if (i + 1 < m) {
                        int newPos = (i+1) * n + j;
                        if (!nxt.count(newPos)) nxt[newPos] = c + (i+2)*(j+1);
                        else nxt[newPos] = min(nxt[newPos], c + (i+2)*(j+1));
                    }
                    if (j + 1 < n) {
                        int newPos = i * n + j + 1;
                        if (!nxt.count(newPos)) nxt[newPos] = c + (i+1)*(j+2);
                        else nxt[newPos] = min(nxt[newPos], c + (i+1)*(j+2));
                    }
                } 

                q = move(nxt);
            } else {
                for (auto& [pos, c] : q) {
                    int i = pos / n, j = pos % n;
                    c += waitCost[i][j];
                }
            }
            status ^= 1;
        }

        return -1;
    }

    long long minCost3(int m, int n, vector<vector<int>>& waitCost) {
        // 参考题解 DP
        // dp[i+1][j+1] = min(dp[i+1][j], dp[i][j+1]) + minCost[i][j] + 1LL * (i+1)(j+1)
        // waitCost[0][0] waitCost[m-1][n-1] 需要抵消掉
        vector dp(m+1, vector<long long>(n+1, LLONG_MAX));
        dp[0][1] = dp[1][0] = 0;  // 也可以初始化为 - waitCost[0][0]
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            dp[i+1][j+1] = min(dp[i+1][j], dp[i][j+1]) + waitCost[i][j] + 1LL * (i+1) * (j+1);
        }
        return dp[m][n] - waitCost[0][0] - waitCost[m-1][n-1];
    }    
};