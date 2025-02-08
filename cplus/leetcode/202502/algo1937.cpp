#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 网格图 DP - 进阶
class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) {
        // 参考题解  前后缀最大值
        // 前后缀分解优化，时间复杂度从 O(mn^2) 优化为 O(mn)
        // f[i][j] = point[i][j] + max{f[i-1][j]-|j-k]}
        //         = point[i][j] - j + max(f[i-1][k] + k), j >= k 前缀最大值
        //           point[i][j] + j + max(f[i-1][k] - k), k > j  后缀最大值
        int m = points.size(), n = points[0].size();
        vector<long> dp(n);

        for (int i=0; i<n; i++) dp[i] = points[0][i];

        for (int i=1; i<m; i++) {
            // 计算后缀最大值
            vector<long> suf_max(n);
            suf_max[n-1] = dp[n-1] - (n-1); // 预置最后一个值
            for (int k=n-2; k>=0; k--) {
                suf_max[k] = max(dp[k] - k, suf_max[k+1]);
            }
            // 一边计算第 i 行状态转移值，一边计算前缀最大值
            vector<long> cur(n);
            long pre_max = 0;
            for (int j=0; j<n; j++) {
                pre_max = max(pre_max, dp[j] + j);
                cur[j] = points[i][j] + max(pre_max-j, suf_max[j] + j);
            }
            dp = cur;

        }

        return *max_element(dp.begin(), dp.end());
                
    }
};