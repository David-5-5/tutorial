#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 11.1 前缀和优化 DP
class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        // 参考题意解答，超时版本
        vector<double> dp(k+maxPts);   // k-1 + maxPts 为取的最大值
        
        for (int i = min(n,k+maxPts-1); i>=k; --i) dp[i] = 1.0;

        for (int i=k-1; i>=0; --i) {
            double res = 0;
            for (int j=maxPts; j; --j) {
                res += dp[i+j];
            }
            dp[i] = res / maxPts;
        }
        return dp[0];  
    }


};