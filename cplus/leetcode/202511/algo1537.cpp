#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 四、双序列双指针 - 4.1 双指针
class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        // 看错题目了，动态规划 :
        // f[i] = f[i-1] + nums1[i] ,nums1[i] < nums2[j]
        // g[j] = g[j-1] + nums2[j] ,nums1[i] > nums2[j]
        // f[i] = g[j] = max(f[i-1], g[j-1]) + nums1[i] ,nums1[i] == nums2[j]
        const int mod = 1e9 + 7;

        int inx1 = 0, n = nums1.size(), inx2 = 0, m = nums2.size();
        long long f = 0, g = 0;
        while (inx1 < n && inx2 < m) {
            if (nums1[inx1] == nums2[inx2]) {
                f = g = max(f, g) + nums1[inx1];
                inx1 ++, inx2 ++;
            } else if (nums1[inx1] < nums2[inx2]) 
                f += nums1[inx1++];
            else g += nums2[inx2++];
        }
        for (int i=inx1; i < n; i++) f +=nums1[i];
        for (int i=inx2; i < m; i++) g +=nums2[i];

        return max(f, g) % mod;  
    }
};