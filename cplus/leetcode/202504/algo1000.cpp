#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  8.2其他区间 DP
class Solution {
public:
    int mergeStones(vector<int>& stones, int k) {
        // 参考题解
        int n = stones.size();
        if ((n-1) % (k-1) != 0 ) return -1;

        vector<int> pres(n+1);
        for(int i=0; i<n; i++) pres[i+1] = pres[i] + stones[i];

        // int memo[n][n][k + 1];
        // memset(memo, -1, sizeof(memo));     
        vector<vector<vector<int>>> memo(n, vector<vector<int>>(n, vector<int>(k+1, -1)));
        
        auto dfs = [&] (this auto&& dfs, int i, int j, int p) -> int {
            auto& res = memo[i][j][p];
            if (res != -1) return res;
            
            if (p == 1)
                return res = i == j ?0 : dfs(i, j, k) + pres[j+1]-pres[i];
            
            res = INT_MAX;
            for (int m=i; m<j; m+=k-1) {
                res = min(res, dfs(i, m, 1) + dfs(m+1, j, p-1));
            }
            return res;
        };
        
        return dfs(0, n-1, 1); 
        
    }
};