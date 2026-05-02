#include <bits/stdc++.h>
using namespace std;

// 八、区间 DP - §8.2 区间 DP
class Solution {
public:
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {
        // 学习视频
        // f(i,j) = f(i, j-1)^f(i+1, j)  f(i,j) 表示区间[i,j]的异或
        // mx(i,j) = max(f(i, j), mx(i, j-1), mx(i+1, j)) mx(i,j) 表示区间[i,j]的异或最大值

        int n = nums.size(), m = queries.size();
        vector f(n, vector<int>(n)), mx(n, vector<int>(n));

        // 观察转移方程 i <- i+1 , j <- j-1，推出 i 从大到小 j 从小到大
        for (int i=n-1; i>=0; i--) {
            f[i][i] = nums[i], mx[i][i] = nums[i];
            for (int j=i+1; j<n; j++) {     // i = n-2 进行循环，避免i+1越界
                f[i][j] = f[i][j-1] ^ f[i+1][j];
                mx[i][j] = max(f[i][j], max(mx[i][j-1], mx[i+1][j]));
            }
        }
        
        vector<int> ans;
        for (auto& q: queries) ans.push_back(mx[q[0]][q[1]]);
        
        return ans;
    }
};

