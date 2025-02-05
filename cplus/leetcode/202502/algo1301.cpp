#include <bits/stdc++.h>
using namespace std;


// 动态规划 - 网格图 DP - 进阶
class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        // 自行解答 用时太长 C++ 不熟悉
        int mod = 1e9 + 7;
        int m = board.size(), n = board[0].size();
        vector<vector<int>> dp(m, vector<int>(n, INT_MIN));
        vector<vector<int>> cnt(m, vector<int>(n, 0));

        dp[0][0] = 0, cnt[0][0] = 1;
        for (int i=1; i<m; i++) {
            if (board[i][0] == 'X') break;
            dp[i][0] = dp[i-1][0] + (board[i][0] - '0'), cnt[i][0] = cnt[i-1][0];
        }
        for (int i=1; i<n; i++) {
            if (board[0][i] == 'X') break;
            dp[0][i] = dp[0][i-1] + (board[0][i] - '0'), cnt[0][i] = cnt[0][i-1];
        }
        for (int i=1; i<m; i++) {
            for (int j=1; j<n; j++) {
                auto ch = board[i][j];
                if (ch == 'X') continue;
                dp[i][j] = max(dp[i-1][j],max(dp[i][j-1],dp[i-1][j-1])) + (ch=='S'?0:ch-'0');
                
                if (dp[i][j] == dp[i-1][j] + (ch=='S'?0:ch-'0'))
                    cnt[i][j] = (cnt[i][j] + cnt[i-1][j]) % mod;
                if (dp[i][j] == dp[i][j-1] + (ch=='S'?0:ch-'0'))
                    cnt[i][j] = (cnt[i][j] + cnt[i][j-1]) % mod;
                if (dp[i][j] == dp[i-1][j-1] + (ch=='S'?0:ch-'0'))
                    cnt[i][j] = (cnt[i][j] + cnt[i-1][j-1]) % mod;
            }   
        }

        if (dp[m-1][n-1] < 0) return {0, 0};
        else return {dp[m-1][n-1], cnt[m-1][n-1]};
    

    }
};