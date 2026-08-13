#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int evensum = 0;
        for (auto & v : nums) {
            if (v % 2 == 0) evensum += v;
        }

        vector<int> ans;
        for (auto & q: queries) {
            auto & v = q[0], &i = q[1];
            if (nums[i] % 2 == 0) evensum -= nums[i];
            nums[i] += v;
            if (nums[i] % 2 == 0) evensum += nums[i];
            ans.push_back(evensum);
        }
        return ans;

    }
};