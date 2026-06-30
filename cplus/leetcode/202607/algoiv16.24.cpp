#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> pairSums(vector<int>& nums, int target) {
        unordered_map<int, int> prev;

        vector<vector<int>> ans;
        for (auto v: nums) {
            if (prev.count(target-v) && prev[target-v]) {
                ans.push_back({v, target - v});
                prev[target-v] --;
            } else prev[v] ++;
        }

        return ans;
    }
};