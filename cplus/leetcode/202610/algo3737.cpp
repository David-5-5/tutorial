#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        vector<int> s_pres = {0}; int pres = 0, ans = 0;
        
        for (auto & v: nums) {
            if (v == target) pres ++;
            else pres --;
            // auto it = upper_bound(s_pres.begin(), s_pres.end(), pres-1);
            auto it = lower_bound(s_pres.begin(), s_pres.end(), pres);
            ans += it - s_pres.begin();
            s_pres.insert(it, pres);
        }

        return ans;
    }
};