#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 组合数学 - 2.3 放球问题
class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k) {
        const int mod = 1e9 + 7;
        // 表示 dp[i][j] 表示 i 个播放包含 j 和不同的歌曲的方案数
        // 因此状态转移方程为
        // dp[i][j] += dp[i-1][j-1] * (n-j+1) 取一个新的歌曲的方案数
        // dp[i][j] += dp[i-1][j] * (j-k) 取一首以及听过的歌曲的方案数
        vector<vector<long long>> dp(goal+1,vector<long long> (n+1));
        dp[0][0] = 1;
        for (int i=1; i<=goal; ++i) for (int j=1; j<=n; ++j) {
            dp[i][j] = 1LL * dp[i-1][j-1] * (n-j+1) % mod;
            dp[i][j] = (dp[i][j] + 1LL * dp[i-1][j] * max(0, j-k)) % mod;   
        }

        return dp[goal][n];
    }
};