#include <bits/stdc++.h>
using namespace std;

// 同 198
class Solution {
public:
    int rob(vector<int>& nums) {
        // 自行解答，静下心来用笔写一下状态转移方程
        int n = nums.size();
        vector<vector<int>> f(n, vector<int>(2));
        f[0][0] = 0, f[0][1] = nums[0];

        for (int i=1; i<n; i++) {
            f[i][0] = max(f[i-1][1], f[i-1][0]);
            f[i][1] = f[i-1][0] + nums[i];
        }

        return max(f.back()[0], f.back()[1]);    
    }
};