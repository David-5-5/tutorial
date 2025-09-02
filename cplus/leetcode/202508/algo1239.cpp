#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.2 子集型回溯
class Solution {
public:
    int maxLength(vector<string>& arr) {
        // 自行解答
        vector<int> nums;
        for (int i=0; i<arr.size(); ++i) {
            int mask = 0; 
            for (auto ch:arr[i]) {
                if ((mask & 1<<(ch-'a')) == 0) mask |= 1<<(ch-'a');
                else {mask = 0; break;}
            }
            if (mask) nums.push_back(mask);
        }
        int ans = 0;
        auto dfs = [&](this auto&& dfs, int i, int mask) {
            ans = max(ans, __builtin_popcount(mask));
            if (i == nums.size()) return;
            dfs(i+1, mask);     // 不选
            if ((mask & nums[i]) == 0) dfs(i+1, mask | nums[i]);
        };
        dfs(0, 0);
        return ans;  
        
    }
};