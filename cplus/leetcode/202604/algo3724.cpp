#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2) {
        // ans 起始为 1， 是增加元素到 nums1 末尾的操作
        long long ans = 1; int n = nums1.size(), last = INT_MAX;
        for (int i=0; i<n; i++) {
            ans += abs(nums1[i] - nums2[i]);
            if (last) { // nums2 最后一个数增加/减少的操作次数
                if (nums2[n] >= min(nums1[i], nums2[i]) && nums2[n] <= max(nums1[i], nums2[i])) 
                    last = 0;   // 在两个数中间，不需要增加/减少
                else {
                    // 和两个数差的最小值，为需要增加或减少的次数
                    last = min(last, abs(nums2[n]-nums1[i]));   
                    last = min(last, abs(nums2[n]-nums2[i]));
                }
            }
        }
        return ans + last;
    }
};