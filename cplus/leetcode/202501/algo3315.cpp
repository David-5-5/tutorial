#include <bits/stdc++.h>
using namespace std;

// 双周赛 141
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        // nums[i] < 1000 时，数据范围很小，可以暴力
        // nums[i] < 10 ** 9 时，找到最高位 0 ，并将 下一位的 1 变更为 0 即可
        // nums[i] == 2  时， ans = -1
        vector<int> ans(nums.size());

        for (int i=0; i<nums.size(); i++) {
            if (nums[i] == 2) {
                ans[i] = -1;
                continue;
            }
            int k = 0;
            for (int j=1; j<31; j++){
                if ((nums[i]>>j & 1) == 0) { // & 优先级低
                    k = j - 1;
                    break;
                }
            }
            ans[i] = nums[i] - (1 << k);
        }
        
        return ans;
    }
};