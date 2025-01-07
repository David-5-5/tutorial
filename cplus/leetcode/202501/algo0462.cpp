#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 中位数贪心
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        // 自行解答
        int m = nums.size() >> 1;
        
        sort(nums.begin(), nums.end());
        
        int ans = 0;
        for (auto v : nums)
            ans += abs(v - nums[m]);
        
        return ans;
    }
};