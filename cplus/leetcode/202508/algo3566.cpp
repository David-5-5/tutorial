#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.2 子集型回溯
class Solution {
public:
    bool checkEqualPartitions(vector<int>& nums, long long target) {
        // 自行解答，带记忆化搜索 + 参考题解增加  target * target != product 判断
        int n = nums.size();
        unordered_map<int, bool> memo;
        unsigned long long product = 1;
        for (auto& num : nums) product *= num;
        if ((unsigned long long)target * target != product) return false;
                
        auto dfs = [&](this auto&& dfs, int mask) -> bool {
            if (__builtin_popcount(mask) == n) return false;    // 必须分成两个集合
            
            if (memo.count(mask)) return memo[mask];

            // 检查现有乘积
            long long prd1 = 1, prd2 = 1;
            for (int i=0; i<n; ++i)  {
                if ((mask >> i) & 1) prd1 *= nums[i];
                if (prd1 > target) return memo[mask] = false;
            }
            
            if (prd1 == target) return memo[mask] = true;

            for (int i=0; i<n; ++i) {
                if (((mask>>i) & 1)) continue;  // 已选择
                if (dfs(mask | 1 << i)) return memo[mask] = true;
             }
             return memo[mask] = false;
        };
        return dfs(0);
    }

    bool checkEqualPartitions2(vector<int>& nums, long long target) {
        // 参考题解， 不需要 meno
        int n = nums.size();

        unsigned long long product = 1;
        for (auto& num : nums) product *= num;
        if ((unsigned long long)target * target != product) return false;
        auto dfs = [&](this auto&& dfs, int mask) -> bool {
            if (__builtin_popcount(mask) == n) return false;    // 必须分成两个集合

            // 检查现有乘积
            long long prd1 = 1;
            for (int i=0; i<n; ++i)  {
                if ((mask >> i) & 1) prd1 *= nums[i];
                if (prd1 > target) return false; 
            }
            if (prd1 == target) return true;

            for (int i=0; i<n; ++i) {
                if (((mask>>i) & 1)) continue;  // 已选择
                if (dfs(mask | 1 << i)) return true;
             }
             return false;
        };
        return dfs(0);
    }    
};