#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 进阶
class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        // 自行解答
        int n = nums1.size();

        vector<vector<int>> memo(n, vector<int>(2,-1));

        // 检查是否 nums[i] > nums[i - 1]
        auto check = [&](int i, int j) -> bool {
            if (j == 1 && nums1[i] > nums2[i-1] && nums2[i] > nums1[i-1] || 
                j == 0  && nums1[i] > nums1[i-1] && nums2[i] > nums2[i-1])
                return true;
            else return false;
        };
        
        auto dfs = [&](this auto&& dfs, int i, int j) -> int{
            if (i == n-1) return check(i, j) ? 0 : 1;

            auto& res = memo[i][j];
            if (res != -1) return res;

            if (check(i, j)) {
                res = dfs(i+1, 0);
                if (check(i, j^1))  // 变更 i 是否满足 nums[i] > nums[i - 1]
                    res = min(res, dfs(i+1, 1) + 1);
            }
            else res = 1 + dfs(i+1, 1);

            return res; 
        };

        return min(dfs(1, 0), 1 + dfs(1, 1));
    }
};