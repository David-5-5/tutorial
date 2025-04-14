#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长回文子序列
class Solution {
public:
    int longestPalindromicSubsequence(string s, int k) {
        // 自行解答
        int n = s.length();

        vector<vector<vector<int>>> memo(n, vector<vector<int>>(n, vector<int>(k+1, -1)));
        auto dfs = [&](this auto&& dfs, int i, int j, int l) -> int {
            if (i == j) return 1;
            if (i > j) return 0;

            auto& res = memo[i][j][l];
           
            if (res != -1) return res;
            
            res = max(dfs(i+1, j, l), dfs(i, j-1, l));
            
            if (s[i] == s[j]) res = max(res, 2 + dfs(i+1, j-1, l));
            else {
                int x = min((s[i]-s[j]+26)%26, (s[j]-s[i]+26)%26);
                if (x <= l) res = max(res, 2 + dfs(i+1, j-1, l-x));
            }
            return res;
        };

        return dfs(0, n-1, k);
    }
};