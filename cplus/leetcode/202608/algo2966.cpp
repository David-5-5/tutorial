#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        int n = nums.size(); sort(nums.begin(), nums.end());

        vector<vector<int>> ans(n/3);
        for (int i=0; i<n/3; i++) {
            if (nums[i*3+2] - nums[i*3] <= k) {
                ans[i] = {nums[i*3], nums[i*3+1], nums[i*3+2]};
            } else return {};
        }

        return ans;
    }
};