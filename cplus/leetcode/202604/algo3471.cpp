#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.2 脑筋急转弯
class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        // 分类讨论 简单题目 但坑不少
        int n = nums.size();
        if (n == k) return ranges::max(nums);
        if (k == 1) {
            unordered_map<int, int> cnt;
            for (auto v : nums) cnt[v] ++;
            int ans = -1;
            for (auto& [k, v]: cnt) 
                if (v>1) continue;
                else ans = max(ans, k);
            return ans;
        }
        if (nums[0] == nums[n-1]) return -1;    // 
        
        // v [begin, end)
        auto f = [&] (int v, int begin, int end) -> int {
            for (int i=begin; i<end; i++) {
                if (nums[i] == v) return -1;
            }
            return v;
        };
        return max(f(nums[0], 1, n), f(nums[n-1], 0, n-1));
    }
};