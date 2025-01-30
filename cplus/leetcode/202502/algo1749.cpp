#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最大子数组和
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        // 自行解答，生成 nums 的负数，再求最大值
        auto max_sum = [](vector<int>& nums) -> int {
            int sum = 0, ans = 0;
            for (auto& v :nums) {
                sum += v;
                if (sum < 0) sum = 0;
                ans = max(ans, sum);
            }
            return ans;
        };

        vector<int> inv;
        for (auto v : nums) inv.push_back(-v);
        return max(max_sum(nums), max_sum(inv));
    }
};