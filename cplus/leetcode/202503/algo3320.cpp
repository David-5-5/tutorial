#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
    public:
    int countWinningSequences(string s) {
        // 自行解答，勉强通过（有一次超时）
        // 用 vector 代替 unordered_map 做记忆化缓存，性能提升很多
        const int mod = 1e9 + 7;
        int n = s.length();

        string game = "FWE";

        auto score = [](char a, char b) -> int {
            if (a == b) return 0;
            if (a == 'F' && b == 'E' || a =='W' && b == 'F' || a=='E' && b == 'W')
                return 1;
            else return -1;
        };
        
        // unordered_map<long, int> memo;
        vector<vector<vector<int>>> memo(n, vector<vector<int>>(2*n+1, vector<int>(3, -1)));
        auto dfs = [&](this auto&& dfs, int i, int t, int p) -> int {
            if (i<0) return t>n?1:0;
            if (i + t < n) return 0; // 剪枝
            
            // 使用 unordered_map 做缓存
            // long mask = ((long) t << 32) | i << 10 | p;
            // if (memo.contains(mask)) return memo[mask];
            // int res = 0;

            auto& res = memo[i][t][p];
            if (res != -1) return res;
            res = 0;
            for (int k=0; k<3; k++) {
                if (i<n-1 && k == p) continue;
                res = (res + dfs(i-1, t + score(game[k], s[i]), k)) % mod;
            }

            return res;
        };

        return dfs(n-1, n, 0);  
    }
};