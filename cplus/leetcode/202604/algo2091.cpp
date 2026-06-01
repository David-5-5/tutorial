#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int mx = INT_MIN, mx_inx=-1, mn = INT_MAX, mn_inx = -1, n = nums.size();

        for (int i=0; i<n; ++i) {
            if (nums[i] > mx) {mx = nums[i], mx_inx = i;}
            if (nums[i] < mn) {mn = nums[i], mn_inx = i;}
        }

        int ans = 0;
        if (mx_inx == mn_inx) return min(mx_inx+1, n-mx_inx);
        else {
            auto ans = min(mx_inx, mn_inx) + 1 + n - max(mx_inx, mn_inx);
            return min(ans, min(n - min(mx_inx, mn_inx), max(mx_inx, mn_inx) + 1));
        }
    }
};