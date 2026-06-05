#include <bits/stdc++.h>
using namespace std;

// 随机
class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), l=0, r=0; nums.emplace_back(0); // sentinel value
        vector<int> l_idx; vector<long long> pres(1, 0);
        while (r<n) {
            if (nums[r] <= nums[r+1]) r ++;
            else {
                l_idx.push_back(l);
                pres.emplace_back(pres.back() + 1LL * (r - l + 1) * (r-l+2) / 2);
                l = ++r;
            }
        }

        vector<long long> ans;
        for (auto q:queries) {
            auto l = q[0], r = q[1];
            auto it_l = ranges::upper_bound(l_idx, l);
            auto it_r = ranges::upper_bound(l_idx, r);
            if (it_l == it_r) ans.emplace_back(1LL * (r - l + 1) * (r-l+2) / 2);
            else {
                long long res = 0; auto l_r = *it_l; auto r_l = *prev(it_r);
                res += 1LL * (l_r - l + 1) * (l_r - l) / 2;
                res += 1LL * (r - r_l + 1) * (r - r_l + 2) / 2;
                res += pres[prev(it_r)-l_idx.begin()] - pres[it_l - l_idx.begin()];
                ans.emplace_back(res);
            }
        }
        return ans;
    }    
};
