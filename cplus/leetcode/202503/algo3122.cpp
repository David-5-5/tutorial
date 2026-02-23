#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        // 自行解答
        int n = grid.size(), m = grid[0].size();

        // 统计每列 0~9 的数量
        vector<vector<int>> cnt(m, vector<int>(10));
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                cnt[j][grid[i][j]] += 1;
            }
        }
        
        vector<vector<int>> memo(m, vector<int>(11, -1));
        auto dfs = [&](this auto&& dfs, int i, int v) -> int {
            if (i == m) return 0;
            
            auto& res = memo[i][v];
            if (res != -1) return res;
            res = n + dfs(i+1, 10);         // 全部都改 10 可以理解为不与前后两列值相同的任意值
            for (int nv=0; nv<10; nv++) {   // 贪心优选频率最大的两列是错误的
                if (nv == v) continue;  // 与前一列相同，跳过
                // i 列都改为 nv，需要修改的数量为 n - cnt[i][nv]
                res = min(res, n - cnt[i][nv] + dfs(i+1, nv));
            }
            return res;
        };

        return dfs(0, 10);      // 10 表示 0-9之外的任意其他数，不会与其他列相同
        
    }

    int minimumOperations2(vector<vector<int>>& grid) {
        // 自行解答 - 记忆化 -> 递推
        int n = grid.size(), m = grid[0].size();

        // 统计每列 0~9 的数量
        vector<vector<int>> cnt(m, vector<int>(10));
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                cnt[j][grid[i][j]] += 1;
            }
        }
        
        vector<vector<int>> dp(m+1, vector<int>(11, INT_MAX/2));
        for (int i=0; i<11; i++) dp[0][i] = 0;
        for (int i=0; i<m; i++){
            for (int v=0; v<11; v++) {
                dp[i+1][10] = min(dp[i+1][10], dp[i][v] + n); 
                for (int nv=0; nv<10; nv++) {
                    if (nv == v) continue;  // 与前一列相同，跳过
                    // i 列都改为 nv，需要修改的数量为 n - cnt[i][nv]
                    dp[i+1][nv] = min(dp[i+1][nv], n - cnt[i][nv] + dp[i][v]);
                }
            }
        }

        return *min_element(dp[m].begin(), dp[m].end());   
        
    }

    
};