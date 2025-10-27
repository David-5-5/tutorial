#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 求子数组个数 2.3.3 恰好型滑动窗口
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        // 自行解答 
        int ans = 0, cnt1 = 0, l1 = 0, cnt2 = 0, l2 = 0, n = nums.size();
        for (int r=0; r<n; ++r) {
            if (nums[r] % 2) cnt1 ++, cnt2++;
            while (l1<r && cnt1 > k) { // [l1,r] k odd
                if (nums[l1] % 2) cnt1 --;
                l1 ++;
            }
            while (l2<r && cnt2 >= k) { // [l2,r] k-1 odd
                if (nums[l2] % 2) cnt2 --;
                l2 ++;
            }
            ans += l2 - l1;
        }
        return ans;        
    }
};