#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.1 前缀和基础
class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> pres(n);

        for (int i=1; i<n; i++) {
            pres[i] = pres[i-1] + ((nums[i]&1)^(nums[i-1]&1));
        }

        vector<bool> ans;
        for (auto& q: queries) {
            ans.push_back(pres[q[1]]-pres[q[0]]==q[1]-q[0]);
        }
        return ans;
    }
};