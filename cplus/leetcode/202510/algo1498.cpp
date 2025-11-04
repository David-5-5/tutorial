#include <bits/stdc++.h>
using namespace std;

const int MX = 1e5, MOD = 1e9 + 7;
vector<int> pow2(MX, 1);
int init = [] {
    for (int i=1; i<MX; ++i) pow2[i] = pow2[i-1] * 2 % MOD;
    return 0;
}();

// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        // 自行解答
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.size()-1, ans = 0;
        while (l <= r) {
            if (nums[l] + nums[r] <= target) {
                // 完成包含 l 到 r 的所有子序列个数统计
                // 关键 l 必须包含, 这样 l 就可以增加了
                ans = (ans + pow2[r-l]) % MOD; l++;
            } else r--;
        }
        return ans;
    }
    
};