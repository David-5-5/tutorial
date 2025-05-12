#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.4 合法括号字符串
class Solution {
public:
    bool checkValidString(string s) {
        // 参考题解 - 动态规划
        // 当仅有 1 个字符时， 字符为 * 时，dp[i][i] = true
        // 当仅有 2 个字符时， 字符为 (), (*, *), ** 四种情况时，dp[i][i+1] = true
        // 当大于等于 3 个字符时，dp[i][j] = true，有下面两种情况：
        // 1. s[i] s[j] 字符为 (), (*, *), **, dp[i+1][j-1] = true, 或
        // 2. 存在 i<= k < j，使得 s[i][k] == true 且 s[k+1][j] = true
        int n = s.length();

        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i=0; i<n; ++i) dp[i][i] = s[i] == '*';

        for (int i=1; i<n; ++i) 
            dp[i-1][i] = s[i-1]!=')' && s[i] != '(';
        
        for (int i=n-3; i>=0; --i) for (int j=i+2; j<n; ++j){
            dp[i][j] = dp[i+1][j-1] && s[i]!=')' && s[j] != '(';
            for (int k=i; k<j&&!dp[i][j]; ++k) dp[i][j] = dp[i][k] && dp[k+1][j];
        }

        return dp[0][n-1];    
    }   
};