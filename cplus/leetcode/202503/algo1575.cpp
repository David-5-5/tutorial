#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        
        const int mod = 1e9 + 7;
        int n = locations.size();

        vector<vector<int>> memo(n, vector<int>(fuel+1, -1));

        auto dfs = [&](this auto&& dfs, int i, int f) -> int {
            if (f < 0) return 0;
            
            auto& res = memo[i][f];
            if (res != -1) return res;

            res = (i==finish);
            for (int j=0; j<n; j++) {
                if (j==i) continue;
                res = (dfs(j, f-abs(locations[i]-locations[j])) + res) % mod ;
            }
            return res;
        };

        return dfs(start, fuel);   
    }
};