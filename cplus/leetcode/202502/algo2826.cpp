#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长递增子序列 (LIS)
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        // 引用 300 LIS 方案
        vector<int> dp;
        for (auto& x : nums) {
            auto it = ranges::upper_bound(dp, x);
            if (it != dp.end()) *it = x;        // c++ iterator usage
            else dp.push_back(x);
        }

        return nums.size() - dp.size();
    }

    int minimumOperations2(vector<int>& nums) {
        // 状态机 DP f(i+1, j) 表示 把 nums[0] 到 nums[i] 变成非递减
        //                    nums[i] == j 的最小修改次数
        int f[4]{};
        for (auto& x : nums) {
            for (int k=3; k; k--) {
                f[k] = *min_element(f+1, f+k+1) + (x != k);
            }
        }
        return min(f);
    }
};