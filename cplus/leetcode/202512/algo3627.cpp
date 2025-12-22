#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution {
public:
    long long maximumMedianSum(vector<int>& nums) {
        // 自行解答
        int i = 0, j = nums.size() - 1; long long ans = 0;
        sort(nums.begin(), nums.end());

        while (i < j) {
            ans += nums[j-1];
            i ++, j -= 2;
        }
        return ans;
    }
};