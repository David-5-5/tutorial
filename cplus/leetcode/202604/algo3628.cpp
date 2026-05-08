#include <bits/stdc++.h>
using namespace std;

// 四、经典线性 DP - 4.1 最长公共子序列（LCS） - 4.1.2 进阶
class Solution {
public:
    long long numOfSubsequences(string s) {
        // 115
        auto numDistinct = [] (string s, string t) -> long long{
            // translate from python
            int n = s.length(), m = t.length();
            vector dp(n+1, vector<long long>(m+1, 0));
            for (int i=0; i<=n; i++) dp[i][0] = 1;
            
            for (int i=0; i<n; i++) 
                // for (int j = 0; j < m; j++)  // 溢出
                for (int j = max(m - n + i, 0); j < min(i + 1, m); j++)
                if (s[i] == t[j])
                    dp[i+1][j+1] =  dp[i][j] + dp[i][j+1];
                else dp[i+1][j+1] =  dp[i][j+1];
            
            return dp[n][m];
        };

        auto calcInsertC = [&] (string s) -> long long {
            int cnt_t = ranges::count(s, 'T'); // s[i+1] 到 s[n-1] 的 'T' 的个数
            int cnt_l = 0; // s[0] 到 s[i] 的 'L' 的个数
            long long res = 0;
            for (char c : s) {
                if (c == 'T') {
                    cnt_t--;
                }
                if (c == 'L') {
                    cnt_l++;
                }
                res = max(res, 1LL * cnt_l * cnt_t);
            }
            return res;
        };


        auto extra = max(numDistinct(s, "CT"), numDistinct(s, "LC"));
        extra = max(extra, calcInsertC(s));
        return numDistinct(s, "LCT") + extra;
    }
};