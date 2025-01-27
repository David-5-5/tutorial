#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 其他
class Solution {
public:
    int findValueOfPartition(vector<int>& nums) {
        // 自行解答，排序后比较相邻元素，取最小值
        sort(nums.begin(), nums.end());

        int ans = INT_MAX;
        for (int i=1; i<nums.size(); i++) {
            ans = min(ans, nums[i]-nums[i-1]);
        }
        return ans;
    }
};