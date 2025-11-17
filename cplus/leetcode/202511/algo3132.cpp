#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 四、双序列双指针 - 4.2 判断子序列
class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        // 自行解答
        int n = nums1.size(), m = nums2.size();
        sort(nums1.begin(), nums1.end()); sort(nums2.begin(), nums2.end()); 
        int mn = *nums2.begin() - *nums1.rbegin(), mx = *nums2.rbegin() - *nums1.begin();
        for (int x=mn; x<=mx; ++x) {
            int inx1 = 0, inx2 = 0;
            while (inx1 <n && inx2 < m) {
                if (nums1[inx1] + x == nums2[inx2]) {
                    inx1 ++; inx2 ++;
                } else inx1 ++;
            }
            if (inx2 == m) return x;

        }
        return -1;
    }


};

