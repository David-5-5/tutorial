#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        // 自行解答
        for (auto& v: nums) v *= v;
        sort(nums.begin(), nums.end()); int n = nums.size();
        return accumulate(nums.begin()+n/2, nums.end(), 0LL) - 
            accumulate(nums.begin(), nums.begin() + n/2, 0LL);        
    }
};