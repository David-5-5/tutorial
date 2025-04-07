#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  8.2其他区间 DP
class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        // 自行解答，记忆化搜索 O(N^3)

        unordered_map<long, int> memo;
        auto dfs = [&](this auto&& dfs, int i, int j) {
            long mask = (long) i << 32 | j;
            if (memo.count(mask)) return memo[mask];

            auto& res = memo[mask];
            res = INT_MAX;
            for (auto v : cuts) {
                if (i < v && v < j) {
                    res = min(res, dfs(i, v) + dfs(v, j));
                }
            }

            if (res == INT_MAX) return res = 0;
            return res += j - i;
        };

        return dfs(0, n);

    }
    
    int minCost2(int n, vector<int>& cuts) {
        // 参考解答，优化实现，记忆化搜索 O(N^3)
        
        cuts.push_back(0), cuts.push_back(n);
        int m = cuts.size();
        sort(cuts.begin(), cuts.end());
        
        vector<vector<int>> memo(m, vector<int>(m, -1));
        auto dfs = [&](this auto&& dfs, int i, int j) {
            if (i+1 == j) return 0;

            auto& res = memo[i][j];
            if (res != - 1) return res;
            res = INT_MAX;
            for (int k=i+1; k < j; ++k) {
                res = min(res, dfs(i, k) + dfs(k, j));
            }
            return res += cuts[j] - cuts[i];
        };

        return dfs(0, m-1);   

    }
};