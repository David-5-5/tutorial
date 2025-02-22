#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长公共子序列  (LCS)
class Solution {
public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        
        int n = b.size();
        // vector<vector<long long>> memo(n, vector<long long>(4, LONG_MIN));

        vector<array<long long, 4>> memo(n);  // it is better than vector<vector<long long>>
        for (auto& row : memo) {
            ranges::fill(row, LLONG_MIN); // 表示没有计算过
        }
        // function<long long(int, int)> dfs = [&] (int i, int j) -> long long {
        auto dfs = [&](this auto&& dfs, int i, int j) -> long long {
            if (j < 0) return 0;
            if (i < j) return LONG_MIN / 2;

            auto& res = memo[i][j];
            if (res != LONG_MIN) return res;

            return res = max(dfs(i-1,j-1) + (long)a[j] * b[i], dfs(i-1,j)); //{} 转换数组超时
            
        };

        return dfs(n-1, 3);
        
    }
};