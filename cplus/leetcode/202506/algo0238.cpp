#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // 自行解答
        int n = nums.size(), pre = 1;
        vector<int> suf(n+1, 1);
        for (int i=n-1; i; --i) suf[i] = nums[i] * suf[i+1];
        vector<int> ans(n);
        for (int i=0; i<n; ++i) {
            ans[i] = pre * suf[i+1];
            pre *= nums[i];
        }

        return ans;
    }
};