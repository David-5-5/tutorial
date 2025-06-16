#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        // 自行解答，不需要前后缀分解，前缀和即可
        int n = nums.size(), ans = 0;
        vector<long> pres(n+1);
        for (int i=0; i<n; ++i) pres[i+1] = pres[i] + nums[i];
        for (int i=1; i<n; ++i) 
            if (pres[i] >= pres[n]-pres[i])  ans ++;  
        
        return ans;     
    }
};