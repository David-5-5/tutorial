#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.2 子集型回溯
class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        // 自行解答 1 <= nums.length <= 16 暴力即可
        int n = nums.size(), mx = 0; for (auto& v: nums) mx |= v;

        int ans = 0;
        unordered_set<int> seen;
        auto dfs = [&](this auto&& dfs, int mask) -> void {
            if (seen.count(mask)) return;
            seen.insert(mask);
            int or_sum = 0;
            for (int i=0; i<n; ++i) {
               if ((mask >> i) & 1) or_sum |= nums[i];
            }
            if (or_sum == mx) ans++;
            for (int i=0; i<n; ++i) {
               if ((mask >> i) & 1) continue;
               dfs(mask | 1 << i);
            }        
        };
        dfs(0);
        return ans; 
    }

    int countMaxOrSubsets2(vector<int>& nums) {
        // 参考题解， 选或不选
        int n = nums.size(), mx = 0; for (auto& v: nums) mx |= v;

        auto dfs = [&](this auto&& dfs, int i, int orsum) -> int {
            if (orsum == mx) return 1 << (n-i); // 优化
            if (i == n) return orsum == mx;
            
            int res = dfs(i+1, orsum);         // 不选
            res += dfs(i+1, orsum|nums[i]); // 不选
            return res;
        };
        return dfs(0, 0);
    }

    int countMaxOrSubsets3(vector<int>& nums) {
        // 位运算，代替方法一，无需递归
        int ans = 0, n = nums.size(), mx = 0; for (auto& v: nums) mx |= v;
        for (int mask = 1; mask<(1<<n); mask++) {
            int or_sum = 0;
            for (int i=0; i<n; ++i) {
               if ((mask >> i) & 1) or_sum |= nums[i];
            }
            if (or_sum == mx) ans ++;
        }

        return ans;

    }
};