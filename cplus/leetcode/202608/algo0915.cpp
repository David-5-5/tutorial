#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        int n = nums.size(); vector<int> suf_mn(n);
        suf_mn[n-1] = nums[n-1];
        for (int i=n-2; i>=0; i--) {
            suf_mn[i] = min(suf_mn[i+1], nums[i]);
        }

        int pre_mx = -1;
        for (int i=0; i<n-1; i++) {
            pre_mx = max(pre_mx, nums[i]);
            if (pre_mx <= suf_mn[i+1]) return i + 1;
        }

        return -1;
    }
};