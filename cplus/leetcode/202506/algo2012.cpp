#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    int sumOfBeauties(vector<int>& nums) {
        // 自行解答
        int n = nums.size();
        vector<int> suf_mn(n);
        suf_mn[n-1] = nums[n-1];
        for (int i =n-2; i>=0; --i) 
            suf_mn[i] = min(suf_mn[i+1], nums[i]);
        
        int pre_mx = nums[0], ans = 0;
        for (int i=1; i<n-1; ++i) {
            auto& x = nums[i];
            if (x > pre_mx && x < suf_mn[i+1]) ans += 2;
            else if (x > nums[i-1] && x < nums[i+1]) ans += 1;
            pre_mx = max(nums[i], pre_mx);
        }

        return ans;        
    }
};