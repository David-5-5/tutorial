#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 基础
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        // 自行解答，前后缀分解
        int n = arr.size();
        
        int mx = ranges::max(arr);
        if (mx<0) return mx;

        vector<int> pres(n+1, 0);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + arr[i];

        vector<int> suf_mx(n+1, INT_MIN/2);
        suf_mx[n] = pres[n];
        for (int i=n-1; i>=0; i--) suf_mx[i] = max(suf_mx[i+1], pres[i]);

        int pre_mn = pres[0];
        int ans = INT_MIN/2;
        for (int i=0; i<n; i++ ) {
            pre_mn = min(pre_mn, pres[i]);
            ans = max(ans, pres[i] - pre_mn + max(0, arr[i]) + suf_mx[i+1] - pres[i+1]);
        }

        return ans;

    }

    int maximumSum2(vector<int>& arr) {
        // 状态 DP
        // state 0, 1, 2
        // 0， 从当前求和， 1， 从 i-1 求和 2：从 i-2 求和
        int n = arr.size(), ans = arr[0];
        vector dp(n, vector<int>(3, INT_MIN/2));
        dp[0][0] = arr[0], dp[0][1] = arr[0];
        for (int i=1; i<n; i++) {
            dp[i][0] = arr[i];
            dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + arr[i];
            
            dp[i][2] = dp[i-1][2] + arr[i];
            if (i>1) dp[i][2] = max(dp[i][2], max(dp[i-2][0], dp[i-2][1]) + arr[i]);
            auto mx = ranges::max(dp[i]);
            if (mx > ans) ans = mx;
        }
        return ans;   
    }    
};