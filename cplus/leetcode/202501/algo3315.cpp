#include <bits/stdc++.h>
using namespace std;

// 双周赛 141
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        // 数学方法 x or (x + 1) ，
        // 如果 x = 101011， x = 101011 | 101100 = 101111
        // 反过来，将 nums[i] = 101111 的可能 x 的取值
        // 101111 = 100111 | 101000 
        // 101111 = 101011 | 101110
        // 101111 = 101101 | 101110
        // 101111 = 101110 | 101111
        // 综上所述，将 nums[i] 最右边的右边的 1 置为 0

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