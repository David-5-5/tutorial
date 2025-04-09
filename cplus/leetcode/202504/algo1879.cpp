#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.1 排列型 - 相邻无关
class Solution {
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        // 自行解答
        int n = nums2.size();

        vector<int> memo(1<<n, INT_MAX);
        auto dfs = [&] (this auto&& dfs, int state) -> int {
            if (state == 0) return 0;
            
            auto& res = memo[state];
            if (res != INT_MAX) return res;
            
            // 计算包含一个的个数，减少一个递归参数
            int i = n - __builtin_popcount(state);  
            for (int j=0; j<n; j++) if ((state >> j) & 1) 
                // 按题解计算数组异或
                res = min(res, (nums1[i] ^ nums2[j]) + dfs(state - (1 << j))) ;

            return res;
        };

        return dfs((1<<n)-1);
    }
};