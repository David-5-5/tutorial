#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 四、双序列双指针 - 4.1 双指针
class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        // 自行解答
        int n = nums1.size(), m = nums2.size();
        int i = 0, ans = 0;
        for (int j=0; j<m; ++j) {
            while (i<n && nums1[i] > nums2[j]) i++;
            // i == n, nums1中 不存在比 nums2[j] 小的数了
            if (i < n && nums1[i] <= nums2[j]) {
                ans = max(ans, j-i);
            }
        }
        return ans;    
    }
};