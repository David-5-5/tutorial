#include <bits/stdc++.h>
using namespace std;


// 动态规划 - 网格图 DP - 2.1 基础
class Solution {
public:
    long long minCost(int m, int n, vector<vector<int>>& waitCost) {
        // 自行解答 
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


};