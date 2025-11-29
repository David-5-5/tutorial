#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 随机算法 - 6.1 随机数
class Solution {
private:
    unordered_map<int, vector<int>> vals;
public:
    Solution(vector<int>& nums) {
        for (int i=0; i<nums.size(); ++i) vals[nums[i]].emplace_back(i);
    }
    
    int pick(int target) {
        return vals[target][rand() % vals[target].size()];
    }
};