#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.1 一维差分（扫描线）
class Solution {
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        // 参考题解
        int n = nums.size();

        long long pos_ans = 0, neg_ans = 0;
        for (int i=0; i<n; ++i) {
            int d = target[i] - nums[i] - (i? target[i-1] - nums[i-1]:0);
            if (d > 0) pos_ans += d;
            else neg_ans -= d;
        }
        return max(pos_ans, neg_ans);
    }    
};