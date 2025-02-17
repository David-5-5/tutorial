#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长公共子序列（LCS）
class Solution {
public:
    int minDistance(string word1, string word2) {
        // 自行解答 
        int m = word1.size(), n = word2.size();

        // LCS 模板 记忆化搜索 时间复杂度 O(mn)/O(n^2)
        // compare word1, word2
        vector<vector<int>> memo(m, vector<int>(n, -1));
        function<int(int, int)> dfs = [&](int i, int j) ->int {
            if (i < 0 || j < 0) return i + j + 2; // 边界条件

            auto& res = memo[i][j];
            if (res != -1) return res;

            // word1, word2 外部变量，需要根据需求变更
            if (word1[i] == word2[j]) return res = dfs(i-1, j-1);
            else return res = min(dfs(i-1, j), min(dfs(i, j-1), dfs(i-1, j-1))) + 1;

        };
        return dfs(m-1, n-1);
    }

    int minDistance2(string word1, string word2) {
        // 递归改为递推迭代
        int m = word1.size(), n = word2.size();

        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (int i=1; i<=m; i++) dp[i][0] = i;  // 设置边界条件
        for (int i=1; i<=n; i++) dp[0][i] = i;  // 设置边界条件

        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (word1[i] == word2[j]) dp[i+1][j+1] = dp[i][j];
                else dp[i+1][j+1] = min(dp[i][j+1], min(dp[i+1][j], dp[i][j])) + 1;
            }
        }

        return dp[m][n];
    }


};