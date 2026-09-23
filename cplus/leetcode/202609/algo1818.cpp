#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        const int mod = 1e9 + 7;
        // set<int> uniq(nums1.begin(), nums1.end());   // 性能差
        vector<int> uniq = nums1; sort(uniq.begin(), uniq.end());
        uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());

        long long absum = 0; int n = nums1.size(), mx = 0;
        for (int i=0; i<n; i++) {
            auto cur = abs(nums1[i] - nums2[i]);
            absum += cur;
            if (cur) { // cur > 0
                // auto it = uniq.lower_bound(nums2[i]); // 对应 set<int> 类型的二分查找
                auto it = lower_bound(uniq.begin(), uniq.end(), nums2[i]);
                auto mn = INT_MAX;
                if (it != uniq.end()) mn = min(mn, *it-nums2[i]);
                if (it != uniq.begin()) mn = min(mn, nums2[i] - *prev(it));
                mx = max(mx, cur - mn);
            }
        }

        return (absum - mx) % mod;
    }
};