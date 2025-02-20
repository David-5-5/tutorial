#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长公共子序列（LCS）
class Solution {
public:
    int numWays(vector<string>& words, string target) {
        // 自行解答， 奇怪，记忆化搜索没有优化也能通过，改为递推就超时!!!
        int MOD = 1e9 + 7;
        int m = words[0].size(), n = target.size();

        vector<vector<int>> memo(m, vector<int>(n, -1));
        auto dfs = [&](this auto&& dfs, int k, int j) -> int {
            if (j < 0) return 1;
            if (k < j) return 0;
            
            auto& res = memo[k][j];
            if (res != -1) return res;
            res = 0;
            for (int i=0; i<words.size(); i++) {
                if (words[i][k] == target[j])
                    res = ((long)res + dfs(k-1, j-1)) % MOD;                
            }
            res =  ((long)res + dfs(k-1, j)) % MOD;;      
            return res;
        };
        
        return dfs(m-1, n-1);    
    }

    int numWays2(vector<string>& words, string target) {
        // 参考题解，对 words 每列统计各个字符出现次数
        int MOD = 1e9 + 7;
        int m = words[0].size(), n = target.size();
        vector<vector<int>> cnt(m, vector<int>(26));
        for (auto& row :words) {
            for (int i=0; i<m; i++) {
                cnt[i][row[i]-'a'] += 1;
            }
        }

        vector<vector<int>> memo(m, vector<int>(n, -1));
        auto dfs = [&](this auto&& dfs, int k, int j) -> int {
            if (j < 0) return 1;
            if (k < j) return 0;
            
            auto& res = memo[k][j];
            if (res != -1) return res;
            res = (cnt[k][target[j]-'a'] * dfs(k-1, j-1)) % MOD;
            res = ((long)res + dfs(k-1, j)) % MOD; // 不选
            return res;
        };
        
        return dfs(m-1, n-1);   
    }   

    int numWays3(vector<string>& words, string target) {
        // 自行解答 递归 -> 迭代
        int MOD = 1e9 + 7;
        int m = words[0].size(), n = target.size();
        vector<vector<int>> cnt(m, vector<int>(26));
        for (auto& row :words) {
            for (int i=0; i<m; i++) {
                cnt[i][row[i]-'a'] += 1;
            }
        }

        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (int i=0; i<=m; i++) dp[i][0] = 1;
        
        for (int j=0; j<n; j++) {
            for (int k=0; k<m; k++) {
                // 选
                dp[k+1][j+1] = ((long) cnt[k][target[j]-'a']*dp[k][j]) % MOD;
                dp[k+1][j+1] = ((long)dp[k+1][j+1] + dp[k][j+1]) % MOD; // 不选
            }

        }
        
        return dp[m][n];   
    }   
}; 