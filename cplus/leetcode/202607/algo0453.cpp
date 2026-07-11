#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        // 数学，等价转换，将 n - 1 个数增加 1，等价于将 1 个数减少 1
        int n = nums.size();
        int ans = 0, mn = ranges::min(nums);
        for (auto &v : nums) {
            ans += v - mn;
        }
        return ans;
    }
};