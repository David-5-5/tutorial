#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
int mx = 131;
vector<vector<int>> comb(mx, vector<int>(mx));
int init = [] {
    for (int i=0; i<mx; ++i) comb[i][0] = 1;
    for (int i=1; i<mx; ++i) for (int j=1;j<=i; ++j) 
        comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % mod;
    return 0;
}();

// 数学算法 - 组合数学 - 2.2 组合计数
class Solution {
public:
    // 参考题解 动态规划
    // 状态定义: 对于每种字母 i 当前长度 j，枚举第 i 种字母的使用数量 x
    //          其中x 的范围是 0 到 min(k, j)，即不超过 k 次且不超过当前剩余长度
    // dp[i][j] = sum(dp[i-1][j-x] * c(j,x)), where x ∈ 0~min(j,k) j ∈ 0~n
    // 初始条件: dp[i][0] = 1, 使用 i 种字母组成空字符串
    // dp[i-1][j-x]: 使用前 i-1 种字母组成长度 j-x 的方案数
    // C(j, x): 组合数，表示从 j 个位置中选 x 个放置第 i 种字母
    int keyboard(int k, int n) {
        if (n > k * 26) return 0;
        if (n == 0) return 1;

        vector<vector<int>> dp(27,vector<int>(n+1));
        for (int i=0; i<=26; ++i) dp[i][0] = 1;
        for (int i=1; i<=26; ++i) for (int j=1; j<=n; ++j)
            for (int x=0; x<=min(j,k); ++x)
                dp[i][j] = (dp[i][j] +  1L * dp[i-1][j-x]*comb[j][x]) % mod;

        return dp[26][n];
    }
};