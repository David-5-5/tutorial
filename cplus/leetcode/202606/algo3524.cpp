#include <bits/stdc++.h>
using namespace std;

// 七、其他线性 DP - 7.3 子数组 DP
class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        // 自行解答
        vector<long long> ans(k); int n = nums.size();
        vector dp(n+1, vector<long long>(k));
        for (int i= 0; i<n; i++) {
            for (long long x=0; x<k; x++) {
                dp[i+1][x * nums[i] % k] += dp[i][x];
            }
            dp[i+1][nums[i]%k] ++;
        }

        for (int i=1; i<=n; i++) {
            for (int x=0; x<k; x++) {
                ans[x] += dp[i][x];
            }
        }        
        return ans;
    }

};