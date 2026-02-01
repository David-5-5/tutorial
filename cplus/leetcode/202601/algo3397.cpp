#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        // 自行解答
        sort(nums.begin(), nums.end());
        int ans = 1, n = nums.size(), prev = nums[0]-k;
        for (int i=1; i<n; ++i) {
            if (prev+1 <= nums[i]+k) {
                ans ++; prev = max(prev+1, nums[i]-k);
            }
        }
        return ans;    
    }
};