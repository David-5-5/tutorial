#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size(); vector<int> suf_mn(n); suf_mn[n-1] = nums[n-1];

        for (int i=n-2; i>=0; i--) {
            suf_mn[i] = min(nums[i], suf_mn[i+1]);
        }

        int pre_mx = 0, mn_st = k+1;
        for (int i=0; i<n; i++) {
            pre_mx = max(pre_mx, nums[i]);
            auto val = pre_mx - suf_mn[i];

            if (val < mn_st){
                return i;
            }
        }
        return -1;
    }
};