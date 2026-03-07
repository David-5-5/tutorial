#include <bits/stdc++.h>
using namespace std;

// 同 540
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int l = 0, n = nums.size(), r = nums.size();
        while (l < r) {
            int mid = (l + r) / 2, mid2 = (l+r)/2;
            if (mid == 0 || mid == n-1 || (nums[mid+1]!=nums[mid] && 
                    nums[mid-1]!= nums[mid]))   
                return nums[mid];
            if (nums[mid-1] == nums[mid]) {
                mid--;
            } else mid2++;

            if ((mid - l)  % 2) r = mid;
            else l = mid2 + 1;
        }

        return -1;        
    }
};