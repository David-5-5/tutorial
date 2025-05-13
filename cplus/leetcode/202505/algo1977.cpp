#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 11.1 前缀和优化 DP 难度分：2817
class Solution {
public:
    int numberOfCombinations(string num) {
        // 自行解答 记忆化搜索 -> 递推 见 python
        // 直接从 python 转换过来，memory overtime
        if (num[0] == '0') return 0;

        const int mod = 1e9 + 7, n = num.size();
        vector<vector<int>> dp(n+1, vector<int>(n));
        
        for (int j=0; j<n; ++j) dp[n][j] = 1;
        for (int i=n-1; i>=0; --i) {
            if (num[i] == '0') {
                for (int j=0; j<n; ++j) dp[i][j] = 0;
                continue;
            }
            int sum = 0;
            for (int k=i+1; k<=n-i; ++k) sum += dp[i+k][i];

            for (int j=max(0, 2*i-n); j<=i; ++j) {
                if (num.substr(i, i-j) >= num.substr(j,i-j))
                    sum = ((long)dp[i+i-j][i] + sum) % mod;
                dp[i][j] = ((long)dp[i][j] + sum) % mod;
                if (num.substr(i, i-j) < num.substr(j,i-j))
                    sum = ((long)dp[i+i-j][i] + sum) % mod;

            }
        }

        return dp[0][0];
    }

    int numberOfCombinations2(string num) {
        if (num[0] == '0') return 0;

        const int mod = 1e9 + 7, n = num.size();
        
        // c++ 需要计算预处理最长公共前缀
        // 最长公共前缀 - 朴素算法
        // lcp[i][j] 表示以 i, j 开始的子串的最长公共前缀的长度
        // lcp[i][j] = lcp[i+1][j+1] + 1, num[i] == num[j]
        //             0                , num[i] != num[j]
        vector<vector<int>> lcp(n, vector<int>(n));
        for (int i=n-1; i>=0; --i) {
            // 以通过画图理解避免 j+1 越界，!!很棒的写法!!
            lcp[i][n-1] = (num[i] == num[n-1]); 
            for (int j=i+1; j<n-1; ++j) {
                lcp[i][j] = (num[i]==num[j])?lcp[i+1][j+1]+1:0;
            }
        }
        // 判断逻辑是 r >= l:true, r<l false
        auto cmp = [&](int l, int r, int len) -> bool {
            if (lcp[l][r] >= len) return true;                      // l == r
            if (num[l+lcp[l][r]] > num[r+lcp[l][r]]) return false;  // l > r
            else return true;                                       // l < r
        };


        vector<vector<int>> dp(n+1, vector<int>(n));
        
        for (int j=0; j<n; ++j) dp[n][j] = 1;
        for (int i=n-1; i>=0; --i) {
            if (num[i] == '0') {
                for (int j=0; j<n; ++j) dp[i][j] = 0;
                continue;
            }
            int sum = 0;
            for (int k=i+1; k<=n-i; ++k) sum = ((long)dp[i+k][i] + sum) % mod;

            for (int j=max(0, 2*i-n); j<=i; ++j) {
                // bool is_large = (num.substr(i, i-j) >= num.substr(j,i-j))
                bool is_large = cmp(j, i, i-j);
                if (is_large)
                    sum = ((long)dp[i+i-j][i] + sum) % mod;
                dp[i][j] = ((long)dp[i][j] + sum) % mod;
                if (!is_large)
                    sum = ((long)dp[i+i-j][i] + sum) % mod;

            }
        }

        return dp[0][0];
    }
};