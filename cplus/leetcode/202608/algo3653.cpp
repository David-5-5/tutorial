#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        // 暴力做法 O(N^2) N = 10^3; 3655 N = 10^5
        const int mod = 1e9 + 7;
        for (auto& q: queries) {
            auto &l = q[0], &r = q[1], & k = q[2], &v = q[3];
            for (int i=l; i<=r; i+=k) {
                nums[i] = (1LL * nums[i] * v) % mod;
            }
        }

        return reduce(nums.begin(), nums.end(), 0, bit_xor<>());
    }
};