#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        // 自行解答
        vector<int> candidate;
        for (int i=0; i<grid.size(); ++i) {
            sort(grid[i].rbegin(), grid[i].rend());
            // for (int j=0; j<limits[i]; ++j) candidate.emplace_back(grid[i][j]);
            candidate.insert(candidate.end(), grid[i].begin(), grid[i].begin() + limits[i]);
        }
        sort(candidate.rbegin(), candidate.rend());
        // long long ans = 0;
        // for (int i=0; i<k; i++)ans += candidate[i];
        // return ans;     
        return accumulate(candidate.begin(), candidate.begin() + k, 0LL);
    }

    long long maxSum2(vector<vector<int>>& grid, vector<int>& limits, int k) {
        // 自行解答
        vector<int> candidate;
        for (int i=0; i<grid.size(); ++i) {
            ranges::sort(grid[i], greater());
            candidate.insert(candidate.end(), grid[i].begin(), grid[i].begin() + limits[i]);
        }
        ranges::sort(candidate, greater());   
        return reduce(candidate.begin(), candidate.begin() + k, 0LL);   // reduce存在int越界的坑
    }    
};