#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        // 同 852
        int n = nums.size(), l = -1, r = n + 1;

        while (l + 1 < r) {
            auto mid = (l + r) / 2;

            if ((mid==0 || nums[mid-1] < nums[mid]) && (mid == n-1 || nums[mid] > nums[mid+1])) return mid;
            else if ((mid==0 || nums[mid-1] < nums[mid]) && (mid == n-1 || nums[mid] < nums[mid+1])) l = mid;
            else r = mid;
        }

        return 0;
    }
};