#include <bits/stdc++.h>
using namespace std;

// 四、数学贪心 - 4.2 乘积贪心
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        // 自行解答
        sort(nums.begin(), nums.end()); int n = nums.size();
        long long third = 1e5;
        return max({abs(third * nums[0] * nums[1]), 
            abs(third * nums[n-1] * nums[n-2]),
            abs(third * nums[0] * nums[n-1])});        
    }
};