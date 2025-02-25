#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 约束划分个数
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();

        vector<int> memo(n, -1);
        auto dfs = [&] (this auto&& dfs, int i) ->int {
            if (i == n) return 0;

            auto& res = memo[i];
            if (res != -1) return res;
            
            res = 0;
            int mx = 0;
            for (int j = 0; j<k && j+i < n; j++) {
                mx = max(mx, arr[i+j]);
                res = max(res, mx * (j+1) + dfs(i+j+1));  
            }
            
            return res;
        };

        return dfs(0);        
    }
};