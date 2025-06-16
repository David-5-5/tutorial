#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        // 自行解答
        int n = nums.size();
        vector<int> suf(n+1);
        for (int i=n-1; i>=0; --i) {
            if (nums[i] == 1) suf[i] = suf[i+1] + 1;
        }

        int prefix = 0, ans = 0;
        for (int i=0; i<n; ++i) {
            ans = max(ans, prefix + suf[i+1]);
            if (nums[i]==1) prefix += 1;
            else prefix = 0;
        }

        return ans;
        
    }
};