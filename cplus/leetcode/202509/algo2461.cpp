#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.1 基础
class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> cnt; int n = nums.size();
        long long sum = 0, ans = 0; 
        for (int i=0; i<k-1;++i) {
            cnt[nums[i]] ++; sum += nums[i];
        }

        for (int i=k-1; i<n; ++i) {
            cnt[nums[i]] ++; sum += nums[i];
            if (cnt.size()==k) ans = max(ans, sum);
            sum -= nums[i-k+1]; cnt[nums[i-k+1]] --;
            if (cnt[nums[i-k+1]] == 0) cnt.erase(nums[i-k+1]);
        }
        return ans;
    }
};