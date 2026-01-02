#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 三、背包 3.1 0-1 背包 进阶
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), m = queries.size(), ans = 0;

        for (int i=0; i<n; ++i) {
            auto& x = nums[i];
            if (x == 0) continue;
            vector<bool> dp(1 + x);  dp[0] = true;
            for (int j=0; j<m; ++j) {
                auto & q = queries[j];
                if (i < q[0] || i > q[1]) continue;
                
                for (int k=x; k>=q[2]; --k) {
                    dp[k] = dp[k] || dp[k-q[2]];
                }
                if (dp[x]) {
                    ans = max(ans, j + 1); break;
                }
            }
            if (!dp[x]) return -1;
        }
        return ans;     
    }
};