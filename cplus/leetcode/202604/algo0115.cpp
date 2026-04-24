#include <bits/stdc++.h>
using namespace std;

// 四、经典线性 DP - 4.1 最长公共子序列（LCS） - 4.1.2 进阶
class Solution {
public:
    int numDistinct(string s, string t) {
        // translate from python
        // 包含的子序列的递推方法需要避免无效的递归数据导致溢出
        int n = s.length(), m = t.length();
        vector dp(n+1, vector<unsigned>(m+1, 0));
        for (int i=0; i<=n; i++) dp[i][0] = 1;
        
        
        for (int i=0; i<n; i++) 
            // for (int j = 0; j < m; j++)  // 溢出
            for (int j = max(m - n + i, 0); j < min(i + 1, m); j++)
            if (s[i] == t[j])
                dp[i+1][j+1] =  dp[i][j] + dp[i][j+1];
            else dp[i+1][j+1] =  dp[i][j+1];
        
        return dp[n][m];
        
    }
};