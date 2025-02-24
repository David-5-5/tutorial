#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最优划分
class Solution {
public:
    long long maximumTotalCost(vector<int>& nums) {
  
        int n = nums.size();

        vector<long> memo(n, -1);
        auto dfs = [&] (this auto&& dfs, int i) -> long {
            if (i >= n) return 0;

            auto& res = memo[i];
            if (res != -1) return res;
            
            res = nums[i] + dfs(i+1);
            if (i+1<n) res = max(res,nums[i] - nums[i+1] +dfs(i+2)); 
            
            return res;
        };

        return dfs(0);        
    }
};