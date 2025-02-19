#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长公共子序列（LCS）
class Solution {
public:
    int numWays(vector<string>& words, string target) {
        // 自行解答
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
                if (words[i][k] == target[j])   // 选
                    res = ((long)res + dfs(k-1, j-1)) % MOD;
            }
            res =  ((long)res + dfs(k-1, j)) % MOD; // 不选
            return res;
        };
        
        return dfs(m-1, n-1);   
    }   
}; 