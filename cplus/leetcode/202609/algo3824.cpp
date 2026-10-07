#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumK(vector<int>& nums) {
        int mx = ranges::max(nums);

        auto check = [&](int k) -> bool {
            int res = 0;
            for (auto &v : nums) {
                res += (v + k - 1) / k;
            }

            return res <= 1LL * k * k;
        };

        int l = 0, r = 1e5 + 1;
        while (l + 1 < r) {
            auto mid = (l + r) >> 1;
            (check(mid)? r : l ) = mid;
        }
        return r; 
    }
};