#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 定长滑动窗口 1.2 进阶
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        // 自行解答
        int n = nums.size();
        int ones = accumulate(nums.begin(), nums.end(), 0);
        if (ones <= 1) return 0;
        
        int cur_ones = 0, ans = n;
        for(int i=0; i<ones-1; ++i) if (nums[i]==1) cur_ones ++;
        for (int i=ones-1; i<2*n; ++i) {
            if(nums[i%n] == 1) cur_ones ++;
            ans = min(ans, ones-cur_ones);
            if (nums[(i-ones+1)%n] == 1) cur_ones--;
        }

        return ans;
    }
};