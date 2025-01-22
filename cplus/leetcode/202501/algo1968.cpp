#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        // 自行解答 使用 942 ID...ID 排列
        sort(nums.begin(), nums.end());
        int mn = 0, mx = nums.size(), even = 1;
        vector<int> ans;
        while (mn < mx)
            if (even) ans.push_back(nums[mn++]), even ^= 1;
            else ans.push_back(nums[--mx]), even ^= 1;
        return ans;
    }

    vector<int> rearrangeArray(vector<int>& nums) {
        // 参考题解，写法不同，思路相同
        sort(nums.begin(), nums.end());
        int n = nums.size(), m = (n+1) / 2;
        vector<int> ans;
        for (int i=0; i<m; i++) {
            ans.push_back(nums[i]);
            if (i+m<n) ans.push_back(nums[i+m]);
        }
        return ans;
    }
};
