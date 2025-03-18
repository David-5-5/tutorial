#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        
        unordered_map<int, int> memo;
        auto dfs = [&](this auto&& dfs, int x0, int x1, int y0, int y1) ->int {
            
            if (x0 + 1 == x1 && y0 + 1 == y1) return 0;
            
            int mask = x0 << 24 | y0 << 16 | x1 << 8 | y1;
            if (memo.count(mask)) return memo[mask];

            int res = INT_MAX/2;

            for (int x=x0+1; x<x1; x++) {
                // cout << "x=" << x << endl;
                res = min(res, horizontalCut[x-1] + dfs(x0, x, y0, y1) + dfs(x, x1, y0, y1));
            }

            for (int y=y0+1; y<y1; y++) {
                res = min(res, verticalCut[y-1] + dfs(x0, x1, y0, y) + dfs(x0, x1, y, y1));
            }

            return memo[mask] = res;
        };
        
        return dfs(0,m,0,n);

    }
};