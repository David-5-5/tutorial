#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    int minimumAverageDifference(vector<int>& nums) {
        // 自行解答
        int n = nums.size();
        vector<int> suf_avg(n+1);
        long sum = 0;
        int pre_avg, min_sub = INT_MAX, inx = 0;
        for (int i=n-1; i>=0; i--) {
            sum += nums[i];
            suf_avg[i] = sum / (n-i);
        }
        sum = 0;
        for (int i=0; i<n; ++i) {
            sum += nums[i];
            pre_avg = sum / (i+1);
            int sub = abs(pre_avg-suf_avg[i+1]);
            if (sub < min_sub) {
                min_sub = sub;
                inx = i;
            }
        }
        return inx;        
    }
};