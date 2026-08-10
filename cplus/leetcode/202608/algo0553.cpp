#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        // 数学 nums[0]/(nums[1]/nums[2]/...nums[i]) 分子越小约好 nums[i] >= 2
        if (nums.size() == 1) return to_string(nums[0]);
        if (nums.size() == 2) return to_string(nums[0]) + "/" + to_string(nums[1]);
        else {
           string div = to_string(nums[1]);
           for (int i=2; i<nums.size(); i++) div += "/" + to_string(nums[i]);
           return to_string(nums[0]) + "/(" + div + ")";
        }
    }
};