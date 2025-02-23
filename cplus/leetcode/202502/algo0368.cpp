#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长递增子序列 (LIS)
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // 排序
        int cnt = 1, inx = 0, n= nums.size();
        vector<pair<int,int>> dp(n, {-1,0});
        dp[0] = {-1, 1};
        // 逻辑同 300
        for (int i=1; i<n; i++) {
            for (int j=i-1; j>=0; j--)
                if (nums[i] % nums[j] == 0 && dp[j].second > dp[i].second) {
                    dp[i].first = j;
                    dp[i].second = dp[j].second;
                }
            dp[i].second += 1;
            if (dp[i].second > cnt) {
                cnt = dp[i].second;
                inx = i;
            }
        }

        vector<int> ans;
        while (inx >= 0) {
            ans.push_back(nums[inx]);
            inx = dp[inx].first;
        }
        return ans;
    }
};