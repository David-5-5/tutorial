#include <bits/stdc++.h>
using namespace std;

// 顺序 同 3202 动态规划
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int ans = 0, k = 2;
        for (int m=0; m<k; m++) {
            vector<int> dp(k);
            for (auto x : nums) {
                x %= k;
                dp[x] = dp[(m - x + k) % k] + 1;
                ans = max(ans, dp[x]);
            }
        }

        return ans;            
    }
};