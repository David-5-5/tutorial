#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.1 一维差分（扫描线）
class Solution {
public:
    int bestRotation(vector<int>& nums) {
        
        int n = nums.size();
        int diff[n];
        memset(diff, 0, sizeof(diff));
        for (int i = 0; i < n; ++i)
        {
            ++diff[(i+1)%n];
            --diff[(n+i+1-nums[i])%n];
        }

        int res = 0;
        int currScore = 0;
        int maxScore = INT_MIN;
        for (int i = 0; i < n; ++i)
        {
            currScore += diff[i];
            if (currScore > maxScore)
            {
                maxScore = currScore;
                res = i;
            }
        }

        return res;
    }
};