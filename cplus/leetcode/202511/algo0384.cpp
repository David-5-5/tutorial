#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 随机算法 - 6.1 随机数
// 暴力
class Solution {
private:
    vector<int> nums;
public:
    Solution(vector<int>& nums) {
        this->nums = nums;
    }
    
    vector<int> reset() {
        return this->nums;
    }
    
    vector<int> shuffle() {
        int n = this->nums.size();
        vector<int> ans(n);
        vector<int> toAssign;
        for (int i=0; i<n; i++) toAssign.emplace_back(i);

        for (int i = 0; i<n; i++) {
            int j = rand() % toAssign.size();
            ans[i] = nums[toAssign[j]];
            toAssign.erase(toAssign.begin() + j);
        }
        return ans;

    }
};



