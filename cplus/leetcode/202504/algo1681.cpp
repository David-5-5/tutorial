#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.2 排列型 - 相邻相关
class Solution {
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        int n = nums.size();
        int cnt = n / k;    // 每组的元素数量

        // 预计算所有子集的不兼容性
        unordered_map<int, int> values;
        for (int mask=1; mask<(1<<n); ++mask) {
            if (__builtin_popcount(mask) != cnt) continue;
            // 同一集合不能有相同元素
            set<int> distinct;
            int mx = 0, mn = 18;
            for (int i=0; i<n; ++i) {
                if (mask >> i & 1) {
                    distinct.emplace(nums[i]);
                    mx = max(mx, nums[i]);
                    mn = min(mn, nums[i]);
                }
            }
            if (distinct.size() == cnt) values[mask] = mx - mn;
        }

        vector<int> dp(1<<n, INT_MAX/2);
        dp[0] = 0;
        for (int mask=0; mask<(1<<n); ++mask) {
            if (dp[mask] >= INT_MAX/2) continue;    // 剪枝
            
            // k nums[i], v: i 相同的值只取一个
            unordered_map<int, int> exclusive;
            for (int i=0; i<n; ++i) {
                if ((mask>>i & 1) == 0){
                    exclusive[nums[i]] = i;
                }
            }
            if (exclusive.size() < cnt) continue;
            int ex_mask = 0;
            for (auto& [_, v]:exclusive)  ex_mask |= (1 << v);
            int nxt = ex_mask;
            while (nxt) {
                if (values.count(nxt)) {
                    dp[mask|nxt] = min(dp[mask|nxt], dp[mask] + values[nxt]);
                }
                nxt = (nxt-1) & ex_mask;
            }
        }

        return dp[(1<<n)-1]<INT_MAX/2?dp[(1<<n)-1]:-1;
    }
};