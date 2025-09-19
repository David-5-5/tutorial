#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.7 搜索 
class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        // 参考题解
        if (accumulate(nums.begin(), nums.end(), 0) < abs(k)) return -1;
        
        int ans = -1, n = nums.size(); 
        unordered_set<long long> vis;
        auto dfs = [&](this auto&& dfs, int i, int alt, int even, int prod, bool sel) -> void {
            long long mask = ((long long)i << 40) + (alt << 22)  + (even << 20) + (prod << 2) + sel;
            if (vis.count(mask)) return;
            vis.insert(mask);
            if (ans == limit or (ans>=0 and prod>limit)) return;
            if (i == n) {
                if (prod<=limit && sel && alt == k) ans = max(ans, prod);
                return;
            };

            dfs(i+1, alt, even, prod, sel);
            // min(prod*nums[i], limit+1) 压缩状态空间
            dfs(i+1, alt + (even==0?nums[i]:-nums[i]), even^1, min(prod*nums[i], limit+1), true);
        };
        dfs(0, 0, 0, 1, false); return ans;  
    }
};