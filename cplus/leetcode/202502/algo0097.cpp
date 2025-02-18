#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长公共子序列（LCS）
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        // 自行解答
        if (s1.size() + s2.size() != s3.size()) return false;

        int m = s1.size(), n = s2.size();
        vector<vector<int>> memo(m, vector<int>(n, -1));

        function<bool(int, int)> dfs = [&](int i, int j) ->bool {
        // auto dfs = [&](this auto&& dfs, int i, int j) -> bool {
            // cout << i << ", " << j << endl;
            if (i == m && j == n) return true;
            if (i == m) return s2.substr(j) == s3.substr(m+j);
            if (j == n) return s1.substr(i) == s3.substr(n+i);
            
            auto& res = memo[i][j];
            if (res != -1) return res;
            
            for (int k=i; k<m; k++)
                if (s1[k] == s3[k+j])  { 
                    res = dfs(k+1, j);
                    if (res) return true;
                } else break;
            

            for (int k=j; k<n; k++)
                if (s2[k] == s3[k+i])  { 
                    res = dfs(i, k+1);
                    if (res) return true;
                } else break;
            
            return false;
        };
        return dfs(0, 0);     
    }
};