#include <bits/stdc++.h>
using namespace std;

// 位运算 - AND/OR LogTrick
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        // 2025.8 复习
        int ans = abs(k-nums[0]);
        for (int i=1; i<nums.size(); ++i) {
            ans = min(ans, abs(nums[i]-k));
            for (int j=i-1; j>=0; j--) {
                if (nums[j] == (nums[j] | nums[i])) break;
                else {
                    nums[j] |= nums[i];
                    ans = min(ans, abs(nums[j]-k));
                }
            }
        }
        return  ans;        
    }
};