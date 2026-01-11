#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.7 摩尔投票法
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        // 自行解答，按题意模拟
        unordered_map<int, int> cnt;
        for (auto & v:nums) {
            cnt[v] ++;
        }
        vector<int> ans;
        for (auto& [v, c]: cnt) {
            if (c > nums.size()/3) ans.push_back(v);
        }

        return ans;        
    }
};